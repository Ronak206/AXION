#include "Repositories/StopWordRepository.hpp"
#include "Queries/StopWordQueries.hpp"
#include <iostream>

std::optional<int> StopWordRepository::add(const StopWord& stopWord) {
    if (!connection) {
        std::cerr << "Add Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec_params(StopWordQueries::INSERT, stopWord.stopWord);
        txn.commit();

        if (!res.empty()) {
            return res[0][0].as<int>();  // Return the generated ID
        }
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
    return std::nullopt;  // Return -1 on failure
}

std::optional<StopWord> StopWordRepository::find(int id) {
    if (!connection) {
        std::cerr << "Find Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(StopWordQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            StopWord stopWord;
            stopWord.id = res[0][0].as<int>();
            stopWord.stopWord = res[0][1].c_str();
            return stopWord;
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << " (Query: " <<
                  StopWordQueries::SELECT_BY_ID << ")" << std::endl;
    }
    return std::nullopt;
}

bool StopWordRepository::isStopword(const std::string& word) {
    if (!connection) {
        std::cerr << "Check Error: Database connection is null!" << std::endl;
        return false;
    }

    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(StopWordQueries::CHECK_EXISTS, word);

        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        std::cerr << "Check Error: " << e.what() << " (Query: " <<
                  StopWordQueries::CHECK_EXISTS << ")" << std::endl;
    }
    return false;
}

void StopWordRepository::update(const StopWord& stopWord) {
    if (!connection) {
        std::cerr << "Update Error: Database connection is null!" << std::endl;
        return;
    }

    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::UPDATE, stopWord.stopWord, stopWord.id);
        txn.commit();
        std::cout << "Updated stop word ID " << stopWord.id << " -> " <<
                  stopWord.stopWord << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << " (Query: " <<
                  StopWordQueries::UPDATE << ")" << std::endl;
    }
}

void StopWordRepository::remove(int id) {
    if (!connection) {
        std::cerr << "Delete Error: Database connection is null!" << std::endl;
        return;
    }

    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::DELETE, id);
        txn.commit();
        std::cout << "Deleted stop word ID " << id << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << " (Query: " <<
                  StopWordQueries::DELETE << ")" << std::endl;
    }
}

void StopWordRepository::removeByWord(const std::string& word) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::DELETE_BY_WORD, word);
        txn.commit();
        std::cout << "Deleted stopword: " << word << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << std::endl;
    }
}
