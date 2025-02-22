#ifndef LEMMA_REPOSITORY_HPP
#define LEMMA_REPOSITORY_HPP

#include "Repository.hpp"
#include "Models/Lemma.hpp"
#include <vector>
#include <optional>

class LemmaRepository : public Repository<Lemma> {
  public:
    // Constructor
    explicit LemmaRepository(Connection connection) : Repository(connection) {}

    // CRUD Operations
    std::optional<int> add(const Lemma &);
    std::optional<Lemma> find(int id);
    std::vector<Lemma> findByWord(const std::string& word);
    std::vector<Lemma> findByLemma(const std::string& lemma);
    void update(const Lemma &);
    void remove(int id);
    void removeByWord(const std::string& word);
};

#endif // LEMMA_REPOSITORY_HPP
