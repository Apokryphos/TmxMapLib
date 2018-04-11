set(TMXMAPLIB_EXAMPLE_SOURCE
    src/Property_Example.cpp
    src/Tile_Example.cpp
)

add_executable(Property_Example src/Property_Example.cpp)
target_include_directories(Property_Example PRIVATE ${TmxMapLib_SOURCE_DIR}/TmxMapLib/include)
target_link_libraries(Property_Example TmxMapLib)

add_executable(Tile_Example src/Tile_Example.cpp)
target_include_directories(Tile_Example PRIVATE ${TmxMapLib_SOURCE_DIR}/TmxMapLib/include)
target_link_libraries(Tile_Example TmxMapLib)