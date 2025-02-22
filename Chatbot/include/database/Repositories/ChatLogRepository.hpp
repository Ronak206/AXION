#ifndef CHATLOGREPOSITORY_HPP
#define CHATLOGREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/ChatLog.hpp"

class ChatLogRepository : public Repository<ChatLog> {
  public:
    ChatLogRepository(Connection connection)
        : Repository<ChatLog>(connection) {}
    int add(const ChatLog& log) override;
    std::optional<ChatLog> find(int id) override;
    std::optional<ChatLog> findByQuestion(const std::string &);
    std::optional<ChatLog> findByAnswer(const std::string &);
    void update(const ChatLog& log) override;
    void remove(int id) override;
};

#endif // CHATLOGREPOSITORY_HPP
