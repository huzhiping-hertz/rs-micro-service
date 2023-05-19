cmake_minimum_required (VERSION 3.10)
project ("RMService" C CXX)

set(CMake_CXX_STANDARD 20)
set(CMake_CXX_STANDARD_REQUARED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Poco)
find_package(gflags)
find_package(Drogon)
find_package(Catch2)
find_package(nlohmann_json)

message(${CMAKE_BUILD_TYPE})
#链接库搜索路径
INCLUDE_DIRECTORIES(Exlibs/LteUl)
INCLUDE_DIRECTORIES(Exlibs/SystemUtility)
LINK_DIRECTORIES(Exlibs)

INCLUDE_DIRECTORIES(./)

#库文件输出路径、执行文件输出路径
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#拷贝配置文件到bin目录
file(COPY ${PROJECT_SOURCE_DIR}/config.txt DESTINATION ${PROJECT_SOURCE_DIR}/bin/${VERSION})

#项目源码
add_subdirectory(CommonUtility)
add_subdirectory(DomainModel)
add_subdirectory(WebApi)
add_subdirectory(UnitTest)