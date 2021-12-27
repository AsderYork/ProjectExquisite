cmake_minimum_required(VERSION 3.12)
project(ProjectExquisite VERSION 0.1.0)
set(BUILD_TESTS OFF)
set(BUILD_STATIC_LIB ON)

add_executable(ProjectExquisite src/main.cpp src/ClientUser/ClientUser.cpp)

add_subdirectory("ext/ppconsul")
target_link_libraries(ProjectExquisite ppconsul)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
conan_target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
