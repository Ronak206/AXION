#include "Repositories/WordVectorMapRepository.hpp"
#include "Queries/WordToVectorMapQueries.hpp"
#include <iostream>

int WordVectorMapRepository::add(const WordVectorMap& wordVector) {
    try {
        pqxx::work txn(*connection);
        pqxx::result res = txn.exec_params(WordVectorMapQueries::INSERT,
                                           wordVector.word, wordVector.value);
        txn.commit();

        if (!res.empty()) {
            return res[0][0].as<int>();  // Return the generated ID
        }
    } catch (const std::exception &e) {
        std::cerr << "Insert Error: " << e.what() << std::endl;
    }
    return -1;  // Return -1 on failure
}

std::optional<WordVectorMap> WordVectorMapRepository::find(int id) {
    WordVectorMap wordVector;
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(WordVectorMapQueries::SELECT_BY_ID, id);

        if (!res.empty()) {
            wordVector.id = res[0][0].as<int>();
            wordVector.word = res[0][1].c_str();

            // Convert PostgreSQL array (stored as string) to std::vector<double>
            std::string vector_str = res[0][2].c_str();  // Read as a string
            std::stringstream ss(vector_str.substr(1,
                                                   vector_str.size() - 2)); // Remove '{' and '}'
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

std::optional<WordVectorMap> WordVectorMapRepository::findByWord(
    const std::string & word) {
    try {
        pqxx::nontransaction txn(*connection);
        pqxx::result res = txn.exec_params(WordVectorMapQueries::SELECT_BY_WORD, word);

        if (!res.empty()) {
            WordVectorMap wordVector;
            wordVector.id = res[0][0].as<int>();
            wordVector.word = res[0][1].c_str();

            // Convert PostgreSQL array to std::vector<double>
            std::string vector_str = res[0][2].c_str();
            std::stringstream ss(vector_str.substr(1,
                                                   vector_str.size() - 2)); // Remove '{' and '}'
            std::vector<double> values;
            std::string value;
            while (std::getline(ss, value, ',')) {
                values.push_back(std::stod(value));
            }
            wordVector.value = values;

            return wordVector;
        }
    } catch (const std::exception &e) {
        std::cerr << "FindByWord Error: " << e.what() << std::endl;
    }
    return std::nullopt;
}

std::optional<WordVectorMap> WordVectorMapRepository::findByVector(
    const std::vector<double> &vector) {
    try {
        pqxx::nontransaction txn(*connection);

        // Convert vector to PostgreSQL array format
        std::ostringstream vectorStream;
        vectorStream << "{";
        for (size_t i = 0; i < vector.size(); ++i) {
            if (i > 0) vectorStream << ",";
            vectorStream << vector[i];
        }
        vectorStream << "}";

        pqxx::result res = txn.exec_params(WordVectorMapQueries::SELECT_BY_VECTOR,
                                           vectorStream.str());

        if (!res.empty()) {
            WordVectorMap wordVector;
            wordVector.id = res[0][0].as<int>();
            wordVector.word = res[0][1].c_str();

            // Convert PostgreSQL array to std::vector<double>
            std::string vector_str = res[0][2].c_str();
            std::stringstream ss(vector_str.substr(1,
                                                   vector_str.size() - 2)); // Remove '{' and '}'
            std::vector<double> values;
            std::string value;
            while (std::getline(ss, value, ',')) {
                values.push_back(std::stod(value));
            }
            wordVector.value = values;

            return wordVector;
        }
    } catch (const std::exception &e) {
        std::cerr << "FindByVector Error: " << e.what() << std::endl;
    }
    return std::nullopt;
}


void WordVectorMapRepository::update(const WordVectorMap& wordVector) {
    try {
        pqxx::work txn(*connection);

        // Convert vector to PostgreSQL array format
        std::ostringstream vectorStream;
        vectorStream << "{";
        for (size_t i = 0; i < wordVector.value.size(); ++i) {
            if (i > 0) vectorStream << ",";
            vectorStream << wordVector.value[i];
        }
        vectorStream << "}";

        txn.exec_params(WordVectorMapQueries::UPDATE, wordVector.word,
                        vectorStream.str(), wordVector.id);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Update Error: " << e.what() << std::endl;
    }
}

void WordVectorMapRepository::updateByWord(const std::string& word,
        const std::vector<double>& newVector) {
    try {
        pqxx::work txn(*connection);

        // Convert std::vector<double> to PostgreSQL array string format
        std::stringstream vector_str;
        vector_str << "{";
        for (size_t i = 0; i < newVector.size(); i++) {
            if (i > 0) vector_str << ",";
            vector_str << newVector[i];
        }
        vector_str << "}";

        // Execute update query
        txn.exec_params(WordVectorMapQueries::UPDATE_BY_WORD, vector_str.str(), word);
        txn.commit();
        std::cout << "Updated vector for word: " << word << std::endl;
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
