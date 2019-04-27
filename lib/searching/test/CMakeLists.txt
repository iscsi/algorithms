file(GLOB_RECURSE SEARCHING_SRC "../src/searching_all.h")
add_executable(SearchingTest searching_test.cc searching_test.h ${SEARCHING_SRC})
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(SearchingTest Rili)
