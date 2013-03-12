add_library(aso MODULE aso.c)
INSTALL(TARGETS aso DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../../dist/lib/amail)