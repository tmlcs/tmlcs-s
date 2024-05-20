#include "server.h"
#include "router.h"
#include "response.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

// Constructor
Server::Server(const ServerConfig& config, Router& router)
    : config_(config), router_(router), serverSocket_(-1) {}

// Método para iniciar el servidor
void Server::run() {
    // Crear un socket TCP
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        std::cerr << "Error: No se pudo crear el socket." << std::endl;
        return;
    }

    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(config_.getPort());

    // Vincular el socket a la dirección y puerto del servidor
    if (bind(serverSocket_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: No se pudo vincular el socket al puerto." << std::endl;
        close(serverSocket_);
        return;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket_, config_.getMaxConnections()) == -1) {
        std::cerr << "Error: No se pudieron escuchar conexiones entrantes." << std::endl;
        close(serverSocket_);
        return;
    }

    //std::cout << "Servidor HTTP iniciado en el puerto " << config_.getPort() <<std::endl;

    // Esperar y manejar conexiones entrantes
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket_, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error: No se pudo aceptar la conexión entrante." << std::endl;
            continue;
        }
        handleConnection(clientSocket);
    }
}

// Método protegido para manejar una conexión entrante
void Server::handleConnection(int clientSocket) {
    // Manejar la solicitud
    handleRequest(clientSocket);

    // Cerrar el socket del cliente
    close(clientSocket);
}

// Método protegido para manejar una solicitud entrante
void Server::handleRequest(int clientSocket) {
    // Leer los datos de la solicitud
    char buffer[1024];
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        std::cerr << "Error: No se pudieron leer los datos de la solicitud." << std::endl;
        return;
    }

    // Analizar la solicitud
    std::string requestData(buffer, bytesRead);
    Request request;
    request.parse(requestData);

     Response response;

    // Verificar si se trata de una solicitud de archivo estático
    if (request.getPath().substr(0, 7) == "/static") {
        handleStaticFileRequest(request, response);
        return;
    }

    // Generar una respuesta utilizando el enrutador
    router_.handleHTTPRequest(request, response);

    // Enviar la respuesta al cliente
    std::string responseData = response.toString();
    ssize_t bytesSent = send(clientSocket, responseData.c_str(), responseData.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Error: No se pudo enviar la respuesta al cliente." << std::endl;
        return;
    }
}

// Método protegido para manejar solicitudes de archivos estáticos
void Server::handleStaticFileRequest(const Request& request, Response& response) {
    // Obtener la ruta del archivo estático desde la solicitud
    std::string path = request.getPath().substr(7); // Eliminar "/static" del inicio

    // Manejar la solicitud de archivo estático utilizando StaticFileHandler
}
