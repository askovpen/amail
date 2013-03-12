#include "../../../core/modules.h"
#include "../../../core/hooks.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>



static void bso_init(void);
static void bso_refresh(void);

gchar *bsodir;
GHashTable* bsofiles;
GHashTable* bsosizes;


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
    bsofiles = g_hash_table_new(g_str_hash, g_str_equal);
    bsosizes = g_hash_table_new(g_str_hash, g_str_equal);
    bso_refresh();
//    printf("bso: %s\n",bsodir);
}
static void bso_refresh(void){
    DIR *dir;
    struct dirent *dirent;
    if( (dir=opendir(bsodir)) == NULL )

    {
	printf("can't open outbound directory \"%s\"", bsodir);
	exit(1);
    }
    g_hash_table_destroy(bsofiles);
    g_hash_table_destroy(bsosizes);

    while( (dirent=readdir(dir)) != NULL )
    {
	if( strlen(dirent->d_name) == 12 &&
	    strspn(dirent->d_name, "0123456789abcdefABCDEF") == 8 )
	{
	    if((strncasecmp(dirent->d_name+8, ".PNT", 4) != 0) &&
		( strncasecmp(dirent->d_name+8, ".REQ", 4) != 0) &&
		( strncasecmp(dirent->d_name+10,  "UT", 2) != 0) &&
		( strncasecmp(dirent->d_name+10,  "LO", 2) != 0) ) continue;
	    printf("file: %s\n",dirent->d_name);
//	    if( point == 0 && strncasecmp(dirent->d_name+8, ".PNT", 4) == 0 )
//	    {
//		printf("scan_dir: BSO: found point directory \"%s\"",dirent->d_name);
//	    }
	}
    }
}
