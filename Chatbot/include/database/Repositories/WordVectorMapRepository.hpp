#ifndef WORDVECTORMAPREPOSITORY_HPP
#define WORDVECTORMAPREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/WordVectorMap.hpp"

class WordVectorMapRepository : public Repository<WordVectorMap> {
  public:
    WordVectorMapRepository(Connection connection)
        : Repository<WordVectorMap>(connection) {}
    void add(const WordVectorMap& wordVector) override;
    WordVectorMap find(int id) override;
    void update(const WordVectorMap& wordVector) override;
    void remove(int id) override;
};

#endif // WORDVECTORMAPREPOSITORY_HPP
