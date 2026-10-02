## Gjs-python-common project


Project Gjs Python Common

## Description

Common components for projects in language python.


## Convenios


### Utilidades: módulo de funciones, no clase de estáticos

Las utilidades sin estado se escriben como **funciones de módulo**, sin
envolverlas en una clase y sin `@staticmethod`:

    # StringUtils.py
    def isEmpty( text: str | None ) -> bool:
        return not text or not text.strip()

En Python el módulo ya es un espacio de nombres, así que la clase sólo lo
duplicaría (`StringUtils.StringUtils`). `@staticmethod` fuera de una clase no
es un patrón: envuelve la función en un objeto `staticmethod`, que no es
invocable antes de Python 3.10 y no es una función para `inspect` ni para
`pickle`.

Se usa una **clase** cuando hay estado por instancia (`Properties`,
`ConfigurationFile`), polimorfismo (`ConfigurationFile` -> `Properties` /
`SettingsYaml`) o ciclo de vida. Regla corta: *si la segunda llamada necesita
recordar algo de la primera, es una clase; si no, es una función de módulo.*


### Importación

Los módulos de funciones se importan **como módulo**, nunca por sus nombres
sueltos; así el espacio de nombres se mantiene y los tests pueden sustituir la
función con `unittest.mock.patch`:

    from org.gjs.python.common import StringUtils      # correcto
    from org.gjs.python.common.StringUtils import isEmpty   # no

Las clases sí se importan por su nombre:

    from org.gjs.python.common.configuration.Properties import Properties


### DTO

Los DTO son dataclasses que heredan de `Dto`. Los que se identifican por un
número heredan de `IdentifiedDto`, y entonces se declaran con
`@dataclass( eq=False )`: un `@dataclass` a secas genera un `__eq__` campo a
campo que sustituye al de `IdentifiedDto`, el que compara por `id`, y además
deja el objeto sin hash.

    @dataclass( eq=False )
    class UserDto( IdentifiedDto ):
        name: str

    UserDto( "ana", id=3 )

El `id` se pasa sólo por nombre, para que las subclases puedan declarar campos
sin valor por defecto.


### Nombres

El guión bajo como separador de palabras se evita en todo el código propio.

* `PascalCase` para clases y para los ficheros.
* `camelCase` para funciones, métodos y propiedades.
* `camelCase` también en los tests: `testReturnsTrueWhenEnvSet`, no
  `test_returns_true_when_env_set`. Lo permite `python_functions = ["test*"]`
  en el `pyproject.toml`; las clases (`Test*`) y los ficheros (`*Test.py`) ya
  casaban sin guión.
* `MAYUSCULAS_CON_GUION` sólo para las constantes de módulo, igual que en los
  stacks C y Java (`HTTP_TRY_TIMEOUT`, `LOG_FORMAT`).

El guión bajo **sí** se mantiene donde lleva significado y no hay alternativa:

* Prefijo `_` de los miembros privados (`_load`, `_parser`, `_logConfigured`).
  Es el único marcador de privacidad que tiene Python: gobierna
  `from x import *` y hace que los linters no lo ofrezcan como API pública.
* Los métodos especiales del lenguaje (`__init__`, `__repr__`).
* Los nombres que imponen pytest o la biblioteca estándar (`tmp_path`,
  `status_code`, `read_text`).


### La versión sale del pom

`setup.py` declara `version='${project.version}'`. Maven lo resuelve al copiar
el fichero a `target/classes` —`copy-python-sources` filtra ese fichero y sólo
ese—, que es desde donde se ejecuta `pip install .`. El `setup.py` del módulo
conserva el token: ejecutarlo a mano desde la raíz aborta con un aviso, porque
ahí la versión no está resuelta.

El código no publica la versión: no hay `__version__`. Si hace falta en tiempo
de ejecución, `Project.getVersion()` la lee del pom (o de los metadatos de la
distribución, si está instalada como wheel y ya no hay pom).


### El árbol de fuentes no se toca al compilar

`src/` es de sólo lectura para la compilación: todo lo generado va a `target/`.
Maven copia las fuentes a `target/test-classes` y ejecuta pytest desde ahí, de
modo que el `__pycache__` de Python no aparece nunca junto al código. Al
ejecutar Python a mano, hacerlo contra `target/` — nunca apuntando a `src/`.


## Requirements

* Maven 3.9.x


## Configuration


      
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
