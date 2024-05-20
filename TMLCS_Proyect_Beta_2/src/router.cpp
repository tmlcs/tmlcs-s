#include "router.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>

// Métodos para manejar solicitudes HTTP
void Router::get(const std::string &path, Handler handler)
{
    httpRoutes_["GET " + path] = {path, handler};
}

void Router::post(const std::string &path, Handler handler)
{
    httpRoutes_["POST " + path] = {path, handler};
}

// Métodos para manejar solicitudes HTTPS
void Router::getHTTPS(const std::string &path, Handler handler)
{
    httpsRoutes_["GET " + path] = {path, handler};
}

void Router::postHTTPS(const std::string &path, Handler handler)
{
    httpsRoutes_["POST " + path] = {path, handler};
}

// Método para manejar una solicitud HTTP en función de su ruta y método
void Router::handleHTTPRequest(const Request &request, Response &response) const
{
    // Obtener la ruta y el método de la solicitud HTTP
    std::string routeKey = request.getMethod() + " " + request.getPath();

    // Buscar la ruta en el mapa de rutas HTTP
    auto it = httpRoutes_.find(routeKey);
    if (it != httpRoutes_.end())
    {
        // Si se encuentra la ruta, llamar al controlador asociado
        it->second.handler(request, response);
    }
    else
    {
        // Si no se encuentra la ruta, devolver un error 404
        response.setStatus(404);
        response.setBody("Not Found");
    }
}

// Método para manejar una solicitud HTTPS en función de su ruta y método
void Router::handleHTTPSRequest(const Request &request, Response &response) const
{
    // Obtener la ruta y el método de la solicitud HTTPS
    std::string routeKey = request.getMethod() + " " + request.getPath();

    // Buscar la ruta en el mapa de rutas HTTPS
    auto it = httpsRoutes_.find(routeKey);
    if (it != httpsRoutes_.end())
    {
        // Si se encuentra la ruta, llamar al controlador asociado
        it->second.handler(request, response);
    }
    else
    {
        // Si no se encuentra la ruta, devolver un error 404
        response.setStatus(404);
        response.setBody("Not Found");
    }
}

// Método para manejar solicitudes de archivos estáticos
void Router::handleStaticFile(const Request &request, Response &response)
{
    // Obtener la ruta del archivo solicitado
    std::string basePath = "/var/www/frontend/templates/";
    std::string requestedPath = request.getPath();

    // Verificar si la solicitud es para la página principal (index.html)
    if (requestedPath == "/")
    {
        requestedPath = "/index.html"; // Si es la página principal, cambia la ruta solicitada a index.html
    }

    // Combinar la ruta base con la ruta solicitada para obtener la ruta completa del archivo
    std::filesystem::path filePath = std::filesystem::canonical(basePath + requestedPath);

    // Verificar y asegurar la ruta del archivo solicitado
    if (!filePath.has_filename() || filePath.native().find(basePath) != 0)
    {
        // La ruta no es válida o no está dentro del directorio base
        response.setStatus(403);
        response.setBody("Forbidden");
        return;
    }

    // Abrir el archivo
    std::ifstream file(filePath, std::ios::binary);
    if (file.is_open())
    {
        // Leer el contenido del archivo en un stringstream
        std::ostringstream content;
        content << file.rdbuf();
        file.close();

        // Establecer el contenido del archivo como el cuerpo de la respuesta
        response.setStatus(200);
        response.setBody(content.str());

        // Determinar el tipo MIME del archivo
        std::string contentType = "text/plain"; // Por defecto
        std::string fileExtension = filePath.extension().string();
        if (fileExtension == ".html")
        {
            contentType = "text/html";
        }
        else if (fileExtension == ".css")
        {
            contentType = "text/css";
        }
        else if (fileExtension == ".js")
        {
            contentType = "application/javascript";
        }
        response.setHeader("Content-Type", contentType);
    }
    else
    {
        // Si el archivo no se pudo abrir, responder con un error 404
        response.setStatus(404);
        response.setBody("File Not Found");
    }
}

void Router::handleIconFile(const Request &request, Response &response)
{
    // Obtener la ruta del archivo solicitado
    std::string basePath = "/var/www/frontend/templates/pages/static/assets/favicons";
    std::string requestedPath = request.getPath();

    // Combinar la ruta base con la ruta solicitada para obtener la ruta completa del archivo
    std::filesystem::path filePath = std::filesystem::canonical(basePath + requestedPath);

    // Verificar y asegurar la ruta del archivo solicitado
    if (!filePath.has_filename() || filePath.native().find(basePath) != 0)
    {
        // La ruta no es válida o no está dentro del directorio base
        response.setStatus(403);
        response.setBody("Forbidden");
        return;
    }

    // Abrir el archivo
    std::ifstream file(filePath, std::ios::binary);
    if (file.is_open())
    {
        // Leer el contenido del archivo en un stringstream
        std::ostringstream content;
        content << file.rdbuf();
        file.close();

        // Establecer el contenido del archivo como el cuerpo de la respuesta
        response.setStatus(200);
        response.setBody(content.str());

        // Determinar el tipo MIME del archivo
        std::string contentType = "text/plain"; // Por defecto
        std::string fileExtension = filePath.extension().string();
        if (fileExtension == ".html")
        {
            contentType = "text/html";
        }
        else if (fileExtension == ".css")
        {
            contentType = "text/css";
        }
        else if (fileExtension == ".js")
        {
            contentType = "application/javascript";
        }
        else if (fileExtension == ".ico")
        {
            contentType = "image/x-icon";
        }
        else if (fileExtension == ".svg")
        {
            contentType = "image/svg+xml";
        }
        response.setHeader("Content-Type", contentType);
    }
    else
    {
        // Si el archivo no se pudo abrir, responder con un error 404
        response.setStatus(404);
        response.setBody("File Not Found");
    }
}
