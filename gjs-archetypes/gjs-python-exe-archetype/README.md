# GJS Python executable Archetype

Project Archetype in python language.


## Description

Archetype to generate the basic structure of a basic executable project in python language.


## Requirements

* Maven 3.9.x


    
## Generación de un proyecto a partir del arquetipo

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjs.maven.archetypes \
							-DarchetypeArtifactId=gjs-python-exe-archetype \
							-DarchetypeVersion=1.0.0-RC.2 

    mvn -B archetype:generate \
							-DarchetypeGroupId=org.gjs.maven.archetypes \
							-DarchetypeArtifactId=gjs-python-exe-archetype \
							-DarchetypeVersion=1.0.0-RC.2 \
							-DshortName=test \ 
							-DgroupId=org.gjs.test \
							-DmainFunction=Main:main \
							-Dauthor="GJ Software" \
							-DauthorMail=gjsoft@gmx.es 
    
  	Archetype Parameters:

	* shortName: Name of the project. Always lowercase. Allows two words separated by a hyphen.

	* groupId: The group of the project artifact. 

	* artifactId: The name of the project artifact. Default is java-module. Not required.

	* package: The project packaging of the source code. Default is org.gjs.maven.archetypes. Not required.

	* version: The project version. Default is 1.0.0-SNAPSHOT. Not required.

	* mainFunction: The main executable function. Default is Main:main. Not required.
                 
	* author: The author of the project. Not required.
	
	* authorMail: The e-mail of the author of the project. Not required.
 	
	
    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
