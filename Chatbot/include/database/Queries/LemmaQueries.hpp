#ifndef LEMMA_QUERIES_HPP
#define LEMMA_QUERIES_HPP

namespace LemmaQueries {

constexpr const char* INSERT = R"(
    INSERT INTO lemma (word, lemma) 
    VALUES ($1, $2) 
    RETURNING id;
)";

constexpr const char* SELECT_BY_ID = R"(
    SELECT id, word, lemma 
    FROM lemma 
    WHERE id = $1;
)";

constexpr const char* SELECT_BY_WORD = R"(
    SELECT id, word, lemma 
    FROM lemma 
    WHERE word = $1;
)";

constexpr const char* SELECT_BY_LEMMA = R"(
    SELECT id, word, lemma 
    FROM lemma 
    WHERE lemma = $1;
)";

constexpr const char* UPDATE = R"(
    UPDATE lemma 
    SET word = $1, lemma = $2 
    WHERE id = $3;
)";

constexpr const char* DELETE = R"(
    DELETE FROM lemma 
    WHERE id = $1;
)";

constexpr const char* DELETE_BY_WORD = R"(
    DELETE FROM lemma 
    WHERE word = $1;
)";

} // namespace LemmaQueries

#endif // LEMMA_QUERIES_HPP
