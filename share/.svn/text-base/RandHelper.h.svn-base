#ifndef __TPOC_RAND_HELPER__
#define __TPOC_RAND_HELPER__

#include "stdafx.h"

class RandHelper
{
public:
	static int32_t CalRandTimes( int32_t nTotalTimes, int32_t nRate, int32_t nTotalRate )
	{
		int32_t times = 0;
		for ( int32_t i = 0; i < nTotalTimes; ++i )
		{
			int32_t nRand = RANDOM.generate( 0, nTotalRate - 1 );
			if ( nRand < nRate )
			{
				++times;
			}
		}
		return times;
	}
};

#endif	//__TPOC_RAND_HELPER__