#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedPrefix = $prefix.substring(0,1).toUpperCase() + $prefix.substring(1))
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
${symbol_pound} ${capitalizedPrefix} ${capitalizedName} Archetype

Project Archetype in ${lan} language.


${symbol_pound}${symbol_pound} Description

Archetype to generate the basic structure of a project in ${lan} language.


${symbol_pound}${symbol_pound} Requirements

* Maven 3.9.x


    
${symbol_pound}${symbol_pound} Generating a project from the archetype

    mvn archetype:generate \
		-DarchetypeGroupId=${infoGroupId} \
		-DarchetypeArtifactId=${infoArtifactId} \
		-DarchetypeVersion=${infoVersion} 

    mvn archetype:generate \
		-DarchetypeGroupId=${infoGroupId} \
		-DarchetypeArtifactId=${infoArtifactId} \
		-DarchetypeVersion=${infoVersion} \
		-DshortName=test-project \ 
		-DprojectGroupId=org.gjsoft.test 
    
	Archetype Parameters:

	* shortName: Name of the project. Always lowercase. Allows two words separated by a hyphen.

	* projectGroupId: The group of the project artifact. 

	* projectArtifactId: The name of the project artifact. Default is ${shortName}. Not required.

	* package: The project packaging of the sourc code. Default is ${projectGroupId}. Not required.

	* projectVersion: The project version. Default is 1.0.0-SNAPSHOT. Not required.
	
	
    
${symbol_pound}${symbol_pound} References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
