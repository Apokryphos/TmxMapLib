set(TMXMAPLIB_TESTS_SOURCE
    Tests_Main.cpp
    Tests_Map.cpp
    Tests_Property.cpp
)

include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib_Tests/Include)
include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include)

add_executable(TmxMapLib_Tests ${TMXMAPLIB_TESTS_SOURCE})
target_link_libraries(TmxMapLib_Tests TmxMapLib Catch ${TINYXML2_LIBRARIES})

add_test(tests TmxMapLib_Tests)

# Copy data files for tests executable
add_custom_command(TARGET TmxMapLib_Tests POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:TmxMapLib_Tests>)