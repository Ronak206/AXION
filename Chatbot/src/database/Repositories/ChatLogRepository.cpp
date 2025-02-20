#include "Repositories/ChatLogRepository.hpp"
#include "Queries/ChatLogQueries.hpp"
#include <iostream>

void ChatLogRepository::add(const ChatLog& log) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(ChatLogQueries::INSERT, log.question, log.answer);
        txn.commit();
        std::cout << "Inserted chat log: " << log.question << " -> " << log.answer <<
                  std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
}

ChatLog ChatLogRepository::find(int id) {
    ChatLog log;
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(ChatLogQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            log.id = res[0][0].as<int>();
            log.question = res[0][1].c_str();
            log.answer = res[0][2].c_str();
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << std::endl;
    }
    return log;
}

void ChatLogRepository::update(const ChatLog& log) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(ChatLogQueries::UPDATE, log.question, log.answer, log.id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << std::endl;
    }
}

void ChatLogRepository::remove(int id) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(ChatLogQueries::DELETE, id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << std::endl;
    }
}
