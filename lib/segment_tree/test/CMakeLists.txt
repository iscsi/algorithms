file(GLOB_RECURSE SEGMENT_TREE_SRC "../src/*.cpp" "../src/*.h")
add_executable(SegmentTreeTest segment_tree_test.cc segment_tree_test.h ${SEGMENT_TREE_SRC})
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(SegmentTreeTest rili)
