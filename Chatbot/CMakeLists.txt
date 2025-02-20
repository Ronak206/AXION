cmake_minimum_required(VERSION 3.10)
project(Chatbot)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(include include/database)

# Find PostgreSQL (libpqxx)
find_package(PostgreSQL REQUIRED)

# Define the main executable
add_executable(chatbot src/main.cpp src/chatbot.cpp src/nlp.cpp src/utils.cpp src/database/Database.cpp)

# Link the PostgreSQL library
target_link_libraries(chatbot pqxx pq)

# Add the test executables
add_executable(test_database tests/test_database_connection.cpp src/database/Database.cpp)
target_link_libraries(test_database pqxx pq)

# Add ChatLogRepository test
add_executable(test_chat_log 
    tests/test_chat_log_repository.cpp 
    src/database/Database.cpp 
    src/database/Repositories/ChatLogRepository.cpp)
target_link_libraries(test_chat_log pqxx pq)

# Add StopWordRepository test
add_executable(test_stopword 
    tests/test_stopword_repository.cpp 
    src/database/Database.cpp 
    src/database/Repositories/StopWordRepository.cpp)
target_link_libraries(test_stopword pqxx pq)

# Add WordVectorMapRepository test
add_executable(test_word_vector_map 
    tests/test_word_vector_map_repository.cpp 
    src/database/Database.cpp 
    src/database/Repositories/WordVectorMapRepository.cpp)
target_link_libraries(test_word_vector_map pqxx pq)
