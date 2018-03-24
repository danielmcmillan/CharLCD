cmake_minimum_required (VERSION 2.6)
project (CharLCD)

add_executable(CharLCD )
target_include_directories(DockKeypad PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_include_directories(DockKeypad PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Link to system WiringPi
find_library(wiringPi_LIB wiringPi)
if(NOT wiringPi_LIB)
  message(FATAL_ERROR "wiringPi library not found")
endif()
target_link_libraries(DockKeypad ${wiringPi_LIB})
target_link_libraries(DockKeypad ${wiringPi_LIB})
