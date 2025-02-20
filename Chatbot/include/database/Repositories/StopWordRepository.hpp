#ifndef STOPWORDREPOSITORY_HPP
#define STOPWORDREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/StopWord.hpp"

class StopWordRepository : public Repository<StopWord> {
  public:
    StopWordRepository(Connection connection)
        : Repository<StopWord>(connection) {}
    void add(const StopWord& stopWord) override;
    StopWord find(int id) override;
    void update(const StopWord& stopWord) override;
    void remove(int id) override;
};

#endif // STOPWORDREPOSITORY_HPP
