#include "Repositories/LemmaRepository.hpp"
#include "Queries/LemmaQueries.hpp"
#include <iostream>

std::optional<int> LemmaRepository::add(const Lemma& lemma) {
    if (!connection) {
        std::cerr << "Add Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }

    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec_params(LemmaQueries::INSERT, lemma.word,
                                           lemma.lemma);
        txn.commit();

        if (!res.empty()) {
            return res[0][0].as<int>();  // Return the generated ID
        }
    } catch (const std::exception& e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
    return std::nullopt;
}

std::optional<Lemma> LemmaRepository::find(int id) {
    if (!connection) {
        std::cerr << "Find Error: Database connection is null!" << std::endl;
        return std::nullopt;
    }
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(LemmaQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            return Lemma(res[0][0].as<int>(), res[0][1].c_str(), res[0][2].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "Find Error: " << e.what() << std::endl;
    }
    return std::nullopt;
}

std::vector<Lemma> LemmaRepository::findByWord(const std::string& word) {
    std::vector<Lemma> lemmas;
    if (!connection) {
        std::cerr << "FindByWord Error: Database connection is null!" << std::endl;
        return lemmas;
    }
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(LemmaQueries::SELECT_BY_WORD, word);

        for (const auto& row : res) {
            lemmas.emplace_back(row[0].as<int>(), row[1].c_str(), row[2].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "FindByWord Error: " << e.what() << std::endl;
    }
    return lemmas;
}

std::vector<Lemma> LemmaRepository::findByLemma(const std::string& lemma) {
    std::vector<Lemma> lemmas;
    if (!connection) {
        std::cerr << "FindByLemma Error: Database connection is null!" << std::endl;
        return lemmas;
    }
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(LemmaQueries::SELECT_BY_LEMMA, lemma);

        for (const auto& row : res) {
            lemmas.emplace_back(row[0].as<int>(), row[1].c_str(), row[2].c_str());
        }
    } catch (const std::exception& e) {
        std::cerr << "FindByLemma Error: " << e.what() << std::endl;
    }
    return lemmas;
}

void LemmaRepository::update(const Lemma& lemma) {
    if (!connection) {
        std::cerr << "Update Error: Database connection is null!" << std::endl;
        return;
    }
    try {
        pqxx::work txn(*connection);
        txn.exec_params(LemmaQueries::UPDATE, lemma.word, lemma.lemma, lemma.id);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Update Error: " << e.what() << std::endl;
    }
}

void LemmaRepository::remove(int id) {
    if (!connection) {
        std::cerr << "Remove Error: Database connection is null!" << std::endl;
        return;
    }
    try {
        pqxx::work txn(*connection);
        txn.exec_params(LemmaQueries::DELETE, id);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "Remove Error: " << e.what() << std::endl;
    }
}

void LemmaRepository::removeByWord(const std::string& word) {
    if (!connection) {
        std::cerr << "RemoveByWord Error: Database connection is null!" << std::endl;
        return;
    }
    try {
        pqxx::work txn(*connection);
        txn.exec_params(LemmaQueries::DELETE_BY_WORD, word);
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "RemoveByWord Error: " << e.what() << std::endl;
    }
}
