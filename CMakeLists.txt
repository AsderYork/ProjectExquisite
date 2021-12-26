cmake_minimum_required(VERSION 3.0.0)
project(ProjectExquisite VERSION 0.1.0)

include(CTest)
enable_testing()


file(GLOB ProjectExquisiteSrc "src/*.h" "src/*.cpp")
add_executable(ProjectExquisite ${ProjectExquisiteSrc})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
