cmake_minimum_required(VERSION 3.10)
project(Bot-cleaner)

set(CMAKE_CXX_COMPILER /usr/bin/c++)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(vendor/tgbot-cpp)

find_package(OpenSSL REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/vendor/tgbot-cpp/libTgBot.a OpenSSL::SSL OpenSSL::Crypto)