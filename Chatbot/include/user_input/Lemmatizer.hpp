// Lemmatizer.hpp
#ifndef LEMMATIZER_HPP
#define LEMMATIZER_HPP

#include "Repositories/LemmaRepository.hpp"
#include <string>

class Lemmatizer {
  private:
    LemmaRepository lemmaRepository;

  public:
    Lemmatizer(LemmaRepository lemmaRepository): lemmaRepository(lemmaRepository) {}
    std::string lemmatize(const std::string& word);
};

#endif // LEMMATIZER_HPP