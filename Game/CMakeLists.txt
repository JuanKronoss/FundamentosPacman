include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE
SOURCE_FILES
"Source/*.cpp"
"Include/*.h")

add_executable(PacmanGame ${SOURCE_FILES})

target_include_directories(PacmanGame PRIVATE ${CMAKE_BINARY_DIR}/_deps/sfml-build/src)
target_compile_features(PacmanGame PRIVATE cxx_std_20)
target_link_libraries(PacmanGame PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PacmanGame)