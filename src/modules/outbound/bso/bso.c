#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <stdlib.h>



static void bso_init(void);
gchar *bsodir;

module_info_t info_bso = {
    .version	= "0.1.12",
    .type	= "outbiund",
    .init	= bso_init,
    .param	= NULL,
    .next	= NULL
};

static void bso_init(void){
    hk_get_param("bso",&bsodir);
    if (bsodir==NULL)
    {
	printf("bsodir not defined\n");
	exit(0);
    }
//    printf("bso: %s\n",bsodir);
}
