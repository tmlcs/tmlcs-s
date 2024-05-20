#include "response.h"
#include <sstream>

// Constructor
Response::Response() : status_(200) {}

// Métodos para configurar la respuesta
void Response::setStatus(int status) {
    status_ = status;
}

void Response::setHeader(const std::string& key, const std::string& value) {
    headers_[key] = value;
}

void Response::setContentType(const std::string& contentType) {
    headers_["Content-Type"] = contentType;
}

void Response::setContentLength(int contentLength) {
    headers_["Content-Length"] = std::to_string(contentLength);
}

void Response::setBody(const std::string& body) {
    body_ = body;
}

// Métodos para configurar respuestas de error comunes
void Response::setNotFound() {
    status_ = 404;
    body_ = "<h1>404 Not Found</h1>";
    setContentType("text/html");
    setContentLength(body_.size());
}

void Response::setServerError() {
    status_ = 500;
    body_ = "<h1>500 Internal Server Error</h1>";
    setContentType("text/html");
    setContentLength(body_.size());
}

// Métodos para configurar respuestas específicas para el manejo de usuarios
void Response::setLoginSuccessResponse(const std::string& token) {
    status_ = 200;
    body_ = "{\"token\": \"" + token + "\"}";
    setContentType("application/json");
    setContentLength(body_.size());
}

void Response::setLoginFailedResponse() {
    status_ = 401;
    body_ = "{\"error\": \"Unauthorized\"}";
    setContentType("application/json");
    setContentLength(body_.size());
}

void Response::setRegistrationSuccessResponse() {
    status_ = 200;
    body_ = "{\"message\": \"Registration successful\"}";
    setContentType("application/json");
    setContentLength(body_.size());
}

void Response::setRegistrationFailedResponse() {
    status_ = 400;
    body_ = "{\"error\": \"Bad Request\"}";
    setContentType("application/json");
    setContentLength(body_.size());
}

// Método para convertir la respuesta a una cadena HTTP
std::string Response::toString() const {
    std::stringstream response;
    response << "HTTP/1.1 " << status_ << " " << "OK\r\n";
    for (const auto& pair : headers_) {
        response << pair.first << ": " << pair.second << "\r\n";
    }
    response << "\r\n";
    response << body_;
    return response.str();
}
