#include "Repositories/WordVectorMapRepository.hpp"
#include "Queries/WordToVectorMapQueries.hpp"
#include <iostream>

void WordVectorMapRepository::add(const WordVectorMap& wordVector) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(WordVectorMapQueries::INSERT, wordVector.word,
                        wordVector.value);
        txn.commit();
        std::cout << "Inserted word vector: " << wordVector.word << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
}

WordVectorMap WordVectorMapRepository::find(int id) {
    WordVectorMap wordVector;
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(WordVectorMapQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            wordVector.id = res[0][0].as<int>();
            wordVector.word = res[0][1].c_str();

            // Convert PostgreSQL array (stored as string) to std::vector<double>
            std::string vector_str = res[0][2].c_str();  // Read as a string
            std::stringstream ss(vector_str.substr(1, vector_str.size() - 2)); // Remove '{' and '}'
            std::vector<double> values;
            std::string value;

            while (std::getline(ss, value, ',')) {
                values.push_back(std::stod(value));  // Convert each value to double
            }

            wordVector.value = values;
        }
    } catch (const std::exception &e) {
        std::cerr << "Find Error: " << e.what() << std::endl;
    }
    return wordVector;
}

void WordVectorMapRepository::update(const WordVectorMap& wordVector) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(WordVectorMapQueries::UPDATE, wordVector.word, wordVector.value,
                        wordVector.id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << std::endl;
    }
}

void WordVectorMapRepository::remove(int id) {
    try {
        pqxx::work txn(*connection);
        txn.exec_params(WordVectorMapQueries::DELETE, id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Delete Error: " << e.what() << std::endl;
    }
}
