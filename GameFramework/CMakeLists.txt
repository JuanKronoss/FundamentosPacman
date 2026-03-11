file(GLOB_RECURSE
  SOURCE_FILES
  "Source/*.cpp"
  "Include/*.h")

add_library(GameFramework STATIC
  ${SOURCE_FILES})

target_include_directories(GameFramework PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_link_libraries(GameFramework PUBLIC SFML::Graphics)

target_compile_features(GameFramework PRIVATE ${COMMON_COMPILE_FEAUTRES})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)