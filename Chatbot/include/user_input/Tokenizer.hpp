// Tokenizer.hpp
#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <string>

class Tokenizer {
public:
    std::vector<std::string> tokenize(const std::string& text);
};

#endif // TOKENIZER_HPP