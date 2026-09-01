# Gjs C Exe Archetype

Project Archetype for a application in c language.


## Description

Archetype to generate the basic structure of a project in c++ language.


## Requirements

* Maven 3.9.x


    
## Generating a project from the archetype

    mvn archetype:generate \
		-DarchetypeGroupId=org.gjsoft.maven.archetypes \
		-DarchetypeArtifactId=gjs-cpp-lib-archetype \
		-DarchetypeVersion=1.0.0-RC.2 

    mvn archetype:generate \
		-DarchetypeGroupId=org.gjsoft.maven.archetypes \
		-DarchetypeArtifactId=gjs-cpp-lib-archetype \
		-DarchetypeVersion=1.0.0-RC.2 \
		-DshortName=test-project \ 
		-DgroupId=org.gjsoft.test  \
 		-DartifactId=test-project  \
		-Dpackage=org.gjs.test \
		-Dversion=1.0.0-SNAPSHOT \
		-Dlog=y \
		-Dparameters=1
   
	Archetype Parameters:

	* shortName: Name of the project. Always lowercase. Allows two words separated by a hyphen.

	* groupId: The group of the project artifact. 

	* artifactId: The name of the project artifact. Default is cpp-lib. Not required.

	* package: The project packaging of the sourc code. Default is org.gjs.maven.archetypes. Not required.

	* version: The project version. Default is 1.0.0-SNAPSHOT. Not required.	
	
	* log: Activates log4cxx. Values y/n. Default is y. Not required.

	* parameters: Number of parameters of the program. Default is 0. Not required. 
 
	
    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
