#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>

static void bso_init(void);

module_info_t info_textconfig = {
    .version	= "0.1.12",
    .type	= "db",
    .init	= textconfig_init,
    .param	= NULL,
    .next	= NULL
};
