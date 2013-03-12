#ifndef __AMAIL_COMMON_H__
#define __AMAIL_COMMON_H__ 1

#include <stdbool.h>

typedef struct faddr {
    bool inetform;	/* Is address in domain form? */
    int zone;	/* -1 value means any?! */
    int net;
    int node;
    int point;
} s_faddr;

typedef struct falist {
    s_faddr addr;
    char *what;
    struct falist *next;
} s_falist;


#endif
