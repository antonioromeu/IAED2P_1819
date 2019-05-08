#ifndef _STD_
#define _STD_

#include <stdlib.h>
#include <stdio.h>
#include "DomainTree.h"

typedef struct STnode *linkD;

void STDinit(linkD*);
int STDcount(linkD);
ItemD STDsearch(linkD, KeyD);
void STDinsert(linkD*, ItemD);
void STDdelete(linkD*, KeyD);
void STDfree(linkD*);

#endif
