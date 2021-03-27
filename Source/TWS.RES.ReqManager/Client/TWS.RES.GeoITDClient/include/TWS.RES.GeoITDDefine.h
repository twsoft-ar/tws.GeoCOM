#ifndef __TWS_RES_MPQMDEFINE_H
#define __TWS_RES_MPQMDEFINE_H

#define CFG_DEBUG_MODE "DEBUG_MODE"

#include "string.h"

#ifdef BYTE_ALIGN
	#undef BYTE_ALIGN
#endif

#if defined(UNDER_CE)
	#define BYTE_ALIGN

	#ifndef max
	#define max(a,b)            (((a) > (b)) ? (a) : (b))
	#endif

	#ifndef min
	#define min(a,b)            (((a) < (b)) ? (a) : (b))
	#endif

#else
	#define BYTE_ALIGN __declspec(align(1))
#endif

namespace GEOITD_MSG
{
	const __int32 Purchase = 0x01;
	const __int32 Reverse = 0x02;
	const __int32 PurchaseVoid = 0x03;
	const __int32 PurchaseRefund = 0x04;
	const __int32 QueryStatus = 0x05;
	const __int32 QueryStatusNoWait = 0x06;
};

#endif