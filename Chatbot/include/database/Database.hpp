#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <pqxx/pqxx>
#include <memory>

#define Connection std::shared_ptr<pqxx::connection>

class Database {
  public:
    static Connection getConnection();
};

#endif // DATABASE_HPP
