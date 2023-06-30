set(APP_NAME "RpcServer")
file(GLOB cpp_files "*.cpp")
add_executable(${APP_NAME} ${cpp_files}  )
target_link_libraries(${APP_NAME} PUBLIC  CommonUtility gflags nlohmann_json::nlohmann_json )