#ifndef __AMAIL_MODULES_H__
#define __AMAIL_MODULES_H__ 1

#include <glib.h>
#include <gmodule.h>

typedef void (*module_init_t)(void);
typedef void (*module_uninit_t)(void);

typedef struct module_info_struct module_info_t;
struct module_info_struct {
    const gchar		*version;
    const gchar		*description;
    const gchar		*type;
    const gchar		*param;
    module_init_t	init;
    module_uninit_t	uninit;
    module_info_t	*next;
};
typedef struct {
    guint          refcount;      // Reference count
    gchar         *name;          // Module name
    GModule       *module;        // Module object
    module_info_t *info;          // Module information struct. May be NULL!
} loaded_module_t;

extern GSList *loaded_modules;

void modules_init(void);
void modules_deinit(void);
const gchar *module_load(const gchar *name, const gchar *param);
const gchar *module_unload(const gchar *name);
void module_list_print(void);
#endif
