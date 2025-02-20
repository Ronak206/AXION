#include "Database.hpp"
#include <iostream>

Connection Database::getConnection() {
    const std::string DATABASE_NAME = "chatbot_db";
    const std::string USERNAME = "chatbot_user";
    const std::string PASSWORD = "chatbot@axion";
    const std::string HOST = "localhost";
    const std::string PORT = "5432";

    try {
        static Connection conn =
            std::make_shared<pqxx::connection>(
                std::string("dbname=") + DATABASE_NAME + " "
                + std::string("user=") + USERNAME + " "
                + std::string("password=") + PASSWORD + " "
                + std::string("host=") + HOST + " "
                + std::string("port=") + PORT
            );

        if (conn->is_open()) {
            return conn;
        } else {
            throw std::runtime_error("Failed to open the database connection.");
        }
    } catch (const std::exception &e) {
        std::cerr << "Database Connection Error: " << e.what() << std::endl;
        throw;
    }
}
