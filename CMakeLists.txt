cmake_minimum_required(VERSION 3.19)
project(Sketcher LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Core Svg Xml)

qt_standard_project_setup()
qt_add_executable(Sketcher
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    DrawingArea.cpp
    DrawingArea.h
)

target_link_libraries(Sketcher
    PRIVATE
        Qt::Widgets
        Qt::Core
        Qt::Svg
        Qt::Xml
)

include(GNUInstallDirs)

install(TARGETS Sketcher
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Sketcher
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

add_library(RectanglePlugin SHARED RectanglePlugin.cpp)
target_link_libraries(RectanglePlugin PRIVATE Qt6::Core Qt6::Gui)
set_target_properties(RectanglePlugin PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)