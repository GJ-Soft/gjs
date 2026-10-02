#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
${symbol_pound}
${symbol_pound} Program ${capitalizedName} Rest Client 
${symbol_pound}
${symbol_pound} Module ${capitalizedName}Client.py
${symbol_pound}

import sys
import os
import httpx

from urllib.parse import urlunparse

from org.gjs.python.common.configuration import ApplicationProperties, getApplicationProperties

# Inyectar ruta de modelos generados
from ${package}.models.Models import ServerStatus

class ${capitalizedName}Client:
    def __init__(self, protocol=getApplicationProperties().get("client.protocol","http"), 
                       hostname= getApplicationProperties().get("client.hostname","localhost"), 
                       port=getApplicationProperties().get("client.port","8000")):
        netloc = f"{hostname}:{port}"
        self.base_url = urlunparse(
            (protocol, netloc, "", "", "", ""))

    def get_server_status(self) -> ServerStatus:
        with httpx.Client() as client:
            response = client.get(f"{self.base_url}/status")
            response.raise_for_status()
            return ServerStatus(**response.json())
            
            