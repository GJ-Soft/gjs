#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $upperExension = $extension.toUpperCase())
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
${symbol_pound}${symbol_pound} ${upperExension} maven extension 

 Project ${capitalizedName}

${symbol_pound}${symbol_pound} Description

Project extension por Maven in java language.


${symbol_pound}${symbol_pound} Requirements

* Maven 3.9.x


${symbol_pound}${symbol_pound} Use

<packaging>${extension}</packaging>

<build>
	<extensions>
		<extension>
			<groupId>${infoGroupId}</groupId>
			<artifactId>${infoArtifactId}</artifactId>
			<version>${infoVersion}</version>
		</extension>
	</extensions>
</build>


${symbol_pound}${symbol_pound} Installation
    
    mvn clean install


${symbol_pound}${symbol_pound} Unit testing

    mvn clean test
    

${symbol_pound}${symbol_pound} Documentation

    mvn site
    

${symbol_pound}${symbol_pound} Deploy 

    mvn deploy

        
${symbol_pound}${symbol_pound} Execution

    
${symbol_pound}${symbol_pound} Security
    
    
${symbol_pound}${symbol_pound} Audit

    
${symbol_pound}${symbol_pound} To start

    

${symbol_pound}${symbol_pound} Avalaible users


${symbol_pound}${symbol_pound} Common mistakes


    
${symbol_pound}${symbol_pound} References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
