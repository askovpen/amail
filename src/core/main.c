#include <stdio.h>
#include <glib.h>
#include "modules.h"
#include "hooks.h"

int main(int argc, char **argv)
{
    modules_init();
    module_list_print();
//    printf("%d\n",g_slist_length(loaded_modules));
    gchar *v;
    v="rr";
//    hk_get_param("address",&v);
//    printf("address: %s\n",v);
//    hk_get_param("daemon",&v);
//    printf("daemon: %s\n",v);
//    hk_get_param("test",&v);
//    printf("test: %s\n",v);
    modules_deinit();
    return 0;
}
