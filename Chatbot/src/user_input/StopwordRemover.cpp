#include "StopwordRemover.hpp"

std::vector<std::string> StopwordRemover::removeStopWords(
    const std::vector<std::string> & tokens
) {
    std::vector<std::string> processedTokens;
    for(auto token : tokens) {
        if(stopwordRepository.isStopword(token)) {
            continue;
        }
        processedTokens.push_back(token);
    }
    return processedTokens;
}
