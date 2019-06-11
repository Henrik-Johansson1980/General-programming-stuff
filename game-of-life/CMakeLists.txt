# Projektets namn
project(GameOfLife)

# Minsta tillåtna cmake version
cmake_minimum_required(VERSION 3.2)

# Kompilera med c++ 11 stöd
set (CMAKE_CXX_STANDARD 11)

# Lägg till katalogen med våra bibliotek till INCLUDE path
# (i dessa kataloger kommer kompilatorn att leta efter de
# header filer som inkluderas i koden)
INCLUDE_DIRECTORIES($ENV{TOOLS_INCLUDE})
include_directories(include)

# Add terminal sub directory
add_subdirectory(terminal)

file(GLOB_RECURSE HEADERS "include/*.*")
add_custom_target(headers SOURCES ${HEADERS})

# Ta med alla källkodsfiler i den aktuella katalogen och
# lägger dem i listan SRC_LIST.
set(SRC_LIST
   src/gameoflifemain.cpp
   src/gameworld.cpp
   src/ruleset.cpp
   src/game.cpp
   src/gamesettings.cpp
   terminal/terminal.cpp
)

set(TEST_LIST
    src/game.cpp
    src/gamesettings.cpp
    src/gameworld.cpp
    src/ruleset.cpp
    src/gamesettings.cpp
    terminal/terminal.cpp
    test/testgameoflife.cpp
    test/catchmain.cpp
    test/testrulehenrik.cpp
    test/testruleanna.cpp
    test/testrulemarcus.cpp
)

# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode samt sätt kompilator
    # direktivet DEBUG
    message("Debug mode")
    add_definitions(-DDEBUG)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# Skapa en exekverbar fil med källkodsfilerna i från
# SRC_LIST. Första parametern är namnet på målet (Target)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME}-Test ${TEST_LIST})

# Static link Terminal with executable ${PROJECT_NAME}
target_link_libraries(${PROJECT_NAME} Terminal)
