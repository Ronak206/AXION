#ifndef CHATLOGREPOSITORY_HPP
#define CHATLOGREPOSITORY_HPP

#include "Repository.hpp"
#include "Models/ChatLog.hpp"

class ChatLogRepository : public Repository<ChatLog> {
  public:
    ChatLogRepository(Connection connection)
        : Repository<ChatLog>(connection) {}
    void add(const ChatLog& log) override;
    ChatLog find(int id) override;
    void update(const ChatLog& log) override;
    void remove(int id) override;
};

#endif // CHATLOGREPOSITORY_HPP
