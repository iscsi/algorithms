file(GLOB_RECURSE FFT_SRC "../src/*.h")
source_group("src" FILES ${FFT_SRC})
add_executable(FFTTest fft_test.cc fft_test.h ../fft_all.h ${FFT_SRC})
add_definitions(-DHOME -D_CRT_SECURE_NO_WARNINGS)
target_link_libraries(FFTTest Rili)
