#include "database.h"
#include <stdexcept>

Database::Database(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : host_(host), user_(user), password_(password), database_(database), driver_(nullptr), connection_(nullptr) {}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    try {
        driver_ = sql::mysql::get_mysql_driver_instance();
        connection_ = driver_->connect(host_, user_, password_);
        connection_->setSchema(database_);
        return true;
    } catch (const sql::SQLException& e) {
        throw std::runtime_error("Failed to connect to database: " + std::string(e.what()));
    }
}

void Database::disconnect() {
    if (connection_ != nullptr) {
        delete connection_;
        connection_ = nullptr;
    }
}

bool Database::emailExists(const std::string& email) {
    try {
        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM User WHERE email = '" + email + "'");
        bool exists = res->next();
        delete res;
        delete stmt;
        return exists;
    } catch (const sql::SQLException& e) {
        throw std::runtime_error("SQL error: " + std::string(e.what()));
    }
}

bool Database::addUser(const std::string& username, const std::string& email, const std::string& password) {
    try {
        sql::PreparedStatement* pstmt = connection_->prepareStatement("INSERT INTO Unregistered_Customers (username, email, password_hash) VALUES (?, ?, ?)");
        pstmt->setString(1, username);
        pstmt->setString(2, email);
        pstmt->setString(3, password);
        int rowsAffected = pstmt->executeUpdate();
        delete pstmt;
        return rowsAffected > 0;
    } catch (const sql::SQLException& e) {
        throw std::runtime_error("SQL error: " + std::string(e.what()));
    }
}

sql::ResultSet* Database::executeQuery(const std::string& query) {
    try {
        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery(query);
        delete stmt;
        return res;
    } catch (const sql::SQLException& e) {
        throw std::runtime_error("SQL error: " + std::string(e.what()));
    }
}

bool Database::executeUpdate(const std::string& query) {
    try {
        sql::Statement* stmt = connection_->createStatement();
        int rowsAffected = stmt->executeUpdate(query);
        delete stmt;
        return rowsAffected > 0;
    } catch (const sql::SQLException& e) {
        throw std::runtime_error("SQL error: " + std::string(e.what()));
    }
}
