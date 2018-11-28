#pragma once
#include "00_Header.h"

template<typename T>
void stl_wipe_vector(vector<T>& rVector)
{
	vector<T> emptyData;
	rVector.swap(emptyData);
}

