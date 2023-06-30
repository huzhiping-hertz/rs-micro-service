set(utility_library_name "ZmqMessager")
file(GLOB ZmqMessager_SRCS "*.cpp")
file(GLOB ZmqMessager_HEAD "*.h")

add_library(${utility_library_name} STATIC ${ZmqMessager_HEAD} ${ZmqMessager_SRCS})
target_link_libraries(${utility_library_name} nlohmann_json::nlohmann_json gflags::gflags libzmq-static CommonUtility)
