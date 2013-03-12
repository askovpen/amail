#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <stdlib.h>



static void fbox_init(void);
gchar *fboxdir;

module_info_t info_fbox = {
    .version	= "0.1.12",
    .type	= "outbiund",
    .init	= fbox_init,
    .param	= NULL,
    .next	= NULL
};

static void fbox_init(void){
    hk_get_param("fbox",&fboxdir);
    if (fboxdir==NULL)
    {
	printf("fboxdir not defined\n");
	exit(0);
    }
//    printf("fbox: %s\n",fboxdir);
}
