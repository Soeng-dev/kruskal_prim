#include "heap.h"

Heap* createHeap(int maxCount)
{
	Heap* heap = calloc(1, sizeof(Heap));
	if (!heap)
		return NULL;

	heap->maxCount = maxCount;
	heap->data = calloc(maxCount, sizeof(HeapData));
	return heap;
}

void deleteHeap(Heap* target)
{
	clearHeapdata(target);
	target->maxCount = 0;
	free(target);
	return;
}

void clearHeapdata(Heap* target)
{
	free(target->data);
	target->data = NULL;

	target->currentCount = 0;
	return;
}

void swap(HeapData* first, HeapData* second)
{
	HeapData copyOfFirst = *first;
	*first = *second;
	*second = copyOfFirst;
	return;
}

int pushHeapData(Heap* heap, HeapData data)
{
	if (isFullHeap(heap))
		return FALSE;

	++heap->currentCount;
	heap->data[heap->currentCount - 1] = data;

	for (int childIndex = heap->currentCount - 1,
		parentIndex = getParentIdx(childIndex);

		parentIndex != ERROR &&
		heap->data[childIndex].weight < heap->data[parentIndex].weight;

		childIndex = parentIndex,
		parentIndex = getParentIdx(childIndex))
	{
		swap(&(heap->data[childIndex]), &(heap->data[parentIndex]));
	}

	return TRUE;
}


int getParentIdx(int childIndex)
{
	if (childIndex == ROOT_IDX)
		return ERROR;

	return ((childIndex - 1) / 2);
}

void heapify(Heap* heap, int parentIndex)
{
	int left = 2 * parentIndex + 1;
	int right = 2 * parentIndex + 2;
	int smallerChild;

	if (left > heap->currentCount - 1)
		return;
	else if (right > heap->currentCount - 1)
		smallerChild = right;
	else if (heap->data[left].weight < heap->data[right].weight)
		smallerChild = left;
	else
		smallerChild = right;
	if (heap->data[parentIndex].weight > heap->data[smallerChild].weight)
	{
		swap(&(heap->data[parentIndex]), &(heap->data[smallerChild]));
		heapify(heap, smallerChild);
	}
}

HeapData popMinData(Heap* heap)
{
	HeapData maxData = heap->data[0];
	heap->data[0] = heap->data[heap->currentCount - 1];
	--heap->currentCount;

	heapify(heap, ROOT_IDX);

	return maxData;
}


int getIndexOfLevel(Heap* heap, int level)
{
	int indexOfLevel = pow(2, level) - 1;

	if (indexOfLevel > heap->maxCount - 1)
		return ERROR;
	else
		return indexOfLevel;
}

int getSizeOfLevel(Heap* heap, int level)
{
	int nextLevelIndex = getIndexOfLevel(heap, level + 1);
	if (nextLevelIndex == ERROR)
		nextLevelIndex = heap->maxCount;

	return (min(heap->currentCount, nextLevelIndex) - getIndexOfLevel(heap, level));
}

int isFullHeap(Heap* heap)
{
	return (heap->maxCount == heap->currentCount);
}

void printHeap(Heap* heap)
{
	for (int level = 0,
		first = getIndexOfLevel(heap, level),
		size = getSizeOfLevel(heap, level);

		first <= heap->currentCount - 1;

		++level,
		first = getIndexOfLevel(heap, level),
		size = getSizeOfLevel(heap, level))
	{
		for (int i = first; i < first + size; ++i)
			printf("%d ", heap->data[i].weight);
		printf("\n");
	}
	printf("total %d\n\n", heap->currentCount);
}