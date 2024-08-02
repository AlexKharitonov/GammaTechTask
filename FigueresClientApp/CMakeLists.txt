set(PROJECT_NAME FigueresClientApp)

project (${PROJECT_NAME})

message(STATUS "${PROJECT_NAME} setup")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_PACK Qt${QT_MAJOR_REQUIRED})

find_package(Qt${QT_MAJOR_REQUIRED} 
             ${QT_MIN_REQUIRED_VERSION} 
             COMPONENTS Core Gui Widgets Network 
             REQUIRED)

set(PROJECT_SOURCES "main.cc"
                    "MainWindow.hpp"
                    "MainWindow.cc"
                    "ItemsConsumer.hpp"
                    "ItemsScene.hpp"
                    "ItemsScene.cc"
                    "Table.hpp"
                    "Table.cc"
                    "ItemsManager/ItemsManager.hpp"
                    "ItemsManager/ItemsManager.cc"
                    "FiguresClient/FiguresClient.hpp"
                    "FiguresClient/FiguresClient.cc"
                    "Figures/FigureBase.hpp"
                    "resources/resources.qrc")

# Generating API header.
add_subdirectory(FiguresClient)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/FiguresClient/FiguresClient)

add_executable (${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})

add_dependencies(${PROJECT_NAME} GenerateFlatBuffers)

target_include_directories(${PROJECT_NAME} PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
                     ${QT_PACK}::Core
                     ${QT_PACK}::Widgets
                     ${QT_PACK}::Network 
                     flatbuffers)

# Bring Qt libs to executable file.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${QT_WINDEPLOY_PATH}
                   "$<TARGET_FILE:${PROJECT_NAME}>")