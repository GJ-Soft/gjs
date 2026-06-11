@echo off
cd gjs-parent
mvn clean install
cd ..
cd gjs-no-java-parent
mvn clean install
cd ..
cd gjs-java
cd gjs-java-base-parents
mvn clean install
cd ..
cd ..
cd gjs-maven
mvn clean install
cd ..
cd gjs-python
mvn clean install
cd ..
cd gjs-archetypes
cd gjs-python-exe-archetype
mvn clean install
cd ..
cd gjs-python-lib-archetype
mvn clean install
cd ..
cd gjs-python-rest-client-archetype
mvn clean install
cd ..
cd gjs-python-rest-server-archetype
mvn clean install
cd ..
cd ..
