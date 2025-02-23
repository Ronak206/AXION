cmake_minimum_required(VERSION 3.10)
project(Chatbot)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(include include/database include/user_input include/core)
include_directories(${GTEST_INCLUDE_DIRS})

# Find PostgreSQL (libpqxx)
find_package(PostgreSQL REQUIRED)
find_package(GTest REQUIRED)

# Define the main executable
# add_executable(chatbot src/main.cpp src/database/Database.cpp)

# Link the PostgreSQL library
# target_link_libraries(chatbot pqxx pq)

# Add the test executables
add_executable(test_database tests/database/test_database_connection.cpp src/database/Database.cpp)
target_link_libraries(test_database pqxx pq)

add_executable(run_tests 
    tests/test_main.cpp 
    tests/database/test_chatlog.cpp 
    tests/database/test_stopword.cpp 
    tests/database/test_wordvector.cpp 
    tests/database/test_wordvector.cpp 
    tests/database/test_lemma.cpp 
    src/database/Repositories/ChatLogRepository.cpp 
    src/database/Repositories/StopWordRepository.cpp 
    src/database/Repositories/WordVectorMapRepository.cpp
    src/database/Repositories/LemmaRepository.cpp
)

# Link against GTest, pthread, and pqxx
target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread pqxx pq)

