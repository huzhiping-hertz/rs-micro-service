set(utility_library_name "snmp")
file(GLOB UTILITY_SRCS "*.cpp")
add_library(${utility_library_name} STATIC ${UTILITY_SRCS})
target_link_libraries(${utility_library_name}  Wsnmp32.lib Wsock32.lib)