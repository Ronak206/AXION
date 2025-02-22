#ifndef CHATLOG_QUERIES_HPP
#define CHATLOG_QUERIES_HPP

namespace ChatLogQueries {

constexpr const char* INSERT = R"(
    INSERT INTO chat_logs (question, answer) 
    VALUES ($1, $2) 
    RETURNING id;
)";

constexpr const char* SELECT_BY_ID = R"(
    SELECT id, question, answer 
    FROM chat_logs 
    WHERE id = $1;
)";

constexpr const char* SELECT_BY_QUESTION = R"(
    SELECT id, question, answer 
    FROM chat_logs 
    WHERE question = $1;
)";

constexpr const char* SELECT_BY_ANSWER = R"(
    SELECT id, question, answer 
    FROM chat_logs 
    WHERE answer = $1;
)";

constexpr const char* UPDATE = R"(
    UPDATE chat_logs 
    SET question = $1, answer = $2 
    WHERE id = $3;
)";

constexpr const char* DELETE = R"(
    DELETE FROM chat_logs 
    WHERE id = $1;
)";

} // namespace ChatLogQueries

#endif // CHATLOG_QUERIES_HPP
