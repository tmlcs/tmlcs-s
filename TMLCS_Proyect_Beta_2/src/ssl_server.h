#ifndef SSL_SERVER_H
#define SSL_SERVER_H

#include "server_config.h"
#include "router.h"
#include "ssl_config.h"
#include "response.h"
#include <openssl/ssl.h>

class SSLServer {
public:
    // Constructor
    SSLServer(const ServerConfig& config, Router& router, const SSLConfig& sslConfig);

    // Método para iniciar el servidor
    void run();

private:
    // Configuración del servidor
    ServerConfig config_;

    // Enrutador para manejar las solicitudes
    Router& router_;

    // Configuración SSL
    SSLConfig sslConfig_;

    // Socket del servidor
    int serverSocket_;

    // Método para manejar una conexión entrante
    void handleConnection(SSL* ssl);

    // Método para manejar una solicitud entrante
    void handleRequest(SSL* ssl);
};

#endif // SSL_SERVER_H
