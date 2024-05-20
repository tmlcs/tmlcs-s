#ifndef SERVER_H
#define SERVER_H

#include "server_config.h"
#include "router.h"
#include "response.h"// Agregamos esta línea

class Server {
public:
    // Constructor
    Server(const ServerConfig& config, Router& router);

    // Método para iniciar el servidor
    virtual void run();

protected:
    // Métodos protegidos para manejar conexiones y solicitudes
    virtual void handleConnection(int clientSocket);
    virtual void handleRequest(int clientSocket);

    // Método para manejar solicitudes de archivos estáticos
    void handleStaticFileRequest(const Request& request, Response& response);

    // Variables miembro
    ServerConfig config_;
    Router& router_;
    int serverSocket_;// Agregamos esta línea
};

#endif // SERVER_H
