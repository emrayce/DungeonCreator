# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Src\\CMakeFiles\\DungeonCreator_autogen.dir\\AutogenUsed.txt"
  "Src\\CMakeFiles\\DungeonCreator_autogen.dir\\ParseCache.txt"
  "Src\\DungeonCreator_autogen"
  )
endif()
