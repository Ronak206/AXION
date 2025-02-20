#ifndef CHATLOG_QUERIES_HPP
#define CHATLOG_QUERIES_HPP

namespace ChatLogQueries {
constexpr const char* INSERT =
    "INSERT INTO chat_log (question, answer) VALUES ($1, $2) RETURNING id;";

constexpr const char* SELECT_BY_ID =
    "SELECT id, question, answer FROM chat_log WHERE id = $1;";

constexpr const char* UPDATE =
    "UPDATE chat_log SET question = $1, answer = $2 WHERE id = $3;";

constexpr const char* DELETE = "DELETE FROM chat_log WHERE id = $1;";
}

#endif // CHATLOG_QUERIES_HPP
