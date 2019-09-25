#pragma once
#include "stdafx.h"

// Âü°í
//http://msdn.microsoft.com/ko-kr/library/windows/desktop/aa366750(v=vs.85).aspx
class LowFragmentationHeap
{
public:
	LowFragmentationHeap()
	{
		ULONG heap_flag_value = 2;
		HANDLE heaps[100];
		DWORD heap_count = GetProcessHeaps(100, heaps);

		for (DWORD i = 0; i < heap_count; i++)
			HeapSetInformation(heaps[i], HeapCompatibilityInformation, &heap_flag_value, sizeof(heap_flag_value));

		printf("Low-fragmentation Heap setting \n");
	}
};
