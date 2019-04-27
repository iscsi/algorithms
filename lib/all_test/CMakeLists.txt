add_executable(AllTest all_test.cc all_test.h )
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(AllTest Rili)
