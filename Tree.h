#ifndef _ST_
#define _ST_

#include <stdlib.h>
#include <stdio.h>
#include "Contact.h"

typedef struct STnode *link;

void STinit(link*);
int STcount(link);
Item STsearch(link, Key);
void STinsert(link*, Item);
void STdelete(link*, Key);
void STsort(link, void (*visit)(Item));
void STfree(link*);

#endif
