set(utility_library_name "DomainModel")
file(GLOB UTILITY_SRCS "*.cpp")
add_library(${utility_library_name} STATIC ${UTILITY_SRCS})
target_link_libraries(${utility_library_name}  Poco::Poco Poco::Foundation Poco::Net nlohmann_json::nlohmann_json CommonUtility Trantor::Trantor)