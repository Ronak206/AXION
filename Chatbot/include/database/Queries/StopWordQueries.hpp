#ifndef STOPWORD_QUERIES_HPP
#define STOPWORD_QUERIES_HPP

namespace StopWordQueries {

constexpr const char* INSERT = R"(
    INSERT INTO stopwords (stopword) 
    VALUES ($1) 
    RETURNING id;
)";

constexpr const char* SELECT_BY_ID = R"(
    SELECT id, stopword 
    FROM stopwords 
    WHERE id = $1;
)";

constexpr const char* CHECK_EXISTS = R"(
    SELECT EXISTS(
        SELECT 1 
        FROM stopwords 
        WHERE stopword = $1
    );
)";

constexpr const char* UPDATE = R"(
    UPDATE stopwords 
    SET stopword = $1 
    WHERE id = $2;
)";

constexpr const char* DELETE = R"(
    DELETE FROM stopwords 
    WHERE id = $1;
)";

constexpr const char* DELETE_BY_WORD = R"(
    DELETE FROM stopwords 
    WHERE stopword = $1;
)";

} // namespace StopWordQueries

#endif // STOPWORD_QUERIES_HPP
