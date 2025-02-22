// test_wordtovector.cpp
#include <gtest/gtest.h>
#include "Repositories/WordVectorMapRepository.hpp"

class WordVectorMapRepositoryTest : public ::testing::Test {
  protected:
    std::shared_ptr<pqxx::connection> conn;
    WordVectorMapRepository* repo;

    void SetUp() override {
        conn = std::make_shared<pqxx::connection>("dbname=chatbot_db user=testuser password=testpass host=127.0.0.1");
        repo = new WordVectorMapRepository(conn);
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

TEST_F(WordVectorMapRepositoryTest, InsertAndFindByWord) {
    WordVectorMap wordVec = {0, "AI", {0.1, 0.2, 0.3}};
    auto id = repo->add(wordVec);
    ASSERT_TRUE(id.has_value());

    auto retrieved = repo->findByWord("AI");
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ(retrieved->word, "AI");
    EXPECT_EQ(retrieved->value.size(), 3);
    EXPECT_DOUBLE_EQ(retrieved->value[0], 0.1);
}

TEST_F(WordVectorMapRepositoryTest, UpdateVectorByWord) {
    WordVectorMap wordVec = {0, "updateTest", {1.0, 1.0, 1.0}};
    auto id = repo->add(wordVec);
    ASSERT_TRUE(id.has_value());

    std::vector<double> newVector = {2.0, 2.0, 2.0};
    repo->updateByWord("updateTest", newVector);

    auto updated = repo->findByWord("updateTest");
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->value.size(), 3);
    EXPECT_DOUBLE_EQ(updated->value[0], 2.0);
}
