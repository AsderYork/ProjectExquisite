cmake_minimum_required(VERSION 3.12)
project(ProjectExquisite VERSION 0.1.0)
set(BUILD_TESTS OFF)
set(BUILD_STATIC_LIB ON)
set(WITH_MYSQL ON)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(ProjectExquisite src/main.cpp src/ClientUser/ClientUser.cpp)
target_link_libraries(ProjectExquisite ${CONAN_LIBS})

link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

target_link_libraries(ProjectExquisite crypt32)
add_subdirectory("ext/mysql-connector-cpp")
target_link_libraries(ProjectExquisite connector)

add_subdirectory("ext/ppconsul")
target_link_libraries(ProjectExquisite ppconsul)

configure_file("ext/libcurl/libcurl.dll" "bin/libcurl.dll" COPYONLY)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
