#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
${symbol_pound} ${capitalizedName} project

Project ${shortName}

${symbol_pound}${symbol_pound} Description

Project cpp-lib in c++ language.


${symbol_pound}${symbol_pound} Requirements

* Maven 3.9.x


${symbol_pound}${symbol_pound} Configuration


      
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
