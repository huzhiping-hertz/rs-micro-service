cmake_minimum_required (VERSION 3.10)
project ("MicroService" C CXX)

IF (WIN32)
    message("-- Compiling under Windows platform")
     #windows下编译动态库时生成symbols文件(lib文件)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_PATH_SPLITER_=92)
    # 引入lib異常，解決error LNK2026: module unsafe for SAFESEH
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO ")		# 程序输出文件为exe文件时起作用
    set(CMAKE_SHARED_LINKR_FLAGS "${CMAKE_SHARED_LINKR_FLAGS} /SAFESEH:NO ")	# 程序输出文件为dll文件时起作用
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKR_FLAGS} /SAFESEH:NO ")	# 程序输出文件为lib文件时起作用
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")	# 程序输出文件为module文件时起作用

ELSEIF (UNIX)
    message("-- Compiling under Linux platform")
    add_definitions(-D_PATH_SPLITER_=47)
ENDIF ()

set(CMake_CXX_STANDARD 20)
set(CMake_CXX_STANDARD_REQUARED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Poco)
find_package(gflags)
find_package(Drogon)
find_package(Catch2)
find_package(nlohmann_json)
find_package(ZeroMQ)
find_package(spdlog)

#链接库搜索路径

INCLUDE_DIRECTORIES(Exlibs)
LINK_DIRECTORIES(Exlibs)

INCLUDE_DIRECTORIES(./)

#库文件输出路径、执行文件输出路径
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#拷贝配置文件到bin目录
file(COPY ${PROJECT_SOURCE_DIR}/config.txt DESTINATION ${PROJECT_SOURCE_DIR}/bin/${VERSION})

#项目源码
INCLUDE_DIRECTORIES(Tools/)
add_subdirectory(Tools)
#add_subdirectory(Examples)
#add_subdirectory(GateWay)
#add_subdirectory(DomainModel)
#add_subdirectory(WebApi)
#add_subdirectory(WebSocket)
#add_subdirectory(TCP)
#add_subdirectory(RpcServer)
#add_subdirectory(VXI11)
add_subdirectory(UnitTest)