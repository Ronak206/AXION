// InputProcessor.hpp
#ifndef INPUT_PROCESSOR_HPP
#define INPUT_PROCESSOR_HPP

#include "Tokenizer.hpp"
#include "Lemmatizer.hpp"
#include "StopwordRemover.hpp"
#include <string>
#include <vector>

class InputProcessor {
  private:
    Tokenizer tokenizer;
    Lemmatizer lemmatizer;
    StopwordRemover stopwordRemover;

    std::string toLower(const std::string& text);

  public:
    InputProcessor(
        Tokenizer tokenizer,
        Lemmatizer lemmatizer,
        StopwordRemover stopwordRemover
    ): tokenizer(tokenizer),
        lemmatizer(lemmatizer),
        stopwordRemover(stopwordRemover) {}

    std::vector<std::string> processInput(const std::string& input);
};

#endif // INPUT_PROCESSOR_HPP