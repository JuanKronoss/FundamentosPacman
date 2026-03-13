cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE
SOURCE_FILES
"Source/*.cpp"
"Include/*.h")

add_executable(PacmanGame ${SOURCE_FILES})

target_include_directories(PacmanGame PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/Include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/../GameFramework/Include")

target_link_libraries(PacmanGame PRIVATE GameFramework)

target_compile_features(PacmanGame PRIVATE ${COMMON_COMPILE_FEATURES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

#add_custom_command(TARGET PacmanGame POST_BUILD
#  COMMAND ${CMAKE_COMMAND} -E copy_directory
#  "${CMAKE_SOURCE_DIR}/Assets"
#  "$<TARGET_FILE_DIR:PacmanGame>/Assets")

add_custom_target(copy_assets ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${CMAKE_SOURCE_DIR}/Assets"
  "$<TARGET_FILE_DIR:PacmanGame>/Assets")

add_dependencies(copy_assets PacmanGame)