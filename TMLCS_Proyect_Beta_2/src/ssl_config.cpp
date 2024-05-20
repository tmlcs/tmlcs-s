#include "ssl_config.h"

SSLConfig::SSLConfig() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
}

SSLConfig::~SSLConfig() {
    ERR_free_strings();
    EVP_cleanup();
}

bool SSLConfig::loadCertificates(const std::string& certFile, const std::string& keyFile, const std::string& caFile) {
    ctx_ = SSL_CTX_new(SSLv23_server_method());
    if (!ctx_) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    // Cargar el certificado del servidor
    if (SSL_CTX_use_certificate_file(ctx_, certFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    // Cargar la clave privada
    if (SSL_CTX_use_PrivateKey_file(ctx_, keyFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    // Cargar la cadena de certificados (certificado intermedio + certificado raíz)
    if (SSL_CTX_load_verify_locations(ctx_, caFile.c_str(), nullptr) != 1) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}



SSL_CTX* SSLConfig::createSSLContext() {
    return ctx_;
}

SSL* SSLConfig::createSSL(SSL_CTX* ctx, int clientSocket) {
    SSL* ssl = SSL_new(ctx);
    if (!ssl) {
        ERR_print_errors_fp(stderr);
        return nullptr;
    }

    SSL_set_fd(ssl, clientSocket);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        return nullptr;
    }

    return ssl;
}
