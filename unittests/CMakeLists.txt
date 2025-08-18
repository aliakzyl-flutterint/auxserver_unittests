cmake_minimum_required(VERSION 3.28)
project(auxunittests CXX)

set(CMAKE_CXX_STANDARD 17)

set(PRODUCTION_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.." CACHE PATH "Path to the production base directory")
set(STUBS_PATH "../stubs")
set(FAKES_PATH "../fakes")
set(MOCKS_PATH "../mocks")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE INTERNAL "" FORCE)

add_subdirectory(googletest gtest) 
add_subdirectory(lobby_tests)
add_subdirectory(jackpot_tests)
add_subdirectory(abe_tests)
add_subdirectory(race_tests)
add_subdirectory(admin_is_tests)
#add_subdirectory(db_tests)