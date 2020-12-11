cmake_minimum_required(VERSION 3.14)

add_executable(regexplore
    regex_engine.cpp
    regex_explore_widget.cpp
    regexplore.main.cpp
)

target_link_libraries(regexplore PRIVATE cppurses)

include(GNUInstallDirs)
install(TARGETS regexplore
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
