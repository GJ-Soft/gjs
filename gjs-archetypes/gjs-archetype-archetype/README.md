# Gjs archetype's archetype.

GJS archetype for archetypes.


## Descripción

Archetype to generate the structure of a archetype of project im any programming language.



## Requirements

* Maven 3.9.x


    
## Generating an archetype from the archetype

    mvn archetype:generate \
		-DarchetypeGroupId=org.gjsoft.maven.archetypes \
		-DarchetypeArtifactId=gjs-archetype-archetype \
		-DarchetypeVersion=1.0.0-RC.2 							    

    mvn archetype:generate \
		-DarchetypeGroupId=org.gjsoft.maven.archetypes \
		-DarchetypeArtifactId=gjs-archetype-archetype \
		-DarchetypeVersion=1.0.0-RC.2  \
		-Dprefix=gjs -DshortName=c-lib -Dlan=c -Dext=c -Dpackaging=nar \
		-DprojectParentGroupId=org.gjsoft \
		-DprojectParentArtifactId=gjs-parent \
		-DprojectParentVersion=1.0.0-SNAPSHOT 							    
    
	Archetype Parameters:

	* prefix: Prefix of the archetype's name. Always lowercase.

	* shortName: Name of the archetype. Always lowercase. Allows two words separated by a hyphen.

	* groupId: The group of the archetype artifact. Default is org.${prefix}.maven.archetypes. Not required.

	* artifactId: The name of the archetype artifact. Default is ${prefix}-${shortName}-archetype. Not required.

	* lan: The project's programming language. Enabled: c|c++|c#|java|python|php

	* ext: The programming language code file extensin. Default is ${lan}

	* packaging: The project's artifact packagind. Default is jar.

	* version: The archetype version. Default is 1.0.0-SNAPSHOT. Not required.           
	
 	* projectParentGroupId: The group of the parent pom of the generated project. 

	* projectParentArtifactId: The name of the parent pom of the generated project.

 	* projectParentVersion: The version of the parent pom of the generated project.           
	
	
    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
