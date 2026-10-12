# GJS Maven Extension Archetype

Project Archetype for maven plugins.


## Description

Archetype to generate the basic structure of a maven extension.


## Requirements

* Maven 3.9.x


    
## Generación de un proyecto a partir del arquetipo

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjsoft.maven.archetypes \
							-DarchetypeArtifactId=gjs-maven-extension-archetype \
							-DarchetypeVersion=1.0.0 

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjsoft.maven.archetypes \
							-DarchetypeArtifactId=gjs-maven-extension-archetype \
							-DarchetypeVersion=1.0.0 \
							-DshortName=test 
    
	Archetype Parameters:

	* shortName: Name of the project. Always lowercase. Allows two words separated by a hyphen.

	* groupId: The group of the project artifact. 

	* artifactId: The name of the project artifact. Default is extension. Not required.

	* package: The project packaging of the sourc code. Default is org.gjs.maven.archetypes. Not required.

	* version: The project version. Default is 1.0.0-SNAPSHOT. Not required.
	
	
    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
