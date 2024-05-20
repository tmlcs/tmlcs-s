#include "request.h"
#include "response.h"
#include "router.h"
#include "server_config.h"
#include "ssl_config.h"
#include "ssl_server.h"
#include "server.h"
#include "database.h"
#include <thread> 
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
#include <ctime>
#include <cstdlib>

void clearTerminal() {
    // Comando para limpiar la pantalla en sistemas Unix/Linux
    #ifdef __unix__
        system("clear");
    #endif

    // Comando para limpiar la pantalla en sistemas Windows
    #ifdef _WIN32
        system("cls");
    #endif
}

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

int main() {

    std::cout << "       ===================================================\n";
    std::cout << "       || Welcome to TMLCS-NeTWORK Server V:alpha_0.002 ||\n";
    std::cout << "       ===================================================\n" << std::endl;
    // Ejemplo de uso
    logMessage("Inicio del programa");

    // Configurar la base de datos MySQL
    Database database("localhost", "root", "@TMLCS20JFL20FR20ps4", "User_Manager");

    // Conectar a la base de datos
    if (database.connect()) {
        std::cout << "\nConexión exitosa a la base de datos MySQL" << std::endl;
        // Aquí puedes ejecutar consultas SQL u otras operaciones con la base de datos
    } else {
        std::cerr << "\nError al conectar a la base de datos MySQL\n" << std::endl;
        return 1;
    }

    // Configuración del servidor HTTP
    ServerConfig httpConfig(8080, 100, "/var/www/frontend/", "192.168.1.24"); // Puerto 8080 para HTTP
    Router httpRouter;

    // Configurar rutas y controladores para el servidor HTTP
    httpRouter.get("/", [](const Request& request, Response& response) {
        std::ifstream file("/var/www/frontend/templates/index.html");
        if (file.is_open()) {
            std::ostringstream content;
            content << file.rdbuf();
            file.close();

            response.setStatus(200);
            response.setBody(content.str());
            response.setHeader("Content-Type", "text/html");
        } else {
            response.setStatus(500);
            response.setBody("Internal Server Error");
        }
    });

        // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpRouter.get("/pages/static/css/normalize.css", [](const Request& request, Response& response) {
        // Ruta completa del archivo CSS en el sistema de archivos
        std::string filePath = "/var/www/frontend/templates/pages/static/css/normalize.css";

        // Intentar abrir el archivo solicitado
        std::ifstream file(filePath);
        if (file.is_open()) {
            // Si el archivo se puede abrir, leer su contenido y configurar la respuesta
            std::ostringstream content;
            content << file.rdbuf();
            file.close();

            response.setStatus(200);
            response.setBody(content.str());
            response.setHeader("Content-Type", "text/css");
        } else {
            // Si el archivo no se puede abrir, responder con un error 404
            response.setStatus(404);
            response.setBody("File Not Found");
        }
    });

    httpRouter.get("/pages/static/css/index.css", [](const Request& request, Response& response) {
        // Ruta completa del archivo CSS en el sistema de archivos
        std::string filePath = "/var/www/frontend/templates/pages/static/css/index.css";

        // Intentar abrir el archivo solicitado
        std::ifstream file(filePath);
        if (file.is_open()) {
            // Si el archivo se puede abrir, leer su contenido y configurar la respuesta
            std::ostringstream content;
            content << file.rdbuf();
            file.close();

            response.setStatus(200);
            response.setBody(content.str());
            response.setHeader("Content-Type", "text/css");
        } else {
            // Si el archivo no se puede abrir, responder con un error 404
            response.setStatus(404);
            response.setBody("File Not Found");
        }
    });

    // Configura la ruta para manejar la solicitud del archivo index.js
    httpRouter.get("/pages/index.js", [](const Request& request, Response& response) {
        // Maneja la solicitud para el archivo index.js
        std::ifstream file("/var/www/frontend/templates/pages/index.js");
        if (file.is_open()) {
            // Si el archivo se puede abrir, lee su contenido y configura la respuesta
            std::ostringstream content;
            content << file.rdbuf();
            file.close();

            response.setStatus(200);
            response.setBody(content.str());
            response.setHeader("Content-Type", "application/javascript");
        } else {
            // Si el archivo no se puede abrir, responde con un error 404
            response.setStatus(404);
            response.setBody("File Not Found");
        }
    });

    // Crear y ejecutar el servidor HTTP
    Server httpServer(httpConfig, httpRouter);
    std::thread httpThread([&]() { httpServer.run(); });

    // Configuración del servidor HTTPS
    SSLConfig sslConfig;
    std::cout<<"\nEsperando inicializacion del servidor HTTPS.."<<std::endl;
    sslConfig.loadCertificates("/ssl/server.crt", "/ssl/server.key", "/ssl/ca.crt");
    ServerConfig httpsConfig(8443, 100, "/var/www/frontend/", "192.168.1.24"); // Puerto 8443 para HTTPS
    Router httpsRouter;

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/favicon.ico", [&](const Request& request, Response& response) {
        httpsRouter.handleIconFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/favicon.svg", [&](const Request& request, Response& response) {
        httpsRouter.handleIconFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/normalize.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/js/dropdown.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/index.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/index/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/index/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/index/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/index/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/index.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/register.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/register/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/register/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/register/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/register/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/register.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/login.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/login/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/login/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/login/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/login/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/login.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/collections.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/collections/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/collections/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/collections/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/collections/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/collections.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/cproducts.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/cproducts/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/cproducts/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/cproducts/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/cproducts/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/cproducts.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/transactions.html", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/transactions/head.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });


    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/transactions/nav.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });


    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/transactions/main.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });


    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/transactions/footer.js", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });

    // Agregar la ruta para manejar solicitudes de archivos estáticos
    httpsRouter.getHTTPS("/pages/static/css/transactions.css", [&](const Request& request, Response& response) {
        httpsRouter.handleStaticFile(request, response);
    });


    // Crear y ejecutar el servidor HTTPS
    SSLServer httpsServer(httpsConfig, httpsRouter, sslConfig);
    std::thread httpsThread([&]() {
        httpsServer.run();
    });
     // Menú de opciones
    std::cout << "\nServidores HTTP y HTTPS iniciados correctamente!\n" << std::endl;
    std::cout << "Servidor HTTP iniciado en el puerto " << httpConfig.getPort() <<std::endl;
    std::cout << "Servidor HTTPS iniciado en el puerto " << httpsConfig.getPort() <<std::endl;

    std::cout << "\n       =================================================\n";
    std::cout << "       ||TMLCS-NeTWORK Server V:alpha_0.002 is on LIVE||\n";
    std::cout << "       =================================================\n" << std::endl;

    std::cout << "Selecciona una opción:\n";
    std::cout << "1. Abrir terminal para manejar logs\n";
    std::cout << "2. Abrir terminal para manejar la base de datos\n";
    std::cout << "3. Vaciar terminal\n";

    int opcion;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            // Abrir una terminal para manejar los logs
            system("gnome-terminal -- /bin/bash -c 'tail -f /server/logs/logs.txt'");
            break;
        case 2:
            // Abrir una terminal para manejar la base de datos
            system("gnome-terminal -- /bin/bash -c 'mysql -u root -p'");
            break;
        case 3:
            // Vaciar el terminal
            clearTerminal();
            break;
        default:
            std::cout << "Opción no válida\n";
            break;
    }
    // Esperar a que ambos servidores terminen
    httpThread.join();
    httpsThread.join();

    database.disconnect();

    return 0;
}
