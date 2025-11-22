cmake_minimum_required(VERSION 3.19)
project(ElectricDiagrams LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(ElectricDiagrams
    WIN32 MACOSX_BUNDLE
    main.cpp
    window.cpp
    window.h
    window.ui
    renderarea.h renderarea.cpp
)

target_link_libraries(ElectricDiagrams
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(ElectricDiagrams PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS ElectricDiagrams
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ElectricDiagrams
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
