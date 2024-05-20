#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <string>

class ServerConfig {
public:
    ServerConfig(int port, int maxConnections, const std::string& rootDirectory, const std::string& ipAddress)
        : port_(port), maxConnections_(maxConnections), rootDirectory_(rootDirectory), ipAddress_(ipAddress) {}

    // Métodos para obtener los valores de configuración
    int getPort() const { return port_; }
    int getMaxConnections() const { return maxConnections_; }
    const std::string& getRootDirectory() const { return rootDirectory_; }
    const std::string& getIPAddress() const { return ipAddress_; }

    // Métodos para configurar los valores de configuración
    void setPort(int port) { port_ = port; }
    void setMaxConnections(int maxConnections) { maxConnections_ = maxConnections; }
    void setRootDirectory(const std::string& rootDirectory) { rootDirectory_ = rootDirectory; }
    void setIPAddress(const std::string& ipAddress) { ipAddress_ = ipAddress; }

private:
    int port_;
    int maxConnections_;
    std::string rootDirectory_;
    std::string ipAddress_; // Nueva variable para almacenar la dirección IP
};

#endif // SERVER_CONFIG_H
