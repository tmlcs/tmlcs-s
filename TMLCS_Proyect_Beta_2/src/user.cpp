#include "user.h"

// Constructor
User::User(const std::string& username, const std::string& email, const std::string& password)
    : username_(username), email_(email), password_(password) {}

// Métodos de acceso
std::string User::getUsername() const {
    return username_;
}

std::string User::getEmail() const {
    return email_;
}

std::string User::getPassword() const {
    return password_;
}
