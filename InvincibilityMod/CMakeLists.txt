add_library(InvincibilityMod SHARED
  InvincibilityMod.cpp)

set_target_properties(InvincibilityMod PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR}
  ARCHIVE_OUTPUT_DIRECTORY ${MOD_OUTPUT_DIR})

target_include_directories(InvincibilityMod PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/Include"
  "${CMAKE_SOURCE_DIR}/GameFramework/Include"
  "${CMAKE_SOURCE_DIR}/Game/Include")

target_link_libraries(InvincibilityMod PUBLIC GameFramework)

target_compile_features(InvincibilityMod PRIVATE ${COMMON_COMPILE_FEATURES})
