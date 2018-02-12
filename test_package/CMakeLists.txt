cmake_minimum_required(VERSION 2.8.11)
project(test_package)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} test_package.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} winhttp.lib Rpcrt4.lib Crypt32.lib)
endif()
