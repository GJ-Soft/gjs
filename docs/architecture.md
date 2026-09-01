# System Architecture

This section describes the component structure of the project.


## Main Components


```text
GJS
├── gjs-parent
├── gjs-no-java-parent
├── gjs-java
├── gjs-maven
├── gjs-plugin
├── gjs-c
├── gjs-python
├── gjs-npm
└── gjs-arche${symbol_pound} ${capitalizedName} projects
```


## Module Structure

### gjs-parent

**Tipo:** Parent POM


#### Description

Common parent pom for all kind of projects and archetypes.
	

#### Maven Profiles:

	* win | linux           : It is automatically selected based on the operating system
	* cygwin                : It is activated if the operating system is Windows and the CYGWIN environment variable has been defined.
	* debug		            : It is activated if the DEBUG porperty has been defined
	* pom | source | plugin : It is automatically selected when the project has packaging pom, maven-plugin or not 
	* eclipse               : It is automatically selected when Maven is executed from Eclipse IDE

	
#### Special properties:
	
	* skip.if.not.source    :  true if packaging is pom, false otherwise
	
#### Environtment propeties:
	
	* CYGWIN: To activate cygwin profile instead the windows profile 
				```text
				export CYGWIN=1
				```
			  To deactivate cygwin profile 		
				```text
				export CYGWIN
				```
					
#### Needs properties in settings.xml file: 
		
	* cygwinDir : Directory of Cygwin installation. Windows style (C:\...), even when
	              building from Cygwin: the auxiliary tools are launched as Windows
	              processes and /cygdrive/... is not resolved.
	* systemUser : Username of the Cygwin / Unix home directory
					


#### Features


- Overall control of project construction.

	* Resource management
	* Plugin management
	

#### Dependencies

None.


#### Related Modules

```text
gjs-parent
   ├── gjs-no-java-parent
   ├── gjs-java-base-parents
   └── gjs-archetype-parent
```


---

### gjs-no-java-parent

**Tipo:** Parent POM

#### Description

Common parent pom for of projects in not java language.


#### Features

- Non-Java projects without a classpath need to have all resources copied for testing.
- Skip unnecesary plugins.

	
#### Dependencies


```text
gjs-parent
   └── gjs-no-java-parent
```
.

#### Related Modules

```text
gjs-no-java-parent
   ├── gjs-c-common-parent
   ├── gjs-npm-parent
   └── gjs-python-parent
```


---

### gjs-java

**Tipo:** Grouper POM

#### Description

Pom grouper for Java: parent poms and common components.


#### Parents poms

```text
gjs-java-base-parent
   ├── gjs-java-parent
   │        └── gjs-java-artifact-parent
   │                   └── gjs-java-web-parent
   │                              ├── gjs-java-war-parent
   │                              ├── gjs-java-springboot-parent
   │                              │           ├── gjs-java-sb-artifact-parent
   │                              │           └── gjs-java-sb-war-parent
   │                              └── gjs-java-sb-test-parent
   ├── gjs-java-maven-base-parent
   │        └── gjs-java-maven-parent
   └── gjs-java-test-base-parent
            └── gjs-java-test-parent
```

##### Maven Profiles:

	* java                  			         : It is automatically setted
	* attach-sources                	         : Generates sources jar
	* attach-javadoc	            	         : Generates javadoc jar
	* jdk-8 | jdk-11 | jdk-17 | jdk-21 | jdk-25  : Java version

	
					
##### Needs properties in settings.xml file: 
		
	* jdk25Dir : Directory of Java Jdk-25 installation
	* jdk21Dir : Directory of Java Jdk-21 installation
	* jdk17Dir : Directory of Java Jdk-17installation
	* jdk11Dir : Directory of Java Jdk-11 installation
	* jdk8Dir  : Directory of Java Jdk-8 installation
					
					
##### Maven special quality, format and documentation commands:

 	* mvn checkstyle:check 
	* mvn javadoc:javadoc		Generate javadoc site
	* mvn javadoc:jar   		Generate javadoc jar (o el perfil attach-javadoc)
	* mvn formatter:format	-Dformatter.file=file-eclipse-likely.xml
	* mvn fmt:format -Dcode.line.max.length=100	
	* mvn spotless:apply   		Apply changes (organize imports)
	* mvn spotless:check   		Just check
	* mvn pmd:check
	* mvn spotbugs:spotbugs
	* mvn spotbugs:check		



##### Features

- General dependency management for java projects. 
- Common dependency and plugin declaration.
	
	
##### Dependencies

```text
gjs-parent
   └── gjs-java-base-parent
```


##### Related Modules

None.


#### Components


| Módulo                         | Description                                  |
|--------------------------------|----------------------------------------------|
| gjs-java-common-test-base      |                                              |
| gjs-java-common-base           |                                              |
| gjs-java-common-support        |                                              |
| gjs-java-common-test-support   |                                              |
| gjs-java-common-io             |                                              |
| gjs-java-common                |                                              |
| gjs-java-common-test-mocks     |                                              |
| gjs-java-common-test           |                                              |
| gjs-java-sb-common-test-support|                                              |
| gjs-java-sb-common             |                                              |
| gjs-java-sb-common-test-mocks  |                                              |
| gjs-java-sb-common-test        |                                              |



##### Features




---

### gjs-maven

**Tipo:** Grouper POM

#### Description

Pom grouper for Maven extensions to handle alternative packaging.

#### Components

| Module              | Packaging |
|---------------------|-----------|
| tgz-maven-extension |    tgz    |
| pyz-maven-extension |    pyz    |
| gz-maven-extension  |    gz     |
| whl-maven-extension |    whl    |


* tgz-maven-extension : Defines packaging tgz

	Languages: typescript
	
	```xml
		<extension>
			<groupId>org.gjsoft.maven.extensions</groupId>
			<artifactId>tgz-maven-extension</artifactId>
			<version>${tgz-maven-extension.version}</version>
		</extension>
	```

* pyz-maven-extension : Defines packaging pyz
	
	Languages: python

	```xml
		<extension>
			<groupId>org.gjsoft.maven.extensions</groupId>
			<artifactId>pyz-maven-extension</artifactId>
			<version>${pyz-maven-extension.version}</version>
		</extension>
	```

* gz-maven-extension  : Defines packaging gz

	Languages: -

	```xml
		<extension>
			<groupId>org.gjsoft.maven.extensions</groupId>
			<artifactId>gz-maven-extension</artifactId>
			<version>${gz-maven-extension.version}</version>
		</extension>
	```

* whl-maven-extension : Defines packaging whl

	Languages: python

	```xml
		<extension>
			<groupId>org.gjsoft.maven.extensions</groupId>
			<artifactId>whl-maven-extension</artifactId>
			<version>${whl-maven-extension.version}</version>
		</extension>
	```

---

### gjs-plugin

**Tipo:** Grouper POM

#### Description

Pom grouper for Maven plugins.

#### Components

| Module              | Language               |
|---------------------|------------------------|
| tgz-maven-plugin    | Typescript packaging   |
| pyz-maven-plugin    | Python executables     |


* tgz-maven-plugin : Manage projects with tgz packaging

	Languages: typescript
	
	```xml
		<plugin>
			<groupId>org.gjsoft.maven.plugins</groupId>
			<artifactId>tgz-maven-plugin</artifactId>
			<version>${tgz-maven-plugin.version}</version>
		</plugin>
	```

* pyz-maven-plugin : Manage projects with pyz packaging

	Languages: python
	
	```xml
		<plugin>
			<groupId>org.gjsoft.maven.plugins</groupId>
			<artifactId>pyz-maven-plugin</artifactId>
			<version>${pyz-maven-plugin.version}</version>
		</plugin>
	```


---

### gjs-c

**Tipo:** Grouper POM


#### Description

Pom grouper for C/C++: parent poms and common components.


#### Parents poms

```text
gjs-c-common-parent
   └── gjs-c-nar-extension-parent
            └── gjs-c-nar-parent
                       ├── gjs-c-parent
                       │          ├── gjs-c-lib-parent
                       │          ├── gjs-c-stlib-parent
                       │          └── gjs-c-exe-parent
                       └── gjs-cpp-parent
                                  ├── gjs-cpp-lib-parent
                                  ├── gjs-cpp-stlib-parent
                                  └── gjs-cpp-exe-parent
```

##### Maven Profiles:

	* cpp                			         	: It is automatically setted
	
					
##### Needs properties in settings.xml file: 
		
	* cygwinDir : Directory of Cygwin installation (from gjs-parent)
	* systemUser : Username for Cygwin, or Linux/Unix system
	* oraDir : Directory of Oracle client installation
					
					

##### Features

- Common directories for special includes and libraries definition.
- Skip for default plugins that have no application in C/C++ projects.
- The adaptation of the Maven lifecycle phases is performed by the maven-nar-plugin.
	
	
##### Dependencies

```text
gjs-parent
   └── gjs-no-java-parent
            └── gjs-c-common-parent
```


##### Related Modules

None.


#### Components


| Módulo                         | Language |  Description                                  |
|--------------------------------|----------------------------------------------|
| gjs-c-common-base              |  C       |                                    |
| gjs-c-common-types             |  C       |                                    |
| gjs-c-common-text              |  C       |                                    |
| gjs-c-common-calculation       |  C       |                                    |
| gjs-c-common-codes             |  C       |                                    |
| gjs-c-common-time              |  C       |                                    |
| gjs-c-common-complex-types     |  C       |                                    |
| gjs-c-common-io                |  C       |                                    |
| gjs-c-common-system            |  C       |                                    |
| gjs-c-common-suppor            |  C       |                                    |
| gjs-c-common-log               |  C       |                                    |
| gjs-c-common-test              |  C       |                                    |
| gjs-cpp-common-base            |  C++     |                                    |
| gjs-cpp-common-types           |  C++     |                                    |
| gjs-cpp-common-time            |  C++     |                                    |
| gjs-cpp-common-log             |  C++     |                                    |
| gjs-cpp-common-io              |  C++     |                                    |
| gjs-cpp-common-system          |  C++     |                                    |
| gjs-cpp-common-support         |  C++     |                                    |
| gjs-cpp-common-database        |  C++     |                                    |
| gjs-cpp-common                 |  C++     |                                    |
| gjs-cpp-common-test            |  C++     |                                    |
| gjs-cpp-common-test-mocks      |  C++     |                                    |


##### Features



---

### gjs-python

**Tipo:** Grouper POM


#### Description

Pom grouper for Python: parent poms and common components


#### Parents poms

```text
gjs-python-parent
   ├── gjs-python-lib-base-parent
   │       └── gjs-python-lib-parent
   └── gjs-python-exe-parent
           └── gjs-python-rest-parent
```

##### Maven Profiles:

	* python        : It is automatically setted
	* upgrade       : Provides previous installation and upgrade of python libraries & tools
		
		```text
		mvn clean install -Pupgrade
		```
	
					

##### Features

- Adaptation of the Maven lifecycle phases using maven-exec-plugin.
- Skip for default plugins that have no application in python projects.
	
	
##### Dependencies

```text
gjs-parent
   └── gjs-no-java-parent
            └── gjs-python-parent
```


##### Related Modules

None.


#### Components


| Módulo                         | Description                                  |
|--------------------------------|----------------------------------------------|
| gjs-python-common              |                                              |


##### Features

- Resources and properties files managing



---

### gjs-npm

**Tipo:** Grouper POM


#### Description

Pom grouper for Npm: parent poms and common components.

#### Parents poms

```text
gjs-npm-parent
   ├── gjs-npm-typescript-parentt
   └── gjs-npm-front-parent
```

##### Maven Profiles:

	* npm    			     	: It is automatically setted
	* angular | react | vue		: Front language implementation 
					
				

##### Features

- Adaptation of the Maven lifecycle phases using maven-exec-plugin.
- Skip for default plugins that have no application in npm projects.
	
	
	
##### Dependencies

```text
gjs-parent
   └── gjs-no-java-parent
            └── gjs-npm-parent
```


##### Related Modules

None.


#### Components


| Módulo                         |  Description                                  |
|--------------------------------|-----------------------------------------------|


##### Features




---

### gjs-archetype projects

**Tipo:** Grouper POM


#### Description

Description.

#### Archetypes availables

| Archetype                             | Language  | Description                            |
|---------------------------------------|----------------------------------------------------|
| gjs-archetype-archetype               |           |                                        |
| gjs-java-artifact-archetype           | java      |                                        |
| gjs-java-exe-archetype                | java      |                                        |
| gjs-java-lib-archetype                | java      |                                        |
| gjs-maven-plugin-archetype            | java      |                                        |
| gjs-maven-extension-archetype         | java      |                                        |
| gjs-c-lib-archetype                   | C         |                                        |
| gjs-c-stlib-archetype                 | C         |                                        |
| gjs-c-exe-archetype                   | C         |                                        |
| gjs-cpp-lib-archetype                 | C++       |                                        |
| gjs-cpp-stlib-archetype               | C++       |                                        |
| gjs-cpp-exe-archetype                 | C++       |                                        |
| gjs-python-lib-archetype              | python    |                                        |
| gjs-python-exe-archetype              | python    |                                        |
| gjs-python-rest-server-archetype      | python    |                                        |
| gjs-python-rest-client-archetype      | python    |                                        |
| gjs-typescript-lib-archetype          | typescript|                                        |


#### Example of project generation:

  Example of use: This command generates the gjs-c-lib-archetype project:    

	```bash
     
    mvn archetype:generate \
		-DarchetypeGroupId=org.gjsoft.maven.archetypes \
		-DarchetypeArtifactId=gjs-archetype-archetype \
		-DarchetypeVersion=1.0.0-RC.2  \
		-Dprefix=gjs -DshortName=c-lib -Dlan=c -Dext=c -Dpackaging=nar \
		-DprojectParentGroupId=org.gjsoft \
		-DprojectParentArtifactId=gjs-parent \
		-DprojectParentVersion=1.0.0-SNAPSHOT 							    
    ```
  
### Common Archetype Parameters:

	* prefix: Prefix of the archetype's name. Always lowercase.
	* shortName: Name of the archetype. Always lowercase. Allows two words separated by a hyphen.
	* groupId: The group of the archetype artifact. Default is org.${prefix}.maven.archetypes. Not required.
	* artifactId: The name of the archetype artifact. Default is ${prefix}-${shortName}-archetype. Not required.
	* lan: The project's programming language. Enabled: c|c++|c#|java|python|php
	* ext: The programming language code file extensin. Default is ${lan}
	* packaging: The project's artifact packagind. Default is jar.
	* version: The archetype version. Default is 1.0.0-SNAPSHOT. Not required.           
 	* projectParentGroupId: The group of the parent pom of the generated projects. 
	* projectParentArtifactId: The name of the parent pom of the generated projects.
 	* projectParentVersion: The version of the parent pom of the generated projects.           
                   
---

## Relaciones entre módulos

```text
gjs-parent
│
├── gjs-java
├── gjs-python
├── gjs-c
├── gjs-npm
│
├── gjs-maven
├── gjs-plugin
└── gjs-arche${symbol_pound} ${capitalizedName} projects
```


## Related Links

* [Return to Main Index](../README.md)
* [Go to Installation Guide](instalacion.md)