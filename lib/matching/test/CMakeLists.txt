add_executable(MatchingTest matching_test.cc matching_test.h)
target_link_libraries(MatchingTest rili)

add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)