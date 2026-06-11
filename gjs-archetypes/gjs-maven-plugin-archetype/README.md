# GJS Maven Plugin Archetype

Project Archetype for maven plugins.


## Description

Archetype to generate the basic structure of a maven plugin.


## Requirements

* Maven 3.9.x


    
## Generación de un proyecto a partir del arquetipo

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjs.maven.archetypes \
							-DarchetypeArtifactId=gjs-maven-plugin-archetype \
							-DarchetypeVersion=1.0.0-RC.1 

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjs.maven.archetypes \
							-DarchetypeArtifactId=gjs-maven-plugin-archetype \
							-DarchetypeVersion=1.0.0-RC.1 \
							-DshortName=test -Drule=test -Dphase=test
    
	Archetype Parameters:

	* shortName: Name of the project. Always lowercase. Allows two words separated by a hyphen.

	* rule: Name of the sample rule. Always lowercase. Allows two words separated by a hyphen.

	* phase: Phase of the Maven LifeCycle. Always lowercase. Allows two words separated by a hyphen. By default is none. Not required.
			Posible values: 
				validate|initialize|generate-sources|process-sources|
				generate-resources|process-resources|compile|process-classes|
				generate-test-sources|process-test-sources|generate-test-resources|
				process-test-resources|test-compile|process-test-classes|test|
				prepare-package|package|pre-integration-test|integration-test|
				post-integration-test|verify|install|deploy|pre-clean|clean|
				post-clean|pre-site|site|post-site|site-deploy|none

	* groupId: The group of the project artifact. 

	* artifactId: The name of the project artifact. Default is plugin. Not required.

	* package: The project packaging of the sourc code. Default is org.gjs.maven.archetypes. Not required.

	* version: The project version. Default is 1.0.0-SNAPSHOT. Not required.
	
	
    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
