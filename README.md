# Gjs project

Project Gjs


## General information


| Element  | Link                                    |
|----------|-----------------------------------------|
| Git      | https://github.com/GJ-Soft/gjs.git      |
| Wiki     | -                                       |
| Issues   | https://github.com/GJ-Soft/gjs/issues   |
| CI/CD    | https://github.com/GJ-Soft/gjs/actions  |
| Releases | -                                       |



## Description

Maven parent poms, Maven arquetypes, Maven plugins and basic support libraries for the arquetypes.

Supported Languages:
	
* C
* C++
* Java
* Python
* Typescript
	

## Requirements

* C			gnu2x
* C++		gnu++20
* Java 		21
* Maven 	3.9.x
* Python 	3.14.x


## Build

Everything is orchestrated with Maven from the repository root:

	mvn clean install

The root `pom.xml` aggregates every module. Three additional aggregators are
provided for partial builds. They are alternative module lists over the same
tree, selected with `-f`:

| Aggregator | Modules | Purpose |
|------------|---------|---------|
| `pomParents.xml` | Parent poms only. | Install the pom hierarchy without building any source module. |
| `pomMinInstall.xml` | The build extensions and plugins, plus the minimum needed to build `openpojo` and `nar-maven-plugin`. | First step of the bootstrap. |
| `pomRemainingInstall.xml` | Everything the previous one leaves out. | Second step, once those two projects are installed. |


### Bootstrap order

Two things have to exist in the local repository before the rest of the tree can
even be read:

* The **build extensions and plugins** of `gjs-maven` and `gjs-plugin`. Several
  parents declare them as build extensions, which Maven resolves during model
  building, before the reactor exists.
* **`nar-maven-plugin` and `openpojo`**, which live in their own repositories:
  the C/C++ parents build with the former, and `gjs-java-test-base-parent`
  manages the latter.

Hence the split:

1. `mvn -f pomMinInstall.xml clean install`
2. Build `openpojo` and `nar-maven-plugin`.
3. `mvn -f pomRemainingInstall.xml clean install`, or `mvn clean install` from
   the root: from this point on the full reactor builds in one go.

`pomMinInstall.xml` and `pomRemainingInstall.xml` cover exactly the same modules
as `pom.xml`, with no overlap.

Notes:

* Each aggregator has a counterpart at the lower levels (`gjs-java/pomMinInstall.xml`,
  `gjs-c/pomParents.xml`, ...). Their `<parent>` points to the alternative file, not
  to the directory, so each alternative tree is self-contained.
* Aggregator poms are never deployed (`maven.deploy.skip`). The three alternative
  ones are not installed either (`maven.install.skip`): they share coordinates with
  `pom.xml` and would overwrite it in the local repository.


### Optional profiles (C/C++)

| Profile | Effect | Requires |
|---------|--------|----------|
| `cppcheck` | Runs cppcheck over `src/main/<language>` and writes a browsable HTML report. | `cppcheck` and `cppcheck-htmlreport` in `${cpp.checkDir}`, and a Windows Python in `cpp.check.python`. |
| `cobertura` | Compiles with `--coverage` and runs gcovr after the tests. Work in progress. | gcovr under the Cygwin Python 3.9 (`tomli` included). |


## Roadmap


### Current version

- 1.0.0-RC.2


### Under Development

- C/C++  
- 

### Next version (1.0.0)

- ...
- ...

### Future versions


## License

GNU GENERAL PUBLIC LICENSE.


## Wiki index

      
* [Conventions](docs/conventions.md)
* [Development Environment Setup Guide](docs/environment.md)
* [Guía de Instalación y Configuración](docs/instalacion.md)
* [Arquitectura del Sistema y Módulos](docs/architecture.md)
* [Ciclo de Vida del Software y Despliegue](docs/ciclo-vida.md)
* [Actualización de versión](docs/actualizacion-version.md)

---
Para reportar fallos o proponer cambios en la documentación, por favor abre un Issue en este repositorio.

    
## References

* [Maven Build Lifecycle](https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html)
