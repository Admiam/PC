cmake_minimum_required(VERSION 3.10)
project(Steganografic C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "src/*.c")

# Add your source files
add_executable(stegim stegim.c)

target_link_libraries(stegim /opt/homebrew/lib/libpng.a)
target_include_directories(stegim PUBLIC /opt/homebrew/include)