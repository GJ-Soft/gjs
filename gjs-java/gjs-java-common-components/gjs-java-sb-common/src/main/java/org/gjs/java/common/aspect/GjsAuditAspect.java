package org.gjs.java.common.aspect;

import java.util.Date;
import java.util.Objects;

import org.apache.commons.lang3.BooleanUtils;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.AfterThrowing;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.gjs.java.common.annotation.GjsAudit;
import org.gjs.java.common.constant.CommonConstants;
import org.gjs.java.common.constant.CommonLiterals;
import org.gjs.java.common.dto.AuditDto;
import org.gjs.java.common.dto.AvisoDto;
import org.gjs.java.common.enums.AuditLogType;
import org.gjs.java.common.singleton.GlobalBundleManager;
import org.gjs.java.common.singleton.GlobalObjectsManager;
import org.springframework.stereotype.Component;

/**
 * The Class GjsAuditAspect.
 *
 * Componente de la librería Gjs
 *
 * Componente que implementa los aspectos que permiten auditar el tiempo que
 * tardan los métodps. Se aplica en general a todos los métodos de la capa de
 * servicios y fachadas, además de los que estén anotados con @GjsAudit.
 *
 * Nota: No hemos conseguido integrar la aplicación general a servicios y
 * fachadas (que se pretende se haga siempre) con el uso de la
 * anotación @GjsAudit, por ejemplo para poder variar el tiempo límite para
 * generar el aviso. Eso sería útil para facilitar las excepciones como métodos
 * especiales que realicen envíos de correo que no pueden tratarse como los
 * demñas ya que pueden llegar a tardar varios segundos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Aspect
@Component("gjsAuditAspect")
public class GjsAuditAspect extends BaseGjsAspect {

	/** The Constant POINTCUT_ANNOTATION. */
	public static final String POINTCUT_ANNOTATION = "@annotation(audit)";

	/** The Constant POINTCUT_ALL. */
	public static final String POINTCUT_ALL = "(execution(* ..*(..)))";

	/**
	 * Log before.
	 *
	 * Siempre se ejecuta en primer lugar al entrar en el método
	 *
	 * @param joinPoint the join point
	 */
	@Before(value = POINTCUT_ALL)
	public void logBefore(JoinPoint joinPoint) {
		doLogBefore(joinPoint);
	}

	/**
	 * Log before.
	 *
	 * Siempre se ejecuta en primer lugar al entrar en el método
	 *
	 * @param joinPoint the join point
	 * @param audit     the audit
	 */
	@Before(value = POINTCUT_ANNOTATION)
	public void logBefore(JoinPoint joinPoint, GjsAudit audit) {
		doLogBefore(joinPoint);
	}

	/**
	 * Log after.
	 *
	 * Siempre se ejecuta en último lugar al salir del método, después del
	 * AfterReturning o AfterThrowing
	 *
	 *
	 * @param joinPoint the join point
	 */
	@After(value = POINTCUT_ALL)
	public void logAfter(JoinPoint joinPoint) {
		doLogAfter(joinPoint);
	}

	/**
	 * Log after.
	 *
	 * Siempre se ejecuta en último lugar al salir del método, después del
	 * AfterReturning o AfterThrowing
	 *
	 * @param joinPoint the join point
	 * @param audit     the audit
	 */
	@After(value = POINTCUT_ANNOTATION)
	public void logAfter(JoinPoint joinPoint, GjsAudit audit) {
		doLogAfter(joinPoint);
	}

	/**
	 * Log after returning.
	 *
	 * Se ejecuta antes del After
	 *
	 * @param joinPoint the join point
	 * @param result    the result
	 */
	@AfterReturning(pointcut = POINTCUT_ALL, returning = "result")
	public void logAfterReturning(JoinPoint joinPoint, Object result) {
		doLogAfterReturning(joinPoint, result);
	}

	/**
	 * Log after returning.
	 *
	 * Se ejecuta antes del After
	 *
	 * @param joinPoint the join point
	 * @param audit     the audit
	 * @param result    the result
	 */
	@AfterReturning(pointcut = POINTCUT_ANNOTATION, returning = "result")
	public void logAfterReturning(JoinPoint joinPoint, GjsAudit audit, Object result) {
		doLogAfterReturning(joinPoint, result);
	}

	/**
	 * Log throw.
	 *
	 * Se ejecuta antes del After
	 *
	 * @param joinPoint the join point
	 * @param error     the error
	 */
	@AfterThrowing(pointcut = POINTCUT_ALL, throwing = "error")
	public void logThrow(JoinPoint joinPoint, Throwable error) {
		doLogThrow(joinPoint, error);
	}

	/**
	 * Log throw.
	 *
	 * Se ejecuta antes del After
	 *
	 * @param joinPoint the join point
	 * @param audit     the audit
	 * @param error     the error
	 */
	@AfterThrowing(pointcut = POINTCUT_ANNOTATION, throwing = "error")
	public void logThrow(JoinPoint joinPoint, GjsAudit audit, Throwable error) {
		doLogThrow(joinPoint, error);
	}

	@Override
	protected long criticalTime() {
		long res = 0;
		final Object objValue = GlobalObjectsManager.getInstance().load(CommonConstants.PARAM_AUDIT_CRITICAL_TIME);
		if (Objects.nonNull(objValue)) {
			res = (Integer) objValue;
		}
		return res;
	}

	@Override
	protected void whenTimeWarn(AuditDto auditDto) {
		final StringBuilder info = new StringBuilder(1024);
		info.append('[').append(auditDto.getModule()).append("][").append(auditDto.getPrimitive()).append("][")
				.append(AuditLogType.TIME_WARN.toString()).append("][Time=").append(auditDto.getTime()).append(" ms]");
		getLogger(auditDto).warn("{}", info);

		final Date hora = new Date();
		final String mensaje = GlobalBundleManager.getSafetyMessage(CommonLiterals.LIT_CRITICAL_TIME_WARNING);
		final String causa = GlobalBundleManager.getSafetyMessage(CommonLiterals.LIT_TIME_WARNING,
				auditDto.getPrimitive(), auditDto.getModule(), auditDto.getTime(), hora);

		AvisoDto avisoDto = new AvisoDto();
		avisoDto.setMensaje(mensaje);
		avisoDto.setCausa(causa);
		avisoDto.setFechaHora(hora);
		final String key = String.format("%s:%s:%s:%s", Thread.currentThread().getName(), auditDto.getModule(),
				auditDto.getPrimitive(), hora.getTime());
		GlobalObjectsManager.getInstance().save(key, avisoDto);
	}

	/**
	 * Do Log before.
	 *
	 * @param joinPoint the join point
	 */
	private void doLogBefore(JoinPoint joinPoint) {
		final boolean skip = !BooleanUtils
				.isTrue((Boolean) GlobalObjectsManager.getInstance().load(CommonConstants.PARAM_SKIP_AUDIT));
		// formatLog no es solo el texto: al empezar guarda la auditoria y al terminar
		// la cierra, asi que se llama siempre, este o no activa la depuracion.
		final String message = super.formatLog(joinPoint, AuditLogType.BEGIN, skip);
		getLogger(joinPoint).debug(message);
	}

	/**
	 * Do Log after.
	 *
	 * @param joinPoint the join point
	 */
	private void doLogAfter(JoinPoint joinPoint) {
		final boolean skip = !BooleanUtils
				.isTrue((Boolean) GlobalObjectsManager.getInstance().load(CommonConstants.PARAM_SKIP_AUDIT));
		// formatLog no es solo el texto: al empezar guarda la auditoria y al terminar
		// la cierra, asi que se llama siempre, este o no activa la depuracion.
		final String message = super.formatLog(joinPoint, AuditLogType.END, skip);
		getLogger(joinPoint).debug(message);
	}

	/**
	 * Do Log after returning.
	 *
	 * @param joinPoint the join point
	 * @param result    the result
	 */
	private void doLogAfterReturning(JoinPoint joinPoint, Object result) {
		final boolean skip = !BooleanUtils
				.isTrue((Boolean) GlobalObjectsManager.getInstance().load(CommonConstants.PARAM_SKIP_AUDIT));
		if (getLogger(joinPoint).isDebugEnabled()) {
			getLogger(joinPoint).debug(super.formatLog(joinPoint, AuditLogType.RETURNS, skip), result);
		}
	}

	/**
	 * Do Log throw.
	 *
	 * @param joinPoint the join point
	 * @param error     the error
	 */
	private void doLogThrow(JoinPoint joinPoint, Throwable error) {
		final boolean skip = !BooleanUtils
				.isTrue((Boolean) GlobalObjectsManager.getInstance().load(CommonConstants.PARAM_SKIP_AUDIT));
		final AuditDto auditDto = getAuditInfo(joinPoint);
		if (Objects.nonNull(auditDto)) {
			auditDto.setThrowed(error);
		}
		if (getLogger(joinPoint).isErrorEnabled()) {
			getLogger(joinPoint).error(error.toString());
		}
		if (getLogger(joinPoint).isDebugEnabled()) {
			getLogger(joinPoint).debug(super.formatLog(joinPoint, AuditLogType.THROWS, skip),
					error.getClass().getName(), error.getMessage());
		}
	}

}
