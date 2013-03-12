#include <glib.h>
#include <stdio.h>
#include "hooks.h"

static GHashTable *hk_handler_hash = NULL;

typedef struct {
    hk_handler_t handler;
    gint      priority;
    gpointer  userdata;
    guint     hid;
} hook_list_data_t;

static guint _new_hook_id(void)
{
    static guint hidcounter;
    return ++hidcounter;
}
static GSList **_new_hook_queue(const gchar *hookname)
{
    GSList **p;
    // Create the hash table if needed.
    if (!hk_handler_hash) {
	hk_handler_hash = g_hash_table_new_full(&g_str_hash, &g_str_equal,&g_free, &g_free);
	if (!hk_handler_hash) {
	    printf("Couldn't create hook hash table!");
            return NULL;
        }
    }
    p = g_new(GSList*, 1);
    *p = NULL;
    g_hash_table_insert(hk_handler_hash, g_strdup(hookname), p);

    return p;
}
guint hk_add_handler(hk_handler_t handler, const gchar *hookname,
                     gint priority, gpointer userdata)
{
    hook_list_data_t *h = g_new(hook_list_data_t, 1);
    GSList **hqueue = NULL;
    
    h->handler  = handler;
    h->priority = priority;
    h->userdata = userdata;
    h->hid      = _new_hook_id();

    if (hk_handler_hash)
	hqueue = g_hash_table_lookup(hk_handler_hash, hookname);

    if (!hqueue)
	hqueue = _new_hook_queue(hookname);
    if (!hqueue)
      return 0;
    *hqueue = g_slist_insert(*hqueue, h,0);
    return h->hid;
}
guint hk_run_handlers(const gchar *hookname, hk_arg_t *args)
{
    GSList **hqueue;
    GSList *h;
    guint ret = 0;

    if (!hk_handler_hash)
	return 0;

    hqueue = g_hash_table_lookup(hk_handler_hash, hookname);

    if (!hqueue)
      return 0; // Should we use a special code?

    for (h = *hqueue; h; h = g_slist_next(h)) {
	hook_list_data_t *data = h->data;
	ret = (data->handler)(hookname, args, data->userdata);
//	printf("ret: %d %s\n",ret,args->value);
	if (ret) break;
    }
    return ret;
}

void hk_get_param(const char *name, gchar **value)
{
    guint h_result;
//    printf("%s\n",name);
    hk_arg_t args[] = {
	{ "name", name },
//	{ "value", *value },
	{ NULL, NULL },
    };

    h_result=hk_run_handlers(HOOK_GET_PARAM,args);
    *value=g_strdup(args->value);
    return ;
}
