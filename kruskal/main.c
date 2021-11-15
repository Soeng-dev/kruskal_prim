#include "kruskal.h"

int main()
{
	ArrayGraph* g = createArrayGraph(15);

	//addVertexAG(g, 0);
	//addVertexAG(g, 1);
	//addVertexAG(g, 2);
	//addVertexAG(g, 4);
	//addVertexAG(g, 6);
	//addVertexAG(g, 7);
	//addVertexAG(g, 11);
	//addVertexAG(g, 12);

	addEdgewithWeightAG(g, 0, 1, 3);
	addEdgewithWeightAG(g, 0, 2, 9);
	addEdgewithWeightAG(g, 1, 2, 6);
	addEdgewithWeightAG(g, 2, 4, 7);
	addEdgewithWeightAG(g, 4, 6, 11);
	addEdgewithWeightAG(g, 4, 7, 22);
	addEdgewithWeightAG(g, 7, 11, 3);
	addEdgewithWeightAG(g, 11, 12, 2);
	addEdgewithWeightAG(g, 6, 12, 13);

	printf("before kruskal\n");
	displayArrayGraph(g);

	ArrayGraph *mst =  getMstFrom(g);
	displayArrayGraph(mst);

	deleteArrayGraph(g);
	deleteArrayGraph(mst);
}