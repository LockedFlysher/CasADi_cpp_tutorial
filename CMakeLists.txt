cmake_minimum_required(VERSION 3.29)
project(CasADi_tutorial)

set(CMAKE_CXX_STANDARD 20)

find_package(casadi REQUIRED)

find_library(CASADI_LIBRARY
        NAMES casadi
        HINTS ${CASADI_INCLUDE_DIR}/../lib $ENV{CASADI_PREFIX}/lib)
if(CASADI_LIBRARY)
    set(CASADI_LIBRARIES ${CASADI_LIBRARIES} ${CASADI_LIBRARY})
endif()

include_directories(include
    ${casadi_INCLUDE_DIRS}
)

add_executable(chapter1 chapter1-SX.cpp)
add_executable(chapter2 chapter2-DM.cpp)
add_executable(chapter3 chapter3-Function.cpp)
add_executable(chapter4 chapter4-OptimalProblem.cpp)
add_executable(chapter5 chapter5-GenCode.cpp)


target_link_libraries(chapter1 ${CASADI_LIBRARIES})
target_link_libraries(chapter2 ${CASADI_LIBRARIES})
target_link_libraries(chapter3 ${CASADI_LIBRARIES})
target_link_libraries(chapter4 ${CASADI_LIBRARIES})
target_link_libraries(chapter5 ${CASADI_LIBRARIES})
