cmake_minimum_required(VERSION 3.2)
project(RegexExplore)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

# LIBRARY
add_library(regex_explore STATIC
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
    src/regex_store.cpp
)

target_compile_options(regex_explore PUBLIC -Wall)
target_compile_features(regex_explore PUBLIC cxx_std_14)
target_link_libraries(regex_explore PUBLIC ncurses
    /usr/local/lib64/liblibcppurses.a)
target_include_directories(regex_explore PUBLIC include/)

# RegExplore App
add_executable(regexplore src/main.cpp)
target_compile_options(regexplore PUBLIC -Wall)
target_compile_features(regexplore PUBLIC cxx_std_14)
target_include_directories(regexplore PUBLIC include/)
target_link_libraries(regexplore PUBLIC regex_explore)

include(GNUInstallDirs)
install(TARGETS regexplore
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
