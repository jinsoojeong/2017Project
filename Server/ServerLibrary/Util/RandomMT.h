#pragma once
#include "stdafx.h"

class RandomMT
{
public:
    static ULONGLONG Generate(int min, int max)
    {
		if (min >= max)
			return 0;

		std::random_device randdom_divice;
		std::mt19937 gen(randdom_divice());
		std::uniform_int_distribution<ULONGLONG> dist(min, max);

		return dist(gen);
    }

	static ULONGLONG Generate(int max) 
	{
		Generate(1, max);
	}
};