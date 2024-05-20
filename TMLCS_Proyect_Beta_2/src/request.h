#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>

class Request {
public:
    // Constructor
    Request();

    // Métodos para configurar la solicitud
    void setMethod(const std::string& method);
    void setPath(const std::string& path);
    void setVersion(const std::string& version);
    void setProtocol(const std::string& protocol); // Changed method name
    void setHeader(const std::string& key, const std::string& value);
    void setBody(const std::string& body);

    // Métodos para obtener información de la solicitud
    std::string getMethod() const;
    std::string getPath() const;
    std::string getVersion() const;
    std::string getProtocol() const; // Changed method name
    std::string getHeader(const std::string& key) const;
    std::string getBody() const;

    // Métodos para obtener datos del usuario de la solicitud
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Método para analizar una cadena de solicitud HTTP
    void parse(const std::string& raw_request);

private:
    std::string method_;
    std::string path_;
    std::string version_;
    std::string protocol_; // Changed member variable name
    std::map<std::string, std::string> headers_;
    std::string body_;
};

#endif // REQUEST_H
