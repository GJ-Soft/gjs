# Changelog


All major changes are referenced in this change log

[Added|Changed|Deprecated|Removed|Fixed|Security] 


## INITIAL VERSION

[Added] Core extension (AbstractMavenLifecycleParticipant) que en afterSessionStart
calcula propiedades y las fija como user properties antes de la activacion de
perfiles del reactor. Registro Plexus del participante en
META-INF/plexus/components.xml. Uso via .mvn/extensions.xml o $MAVEN_HOME/lib/ext.

[Added] Configuracion externa mediante fichero clave=expresion
($MAVEN_HOME/conf/profile-activator.properties o -Dprofile-activator.config),
con mini-lenguaje de expresiones (PropertyExpression: ?: || && == != ~ ! ( ),
env.X y referencias a propiedades). Evaluacion en orden con referencias entre
lineas; respeta los -D del usuario. Si no hay fichero, regla por defecto
environment.style / cygwin.style. Ver profile-activator.properties.example.



