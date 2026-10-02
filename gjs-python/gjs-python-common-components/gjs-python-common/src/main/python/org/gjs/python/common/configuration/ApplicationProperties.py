# ApplicationProperties.py
"""Propiedades de la aplicación."""

from functools import lru_cache

from org.gjs.python.common.configuration.Properties import Properties


class ApplicationProperties( Properties ):
    """Acceso tipado a las propiedades de la aplicación."""

    def __init__( self ) -> None:
        super().__init__( "application.properties" )

    # Propiedades de aplicación
    @property
    def appName( self ) -> str:
        return self.get( "app.name", "app" )

    @property
    def appVersion( self ) -> str:
        return self.get( "app.version", "0.0.0" )

    @property
    def appCacheEnabled( self ) -> bool:
        return self.getBool( "app.cache.enabled", False )

    @property
    def appCacheDirectory( self ) -> str:
        return self.get( "app.cache.directory", "" )

    # Propiedades de base de datos
    @property
    def dbUrl( self ) -> str:
        return self.get( "db.url" )

    @property
    def dbEcho( self ) -> bool:
        return self.getBool( "db.echo", False )

    # Propiedades de servidor
    @property
    def appPort( self ) -> int:
        return self.getInt( "app.port", 0 )

    def __customRepr__( self ) -> str:
        # db.url se lee sin exigirla: __repr__ nunca debe lanzar.
        return (
            f"app.name={self.appName!r}; "
            f"app.version={self.appVersion!r}; "
            f"db.url={self.get( 'db.url', '' )!r}; "
            f"db.echo={self.dbEcho}"
        )


@lru_cache( maxsize=1 )
def getApplicationProperties() -> ApplicationProperties:
    """
    Instancia única, creada en la primera llamada.

    No se construye al importar el módulo: así importar la clase no obliga
    a que exista 'application.properties'.
    """
    return ApplicationProperties()
