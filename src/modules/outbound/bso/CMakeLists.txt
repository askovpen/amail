add_library(bso MODULE bso.c)
INSTALL(TARGETS bso DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../../dist/lib/amail)