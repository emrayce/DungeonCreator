Visualize a dungeon in 3D from a text based file.
I make this project to improve my openGL skills and learned the Qt environment.

This project uses Qt under LGPL v3 license


To compile this project
Use cmake to create the build system either with visual studio directly that will use the CMakePresets.json or by using cmake directly with commands line:
	In the root CMakelists.txt specify the location of your qt library (CMAKE_PREFIX_PATH)
	cmake -B *build_directory* 
	cmake --build *build_directory*

Use windeployqt.exe where the executable is to let qt add the needed library for it to work.