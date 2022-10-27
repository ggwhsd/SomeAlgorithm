CMAKE_MINIMUM_REQUIRED(VERSION 3.12.3) #cmake最低版本要求。
PROJECT(SomeProblemAlgorithm) #项目名称。
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    message("Debug mode (CMAKE_C_FLAGS):${CMAKE_C_FLAGS_DEBUG}")
    message("Debug mode (CMAKE_CXX_FLAGS):${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    message("Release mode (CMAKE_C_FLAGS):${CMAKE_C_FLAGS_RELEASE}")
    message("Release mode (CMAKE_CXX_FLAGS):${CMAKE_CXX_FLAGS_RELEASE}")
else()
    message("default mode:${CMAKE_BUILD_TYPE}")
    message("default (CMAKE_C_FLAGS):${CMAKE_C_FLAGS_RELEASE}")
    message("default (CMAKE_CXX_FLAGS):${CMAKE_C_FLAGS_RELEASE}")
endif()

AUX_SOURCE_DIRECTORY(. SRC_LIST) #把当前目录(.)下所有源代码文件和头文件加入变量SRC_LIST
ADD_EXECUTABLE(SomeProblemAlgorithm ${SRC_LIST}) #生成应用程序 hello (在windows下会自动生成hello.exe)

