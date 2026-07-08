package org.gjs.maven.extensions.profile;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

/**
 * Mini-lenguaje de expresiones para el fichero de configuracion de la extension.
 *
 * <p>Gramatica (precedencia de menor a mayor):</p>
 * <pre>
 *   expr     := ternary
 *   ternary  := or ('?' expr ':' expr)?
 *   or       := and ('||' and)*
 *   and      := equality ('&&' equality)*
 *   equality := unary (('==' | '!=' | '~') unary)*
 *   unary    := '!' unary | primary
 *   primary  := '(' expr ')' | STRING | reference
 * </pre>
 *
 * <ul>
 *   <li>{@code STRING}: literal entre comillas simples, p.ej. {@code 'windows'} (sin escapes).</li>
 *   <li>{@code reference}: identificador. Si empieza por {@code env.} es una variable de
 *       entorno; en otro caso es una propiedad existente. Lo resuelve el {@link Resolver}.</li>
 *   <li>{@code ~}: "contiene", insensible a mayusculas ({@code os.name ~ 'windows'}).</li>
 *   <li>Verdad/falsedad: solo {@code null} y {@code "false"} son falso; el resto es verdad.
 *       Una cadena vacia es verdad: refleja la semantica de Maven "variable definida"
 *       (p.ej. {@code env.CYGWIN} activo aunque la variable este vacia).</li>
 * </ul>
 */
final class PropertyExpression {

	/** Resuelve un identificador a su valor (String) o {@code null} si no existe. */
	interface Resolver {
		String resolve(String name);
	}

	private final Node root;

	private PropertyExpression(Node root) {
		this.root = root;
	}

	static PropertyExpression parse(String source) {
		List<Token> tokens = new Lexer(source).tokenize();
		Parser parser = new Parser(tokens);
		Node node = parser.parseExpression();
		parser.expectEnd();
		return new PropertyExpression(node);
	}

	String evaluate(Resolver resolver) {
		return root.eval(resolver);
	}

	static boolean truthy(String value) {
		return value != null && !value.equalsIgnoreCase("false");
	}

	// ---------------------------------------------------------------- AST

	private interface Node {
		String eval(Resolver resolver);
	}

	private static final class Literal implements Node {
		private final String value;

		Literal(String value) {
			this.value = value;
		}

		public String eval(Resolver resolver) {
			return value;
		}
	}

	private static final class Ref implements Node {
		private final String name;

		Ref(String name) {
			this.name = name;
		}

		public String eval(Resolver resolver) {
			return resolver.resolve(name);
		}
	}

	private static final class Not implements Node {
		private final Node child;

		Not(Node child) {
			this.child = child;
		}

		public String eval(Resolver resolver) {
			return truthy(child.eval(resolver)) ? "false" : "true";
		}
	}

	private static final class And implements Node {
		private final Node left;
		private final Node right;

		And(Node left, Node right) {
			this.left = left;
			this.right = right;
		}

		public String eval(Resolver resolver) {
			if (!truthy(left.eval(resolver))) {
				return "false";
			}
			return truthy(right.eval(resolver)) ? "true" : "false";
		}
	}

	private static final class Or implements Node {
		private final Node left;
		private final Node right;

		Or(Node left, Node right) {
			this.left = left;
			this.right = right;
		}

		public String eval(Resolver resolver) {
			if (truthy(left.eval(resolver))) {
				return "true";
			}
			return truthy(right.eval(resolver)) ? "true" : "false";
		}
	}

	private static final class Compare implements Node {

		enum Op {
			EQ, NE, CONTAINS
		}

		private final Node left;
		private final Node right;
		private final Op op;

		Compare(Node left, Node right, Op op) {
			this.left = left;
			this.right = right;
			this.op = op;
		}

		public String eval(Resolver resolver) {
			String a = left.eval(resolver);
			String b = right.eval(resolver);
			boolean result;
			switch (op) {
				case EQ:
					result = equal(a, b);
					break;
				case NE:
					result = !equal(a, b);
					break;
				case CONTAINS:
					result = contains(a, b);
					break;
				default:
					result = false;
			}
			return result ? "true" : "false";
		}

		private static boolean equal(String a, String b) {
			return (a == null) ? (b == null) : a.equals(b);
		}

		private static boolean contains(String a, String b) {
			if (a == null || b == null) {
				return false;
			}
			return a.toLowerCase(Locale.ROOT).contains(b.toLowerCase(Locale.ROOT));
		}
	}

	private static final class Ternary implements Node {
		private final Node condition;
		private final Node whenTrue;
		private final Node whenFalse;

		Ternary(Node condition, Node whenTrue, Node whenFalse) {
			this.condition = condition;
			this.whenTrue = whenTrue;
			this.whenFalse = whenFalse;
		}

		public String eval(Resolver resolver) {
			return truthy(condition.eval(resolver)) ? whenTrue.eval(resolver) : whenFalse.eval(resolver);
		}
	}

	// ---------------------------------------------------------------- Lexer

	private enum Type {
		STRING, IDENT, AND, OR, NOT, EQ, NE, CONTAINS, QUESTION, COLON, LPAREN, RPAREN, EOF
	}

	private static final class Token {
		final Type type;
		final String text;

		Token(Type type, String text) {
			this.type = type;
			this.text = text;
		}
	}

	private static final class Lexer {

		private final String source;
		private int i;

		Lexer(String source) {
			this.source = source;
		}

		List<Token> tokenize() {
			List<Token> tokens = new ArrayList<>();
			while (i < source.length()) {
				char c = source.charAt(i);
				if (Character.isWhitespace(c)) {
					i++;
					continue;
				}
				switch (c) {
					case '(':
						tokens.add(new Token(Type.LPAREN, "("));
						i++;
						break;
					case ')':
						tokens.add(new Token(Type.RPAREN, ")"));
						i++;
						break;
					case '?':
						tokens.add(new Token(Type.QUESTION, "?"));
						i++;
						break;
					case ':':
						tokens.add(new Token(Type.COLON, ":"));
						i++;
						break;
					case '~':
						tokens.add(new Token(Type.CONTAINS, "~"));
						i++;
						break;
					case '&':
						if (peek(1) == '&') {
							tokens.add(new Token(Type.AND, "&&"));
							i += 2;
						} else {
							throw error("se esperaba '&&' en la posicion " + i);
						}
						break;
					case '|':
						if (peek(1) == '|') {
							tokens.add(new Token(Type.OR, "||"));
							i += 2;
						} else {
							throw error("se esperaba '||' en la posicion " + i);
						}
						break;
					case '=':
						if (peek(1) == '=') {
							tokens.add(new Token(Type.EQ, "=="));
							i += 2;
						} else {
							throw error("se esperaba '==' en la posicion " + i);
						}
						break;
					case '!':
						if (peek(1) == '=') {
							tokens.add(new Token(Type.NE, "!="));
							i += 2;
						} else {
							tokens.add(new Token(Type.NOT, "!"));
							i++;
						}
						break;
					case '\'':
						tokens.add(readString());
						break;
					default:
						if (isIdentStart(c)) {
							tokens.add(readIdent());
						} else {
							throw error("caracter inesperado '" + c + "' en la posicion " + i);
						}
				}
			}
			tokens.add(new Token(Type.EOF, ""));
			return tokens;
		}

		private char peek(int offset) {
			int j = i + offset;
			return (j < source.length()) ? source.charAt(j) : '\0';
		}

		private Token readString() {
			i++; // comilla de apertura
			int start = i;
			while (i < source.length() && source.charAt(i) != '\'') {
				i++;
			}
			if (i >= source.length()) {
				throw error("literal de cadena sin cerrar");
			}
			String text = source.substring(start, i);
			i++; // comilla de cierre
			return new Token(Type.STRING, text);
		}

		private Token readIdent() {
			int start = i;
			while (i < source.length() && isIdentPart(source.charAt(i))) {
				i++;
			}
			return new Token(Type.IDENT, source.substring(start, i));
		}

		private static boolean isIdentStart(char c) {
			return Character.isLetter(c) || c == '_';
		}

		private static boolean isIdentPart(char c) {
			return Character.isLetterOrDigit(c) || c == '_' || c == '.' || c == '-';
		}

		private static IllegalArgumentException error(String message) {
			return new IllegalArgumentException(message);
		}
	}

	// ---------------------------------------------------------------- Parser

	private static final class Parser {

		private final List<Token> tokens;
		private int p;

		Parser(List<Token> tokens) {
			this.tokens = tokens;
		}

		Node parseExpression() {
			return parseTernary();
		}

		void expectEnd() {
			if (!check(Type.EOF)) {
				throw error("tokens sobrantes a partir de '" + peek().text + "'");
			}
		}

		private Node parseTernary() {
			Node condition = parseOr();
			if (match(Type.QUESTION)) {
				Node whenTrue = parseExpression();
				expect(Type.COLON);
				Node whenFalse = parseExpression();
				return new Ternary(condition, whenTrue, whenFalse);
			}
			return condition;
		}

		private Node parseOr() {
			Node left = parseAnd();
			while (match(Type.OR)) {
				left = new Or(left, parseAnd());
			}
			return left;
		}

		private Node parseAnd() {
			Node left = parseEquality();
			while (match(Type.AND)) {
				left = new And(left, parseEquality());
			}
			return left;
		}

		private Node parseEquality() {
			Node left = parseUnary();
			while (check(Type.EQ) || check(Type.NE) || check(Type.CONTAINS)) {
				Type t = next().type;
				Node right = parseUnary();
				Compare.Op op = (t == Type.EQ) ? Compare.Op.EQ
						: (t == Type.NE) ? Compare.Op.NE
						: Compare.Op.CONTAINS;
				left = new Compare(left, right, op);
			}
			return left;
		}

		private Node parseUnary() {
			if (match(Type.NOT)) {
				return new Not(parseUnary());
			}
			return parsePrimary();
		}

		private Node parsePrimary() {
			if (match(Type.LPAREN)) {
				Node inner = parseExpression();
				expect(Type.RPAREN);
				return inner;
			}
			if (check(Type.STRING)) {
				return new Literal(next().text);
			}
			if (check(Type.IDENT)) {
				return new Ref(next().text);
			}
			throw error("se esperaba un valor pero se encontro '" + peek().text + "'");
		}

		private Token peek() {
			return tokens.get(p);
		}

		private Token next() {
			return tokens.get(p++);
		}

		private boolean check(Type type) {
			return peek().type == type;
		}

		private boolean match(Type type) {
			if (check(type)) {
				p++;
				return true;
			}
			return false;
		}

		private Token expect(Type type) {
			if (!check(type)) {
				throw error("se esperaba " + type + " pero se encontro '" + peek().text + "'");
			}
			return next();
		}

		private static IllegalArgumentException error(String message) {
			return new IllegalArgumentException(message);
		}
	}
}
