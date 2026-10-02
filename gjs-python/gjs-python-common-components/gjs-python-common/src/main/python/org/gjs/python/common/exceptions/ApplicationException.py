# ApplicationException.py
"""Excepción base de la aplicación."""

from org.gjs.python.common.exceptions import ExceptionUtils


class ApplicationException( Exception ):
    """
    Excepción base de la aplicación, con código de error y causa opcionales.

    La causa queda también en ``__cause__``, de modo que la traza la muestra
    como si se hubiera lanzado con ``raise ... from causa``.
    """

    def __init__( self, message: str, errorCode: str | None = None,
                  exception: BaseException | None = None ) -> None:
        super().__init__( ExceptionUtils.formatMessage( message, errorCode, exception ) )
        self.message = message
        self.errorCode = errorCode
        self.exception = exception
        self.__cause__ = exception
