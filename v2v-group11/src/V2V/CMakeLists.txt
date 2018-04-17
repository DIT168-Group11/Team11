cmake_minimum_required(VERSION 3.5)

project(group11-V2V)

set(CMAKE_CXX_STANDARD 14)

# libcluon is needed to run
find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/Messages.cpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND cluon-msc --cpp-sources --cpp-add-include-file=Messages.hpp --out=${CMAKE_BINARY_DIR}/Messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Messages.odvd
        COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/Messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/Messages.odvd
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Messages.odvd)

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/DriveMessages.cpp
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND cluon-msc --cpp-sources --cpp-add-include-file=DriveMessages.hpp --out=${CMAKE_BINARY_DIR}/DriveMessages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/DriveMessages.odvd
        COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/DriveMessages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/DriveMessages.odvd
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/DriveMessages.odvd)

include_directories(SYSTEM ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/V2VService.cpp ${CMAKE_BINARY_DIR}/Messages.cpp ${CMAKE_BINARY_DIR}/DriveMessages.cpp)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
