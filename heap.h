#pragma once

#ifndef HEAP_H
#define HEAP_H

#define TRUE 1
#define FALSE 0
#define ERROR -1

#define ROOT_IDX 0

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


typedef struct HeapDataType
{
	int fromVertex;
	int toVertex;
	int weight;
} HeapData;

typedef struct Heap
{
	HeapData *data;
	int maxCount;
	int currentCount;

} Heap;

Heap* createHeap(int maxCount);
void deleteHeap(Heap* target);
void clearHeapdata(Heap* target);

int pushHeapData(Heap* heap, HeapData data);
HeapData popMinData(Heap* heap);

int getParentIdx(int childIndex);
int getIndexOfLevel(Heap *heap, int level);
int getSizeOfLevel(Heap* heap, int level);
int isFullHeap(Heap* heap);

void printHeap(Heap* heap);

#endif