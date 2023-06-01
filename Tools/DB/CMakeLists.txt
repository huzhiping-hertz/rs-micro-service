set(library_name "DBBase")
file(GLOB UTILITY_SRCS "*.cpp")
add_library(${library_name} STATIC ${UTILITY_SRCS})
target_link_libraries(${library_name}  Poco::Util Poco::JSON  Poco::Data  Poco::DataSQLite  gflags)