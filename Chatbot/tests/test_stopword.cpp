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
        delete repo;
    }
};

TEST_F(StopWordRepositoryTest, InsertAndCheckExists) {
    StopWord sw = {0, "the"};
    repo->add(sw);

    EXPECT_TRUE(repo->isStopword("the"));
    EXPECT_FALSE(repo->isStopword("randomword"));
}

TEST_F(StopWordRepositoryTest, DeleteByWord) {
    StopWord sw = {0, "deleteMe"};
    repo->add(sw);

    repo->removeByWord("deleteMe");

    EXPECT_FALSE(repo->isStopword("deleteMe"));
}
