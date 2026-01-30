# Add source to this project's executable.
qt_add_executable (DungeonCreator "Main.cpp" "OpenGLWindow.cpp" "TriangleWindow.h")

target_link_libraries(DungeonCreator PRIVATE Qt6::OpenGL)

set_target_properties(DungeonCreator PROPERTIES
    WIN32_EXECUTABLE ON
)