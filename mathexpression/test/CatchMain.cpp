/*
 * Autor       : Mikael Nilsson
 * Filename    : IncludeCatch.cpp
 * Description : Används för att minska på kompieringstiden genom
 * att definera CATCH_CONFIG_MAIN i en kompileringsenhet
 * som aldrig ändras och därför aldrig behöver kompileras om.
 *
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
