#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <stdlib.h>



static void aso_init(void);
gchar *asodir;

module_info_t info_aso = {
    .version	= "0.1.12",
    .type	= "outbiund",
    .init	= aso_init,
    .param	= NULL,
    .next	= NULL
};

static void aso_init(void){
    hk_get_param("aso",&asodir);
    if (asodir==NULL)
    {
	printf("asodir not defined\n");
	exit(0);
    }
//    printf("aso: %s\n",asodir);
}
