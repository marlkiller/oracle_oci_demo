cmake_minimum_required(VERSION 3.28)
project(oracle_oci_demo)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Od")

message("CMAKE_SOURCE_DIR is : ${CMAKE_SOURCE_DIR}")

file(GLOB Main ${CMAKE_SOURCE_DIR}/*.cpp)
file(GLOB MainHeader ${CMAKE_SOURCE_DIR}/*.h)
file(GLOB OracleClient ${CMAKE_SOURCE_DIR}/ocis/instantclient_23_4)

file(GLOB StaticLibs ${OracleClient}/sdk/lib/msvc/*.lib)

include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${OracleClient}/sdk/include/
)


## 编译为 bin 可执行程序
add_executable(${PROJECT_NAME}
        ${Main}
        ${MainHeader}
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTION})
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTION})



message("CMAKE_BUILD_TYPE is : ${CMAKE_BUILD_TYPE}")


# 需要指定 CMAKE_BUILD_TYPE Debug/Release eg: -D CMAKE_BUILD_TYPE=Debug
# Debug 模式下,需要link 名字中有 d 的 lib, 比如
# Debug: oraocci23d.lib , Release: oraocci23.lib
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    foreach(lib IN LISTS StaticLibs)
        if(lib MATCHES "oraocci23\\.lib$")
            message(STATUS "Removing library: ${lib}")
            list(REMOVE_ITEM StaticLibs ${lib})
        elseif(lib MATCHES "oraoccixxxxxxxxx\\.lib$")
            message(STATUS "Removing library: ${lib}")
            list(REMOVE_ITEM StaticLibs ${lib})
        endif()
    endforeach()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    foreach(lib IN LISTS StaticLibs)
        if(lib MATCHES "oraocci23d\\.lib$")
            message(STATUS "Removing library: ${lib}")
            list(REMOVE_ITEM StaticLibs ${lib})
        elseif(lib MATCHES "oraoccixxxxxxxxxd\\.lib$")
            message(STATUS "Removing library: ${lib}")
            list(REMOVE_ITEM StaticLibs ${lib})
        endif()
    endforeach()
else ()
endif ()

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${StaticLibs}
)



# install ;
#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/release)