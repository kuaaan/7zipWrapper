#include "StdAfx.h"
#include "ArchMgr.h"
#include "CxArchMgr.h"

IxArchMgr* __cdecl		GetArchMgrInstance()
{
	return		CxArchMgr::GetInstance();
}