# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "seadash-panel\\CMakeFiles\\seadash-panel_app_autogen.dir\\AutogenUsed.txt"
  "seadash-panel\\CMakeFiles\\seadash-panel_app_autogen.dir\\ParseCache.txt"
  "seadash-panel\\CMakeFiles\\seadash-panel_autogen.dir\\AutogenUsed.txt"
  "seadash-panel\\CMakeFiles\\seadash-panel_autogen.dir\\ParseCache.txt"
  "seadash-panel\\CMakeFiles\\seadash-panelplugin_autogen.dir\\AutogenUsed.txt"
  "seadash-panel\\CMakeFiles\\seadash-panelplugin_autogen.dir\\ParseCache.txt"
  "seadash-panel\\seadash-panel_app_autogen"
  "seadash-panel\\seadash-panel_autogen"
  "seadash-panel\\seadash-panelplugin_autogen"
  )
endif()
