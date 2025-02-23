#include "InputProcessor.hpp"

std::string InputProcessor::toLower(const std::string& text) {
    std::string lowerText = text;
    std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(),
                   ::tolower);
    return lowerText;
}

std::vector<std::string> InputProcessor::processInput(const std::string&
        input) {
    std::string lowerInput = toLower(input);
    std::vector<std::string> tokens = tokenizer.tokenize(lowerInput);
    std::vector<std::string> processedTokens;
    tokens = stopwordRemover.removeStopWords(tokens);

    for (const std::string& token : tokens) {
        std::string lemma = lemmatizer.lemmatize(token);
        processedTokens.push_back(lemma);
    }
    return processedTokens;
}
