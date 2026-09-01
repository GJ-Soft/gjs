## PYZ maven plugin 

 Project PYZ Maven Plugin 
 
## Description

Project plugin in java language.

Define the pyz packaging for maven projects 


## Requirements

* Maven 3.9.x


## Pom plugin definition:

	<plugin>
		<groupId>org.gjsoft.maven</groupId>
		<artifactId>pyz-maven-plugin</artifactId>
		<version>1.0.0-RC.2</version>
	</plugin>


## Use

<packaging>pyz</packaging>

<build>
	<extensions>
		<extension>
			<groupId>org.gjsoft.maven</groupId>
			<artifactId>pyz-maven-plugin</artifactId>
			<version>1.0.0-RC.2</version>
		</extension>
	</extensions>
</build>

	

## Configuration

    <plugin>
		<groupId>org.gjsoft.maven</groupId>
		<artifactId>pyz-maven-plugin</artifactId>
		<version>1.0.0-RC.2</version>

		<configuration>
			<baseDirectory>${project.basedir}/dist</baseDirectory>
			<outputDirectory>${project.build.directory}</outputDirectory>
			<finalName>mi-app</finalName>
			<includeBaseDirectory>true</includeBaseDirectory>
		</configuration>
    </plugin>

      
## Installation
    
    mvn clean install


## Unit testing

    mvn clean test
    

## Documentation

    mvn site
    

## Deploy 

    mvn deploy

        
## Execution

    
## Security
    
    
## Audit

    
## To start

    

## Avalaible users


## Common mistakes


    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
