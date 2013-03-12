#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <stdlib.h>



static void lbox_init(void);
gchar *lboxdir;

module_info_t info_lbox = {
    .version	= "0.1.12",
    .type	= "outbiund",
    .init	= lbox_init,
    .param	= NULL,
    .next	= NULL
};

static void lbox_init(void){
    hk_get_param("lbox",&lboxdir);
    if (lboxdir==NULL)
    {
	printf("lboxdir not defined\n");
	exit(0);
    }
//    printf("lbox: %s\n",lboxdir);
}
