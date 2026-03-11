cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE
SOURCE_FILES
"Source/*.cpp"
"Include/*.h")

add_executable(PacmanGame ${SOURCE_FILES})

target_include_directories(PacmanGame PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/../GameFramework/Include")

target_link_libraries(PacmanGame PRIVATE GameFramework)

target_compile_features(PacmanGame PRIVATE ${COMMON_COMPILE_FEAUTRES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")