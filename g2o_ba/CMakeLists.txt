cmake_minimum_required(VERSION 2.8)
project(pba_g2o_compare)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release)
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-register -std=c++11")

find_package(OpenCV QUIET)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
endif()

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

find_package(Eigen3 3.1.0 REQUIRED)

set(G2O_LIBRARIES ${PROJECT_SOURCE_DIR}/thirdparty/g2o/lib/libg2o.so)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
${EIGEN3_INCLUDE_DIR}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file(GLOB INCLUDES include/*.h*)
file(GLOB SRC src/*.c*)

add_executable(g2o_driver ${SRC})

target_link_libraries(g2o_driver
    ${OpenCV_LIBS}
    ${G2O_LIBRARIES}
    ${EIGEN3_LIBS}
)
# target_link_libraries(g2o_ba ${PROJECT_NAME})