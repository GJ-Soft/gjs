# Resources.py

from pathlib import Path


class Resources:

    @staticmethod
    def getResource(name: str) -> Path | None:
        """
        Busca un fichero por nombre comenzando en la raíz del proyecto.

        :param name: Nombre del fichero a buscar.
        :return: Ruta absoluta al fichero o None si no se encuentra.
        """

        # Se presupone que el directorio de trabajo es la raíz del proyecto.
        root = Path.cwd();

        for path in root.rglob(name):
            if path.is_file():
                return path
        
        return None