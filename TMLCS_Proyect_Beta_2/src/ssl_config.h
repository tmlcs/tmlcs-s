#ifndef SSL_CONFIG_H
#define SSL_CONFIG_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>

class SSLConfig {
public:
    // Constructor
    SSLConfig();

    // Destructor
    ~SSLConfig();

    // Método para cargar los certificados SSL
    bool loadCertificates(const std::string& certFile, const std::string& keyFile, const std::string& caFile);

    // Método para crear el contexto SSL
    SSL_CTX* createSSLContext();

    // Método para crear una conexión SSL
    SSL* createSSL(SSL_CTX* ctx, int clientSocket);

private:
    SSL_CTX* ctx_;
};

#endif // SSL_CONFIG_H
