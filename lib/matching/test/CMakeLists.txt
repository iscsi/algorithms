file(GLOB_RECURSE MATCHING_SRC "../src/*.h")
source_group("src" FILES ${MATCHING_SRC})
add_executable(MatchingTest matching_test.cc matching_test.h ../matching.h ${MATCHING_SRC})
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(MatchingTest Rili)

