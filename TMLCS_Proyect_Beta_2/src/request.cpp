#include "request.h"
#include <iostream>
#include <sstream>
#include <fstream>

Request::Request() {}

// Métodos para configurar la solicitud
void Request::setMethod(const std::string& method) {
    method_ = method;
}

void Request::setPath(const std::string& path) {
    path_ = path;
}

void Request::setVersion(const std::string& version) {
    version_ = version;
}

void Request::setProtocol(const std::string& protocol) {
    protocol_ = protocol;
}

void Request::setHeader(const std::string& key, const std::string& value) {
    headers_[key] = value;
}

void Request::setBody(const std::string& body) {
    body_ = body;
}

// Métodos para obtener información de la solicitud
std::string Request::getMethod() const {
    return method_;
}

std::string Request::getPath() const {
    return path_;
}

std::string Request::getVersion() const {
    return version_;
}

std::string Request::getProtocol() const {
    return protocol_;
}

std::string Request::getHeader(const std::string& key) const {
    auto it = headers_.find(key);
    if (it != headers_.end()) {
        return it->second;
    } else {
        return ""; // Return empty string if header not found
    }
}

std::string Request::getBody() const {
    return body_;
}

// Métodos para obtener datos del usuario de la solicitud
std::string Request::getUsername() const {
    // Implement logic to extract username from headers or body
    return ""; // Placeholder
}

std::string Request::getEmail() const {
    // Implement logic to extract email from headers or body
    return ""; // Placeholder
}

std::string Request::getPassword() const {
    // Implement logic to extract password from headers or body
    return ""; // Placeholder
}

void Request::parse(const std::string& raw_request) {
    std::istringstream iss(raw_request);
    std::string line;
    std::getline(iss, line);
    size_t method_end = line.find(' ');
    size_t path_end = line.find(' ', method_end + 1);
    setMethod(line.substr(0, method_end));
    setPath(line.substr(method_end + 1, path_end - method_end - 1));
    setVersion(line.substr(path_end + 1));

    while (std::getline(iss, line) && line != "\r") {
        size_t separator = line.find(':');
        if (separator != std::string::npos) {
            std::string key = line.substr(0, separator);
            std::string value = line.substr(separator + 2);
            setHeader(key, value);
        }
    }

    std::getline(iss, line);
    setBody(line);
}
