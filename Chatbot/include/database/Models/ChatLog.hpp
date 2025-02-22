#ifndef CHATLOG_HPP
#define CHATLOG_HPP

#include "Model.hpp"
#include <string>

struct ChatLog : public Model {
    std::string question;
    std::string answer;

    ChatLog() {}

    ChatLog(int id, std::string question, std::string answer) : Model(id),
        question(question), answer(answer) {}
};

#endif // CHATLOG_HPP
