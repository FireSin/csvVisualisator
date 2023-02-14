# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/drawCsv_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/drawCsv_autogen.dir/ParseCache.txt"
  "drawCsv_autogen"
  )
endif()
