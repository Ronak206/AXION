#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

#include "Database.hpp"
#include "Models/Model.hpp"

template <typename T>
class Repository {
  protected:
    Connection connection;

  public:
    explicit Repository(Connection connection) {
        this->connection = connection;
    }

    virtual int add(const T& entity) = 0;
    virtual std::optional<T> find(int id) = 0;
    virtual void update(const T& entity) = 0;
    virtual void remove(int id) = 0;

    virtual ~Repository() = default;
};

#endif // REPOSITORY_HPP
