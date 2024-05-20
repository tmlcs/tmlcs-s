#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username_;
    std::string email_;
    std::string password_;

public:
    // Constructor
    User(const std::string& username, const std::string& email, const std::string& password);

    // Métodos de acceso
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Otros métodos (por ejemplo, para validar contraseñas, verificar credenciales, etc.)
};

#endif // USER_H
