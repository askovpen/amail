#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>

static void bso_init(void);

module_info_t info_bso = {
    .version	= "0.1.12",
    .type	= "outbiund",
    .init	= bso_init,
    .param	= NULL,
    .next	= NULL
};

static void bso_init(void){

}
