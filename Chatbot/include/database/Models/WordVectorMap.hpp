#ifndef WORDVECTORMAP_HPP
#define WORDVECTORMAP_HPP

#include "Model.hpp"
#include <string>
#include <vector>

struct WordVectorMap : public Model {
    std::string word;
    std::vector<double> value;

    WordVectorMap() {}
    WordVectorMap(int id, std::string word, std::vector<double> value) : Model(id),
        word(word), value(value) {}
};

#endif // WORDVECTORMAP_HPP
