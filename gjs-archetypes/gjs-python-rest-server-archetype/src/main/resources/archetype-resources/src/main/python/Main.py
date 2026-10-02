#
# Program ${capitalizedName} Rest Server 
#
# Module Main.py
#

import sys
import platform
import site


# Forzar la inclusión de la ruta de usuario donde se instalan los paquetes
site.ENABLE_USER_SITE = True
user_site = site.getusersitepackages()
if user_site not in sys.path:
    sys.path.append(user_site)


from ${package}.server.${capitalizedName}Server import ${capitalizedName}Server
 
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
        
        server = ${capitalizedName}Server()
        server.start()
        
    except ImportError:
        print("\nNo se han encontrado las propiedades de la aplicación.")
        sys.exit(1)
    except ValueError as e:
        print(f"\nConfiguración de base de datos inválida: {e}")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nPrograma finalizado por el usuario.")
        sys.exit(0)

if __name__ == "__main__":
    main()