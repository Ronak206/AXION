// test_stopword.cpp
#include <gtest/gtest.h>
#include "Repositories/StopWordRepository.hpp"

class StopWordRepositoryTest : public ::testing::Test {
  protected:
    std::shared_ptr<pqxx::connection> conn;
    StopWordRepository* repo;

    void SetUp() override {
        conn = std::make_shared<pqxx::connection>("dbname=chatbot_db user=testuser password=testpass host=127.0.0.1");
        repo = new StopWordRepository(conn);
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

TEST_F(StopWordRepositoryTest, InsertAndCheckExists) {
    StopWord sw = {0, "the"};
    auto id = repo->add(sw);
    ASSERT_TRUE(id.has_value());

    EXPECT_TRUE(repo->isStopword("the"));
    EXPECT_FALSE(repo->isStopword("randomword"));
}

TEST_F(StopWordRepositoryTest, DeleteByWord) {
    StopWord sw = {0, "deleteMe"};
    auto id = repo->add(sw);
    ASSERT_TRUE(id.has_value());

    repo->removeByWord("deleteMe");
    EXPECT_FALSE(repo->isStopword("deleteMe"));
}
