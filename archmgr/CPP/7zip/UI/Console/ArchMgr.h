#pragma once

#include "IxArchMgr.h"

#ifndef _EXPORTING
#define PARESULTAPI	extern "C" __declspec(dllimport) 	
#else
#define PARESULTAPI	extern "C" __declspec(dllexport) 	
#endif


PARESULTAPI	IxArchMgr* __cdecl		GetArchMgrInstance();

typedef IxArchMgr* (__cdecl* PFN_GET_ARESULT_INSTANCE)();