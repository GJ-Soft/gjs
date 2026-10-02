import sys
import os
import uvicorn
from fastapi import FastAPI
from datetime import datetime, timezone

from org.gjs.python.common.configuration import ApplicationProperties, getApplicationProperties

# Inyectar ruta de modelos generados
from ${package}.models.Models import ServerStatus

class ${capitalizedName}Server:
    def __init__(self, host="0.0.0.0", port=getApplicationProperties().appPort):
        self.host = host
        self.port = port
        self.app = FastAPI()
        self._setup_routes()

    def _setup_routes(self):
        @self.app.get("/status", response_model=ServerStatus)
        async def get_status():
            return {
                "status": "OK",
                "date-time": datetime.now(timezone.utc).isoformat()
            }

    def start(self):
        uvicorn.run(self.app, host=self.host, port=self.port)