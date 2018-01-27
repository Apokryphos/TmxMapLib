set(TMXMAPLIB_EXAMPLE_SOURCE
    Source/Property_Example.cpp
    Source/Tile_Example.cpp
)

add_executable(Property_Example Source/Property_Example.cpp)
target_include_directories(Property_Example PRIVATE ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include)
target_link_libraries(Property_Example TmxMapLib)

add_executable(Tile_Example Source/Tile_Example.cpp)
target_include_directories(Tile_Example PRIVATE ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include)
target_link_libraries(Tile_Example TmxMapLib)