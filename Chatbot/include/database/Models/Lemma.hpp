#ifndef LEMMA_HPP
#define LEMMA_HPP

#include <string>

class Lemma {
  public:
    int id;
    std::string word;
    std::string lemma;

    // Constructors
    Lemma() = default;
    Lemma(int id, std::string word, std::string lemma)
        : id(id), word(std::move(word)), lemma(std::move(lemma)) {}

    // Destructor
    ~Lemma() = default;
};

#endif // LEMMA_HPP
