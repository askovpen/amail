#include <stdio.h>
#include <glib.h>
#include "modules.h"
#include "hooks.h"
#include "config.h"

int main(int argc, char **argv)
{
    s_falist *alist=NULL,*alst;
    modules_init();
    module_list_print();
//    printf("%d\n",g_slist_length(loaded_modules));
//    gchar *v;
//    v="rr";
//    get_addr(&alist);
//    for( alst = alist; alst; alst = alst->next )
//    {
//	printf("%d:%d/%d.%d\n",alst->addr.zone,alst->addr.net,alst->addr.node,alst->addr.point);
//    }
//    hk_get_param("address",&v);
//    printf("address: %s\n",v);
//    hk_get_param("daemon",&v);
//    printf("daemon: %s\n",v);
//    hk_get_param("test",&v);
//    printf("test: %s\n",v);
    modules_deinit();
    return 0;
}
