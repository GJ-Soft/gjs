# Conventions

## Versioning

GJS uses a semantic versioning variant based on the following format:

```
MAJOR.MINOR.PATCH[-QUALIFIER]
```

### Stable Releases

Stable releases follow the format:

```
1.0.0
1.1.0
1.1.1
2.0.0
```

### Release Candidate Releases

Release candidate releases may be published before a stable release:

```
1.0.0-RC.2
1.0.0-RC.2
1.0.0-RC.3
```

These releases are considered functionally complete and are intended for final testing and validation.

### Development Releases

The version under active development of the project uses the suffix:

```
1.0.0-SNAPSHOT
1.1.0-SNAPSHOT
2.0.0-SNAPSHOT
```

A SNAPSHOT version represents a temporary state of the source code and may change between builds.


#### Release Cycle

Typical Example:

```
1.0.0-SNAPSHOT

↓
1.0.0-RC.2

↓
1.0.0-RC.2

↓
1.0.0

↓
1.0.1-SNAPSHOT
```

### Compatibility

- PATCH versions are fully compatible within the same MINOR version.

- MINOR versions maintain backward compatibility unless explicitly stated otherwise.

- MAJOR versions may introduce incompatible changes.



## Publication

- Maven Repository
- PyPI
- NPM


## Related Links

* [Return to Main Index](../README.md)
