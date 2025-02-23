#include <iostream>
#include <csignal>

#include "Utils.hpp"
#include "Chatbot.hpp"
#include "InputProcessor.hpp"
#include "Repositories/ChatLogRepository.hpp"
#include "Repositories/LemmaRepository.hpp"
#include "Repositories/StopWordRepository.hpp"
#include "Repositories/WordVectorMapRepository.hpp"

int main() {
    signal(SIGINT, Utils::handleExit);

    std::string userInput;
    printf("Chatbot: Hello! Let's chat. Type 'exit' to stop.");

    while (true) {
        std::cout << "You: ";
        getline(std::cin, userInput);

        if (userInput == "exit") break;

        Connection connection = Database::getConnection();

        ChatLogRepository chatLogRepository = ChatLogRepository(connection);
        LemmaRepository lemmaRepository = LemmaRepository(connection);
        StopWordRepository stopwordRepository = StopWordRepository(connection);
        WordVectorMapRepository wordVectorMapRepository = WordVectorMapRepository(
                    connection);

        Tokenizer tokenizer = Tokenizer();
        Lemmatizer lemmatizer = Lemmatizer(lemmaRepository);
        StopwordRemover stopwordRemover = StopwordRemover();

        InputProcessor inputProcessor(
            tokenizer,
            lemmatizer,
            stopwordRemover
        );

        std::vector<std::string> tokens = inputProcessor.processInput(userInput);

        Chatbot chatbot(chatLogRepository, wordVectorMapRepository);

        std::string response = chatbot.ask(userInput);

        std::cout << "Chatbot: " << response << std::endl;
    }

    // NeuralNetChatbot bot;
    // globalBot = &bot;

    // std::string botResponse = bot.predict(userInput);
    // std::cout << "Chatbot: " << botResponse << std::endl;
    // if (botResponse == "I'm not sure about that. Can you explain more?"
    //         || botResponse == "Can you tell me more?") {
    //     std::cout << "Teach me! What should I reply?\nYou: ";
    //     std::string response;
    //     getline(std::cin, response);
    //     bot.train(userInput, response);
    //     std::cout << "Chatbot: Got it! I'll remember that." << endl;
    // }

    // bot.saveTrainingData();
    // cout << "Chatbot: It was great talking to you. Goodbye!" << endl;
    // return 0;
}