cmake_minimum_required(VERSION 3.2)
project(RegExplore)

add_executable(regexplore
    src/main.cpp
    src/regex_engine.cpp
    src/top_bar.cpp
    src/target_text_section.cpp
    src/textbox_highlight.cpp
    src/regex_explore_widget.cpp
    src/match_box.cpp
    src/options_page.cpp
    src/reference_page.cpp
    src/options_and_reference.cpp
    src/match_page.cpp
    src/options_box.cpp
)

target_compile_options(regexplore PUBLIC -Wall)
target_compile_features(regexplore PUBLIC cxx_std_14)
target_link_libraries(regexplore PUBLIC ncurses pthread
    /usr/local/lib64/libcppurses.a)

include(GNUInstallDirs)
install(TARGETS regexplore
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
