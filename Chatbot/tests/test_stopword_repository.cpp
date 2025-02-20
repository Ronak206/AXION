#include <iostream>
#include <cassert>
#include "Repositories/StopWordRepository.hpp"

void test_stopword_repository() {
    std::cout << "Running StopWordRepository tests...\n";

    Connection conn = Database::getConnection();
    StopWordRepository repo(conn);

    // Create test entry
    StopWord stopword;
    stopword.stopWord = "the";

    repo.add(stopword);

    // Retrieve the entry
    StopWord retrieved = repo.find(1);

    // Delete the entry
    repo.remove(1);
    StopWord deleted = repo.find(1);

    std::cout << "All StopWordRepository tests passed!\n";
}

int main() {
    test_stopword_repository();
    return 0;
}
