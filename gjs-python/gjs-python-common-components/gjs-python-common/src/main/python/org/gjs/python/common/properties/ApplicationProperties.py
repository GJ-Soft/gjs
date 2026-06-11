
from __future__ import annotations

from .Properties import Properties




class ApplicationProperties(Properties):
    """Acceso tipado a las propiedades de la aplicación."""

    def __init__(self) -> None:
        super().__init__("application.properties")

    # Propiedades de aplicación
    @property
    def app_name(self) -> str:
        return self.get("app.name", "app")

    @property
    def app_version(self) -> str:
        return self.get("app.version", "0.0.0")

    # Propiedades de base de datos
    @property
    def db_url(self) -> str:
        return self.get("db.url")

    @property
    def db_echo(self) -> bool:
        return self.get("db.echo", "false").lower() == "true"

 
    # Propiedades de servidor
    @property
    def app_port(self) -> str:
        return self.get("app.port", "0")


    def __repr__(self) -> str:
        return (
            f"{super().__repr__()} "
            f"<db_url={self.db_url!r} db_echo={self.db_echo}>"
        )


# Instancia singleton lista para importar en cualquier módulo
applicationProperties = ApplicationProperties()
