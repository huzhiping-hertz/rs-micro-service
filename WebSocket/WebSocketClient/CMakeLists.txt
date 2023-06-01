set(CMAKE_CXX_STANDARD 20)

find_package(Drogon CONFIG REQUIRED)
include(CheckIncludeFileCXX)

set(APP_NAME "WebSocketClient")
file(GLOB cpp_files "*.cpp")
add_executable(${APP_NAME} ${cpp_files})
target_link_libraries(${APP_NAME} PUBLIC Drogon::Drogon gflags CommonUtility )


