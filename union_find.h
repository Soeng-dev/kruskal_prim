#ifndef UNION_FIND_H
#define UNION_FIND_H

#include "arraygraph.h"

#define TRUE 1
#define FALSE 0


void unionParent(int parents[], int a, int b);
int haveSameParent(int parents[], int a, int b);

#endif