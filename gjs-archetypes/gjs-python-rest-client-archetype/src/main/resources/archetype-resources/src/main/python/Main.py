#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
${symbol_pound}
${symbol_pound} Program ${capitalizedName} Rest Client 
${symbol_pound}
${symbol_pound} Module Main.py
${symbol_pound}

import sys
import platform

from ${package}.client.${capitalizedName}Client import ${capitalizedName}Client

def inicializar( applicationProperties ):
    print(f"Se inicia el ejecutable {applicationProperties.appName}-{applicationProperties.appVersion} ")
    print(f"Sistema operativo: {platform.system()}")
    print(f"Versión de Python: {platform.python_version()}")
        
    if len(sys.argv) > 1:
        print(f"\nArgumentos recibidos: {sys.argv[1:]}")
    else:
        print("\nNo se pasaron argumentos adicionales.")

def main():
    try:
        from org.gjs.python.common.configuration import getApplicationProperties

        inicializar( getApplicationProperties() )
        
        client = ${capitalizedName}Client()

        resultado = client.getServerStatus()
        print(f"Respuesta recibida: {resultado}")
        
    except ImportError:
        print("\nNo se han encontrado las propiedades de la aplicación.")
        sys.exit(1)
    except ValueError as e:
        print(f"\nConfiguración de base de datos inválida: {e}")
        sys.exit(1)
    except Exception as e:
        print(f"Error en la llamada: {e}")
        
        
if __name__ == "__main__":
    main()