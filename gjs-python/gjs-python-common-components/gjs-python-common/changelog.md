# Changelog


All major changes are referenced in this change log

[Added|Changed|Deprecated|Removed|Fixed|Security]


## 1.0.0-RC.2

### Added

* `dto`: `Dto`, la raíz de los DTO, e `IdentifiedDto`, el DTO identificado por
  un entero positivo. La igualdad, el orden y el hash los da el `id`, y sólo
  entre objetos de la misma clase; sin `id` (un objeto aún no guardado) sólo es
  igual a sí mismo y se ordena delante. El `id` se pasa sólo por nombre, y las
  subclases se declaran con `@dataclass( eq=False )`.
* `exceptions`: `ApplicationException`, con código de error y causa opcionales
  (la causa queda también en `__cause__`), y `ExceptionUtils.formatMessage()`,
  que compone `[código] mensaje: causa`.
* `configuration.PropertiesUtils.read()`: lee un `.properties` a un `dict`, y
  lanza `ApplicationException` si no puede leerlo o el formato no es válido.

### Changed

* El paquete `properties` pasa a `configuration`: `Properties`,
  `ApplicationProperties` y `getApplicationProperties()` se importan ahora de
  `org.gjs.python.common.configuration`. Los tests se mueven con ellos.
* `Properties` lee el fichero con `PropertiesUtils.read()`, así que un fichero
  con formato incorrecto lanza `ApplicationException` al cargarlo.

* Las utilidades sin estado pasan a ser **módulos de funciones** en vez de clases
  con métodos estáticos: `StringUtils`, `ValueUtils`, `YamlUtils`, `HttpResponse`,
  `Http`, `Zip`, `Log`, `Application`, `Project` y `Resources`.
  Se retiran los `@staticmethod` sueltos a nivel de módulo, que no son un patrón
  de Python (envuelven la función en un objeto `staticmethod`, no invocable
  antes de 3.10).
* Convenio de nombres unificado: `camelCase` para funciones, métodos y
  propiedades; `PascalCase` para clases y ficheros. El guión bajo como
  separador de palabras se elimina de todo el código propio, tests incluidos:
  `python_functions` pasa a `["test*"]` en el `pyproject.toml` y los 157
  métodos de test adoptan `camelCase`. Se conserva sólo donde lleva
  significado: prefijo de privado, métodos especiales del lenguaje,
  constantes de módulo y nombres impuestos por pytest o la estándar.
* Convenio de importación: se importa el **módulo**, no los nombres sueltos
  (`from org.gjs.python.common import StringUtils`).
* `ApplicationProperties` ya no crea la instancia al importar el módulo; se
  obtiene con `getApplicationProperties()`, perezosa y cacheada.
* `ApplicationProperties.appCacheEnabled` y `dbEcho` devuelven `bool`, y
  `appPort` devuelve `int`, en vez de `str`.
* `Properties` añade `getBool()` y `getInt()`.
* `Http.exists()` usa `HEAD` y acepta cualquier código que no sea de error, en
  vez de descartar sólo el 404.
* `python_requires` sube a 3.10: el código usa `str | None` y `list[...]`.
* La versión deja de estar escrita a mano. El `pom.xml` es la única fuente:
  `setup.py` declara `version='${project.version}'` y Maven lo resuelve al
  copiarlo a `target/classes`, que es desde donde se ejecuta `pip install .`.
  Para ello `copy-python-sources` (en `gjs-python-parent`) pasa a tener dos
  bloques `<resource>`: uno sólo para `setup.py`, con `<filtering>true</filtering>`,
  y otro sin filtrar para `src/**` y `pyproject.toml`, que no deben tocarse.
  El `setup.py` del módulo conserva el token a propósito y aborta con un
  mensaje propio si se ejecuta sin filtrar. La cadena entregada a setuptools es
  la misma que antes, así que el nombre del wheel no cambia.
* `org.gjs.python.common.__version__` desaparece: la versión la publica el
  empaquetado, no el código.
* `Project` gana `getVersion()`, que localiza el `pom.xml` subiendo directorios
  y aplica la herencia de Maven (la versión propia si existe y, si no, la del
  `<parent>`, que es el caso de este módulo); si no hay pom alcanzable recurre a
  los metadatos de la distribución instalada. No lo usa hoy `setup.py`, que va
  por filtrado, pero queda disponible para quien necesite la versión en tiempo
  de ejecución.

### Fixed

* `Properties`: un `%` en un valor (una contraseña codificada en una URL)
  lanzaba `InterpolationSyntaxError`; ahora es un carácter más.
* Los `__init__.py` de `application`, `configuration`, `http`, `log`, `settings`
  y `zip` eran copia del de `properties` y hacían fallar el import del paquete.
* `Object.__repr__` usaba `__name__` (el nombre del módulo) en lugar del nombre
  de la clase.
* `ConfigurationFile` usaba `@abstractmethod` sin importarlo, y el mensaje de
  `FileNotFoundError` mostraba `None` en vez del fichero pedido.
* `YamlUtils.load()` pasaba el `Path` a `yaml.safe_load()` en vez del contenido.
* `Log`: sintaxis Java (`bool x = false`), anotaciones `int | logging.INFO` en
  lugar de valores por defecto, `global` ausente en el indicador de
  configuración, el formateador se perdía al añadir el handler, `directory` no
  se usaba, y la comparación `suffix in ["yml","yaml"]` nunca acertaba porque
  `Path.suffix` incluye el punto.
* `Http`: sintaxis Java en las constantes, `except` mal indentados, `import
  request`, `max_attemps` sin declarar en `download()`, falta de `timeout` en
  las peticiones y comprobación invertida del fichero destino.
* `Zip`: `extractall()` ignoraba el directorio destino, `logger` no existía y se
  usaba una variable inexistente. Se rechazan las entradas que apuntan fuera del
  destino (zip slip).
* `Application`: operador `!`, `global` ausente, imports relativos incorrectos y
  `logger` inexistente.
* `SettingsYaml`: nombre de módulo mal escrito en dos imports, funciones
  llamadas por un nombre que no existía, `_load` sobre una variable inexistente
  y el modelo generado se descartaba.
* `StringUtils.length()` estaba anotada `-> str`, y `reverseTruncate()` devolvía
  la cadena vacía cuando el tamaño era 0.
* `requirements.txt` pedía `request` (por `requests`) y `zipfile`, que es de la
  biblioteca estándar.
