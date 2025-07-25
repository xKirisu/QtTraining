cmake_minimum_required(VERSION 3.16)

project(QtTraining VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtTraining
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

        lessons/lesson1.h lessons/lesson1.cpp lessons/lesson1.ui
        lessons/lesson2.h lessons/lesson2.cpp lessons/lesson2.ui
        lessons/lesson3.h lessons/lesson3.cpp lessons/lesson3.ui
        lessons/lesson4.h lessons/lesson4.cpp lessons/lesson4.ui
        lessons/lesson5.h lessons/lesson5.cpp lessons/lesson5.ui
        tictactoe.h tictactoe.cpp tictactoe.ui

        lessons/models/userl3.h
        lessons/models/userl3model.h lessons/models/userl3model.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtTraining APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtTraining SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtTraining
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QtTraining PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QtTraining)
endif()
set_target_properties(QtTraining PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtTraining
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtTraining)
endif()

# Extendends

find_package(Qt6 REQUIRED COMPONENTS Widgets)
target_link_libraries(QtTraining PRIVATE Qt6::Widgets)

find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(QtTraining PRIVATE Qt6::Core)

find_package(Qt6 REQUIRED COMPONENTS PrintSupport)
target_link_libraries(QtTraining PRIVATE Qt6::PrintSupport)

find_package(Qt6 REQUIRED COMPONENTS Sql)
target_link_libraries(QtTraining PRIVATE Qt6::Sql)
