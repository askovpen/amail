set(amail_SRCS main.c modules.c hooks.c)
add_executable(amail ${amail_SRCS})
target_link_libraries (amail ${GLIB_LIBRARIES})
