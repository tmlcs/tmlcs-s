#ifndef ROUTER_H
#define ROUTER_H

#include <functional>
#include <map>
#include <string>
#include <filesystem>
#include "request.h"
#include "response.h"

class Router {
public:
    // Definición de un tipo de función de controlador de solicitud
    typedef std::function<void(const Request&, Response&)> Handler;

    // Métodos para manejar solicitudes HTTP
    void get(const std::string& path, Handler handler);
    void post(const std::string& path, Handler handler);
    // Agregar más métodos HTTP según sea necesario

    // Métodos para manejar solicitudes HTTPS
    void getHTTPS(const std::string& path, Handler handler);
    void postHTTPS(const std::string& path, Handler handler);
    // Agregar más métodos HTTPS según sea necesario

    // Método para manejar una solicitud HTTP en función de su ruta y método
    void handleHTTPRequest(const Request& request, Response& response) const;

    // Método para manejar una solicitud HTTPS en función de su ruta y método
    void handleHTTPSRequest(const Request& request, Response& response) const;

    // Método para manejar solicitudes de archivos estáticos
    void handleIconFile(const Request& request, Response& response);

    // Método para manejar solicitudes de archivos estáticos
    void handleStaticFile(const Request& request, Response& response);


private:
    // Estructura para almacenar rutas y controladores HTTP
    struct Route {
        std::string path;
        Handler handler;
    };

    // Estructura para almacenar rutas y controladores HTTPS
    struct HTTPSRoute {
        std::string path;
        Handler handler;
    };

    // Mapas para almacenar rutas y controladores HTTP y HTTPS
    std::map<std::string, Route> httpRoutes_;
    std::map<std::string, HTTPSRoute> httpsRoutes_;
};

#endif // ROUTER_H
