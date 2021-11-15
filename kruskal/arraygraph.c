#include "arraygraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayGraph* createArrayGraph(int maxVertexCount)
{
	ArrayGraph* pGraph = NULL;
	if (maxVertexCount <= 0)
		return (NULL);
	if (!(pGraph = (ArrayGraph*)malloc(sizeof(ArrayGraph))))
		return (NULL);
	pGraph->maxVertexCount = maxVertexCount;
	pGraph->currentVertexCount = 0;
	pGraph->graphType = GRAPH_UNDIRECTED;
	if (!(pGraph->ppAdjEdge = malloc(sizeof(int*) * maxVertexCount)))
	{
		free(pGraph);
		return (NULL);
	}
	if (!(pGraph->pVertex = malloc(sizeof(int) * maxVertexCount)))
	{
		free(pGraph->ppAdjEdge);
		free(pGraph);
		return (NULL);
	}
	memset(pGraph->pVertex, 0, sizeof(int) * maxVertexCount);
	for (int i = 0; i < maxVertexCount; i++)
	{
		if (!(pGraph->ppAdjEdge[i] = malloc(sizeof(int) * maxVertexCount)))
		{
			free(pGraph->pVertex);
			free(pGraph->ppAdjEdge);
			free(pGraph);
			return (NULL);
		}
		memset(pGraph->ppAdjEdge[i], 0, sizeof(int) * maxVertexCount);
	}
	return (pGraph);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount)
{
	ArrayGraph* pGraph = createArrayGraph(maxVertexCount);
	pGraph->graphType = GRAPH_DIRECTED;
	return (pGraph);
}

void deleteArrayGraph(ArrayGraph* pGraph)
{
	if (pGraph)
	{
		if (pGraph->pVertex)
			free(pGraph->pVertex);
		for (int i = 0; i < pGraph->maxVertexCount; i++)
			if (pGraph->ppAdjEdge)
				free(pGraph->ppAdjEdge[i]);
		if (pGraph->ppAdjEdge)
			free(pGraph->ppAdjEdge);
		free(pGraph);
	}
}

int isEmptyAG(ArrayGraph* pGraph)
{
	if (pGraph->currentVertexCount == 0)
		return (TRUE);
	return (FALSE);
}

int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (!pGraph)
		return (FALSE);
	if (pGraph->maxVertexCount < vertexID)
		return (FALSE);
	if (pGraph->pVertex[vertexID] == 1)
		return (FALSE);

	pGraph->pVertex[vertexID] = 1;
	pGraph->currentVertexCount++;
	return (TRUE);
}

int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!pGraph) return FALSE;

	addVertexAG(pGraph, fromVertexID);
	addVertexAG(pGraph, toVertexID);
	if (pGraph->maxVertexCount > fromVertexID && pGraph->maxVertexCount > toVertexID)
	{
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = 1;
		if (pGraph->graphType == GRAPH_UNDIRECTED)
			pGraph->ppAdjEdge[toVertexID][fromVertexID] = 1;
		return (TRUE);
	}
	return (FALSE);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
	if (!pGraph) return FALSE;

	addVertexAG(pGraph, fromVertexID);
	addVertexAG(pGraph, toVertexID);
	if (pGraph->maxVertexCount > fromVertexID && pGraph->maxVertexCount > toVertexID)
	{
		pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
		if (pGraph->graphType == GRAPH_UNDIRECTED)
			pGraph->ppAdjEdge[toVertexID][fromVertexID] = weight;
		return (TRUE);
	}
	return (FALSE);
}

int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
	if (pGraph)
	{
		for (int i = 0; i < pGraph->currentVertexCount; i++)
		{
			removeEdgeAG(pGraph, vertexID, i);
			removeEdgeAG(pGraph, i, vertexID);
		}
		pGraph->pVertex[vertexID] = 0;
		pGraph->currentVertexCount--;
		return (TRUE);
	}
	return (FALSE);
}

int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (pGraph)
	{
		if (pGraph->maxVertexCount > fromVertexID && pGraph->maxVertexCount > toVertexID)
		{
			pGraph->ppAdjEdge[fromVertexID][toVertexID] = 0;
			if (pGraph->graphType == GRAPH_UNDIRECTED)
				pGraph->ppAdjEdge[toVertexID][fromVertexID] = 0;
			return (TRUE);
		}
	}
	return (FALSE);
}

void displayArrayGraph(ArrayGraph* pGraph)
{
	if (pGraph)
	{
		printf("\t");
		for (int i = 0; i < pGraph->maxVertexCount; i++)
			printf("%d\t", i);
		printf("\n\n");
		for (int i = 0; i < pGraph->maxVertexCount; i++)
		{
			printf("%d.\t", i);
			for (int j = 0; j < pGraph->maxVertexCount; j++)
			{
				if (pGraph->pVertex[i])
					printf("%d\t", pGraph->ppAdjEdge[i][j]);
			}
			printf("\n");
		}
	}
}
