# Changelog


All major changes are referenced in this change log

[Added|Changed|Deprecated|Removed|Fixed|Security] 


## INITIAL VERSION

[Added] Core extension (AbstractMavenLifecycleParticipant) que en afterSessionStart
calcula propiedades y las fija como user properties antes de la activacion de
perfiles del reactor. Registro Plexus del participante en
META-INF/plexus/components.xml. Uso via .mvn/extensions.xml o $MAVEN_HOME/lib/ext.

[Added] Configuracion externa mediante fichero clave=expresion
($MAVEN_HOME/conf/property-bootstrap.properties o -Dproperty-bootstrap.config),
con mini-lenguaje de expresiones (PropertyExpression: ?: || && == != ~ ! ( ),
env.X y referencias a propiedades). Evaluacion en orden con referencias entre
lineas; respeta los -D del usuario. Si no hay fichero, regla por defecto
environment.style / cygwin.style. Ver property-bootstrap.properties.example.

[Added] Llamadas a funcion en el mini-lenguaje (PropertyExpression.Call, token
COMMA) y conversion de rutas Windows <-> Cygwin (PathStyle): path(x) convierte al
estilo de environment.style, cygpath(x) y winpath(x) fuerzan el destino. Todas
idempotentes. Permite normalizar en el arranque una propiedad como cygwinDir, que
el settings.xml define en formato Windows, al formato que toque en cada modo.

[Added] El Resolver busca tambien en los <properties> de los perfiles activos de
settings.xml (activeProfiles, -P y activeByDefault). Maven no los expone como
user/system properties en afterSessionStart: los aplica durante el model
building, asi que se leen de la MavenExecutionRequest. Valor crudo, sin
interpolar ${...}.

[Fixed] Documentacion: nombres heredados de profile-activator-maven-extension que
ya no coincidian con el codigo ni con el pom (fichero y propiedad de
configuracion, artifactId del bloque .mvn/extensions.xml, fichero de ejemplo).



