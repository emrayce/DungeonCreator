# Add source to this project's executable.

set(GENEREATED_FILES "${CMAKE_HOME_DIRECTORY}/Generated")
configure_file(
    Utils.h.in
    ${GENEREATED_FILES}/Utils.h)

qt_add_executable(DungeonCreator "Main.cpp" "TriangleWindow.cpp" "Shader.cpp" "Mesh.cpp")

target_include_directories(DungeonCreator PUBLIC
                            "${GENEREATED_FILES}"
                        )

target_link_libraries(DungeonCreator PRIVATE Qt6::OpenGL)

set_target_properties(DungeonCreator PROPERTIES
    WIN32_EXECUTABLE ON
)
