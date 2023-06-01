set(APP_NAME "DataGateWay")
file(GLOB cpp_files "*.cpp")
ADD_EXECUTABLE(${APP_NAME} ${cpp_files})
target_link_libraries(${APP_NAME} Poco::Util Poco::JSON  gflags ZmqMessager CommonUtility )
