package org.gjs.java.test.tester;

import org.gjs.java.common.util.LogUtils;
import org.slf4j.Logger;

import com.openpojo.reflection.PojoClass;

/**
 * The Class BaseFieldTester.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta base para implementar tester customizados sobre atributos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class BaseFieldTester extends BaseTester {

	/** The tester name. */
	protected String testerName;

	/** The class name. */
	protected String className;

	/** The fields tested. */
	private int fieldsTested;

	/** The total fields. */
	private int totalFields;

	/**
	 * Instantiates a new base field tester.
	 *
	 * @param logger     the logger
	 * @param testerName the tester name
	 */
	protected BaseFieldTester(Logger logger, String testerName) {
		this.testerName = testerName;
		setLogger(logger);
	}

	/**
	 * Instantiates a new base field tester.
	 *
	 * @param logger      the logger
	 * @param testerName  the tester name
	 * @param stopOnError the stop on error
	 */
	protected BaseFieldTester(Logger logger, String testerName, boolean stopOnError) {
		super(stopOnError);
		this.testerName = testerName;
		setLogger(logger);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.tester.BaseTester#canRun(com.openpojo.reflection.PojoClass)
	 */

	@Override
	protected boolean canRun(PojoClass pojoClass) {
		return true;
	}

	/**
	 * Begin class.
	 *
	 * @param className   the class name
	 * @param totalFields the total fields
	 */
	protected void beginClass(String className, int totalFields) {
		final String _METHOD_ = LogUtils.getMethodName();
		this.className = className;
		this.fieldsTested = 0;
		this.totalFields = totalFields;
		logFormattedInfo(_METHOD_, "{} Tester for class {}", this.testerName, this.className);
	}

	/**
	 * Field processed.
	 */
	protected void fieldProcessed() {
		fieldsTested = fieldsTested + 1;
	}

	/**
	 * End class.
	 */
	protected void endClass() {
		final String _METHOD_ = LogUtils.getMethodName();
		logFormattedInfo(_METHOD_, "Class {}: fields tested{}/{}", className, fieldsTested, totalFields);
	}

}
