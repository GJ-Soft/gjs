from fastapi.testclient import TestClient
from ${package}.server.${capitalizedName}Server import ${capitalizedName}Server

def testStatusEndpoint():
    # Instanciamos la clase del servidor
    serverInstance = ${capitalizedName}Server()
    # Usamos el TestClient sobre la propiedad .app de la clase
    client = TestClient(serverInstance.app)
    
    response = client.get("/status")
    
    assert response.status_code == 200
    data = response.json()
    assert "status" in data
    assert "date-time" in data
    assert data["status"] == "OK"