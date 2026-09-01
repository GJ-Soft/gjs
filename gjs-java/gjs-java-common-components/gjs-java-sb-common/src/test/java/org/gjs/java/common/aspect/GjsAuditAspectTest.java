package org.gjs.java.common.aspect;

import static org.junit.jupiter.api.Assertions.fail;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.Signature;
import org.gjs.java.common.annotation.GjsAudit;
import org.gjs.java.common.aspect.GjsAuditAspect;
import org.gjs.java.common.constant.CommonConstants;
import org.gjs.java.common.singleton.GlobalObjectsManager;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.samples.aspect.TargetAspectSample;
import org.junit.jupiter.api.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;

class GjsAuditAspectTest extends BaseUnitTest<GjsAuditAspect> {

	@InjectMocks
	private GjsAuditAspect gjsAuditAspect;

	@Mock
	private ProceedingJoinPoint proceedingJoinPoint;

	@Mock
	private GjsAudit audit;

	@Mock
	private Signature signature;

	@InjectMocks
	private GjsAuditAspect aspect;

	private TargetAspectSample targetAspectSample;

	@Override
	protected void initialize() throws Exception {
		targetAspectSample = new TargetAspectSample();
		GlobalObjectsManager.getInstance().save(CommonConstants.PARAM_SKIP_AUDIT, Boolean.valueOf(true));
		GlobalObjectsManager.getInstance().save(CommonConstants.PARAM_AUDIT_CRITICAL_TIME, Integer.valueOf(2000));
	}

	@Test
	void testLogBefore1() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logBefore(proceedingJoinPoint, audit);

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogBefore2() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logBefore(proceedingJoinPoint);

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogAfter1() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logAfter(proceedingJoinPoint, audit);

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogAfter2() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logAfter(proceedingJoinPoint);

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogAfterReturning1() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logAfterReturning(proceedingJoinPoint, audit, "Result test");

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogAfterReturning2() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logAfterReturning(proceedingJoinPoint, "Result test");

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogThrow1() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logThrow(proceedingJoinPoint, audit, new RuntimeException("Error test"));

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testLogThrow2() {
		try {
			final List<Object> listArgs = new ArrayList<>();
			final Object args[] = listArgs.toArray(new Object[listArgs.size()]);
			final String signatureName = "Run";
			Mockito.when(proceedingJoinPoint.getTarget()).thenReturn(targetAspectSample);
			Mockito.when(proceedingJoinPoint.getArgs()).thenReturn(args);
			Mockito.when(proceedingJoinPoint.getSignature()).thenReturn(signature);
			Mockito.when(signature.getName()).thenReturn(signatureName);

			aspect.logThrow(proceedingJoinPoint, new RuntimeException("Error test"));

		} catch (final Throwable e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

}
