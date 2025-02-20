#include <iostream>
#include <cassert>
#include "Repositories/WordVectorMapRepository.hpp"

void test_word_vector_map_repository() {
    std::cout << "Running WordVectorMapRepository tests...\n";

    Connection conn = Database::getConnection();
    WordVectorMapRepository repo(conn);

    // Create test entry
    WordVectorMap wvm;
    wvm.word = "hello";
    wvm.value = {0.1, 0.2, 0.3, 0.4};

    repo.add(wvm);

    // Retrieve the entry
    WordVectorMap retrieved = repo.find(1);

    // Update the entry
    retrieved.value = {0.5, 0.6, 0.7, 0.8};
    repo.update(retrieved);

    WordVectorMap updated = repo.find(1);

    // Delete the entry
    repo.remove(1);
    WordVectorMap deleted = repo.find(1);

    std::cout << "All WordVectorMapRepository tests passed!\n";
}

int main() {
    test_word_vector_map_repository();
    return 0;
}
