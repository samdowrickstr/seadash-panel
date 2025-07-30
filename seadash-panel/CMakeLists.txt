cmake_minimum_required(VERSION 3.16)
project(seadash-panel LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR}
    REQUIRED COMPONENTS
        Quick
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    QtAwesome/QtAwesome.cpp
    QtAwesome/QtAwesomeAnim.cpp
)

if(QT_VERSION VERSION_LESS 5.15)
    qt5_add_resources(PROJECT_SOURCES qml.qrc QtAwesome/QtAwesomeFree.qrc)
elseif(QT_VERSION VERSION_LESS 6.2)
    qt_add_resources(PROJECT_SOURCES qml.qrc QtAwesome/QtAwesomeFree.qrc)
endif()

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if(QT_VERSION VERSION_GREATER_EQUAL 6.2)
    qt_add_qml_module(${PROJECT_NAME}
        URI seadash-panel
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml/"
        QML_FILES
            TitleBarWindow.qml
    )
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Quick
        Qt::Widgets
)


if(Qt6_FOUND)
    qt_import_qml_plugins(${PROJECT_NAME})
endif()
