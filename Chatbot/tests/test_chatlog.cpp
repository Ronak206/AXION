#include <gtest/gtest.h>
#include "Repositories/ChatLogRepository.hpp"

class ChatLogRepositoryTest : public ::testing::Test {
  protected:
    std::shared_ptr<pqxx::connection> conn;
    ChatLogRepository* repo;

    void SetUp() override {
        conn = std::make_shared<pqxx::connection>("dbname=chatbot_db user=testuser password=testpass host=127.0.0.1");
        repo = new ChatLogRepository(conn);
    }

    void TearDown() override {
        delete repo;
    }
};

TEST_F(ChatLogRepositoryTest, InsertAndFind) {
    ChatLog log = {0, "What is AI?", "AI stands for Artificial Intelligence."};
    int id = repo->add(log);
    auto retrieved = repo->find(id);

    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ(retrieved->question, "What is AI?");
    EXPECT_EQ(retrieved->answer, "AI stands for Artificial Intelligence.");
}

TEST_F(ChatLogRepositoryTest, Update) {
    ChatLog log = {0, "Old Question", "Old Answer"};
    int id = repo->add(log);

    log.id = id;
    log.question = "New Question";
    log.answer = "New Answer";
    repo->update(log);

    auto updated = repo->find(id);
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->question, "New Question");
    EXPECT_EQ(updated->answer, "New Answer");
}

TEST_F(ChatLogRepositoryTest, Delete) {
    ChatLog log = {0, "To be deleted?", "Yes"};
    int id = repo->add(log);

    repo->remove(id);
    auto deleted = repo->find(id);

    EXPECT_FALSE(deleted.has_value());
}
