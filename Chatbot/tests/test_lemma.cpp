#include <gtest/gtest.h>
#include "Repositories/LemmaRepository.hpp"

class LemmaRepositoryTest : public ::testing::Test {
  protected:
    std::shared_ptr<pqxx::connection> conn;
    LemmaRepository* repo;

    void SetUp() override {
        conn = std::make_shared<pqxx::connection>("dbname=chatbot_db user=testuser password=testpass host=127.0.0.1");
        repo = new LemmaRepository(conn);
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

TEST_F(LemmaRepositoryTest, InsertAndFind) {
    Lemma lemma{0, "running", "run"};
    auto id = repo->add(lemma);
    ASSERT_TRUE(id.has_value());

    auto retrieved = repo->find(id.value());
    ASSERT_TRUE(retrieved.has_value());
    EXPECT_EQ(retrieved->word, "running");
    EXPECT_EQ(retrieved->lemma, "run");
}

TEST_F(LemmaRepositoryTest, FindByWord) {
    Lemma lemma{0, "jumping", "jump"};
    repo->add(lemma);

    auto results = repo->findByWord("jumping");
    ASSERT_FALSE(results.empty());
    EXPECT_EQ(results[0].lemma, "jump");
}

TEST_F(LemmaRepositoryTest, Update) {
    Lemma lemma{0, "old", "outdated"};
    auto id = repo->add(lemma);
    ASSERT_TRUE(id.has_value());

    lemma.id = id.value();
    lemma.lemma = "new";
    repo->update(lemma);

    auto updated = repo->find(id.value());
    ASSERT_TRUE(updated.has_value());
    EXPECT_EQ(updated->lemma, "new");
}

TEST_F(LemmaRepositoryTest, Delete) {
    Lemma lemma{0, "obsolete", "old"};
    auto id = repo->add(lemma);
    ASSERT_TRUE(id.has_value());

    repo->remove(id.value());
    auto deleted = repo->find(id.value());
    EXPECT_FALSE(deleted.has_value());
}
