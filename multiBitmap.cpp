#include "multiBitmap.h"
#include <cmath>
#include <memory>
#define  NULL 0 
using namespace  std;
CMultiBitMap :: CMultiBitMap(const size_t size)
{
	bits = NULL ;
	bitSize = size ; //bit位的大小
	if (size)
	{
		int tempSize = size >> SHIFT ;
		if (size & MASK)
			tempSize ++ ;
		bits = new int[tempSize] ; //申请空间
		memset(bits, 0, sizeof(int)*tempSize) ; //全部清0
	}
	
}

CMultiBitMap :: ~CMultiBitMap()
{
	if (bits != NULL)
	{
		delete[] bits ;
		bits = NULL ;
	}
}

void CMultiBitMap :: resize(size_t newSize)
{
	if (newSize != bitSize)
	{
		bitSize = newSize ;
		if (bits != NULL)
		{
			delete[] bits ;
			bits = NULL ;
		}

		int tempSize = bitSize >> SHIFT ;
		if (bitSize & MASK)
			tempSize ++ ;
		bits = new int[tempSize] ;
		memset(bits, 0, sizeof(int)*tempSize) ; //全部清0
	}
	else
	{
		int tempSize = bitSize >> SHIFT ;
		if (bitSize & MASK)
			tempSize ++ ;
		memset(bits, 0, sizeof(int)*tempSize) ; //全部清0
	}
}