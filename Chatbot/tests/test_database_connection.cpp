#include <iostream>
#include "Database.hpp"

int main() {
    try {
        Database db;
        auto conn = db.getConnection();
        std::cout << "Connected to database: " << conn->dbname() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Database error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
