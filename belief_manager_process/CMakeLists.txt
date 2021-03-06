cmake_minimum_required(VERSION 2.8.3)
project(belief_manager_process)

## ================= Compiler-specific C++11 activation =================

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
    message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater.")
  endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
  message(FATAL_ERROR "Your C++ compiler does not support C++11.")
endif ()

add_definitions(-std=c++11)

## ================= Set project variables ==================

set(BELIEF_MANAGER_PROCESS_SOURCE_DIR src/source)

set(BELIEF_MANAGER_PROCESS_INCLUDE_DIR src/include)

set(BELIEF_MANAGER_PROCESS_SOURCE_FILES
  ${BELIEF_MANAGER_PROCESS_SOURCE_DIR}/belief_manager_process.cpp
  ${BELIEF_MANAGER_PROCESS_SOURCE_DIR}/belief_manager_process_main.cpp
)

set(BELIEF_MANAGER_PROCESS_HEADER_FILES
  ${BELIEF_MANAGER_PROCESS_INCLUDE_DIR}/belief_manager_process.h
)

## ================= Find catkin macros and libraries =================

find_package(catkin REQUIRED COMPONENTS
  roscpp
  drone_process
  belief_manager
  std_msgs
  droneMsgsROS
)
## ================= Catkin specific configuration =================

catkin_package(
  CATKIN_DEPENDS
  roscpp
  drone_process
  belief_manager
  droneMsgsROS
  DEPENDS yaml-cpp
)

## ================= Build =================

include_directories(${BELIEF_MANAGER_PROCESS_INCLUDE_DIR})
include_directories(${catkin_INCLUDE_DIRS})

add_library(
  belief_manager_process_lib
  ${BELIEF_MANAGER_PROCESS_SOURCE_FILES}
  ${BELIEF_MANAGER_PROCESS_HEADER_FILES}
)
add_dependencies(belief_manager_process_lib ${catkin_EXPORTED_TARGETS})
target_link_libraries(belief_manager_process_lib ${catkin_LIBRARIES})

add_executable(
  belief_manager_process_main
  ${BELIEF_MANAGER_PROCESS_SOURCE_DIR}/belief_manager_process_main.cpp
)
add_dependencies(belief_manager_process_main ${catkin_EXPORTED_TARGETS})
target_link_libraries(belief_manager_process_main belief_manager_process_lib)
target_link_libraries(belief_manager_process_main ${catkin_LIBRARIES})
target_link_libraries(belief_manager_process_lib yaml-cpp)

if(CATKIN_ENABLE_TESTING)
  find_package(rostest REQUIRED)
  add_rostest_gtest(
    belief_manager_process_test
    launch/belief_manager_process.launch
    src/test/belief_manager_process_test.cpp
  )
  target_link_libraries(belief_manager_process_test ${catkin_LIBRARIES})
endif()
