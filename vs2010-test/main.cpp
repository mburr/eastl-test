#include <stdio.h>
#include <time.h>

#include <string>
#include <vector>

#include "EASTL/string.h"
#include "EASTL/vector.h"


void performance_test(void)
{
    clock_t start;
    clock_t end;


    // EA

    eastl::string strEA = "hello";
    eastl::vector<eastl::string> vec_EA;

    start = clock();
    for (size_t i = 0; i < 1000000; i++)
    {
        vec_EA.push_back(strEA);
    }

    end = clock();
    printf("EA       %f\n", (double(end - start) / 1000));

    // Standard

    std::string strStandard = "hello";
    std::vector<std::string> vec_Standard;

    start = clock();
    for (size_t i = 0; i < 1000000; i++)
    {
        vec_Standard.push_back(strStandard);
    }

    end = clock();
    printf("Standard %f\n", (double(end - start) / 1000));
}


int main(void)
{
	performance_test();
}


// needed by EASTL - taken from EASTL's example/example1.cpp
//

// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* pName, int flags,
	unsigned debugFlags, const char* file, int line)
{
	return malloc(size);
}
void* operator new[](size_t size, size_t alignment, size_t alignmentOffset,
	const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	// this allocator doesn't support alignment
	EASTL_ASSERT(alignment <= 8);
	return malloc(size);
}

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnprintf(pDestination, n, pFormat, arguments);
#else
	return vsnprintf(pDestination, n, pFormat, arguments);
#endif
}
