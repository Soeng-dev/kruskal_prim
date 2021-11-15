#include "kruskal.h"

ArrayGraph* getMstFrom(ArrayGraph* g)
{
	if (!g || !g->ppAdjEdge)
		return NULL;

	Heap* edgeHeap = createHeap(g->currentVertexCount * (g->currentVertexCount - 1));
	//push edges to Heap
	for (int fromVertex = 0; fromVertex < g->maxVertexCount;++fromVertex)
	{
		for (int toVertex = fromVertex + 1; toVertex < g->maxVertexCount; ++toVertex)
		{
			if (g->ppAdjEdge[fromVertex][toVertex])
			{
				HeapData data;
				data.fromVertex = fromVertex;
				data.toVertex = toVertex;
				data.weight = g->ppAdjEdge[fromVertex][toVertex];
				pushHeapData(edgeHeap, data);
			}
		}
	}

	ArrayGraph* mst = createArrayGraph(g->maxVertexCount);
	if (!mst) return NULL;

	//Select min edge which doesn't make cycle
	int* parents = malloc((g->maxVertexCount +1)* sizeof(int));
	if (!parents) return NULL;
	for (int i = 0; i < g->maxVertexCount;++i) parents[i] = i;
	
	while(edgeHeap->currentCount)
	{
		HeapData minEdge = popMinData(edgeHeap);

		if (parents[minEdge.fromVertex] == parents[minEdge.toVertex])
			continue;
		else
		{
			addEdgewithWeightAG(mst, minEdge.fromVertex, minEdge.toVertex, minEdge.weight);
			unionParent(parents, minEdge.fromVertex, minEdge.toVertex);
		}
	}

	return mst;
}