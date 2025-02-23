// StopwordRemover.hpp
#ifndef STOPWORDREMOVER_HPP
#define STOPWORDREMOVER_HPP

#include <string>
#include <vector>

#include "Repositories/StopWordRepository.hpp"

class StopwordRemover {
    StopWordRepository stopwordRepository;

  public:
    StopwordRemover() : stopwordRepository(stopwordRepository) {}
    std::vector<std::string> removeStopWords(const std::vector<std::string> &
            tokens);
};

#endif // LEMMATIZER_HPP