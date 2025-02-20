#include "Repositories/StopWordRepository.hpp"
#include "Queries/StopWordQueries.hpp"
#include <iostream>

void StopWordRepository::add(const StopWord& stopWord) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::INSERT, stopWord.stopWord);
        txn.commit();
        std::cout << "Inserted stop word: " << stopWord.stopWord << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
}

StopWord StopWordRepository::find(int id) {
    StopWord stopWord;
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(StopWordQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            stopWord.id = res[0][0].as<int>();
            stopWord.stopWord = res[0][1].c_str();
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << std::endl;
    }
    return stopWord;
}

void StopWordRepository::update(const StopWord& stopWord) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::UPDATE, stopWord.stopWord, stopWord.id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << std::endl;
    }
}

void StopWordRepository::remove(int id) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(StopWordQueries::DELETE, id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << std::endl;
    }
}
