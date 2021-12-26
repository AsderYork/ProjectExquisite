cmake_minimum_required(VERSION 3.12)
project(ProjectExquisite VERSION 0.1.0)
set(BUILD_TESTS OFF)
set(BUILD_STATIC_LIB ON)

include(CTest)
enable_testing()

add_executable(ProjectExquisite src/main.cpp src/ClientUser/ClientUser.cpp)

message("This will be compiled")
message("${ProjectExquisiteSrc}")


add_subdirectory("ext/ppconsul")

target_link_libraries(ProjectExquisite ppconsul)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
