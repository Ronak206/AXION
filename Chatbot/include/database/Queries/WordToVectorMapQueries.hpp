#ifndef WORDVECTOR_QUERIES_HPP
#define WORDVECTOR_QUERIES_HPP

namespace WordVectorMapQueries {
constexpr const char* INSERT =
    "INSERT INTO word_to_vector (word, vector) VALUES ($1, $2) RETURNING id;";

constexpr const char* SELECT_BY_ID =
    "SELECT id, word, vector FROM word_to_vector WHERE id = $1;";

constexpr const char* UPDATE =
    "UPDATE word_to_vector SET word = $1, vector = $2 WHERE id = $3;";

constexpr const char* DELETE = "DELETE FROM word_to_vector WHERE id = $1;";
}

#endif // WORDVECTOR_QUERIES_HPP
