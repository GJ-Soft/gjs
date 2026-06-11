#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
${symbol_pound}
${symbol_pound} Program ${capitalizedName}  
${symbol_pound}
${symbol_pound} Module Main.py
${symbol_pound}

import sys
import platform

def saludar():
    print("¡Hola! Este es un ejecutable Python (.pyz)")
    print(f"Sistema operativo: {platform.system()}")
    print(f"Versión de Python: {platform.python_version()}")
    
    if len(sys.argv) > 1:
        print(f"\nArgumentos recibidos: {sys.argv[1:]}")
    else:
        print("\nNo se pasaron argumentos adicionales.")

def main():
    try:
        saludar()
    except KeyboardInterrupt:
        print("\nPrograma finalizado por el usuario.")
        sys.exit(0)

if __name__ == "__main__":
    main()