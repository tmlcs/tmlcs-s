#include "ssl_server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ctime>

// Constructor
SSLServer::SSLServer(const ServerConfig& config, Router& router, const SSLConfig& sslConfig)
    : config_(config), router_(router), sslConfig_(sslConfig), serverSocket_(-1) {}

void logMessage(const std::string& message) {
    // Obtener la hora actual del sistema
    std::time_t currentTime = std::time(nullptr);
    
    // Convertir la hora actual a una estructura tm
    std::tm* localTime = std::localtime(&currentTime);
    
    // Formatear la hora y fecha como una cadena
    char timeString[100];
    std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);
    
    // Mostrar el mensaje del registro junto con la hora
    std::cout << "[" << timeString << "] " << message << std::endl;
}

// Método para iniciar el servidor
void SSLServer::run() {
    // Crear un socket TCP
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        //std::cerr << "Error: No se pudo crear el socket." << std::endl;
        logMessage("Error: No se pudo crear el socket.");
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

    //std::cout << "Servidor HTTPS iniciado en el puerto " << config_.getPort() << std::endl;

    // Configurar el contexto SSL
    SSL_CTX* ctx = sslConfig_.createSSLContext();
    if (!ctx) {
        std::cerr << "Error: No se pudo crear el contexto SSL." << std::endl;
        close(serverSocket_);
        return;
    }

    // Esperar y manejar conexiones entrantes
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket_, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error: No se pudo aceptar la conexión entrante." << std::endl;
            continue;
        }

        // Establecer la conexión SSL
        SSL* ssl = sslConfig_.createSSL(ctx, clientSocket);
        if (!ssl) {
            //std::cerr << "Error: No se pudo establecer la conexión SSL." << std::endl;
            logMessage("Error: No se pudo establecer la conexión SSL.");
            close(clientSocket);
            continue;
        }

        // Manejar la conexión
        handleConnection(ssl);

        // Cerrar la conexión SSL
        SSL_free(ssl);
        close(clientSocket);
    }

    // Liberar el contexto SSL
    SSL_CTX_free(ctx);
}

// Método protegido para manejar una conexión entrante
void SSLServer::handleConnection(SSL* ssl) {
    // Manejar la solicitud
    handleRequest(ssl);
}

// Método protegido para manejar una solicitud entrante
void SSLServer::handleRequest(SSL* ssl) {
    // Leer los datos de la solicitud
    char buffer[1024];
    int bytesRead = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        std::cerr << "Error: No se pudieron leer los datos de la solicitud." << std::endl;
        return;
    }

    // Analizar la solicitud
    std::string requestData(buffer, bytesRead);
    Request request;
    request.parse(requestData);

    // Generar una respuesta utilizando el enrutador
    Response response;
    router_.handleHTTPSRequest(request, response);

    // Enviar la respuesta al cliente
    std::string responseData = response.toString();
    int bytesSent = SSL_write(ssl, responseData.c_str(), responseData.size());
    if (bytesSent <= 0) {
        std::cerr << "Error: No se pudo enviar la respuesta al cliente." << std::endl;
        return;
    }
}
