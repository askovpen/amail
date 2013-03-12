pkg_check_modules(LC REQUIRED libconfig)
add_library(textconfig MODULE textconfig.c)
target_link_libraries (textconfig ${LC_LIBRARIES})
INSTALL(TARGETS textconfig DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../../../../dist/lib/amail)