set(TMXMAPLIB_TESTS_SOURCE
    src/Tests_Main.cpp
    src/Tests_Map.cpp
    src/Tests_Property.cpp
)

include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib_Tests/include)
include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib/include)

add_executable(TmxMapLib_Tests ${TMXMAPLIB_TESTS_SOURCE})
include_directories(${CATCH_INCLUDE_DIR})
target_link_libraries(TmxMapLib_Tests TmxMapLib Catch ${TINYXML2_LIBRARIES})

add_test(tests TmxMapLib_Tests)

# Copy data files for tests executable
add_custom_command(TARGET TmxMapLib_Tests POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:TmxMapLib_Tests>)