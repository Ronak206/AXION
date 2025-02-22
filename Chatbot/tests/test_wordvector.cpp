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
        delete repo;
    }
};

TEST_F(WordVectorMapRepositoryTest, InsertAndFindByWord) {
    WordVectorMap wordVec = {0, "AI", {0.1, 0.2, 0.3}};
    repo->add(wordVec);

    auto retrieved = repo->findByWord("AI");

    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ(retrieved->word, "AI");
    EXPECT_EQ(retrieved->value.size(), 3);
    EXPECT_DOUBLE_EQ(retrieved->value[0], 0.1);
}

TEST_F(WordVectorMapRepositoryTest, UpdateVectorByWord) {
    WordVectorMap wordVec = {0, "updateTest", {1.0, 1.0, 1.0}};
    repo->add(wordVec);

    std::vector<double> newVector = {2.0, 2.0, 2.0};
    repo->updateByWord("updateTest", newVector);

    auto updated = repo->findByWord("updateTest");
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->value.size(), 3);
    EXPECT_DOUBLE_EQ(updated->value[0], 2.0);
}
