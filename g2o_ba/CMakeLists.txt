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

set(G2O_LIBRARIES ${PROJECT_SOURCE_DIR}/thirdparty/g2o/lib/libg2o_openmp.so)

include_directories(
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

file(GLOB INCLUDES include/*.h*)
file(GLOB SRC src/*.c*)

# target_link_libraries(
#     ${OpenCV_LIBS}
#     ${G2O_LIBRARIES}
# )

add_executable(g2o_driver ${SRC})
# target_link_libraries(g2o_ba ${PROJECT_NAME})