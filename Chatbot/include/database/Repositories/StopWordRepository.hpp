#ifndef STOPWORDREPOSITORY_HPP
#define STOPWORDREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/StopWord.hpp"

class StopWordRepository : public Repository<StopWord> {
  public:
    StopWordRepository(Connection connection)
        : Repository<StopWord>(connection) {}
    std::optional<int> add(const StopWord &) override;
    std::optional<StopWord> find(int id) override;
    bool isStopword(const std::string &);
    void update(const StopWord &) override;
    void remove(int) override;
    void removeByWord(const std::string& word);
};

#endif // STOPWORDREPOSITORY_HPP
