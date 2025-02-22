#ifndef WORDVECTORMAPREPOSITORY_HPP
#define WORDVECTORMAPREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/WordVectorMap.hpp"

class WordVectorMapRepository : public Repository<WordVectorMap> {
  public:
    WordVectorMapRepository(Connection connection)
        : Repository<WordVectorMap>(connection) {}
    std::optional<int> add(const WordVectorMap& wordVector) override;
    std::optional<WordVectorMap> find(int id) override;
    std::optional<WordVectorMap> findByWord(const std::string & word);
    std::optional<WordVectorMap> findByVector(const std::vector<double> & value);
    void update(const WordVectorMap& wordVector) override;
    void updateByWord(
        const std::string & word,
        const std::vector<double> & newVector);
    void remove(int id) override;
};

#endif // WORDVECTORMAPREPOSITORY_HPP
