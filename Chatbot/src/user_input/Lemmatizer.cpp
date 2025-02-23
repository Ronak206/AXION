#include "Lemmatizer.hpp"

std::string Lemmatizer::lemmatize(const std::string& word) {
    Lemma lemmaRow = lemmaRepository.findByWord(word)[0];
    return lemmaRow.lemma;
}