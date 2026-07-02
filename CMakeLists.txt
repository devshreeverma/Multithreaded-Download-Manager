cmake_minimum_required(VERSION 3.16)

project(MultithreadedDownloadManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(CURL REQUIRED)

add_executable(download_manager
    src/main.cpp
    src/HTTPClient.cpp
)

target_link_libraries(download_manager CURL::libcurl)