cmake_minimum_required(VERSION 3.16)

project(LookFor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(LookFor
    cpp/main.cpp
)

qt_add_qml_module(LookFor
    URI LookFor
    VERSION 1.0

    SOURCES cpp/Backend.h cpp/Backend.cpp
    SOURCES cpp/FoundFile.h cpp/FoundFile.cpp

    QML_FILES qml/Main.qml
    QML_FILES qml/delegates/PathDelegate.qml
    QML_FILES qml/delegates/ImageDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(LookFor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LookFor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    # WIN32_EXECUTABLE TRUE
    WIN32_EXECUTABLE FALSE # allows to start application from cmd and view their stdout
)

target_link_libraries(LookFor
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS LookFor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
