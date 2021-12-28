cmake_minimum_required(VERSION 3.13)
project(ProjectExquisite VERSION 0.1.0)
set(BUILD_TESTS OFF)
set(BUILD_STATIC_LIB ON)


#Downloading git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE ext/ppconsul/conanfile.txt BASIC_SETUP KEEP_PATHS)
conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP BUILD_TYPE "Release")


add_executable(ProjectExquisite src/main.cpp src/ClientUser/ClientUser.cpp src/Dataserver/Dataserver.cpp)
target_link_libraries(ProjectExquisite ${CONAN_LIBS})

link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

add_subdirectory("ext/mysql-connector-cpp")
target_link_libraries(connector PRIVATE "crypt32.lib")
target_link_libraries(ProjectExquisite connector)

add_subdirectory("ext/ppconsul")
target_link_libraries(ProjectExquisite ppconsul)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
