cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (CharLCD)

SET(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_library(CharLCD ${SRC_DIR}/LCDBackend.cpp ${SRC_DIR}/LCDController.cpp ${SRC_DIR}/Symbols.cpp)
target_include_directories(CharLCD PRIVATE ${SRC_DIR})
target_include_directories(CharLCD PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Link to system WiringPi
find_library(wiringPi_LIB wiringPi)
find_library(wiringPiDev_LIB wiringPiDev)
if(NOT wiringPi_LIB OR NOT wiringPiDev_LIB)
  message(FATAL_ERROR "wiringPi library not found")
endif()
target_link_libraries(CharLCD ${wiringPi_LIB})
target_link_libraries(CharLCD ${wiringPiDev_LIB})

add_executable(bounce ${SRC_DIR}/bounce.cpp)
target_include_directories(bounce PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(bounce CharLCD)