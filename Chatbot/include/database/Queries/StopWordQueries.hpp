#ifndef STOPWORD_QUERIES_HPP
#define STOPWORD_QUERIES_HPP

namespace StopWordQueries {
constexpr const char* INSERT =
    "INSERT INTO stopwords (word) VALUES ($1) RETURNING id;";

constexpr const char* SELECT_BY_ID =
    "SELECT id, word FROM stopwords WHERE id = $1;";

constexpr const char* UPDATE =
    "UPDATE stopwords SET word = $1 WHERE id = $2;";

constexpr const char* DELETE = "DELETE FROM stopwords WHERE id = $1;";
}

#endif // STOPWORD_QUERIES_HPP
