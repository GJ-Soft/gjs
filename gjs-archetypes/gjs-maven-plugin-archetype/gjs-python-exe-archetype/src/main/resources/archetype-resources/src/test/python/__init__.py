#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
#set( $pythonVersion = $version.replace("SNAPSHOT", "DEV"))
${symbol_pound} Test suite
${symbol_pound}
${symbol_pound} Program ${capitalizedName} 
${symbol_pound}

__version__ = "${pythonVersion}"






