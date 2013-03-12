#include <glib.h>
#include <gmodule.h>
#include <string.h>

#include "modules.h"
#include "stdio.h"


GSList *loaded_modules = NULL;


static gint module_list_comparator(gconstpointer arg1, gconstpointer arg2)
{
    const loaded_module_t *module = arg1;
    const char *name = arg2;
    return g_strcmp0(module->name, name);
}

void modules_init(void)
{
    module_load("textconfig",NULL);
}
void modules_deinit(void)
{
    module_unload("textconfig");
}

const gchar *module_load(const gchar *arg, const gchar *param)
{
    GModule       *mod;
    module_info_t *info;

    gchar *path = g_module_build_path("../modules/db/textconfig", arg);
    mod = g_module_open(path, G_MODULE_BIND_LAZY);
    g_free(path);
    if (!mod)
    {
	printf("%s", g_module_error());
	return "error";
    }
    gchar *varname = g_strdup_printf("info_%s", arg);
    gpointer var = NULL;
    if (!g_module_symbol(mod, varname, &var)) {
	printf("Module provides no information structure\n");
	return "error";
    }
    g_free(varname);
    info = var;
    if (info) {
        while (info) {
    	    if (!info->version)
    	    {
    		printf("no version\n");
    	    }
    	    else
    	    {	break; }
	    info=info->next;
        }
        if (!info)
        {
    	    if(!g_module_close(mod))
    		printf("Error closing module: %s.", g_module_error());
    	    return "error";
    	}
    }

    { // Register module
	loaded_module_t *module = g_new(loaded_module_t, 1);
	module->refcount     = 1;
	module->name         = g_strdup(arg);
	module->module       = mod;
	module->info         = info;
	loaded_modules = g_slist_prepend(loaded_modules, module);
//        module->module->textconfig_init();
    }
	info->param=param;
    if (info && info->init)
	info->init();

    printf("Loaded module %s.\n", arg);
    return NULL;
}
const gchar *module_unload(const gchar *arg)
{
    GSList          *lmod;
    loaded_module_t *module;
    module_info_t   *info;
    if (!arg || !*arg)
	return "Missing module name";
    lmod = g_slist_find_custom(loaded_modules, arg, module_list_comparator);
    if (!lmod)
        return "Module not found";

    module = lmod->data;
    info = module->info;

    // Run uninitialization routine
    if (info && info->uninit)
	info->uninit();
    module->info = NULL;

    // Unload module
    if (!g_module_close(module->module))
	return g_module_error(); // XXX destroy structure?

    // Destroy structure
    loaded_modules = g_slist_delete_link(loaded_modules, lmod);
    // Output this here, as arg may point to module->name
    printf("Unloaded module %s.\n", module->name);
    g_free(module->name);
    g_free(module);

    return NULL;
}
void module_list_print(void)
{
    GSList *mel;
    gsize maxlen = 0;
    gchar *format;
    GString *message;
    guint module_count = 0;
    if (!loaded_modules) {
        printf("No modules loaded.\n");
        return;
    }
    message = g_string_new("---\nLoaded modules:\n");
    for (mel = loaded_modules; mel; mel = mel -> next) {
	loaded_module_t *module = mel->data;
	gsize len = strlen(module->name);
	if (len > maxlen)
	    maxlen = len;
	module_count++;
    }

    // Create format string
    format = g_strdup_printf("%%-%us  %%2u", (unsigned)maxlen);

    for (mel = loaded_modules; mel; mel = mel -> next) {
	loaded_module_t *module = mel->data;
	g_string_append_printf(message, format, module->name, module->refcount);
	if (module->info) {
	    module_info_t *info = module->info;

	    // Module version
	    if (info->version) {
		g_string_append(message, " version: ");
		    g_string_append(message, info->version);
	    }
	}
	g_string_append_c(message, '\n');
    }
//    g_string_truncate(message, message->len - 1);
    printf("%s---\n", message->str);
    g_string_free(message, TRUE);
    g_free(format);
}
