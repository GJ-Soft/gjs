#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set($tagLib = "_" + ${package.replace('.','_').toUpperCase()} + "_" + ${shortName.toUpperCase()} + "_CONFIG_H")
${symbol_pound}ifndef ${tagLib}
${symbol_pound}define ${tagLib}

// Dependencias comunes
${symbol_pound}include <CppEntorno.h>

${symbol_pound}include <string>
${symbol_pound}include <vector>


#endif
