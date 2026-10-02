# ExceptionUtils.py
"""Utilidades para las excepciones."""


def formatMessage( message: str, errorCode: str | None = None, exception: BaseException | None = None ) -> str:
    """
    Compone el texto de una excepción: ``[código] mensaje: causa``.

    Las partes que no llegan se omiten. Si la causa no tiene texto, se pone el
    nombre de su clase.

    :param message: Mensaje propio.
    :param errorCode: Código de error.
    :param exception: Excepción que la provoca.
    :return: El texto compuesto.
    """
    text = message
    if errorCode:
        text = f"[{errorCode}] {text}"
    if exception is not None:
        text = f"{text}: {str( exception ) or type( exception ).__name__}"
    return text
