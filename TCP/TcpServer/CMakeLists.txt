set(APP_NAME "TcpServer")
file(GLOB cpp_files "*.cpp")
add_executable(${APP_NAME} ${cpp_files}  )
target_link_libraries(${APP_NAME} PUBLIC   CommonUtility gflags Poco::Poco Poco::Foundation Poco::Net nlohmann_json::nlohmann_json )