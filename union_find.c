#include "union_find.h"

int getParent(int parents[], int vertexID)
{
	if (parents[vertexID] == vertexID)
		return vertexID;

	return parents[vertexID] = getParent(parents, parents[vertexID]);
}

void unionParent(int parents[], int a, int b)
{
	a = getParent(parents, a);
	b = getParent(parents, b);

	if (a < b) parents[b] = a;
	else parents[a] = b;
}

int haveSameParent(int parents[], int a, int b)
{
	return (getParent(parents, a) == getParent(parents, b));
}