set(APP_NAME "UnitTest")
file(GLOB cpp_files "*.cpp")
add_executable(${APP_NAME} ${cpp_files} )

target_link_libraries(${APP_NAME}  CommonUtility Catch2::Catch2WithMain nlohmann_json::nlohmann_json )
