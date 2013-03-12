#include "common.h"
#include "modules.h"
#include "hooks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRNUM_MIN	0x0000
#define ADDRNUM_MAX	0x7fff

static int addrstr2int(const char *s)
{
    int val = atoi(s);
    if( val < ADDRNUM_MIN )
	val = ADDRNUM_MIN;
    else if( val > ADDRNUM_MAX )
	val = ADDRNUM_MAX;

    return val;
}


int get_addr(s_falist **alist)
{
    int ptr=0,i=0;
    gchar *v,**a;
    hk_get_param("address",&v);
//    printf("addr: %s",v);
    a=g_strsplit(v,",",-1);
    bool badaddr  = 0;
    bool stop     = 0;
    const char *p;
//    memset(addr, '\0', sizeof(s_faddr));
//	(*alist) = (s_falist *)malloc(sizeof(s_falist));
    while (a[i]!=NULL)
    {
	printf("addr %s\n",a[i]);
	p=a[i];
	stop=0;
	(*alist) = (s_falist *)malloc(sizeof(s_falist));
	(*alist)->addr.node=-1;
	while( !stop && !badaddr )
	{
	    switch(*p)
	    {
		case ':': 
		    (*alist)->addr.zone=addrstr2int(a[i]);
		    a[i]=g_strdup(++p);
		    break;
		case '/': 
		    (*alist)->addr.net=addrstr2int(a[i]);
		    a[i]=g_strdup(++p);
		    break;
		case '.': 
		    (*alist)->addr.node=addrstr2int(a[i]);
		    a[i]=g_strdup(++p);
		    break;
		case '\0':
		    if ((*alist)->addr.node==-1)
		    {
		    (*alist)->addr.node=addrstr2int(a[i]);
		    (*alist)->addr.point=0;
		    }
		    else
		    {
		    (*alist)->addr.point=addrstr2int(a[i]);
		    }
		    alist = (s_falist**)&((*alist)->next);
		    stop=1;
		default: ++p;
	    }
	}
	i++;
    }
    return 0;
}