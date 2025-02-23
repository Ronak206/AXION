// test_chatlog.cpp
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
        pqxx::work txn(*conn);
    
        // Truncate tables (removes data while preserving schema)
        txn.exec("TRUNCATE TABLE chat_logs, stopwords, word_to_vector, lemma CASCADE;");
    
        // Reset sequences safely (without requiring ownership)
        txn.exec("SELECT setval(pg_get_serial_sequence('chat_logs', 'id'), 1, false);");
        txn.exec("SELECT setval(pg_get_serial_sequence('stopwords', 'id'), 1, false);");
        txn.exec("SELECT setval(pg_get_serial_sequence('word_to_vector', 'id'), 1, false);");
        txn.exec("SELECT setval(pg_get_serial_sequence('lemma', 'id'), 1, false);");
    
        txn.commit();
        delete repo;
    }
    
};

TEST_F(ChatLogRepositoryTest, InsertAndFind) {
    ChatLog log = {0, "What is AI?", "AI stands for Artificial Intelligence."};
    auto id = repo->add(log);
    ASSERT_TRUE(id.has_value());

    auto retrieved = repo->find(id.value());
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ(retrieved->question, "What is AI?");
    EXPECT_EQ(retrieved->answer, "AI stands for Artificial Intelligence.");
}

TEST_F(ChatLogRepositoryTest, Update) {
    ChatLog log = {0, "Old Question", "Old Answer"};
    auto id = repo->add(log);
    ASSERT_TRUE(id.has_value());

    log.id = id.value();
    log.question = "New Question";
    log.answer = "New Answer";
    repo->update(log);

    auto updated = repo->find(id.value());
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->question, "New Question");
    EXPECT_EQ(updated->answer, "New Answer");
}

TEST_F(ChatLogRepositoryTest, Delete) {
    ChatLog log = {0, "To be deleted?", "Yes"};
    auto id = repo->add(log);
    ASSERT_TRUE(id.has_value());

    repo->remove(id.value());
    auto deleted = repo->find(id.value());

    EXPECT_FALSE(deleted.has_value());
}
