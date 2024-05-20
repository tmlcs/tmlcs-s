#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <string>

class Database {
public:
    Database(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~Database();

    bool connect();
    void disconnect();

    bool emailExists(const std::string& email);
    bool addUser(const std::string& username, const std::string& email, const std::string& password);


    sql::ResultSet* executeQuery(const std::string& query);
    bool executeUpdate(const std::string& query);

private:
    std::string host_;
    std::string user_;
    std::string password_;
    std::string database_;

    sql::mysql::MySQL_Driver* driver_;
    sql::Connection* connection_;
};

#endif // DATABASE_H
