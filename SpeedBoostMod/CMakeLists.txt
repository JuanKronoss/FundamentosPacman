add_library(SpeedBoostMod SHARED
  SpeedBoostMod.cpp)

set(MOD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/Assets/Mods")

set_target_properties(SpeedBoostMod PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR})

target_include_directories(SpeedBoostMod PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/Include"
  "${CMAKE_SOURCE_DIR}/GameFramework/Include"
  "${CMAKE_SOURCE_DIR}/Game/Include")

target_link_libraries(SpeedBoostMod PUBLIC GameFramework)

target_compile_features(SpeedBoostMod PRIVATE ${COMMON_COMPILE_FEATURES})

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Assets/Mods")
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Assets/Mods")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Assets/Mods")


