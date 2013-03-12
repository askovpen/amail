#ifndef __AMAIL_HOOKS_H__
#define __AMAIL_HOOKS_H__ 1

#define HOOK_GET_PARAM     "hook-read-param"

typedef struct {
    const char *name;
    const char *value;
} hk_arg_t;

typedef guint (*hk_handler_t) (const gchar *hookname, hk_arg_t *args,
                               gpointer userdata);
guint hk_add_handler(hk_handler_t handler, const gchar *hookname,
                     gint priority, gpointer userdata);
void hk_get_param(const char *name, gchar **value);
#endif
