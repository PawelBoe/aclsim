# Usage:
# - Make shure cmake is installed on your system
# - Generate Makefiles:
#   - mkdir path/to/aclsim/build
#   - cd build
#   - cmake .. -G "Unix Makefiles"
# - Run build process:
#   - make
# - Clean binaries:
#   - make clean

cmake_minimum_required(VERSION 3.2)

project(aclsim C)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(aclsim src/ip.c src/main.c src/match.c src/rule.c src/vector.c)
