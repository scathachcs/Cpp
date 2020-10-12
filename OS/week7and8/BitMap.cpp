#include "BitMap.h"
#include <math.h>
#include <stdio.h>

void createEmptyBitMap(SBitMap& voBitMap, int vNumTotalBits)
{
	voBitMap.NumBits  = vNumTotalBits;
	int NumWords = (int)ceil(vNumTotalBits / (double)g_NumBitsInWord);
	voBitMap.pMapData = new int[NumWords];

	for (int i=0; i<NumWords; ++i) voBitMap.pMapData[i] = 0;
}

void markBitAt(int vBitPosition, SBitMap& vioBitMap) 
{ 
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] |= 1 << (vBitPosition % g_NumBitsInWord);
}

void clearBitAt(int vBitPosition, SBitMap& vioBitMap) 
{
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] &= ~(1 << (vBitPosition % g_NumBitsInWord));
}

bool isAvailableBitAt(int vBitPosition, const SBitMap& vBitMap)
{
	return (vBitMap.pMapData[vBitPosition / g_NumBitsInWord]|~(1 << (vBitPosition % g_NumBitsInWord)))!=-1;
}

int countClearBits(const SBitMap& vBitMap)
{
	int count=0;
	for (int i=0; i<vBitMap.NumBits; ++i) 
	{
		if (isAvailableBitAt(i, vBitMap))
			count++;
	}
	return count;
}

int findAndSetAvailableBit(SBitMap& voBitMap) 
{
	for (int i=0; i<voBitMap.NumBits; ++i) 
	{
		if (isAvailableBitAt(i, voBitMap)){
			markBitAt(i,voBitMap);
			return i;
		}
	}
	return -1;//代表无空闲位
}

void printfBitMap(const SBitMap& vBitMap)
{
	for (int i=0; i<vBitMap.NumBits; ++i) 
	{
		if (isAvailableBitAt(i, vBitMap)) printf("0 ");
		else printf("1 "); 
	}
	printf("\n"); 
}