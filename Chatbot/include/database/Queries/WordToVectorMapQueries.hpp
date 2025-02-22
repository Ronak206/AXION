#ifndef WORDVECTOR_QUERIES_HPP
#define WORDVECTOR_QUERIES_HPP

namespace WordVectorMapQueries {

constexpr const char* INSERT = R"(
    INSERT INTO word_to_vector (word, value) 
    VALUES ($1, $2) 
    RETURNING id;
)";

constexpr const char* SELECT_BY_ID = R"(
    SELECT id, word, value 
    FROM word_to_vector 
    WHERE id = $1;
)";

constexpr const char* SELECT_BY_WORD = R"(
    SELECT id, word, value 
    FROM word_to_vector 
    WHERE word = $1 
    LIMIT 1;
)";

constexpr const char* SELECT_BY_VECTOR = R"(
    SELECT id, word, value 
    FROM word_to_vector 
    WHERE value = $1 
    LIMIT 1;
)";

constexpr const char* UPDATE = R"(
    UPDATE word_to_vector 
    SET word = $1, value = $2 
    WHERE id = $3;
)";

constexpr const char* UPDATE_BY_WORD = R"(
    UPDATE word_to_vector 
    SET value = $1 
    WHERE word = $2;
)";

constexpr const char* DELETE = R"(
    DELETE FROM word_to_vector 
    WHERE id = $1;
)";

} // namespace WordVectorMapQueries

#endif // WORDVECTOR_QUERIES_HPP
