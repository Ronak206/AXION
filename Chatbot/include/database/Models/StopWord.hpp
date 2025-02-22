#ifndef STOPWORD_HPP
#define STOPWORD_HPP

#include "Model.hpp"
#include <string>

struct StopWord : public Model {
    std::string stopWord;

    StopWord() {}
    StopWord(int id, std::string stopword) : Model(id), stopWord(stopword) {}
};

#endif // STOPWORD_HPP
