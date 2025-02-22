#include "Repositories/ChatLogRepository.hpp"
#include "Queries/ChatLogQueries.hpp"
#include <iostream>
#include <optional>

int ChatLogRepository::add(const ChatLog& log) {
    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec_params(ChatLogQueries::INSERT, log.question,
                                           log.answer);
        txn.commit();

        if (!res.empty()) {
            return res[0][0].as<int>();  // Return the generated ID
        }
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
    return -1;  // Return -1 on failure
}


std::optional<ChatLog> ChatLogRepository::find(int id) {
    if (!connection) {
        std::cerr << "Find Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(ChatLogQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            ChatLog log;
            log.id = res[0][0].as<int>();
            log.question = res[0][1].c_str();
            log.answer = res[0][2].c_str();
            return log;
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << " (Query: " <<
                  ChatLogQueries::SELECT_BY_ID << ")" << std::endl;
    }
    return std::nullopt;
}

std::optional<ChatLog> ChatLogRepository::findByQuestion(
    const std::string& question) {
    if (!connection) {
        std::cerr << "Find Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(ChatLogQueries::SELECT_BY_QUESTION,
                                           question);

        if (!res.empty()) {
            ChatLog log;
            log.id = res[0][0].as<int>();
            log.question = res[0][1].c_str();
            log.answer = res[0][2].c_str();
            return log;
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << " (Query: " <<
                  ChatLogQueries::SELECT_BY_QUESTION << ")" << std::endl;
    }
    return std::nullopt;
}

std::optional<ChatLog> ChatLogRepository::findByAnswer(const std::string&
        answer) {
    if (!connection) {
        std::cerr << "Find Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(ChatLogQueries::SELECT_BY_ANSWER, answer);

        if (!res.empty()) {
            ChatLog log;
            log.id = res[0][0].as<int>();
            log.question = res[0][1].c_str();
            log.answer = res[0][2].c_str();
            return log;
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << " (Query: " <<
                  ChatLogQueries::SELECT_BY_ANSWER << ")" << std::endl;
    }
    return std::nullopt;
}

void ChatLogRepository::update(const ChatLog& log) {
    if (!connection) {
        std::cerr << "Update Error: Database connection is null!" << std::endl;
        return;
    }

    try {
        pqxx::work txn(*connection);
        txn.exec_params(ChatLogQueries::UPDATE, log.question, log.answer, log.id);
        txn.commit();
        std::cout << "Updated chat log ID " << log.id << " -> " << log.question << " : "
                  << log.answer << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << " (Query: " <<
                  ChatLogQueries::UPDATE << ")" << std::endl;
    }
}

void ChatLogRepository::remove(int id) {
    if (!connection) {
        std::cerr << "Delete Error: Database connection is null!" << std::endl;
        return;
    }

    try {
        pqxx::work txn(*connection);
        txn.exec_params(ChatLogQueries::DELETE, id);
        txn.commit();
        std::cout << "Deleted chat log ID " << id << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << " (Query: " <<
                  ChatLogQueries::DELETE << ")" << std::endl;
    }
}
