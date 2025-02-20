#ifndef CHATLOG_HPP
#define CHATLOG_HPP

#include "Model.hpp"
#include <string>

struct ChatLog : public Model {
    std::string question;
    std::string answer;
};

#endif // CHATLOG_HPP
