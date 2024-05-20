#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <map>

class Response {
public:
    // Constructor
    Response();

    // Métodos para configurar la respuesta
    void setStatus(int status);
    void setHeader(const std::string& key, const std::string& value);
    void setContentType(const std::string& contentType);
    void setContentLength(int contentLength);
    void setBody(const std::string& body);

    // Métodos para configurar respuestas de error comunes
    void setNotFound();
    void setServerError();

    // Métodos para configurar respuestas específicas para el manejo de usuarios
    void setLoginSuccessResponse(const std::string& token);
    void setLoginFailedResponse();
    void setRegistrationSuccessResponse();
    void setRegistrationFailedResponse();

    // Método para convertir la respuesta a una cadena HTTP
    std::string toString() const;

private:
    int status_;
    std::map<std::string, std::string> headers_;
    std::string body_;
};

#endif // RESPONSE_H
