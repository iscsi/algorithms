file(GLOB_RECURSE NUMBER_THOERY_SRC "../src/*.cpp" "../src/*.h")
add_executable(NumberTheoryTest number_theory_test.cc number_theory_test.h ${NUMBER_THOERY_SRC})
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(NumberTheoryTest rili)
#set(RESOURCE_FILES ../src/basic_number_theory.h)
#set_target_properties(NumberTheoryTest PROPERTIES RESOURCE "${RESOURCE_FILES}")


#source_group("Source Files\\src" FILES ${NUMBER_THOERY_SRC})