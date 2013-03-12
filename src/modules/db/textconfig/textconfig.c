#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig.h>

static void textconfig_init(void);
static guint get_param_hid;
GSList *config=NULL;
config_t cfg;
module_info_t info_textconfig = {
    .version         = "1.12",
    .type            = "db",
    .init           = textconfig_init,
    .param=NULL,
    .next	= NULL
};

static guint get_param_hh(const gchar *hookname, hk_arg_t *args,
                            gpointer userdata)
{
    config_setting_t *setting;
    int i;
    int type;

    setting = config_lookup(&cfg, g_strconcat ("config.",args[0].value,NULL));
//    printf("format: %d\n",config_setting_type(setting));
    if(setting != NULL)
    {
	type=config_setting_type(setting);

	if (type==CONFIG_TYPE_ARRAY)
	    setting = config_lookup(&cfg, g_strconcat ("config.",args[0].value,NULL));
	else if (type==CONFIG_TYPE_STRING)
	    setting = config_lookup(&cfg, "config");

	const char *tt="";
	if (type==CONFIG_TYPE_ARRAY)
	{
	    for (i=0;i<config_setting_length(setting);i++)
	    {
		if (strlen(tt)>0)
		    tt=g_strjoin(",",tt,config_setting_get_string_elem (setting, i),NULL);
		else
		    tt=config_setting_get_string_elem (setting, i);
	    }
	}
	else if (type==CONFIG_TYPE_STRING)
	{
	    config_setting_lookup_string(setting,args[0].value,&tt);
	}
	else
	{
	    printf("error\n\n\n");
	}
	args[0].value=tt;
	
    }
    else 
    {
	printf("huy\n");
	args->value=NULL;
    }
    return 0;
}
static void textconfig_init(void)
{
    get_param_hid=hk_add_handler(get_param_hh,HOOK_GET_PARAM,G_PRIORITY_DEFAULT_IDLE, NULL);
    config_init(&cfg);
     if(! config_read_file(&cfg, "test.cfg"))
     {
        printf("err %s:%d - %s\n",config_error_file(&cfg),config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        exit(0);
     }
//    printf("myini \n");
}
