@echo off
cd gjs-parent
mvn clean install
cd ..
cd gjs-java
mvn clean install
cd ..
cd gjs-plugin
mvn clean install
cd ..
