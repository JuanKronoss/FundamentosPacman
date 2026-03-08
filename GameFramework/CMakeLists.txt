file(GLOB_RECURSE
  SOURCE_FILES
  "Source/*.cpp"
  "Include/*.h")

add_library(GameFramework STATIC
  ${SOURCE_FILES})
