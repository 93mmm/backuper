cmake_minimum_required(VERSION 3.5)

project(Backuper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(nlohmann_json 3.2.0 REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/helpers/helpers.h
        src/helpers/helpers.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
        src/ui/widget.cpp
        src/ui/widget.h
        src/ui/widget.ui
        src/json/config.json
)

set(RESOURCE_FILES
        src/json/config.json
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Backuper
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Backuper APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Backuper SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Backuper
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Backuper 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE nlohmann_json::nlohmann_json
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Backuper)
endif()
set_target_properties(Backuper PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    RESOURCE "${RESOURCE_FILES}"
)

include(GNUInstallDirs)
install(TARGETS Backuper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Backuper)
endif()
