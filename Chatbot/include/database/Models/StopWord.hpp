#ifndef STOPWORD_HPP
#define STOPWORD_HPP

#include "Model.hpp"
#include <string>

struct StopWord : public Model {
    std::string stopWord;
};

#endif // STOPWORD_HPP
