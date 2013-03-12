add_library(fbox MODULE fbox.c)
INSTALL(TARGETS fbox DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../../dist/lib/amail)