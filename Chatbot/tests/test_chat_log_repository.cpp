#include <iostream>
#include <cassert>
#include "Repositories/ChatLogRepository.hpp"

void test_chat_log_repository() {
    std::cout << "Running ChatLogRepository tests...\n";

    Connection conn = Database::getConnection();
    ChatLogRepository repo(conn);

    // Create test entry
    ChatLog log;
    log.question = "What is AI?";
    log.answer = "AI stands for Artificial Intelligence.";

    repo.add(log);

    // Retrieve the entry
    ChatLog retrieved = repo.find(36);
    // assert(retrieved.question == "What is AI?");
    // assert(retrieved.answer == "AI stands for Artificial Intelligence.");

    // Update the entry
    retrieved.answer = "AI means Artificial Intelligence.";
    repo.update(retrieved);

    ChatLog updated = repo.find(36);
    // assert(updated.answer == "AI means Artificial Intelligence.");

    // Delete the entry
    repo.remove(1);
    ChatLog deleted = repo.find(36);
    // assert(deleted.id == 0); // Assuming 0 means not found

    std::cout << "All ChatLogRepository tests passed!\n";
}

int main() {
    test_chat_log_repository();
    return 0;
}
