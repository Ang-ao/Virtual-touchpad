cmake_minimum_required(VERSION 3.20)

project(Vtouchpad LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
if(Qt5_FOUND)
    message("Qt5_FOUND")
endif()

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32)
else()
    add_executable(${PROJECT_NAME} src/VMouse.h)
endif()


file(GLOB sources CONFIGURE_DEPENDS res/res.qrc src/*.cpp src/*.h)

target_sources(${PROJECT_NAME} PUBLIC ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)

