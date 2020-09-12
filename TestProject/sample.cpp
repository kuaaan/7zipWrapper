// TestProject.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include "shlwapi.h"
#include "ArchMgr.h"
#pragma comment(lib, "shlwapi.lib")

int wmain(int argc, WCHAR** argv)
{
	WCHAR	szDllPath[MAX_PATH] = { 0, };
	IxArchMgr* pInstance = NULL;
	PARCH_RESULT pResult = NULL;
	ARESULT			ar = 0;

	GetModuleFileName(NULL, szDllPath, _countof(szDllPath));
	PathRemoveFileSpec(szDllPath);
	PathAppend(szDllPath, L"archmgr.dll");

	HMODULE		hMod = LoadLibrary(szDllPath);
	if (NULL == hMod)
	{
		goto FINAL;
	}

	PFN_GET_ARESULT_INSTANCE	pfnGetInstance = NULL;
	
	pfnGetInstance = (PFN_GET_ARESULT_INSTANCE)GetProcAddress(hMod, "GetArchMgrInstance");
	if (NULL == pfnGetInstance)
	{
		goto FINAL;
	}

	pInstance = pfnGetInstance();

	GetModuleFileName(NULL, szDllPath, _countof(szDllPath));
	PathRemoveFileSpec(szDllPath);

	ar = pInstance->Initialize(szDllPath);
	if (!SUCCEEDED(ar))
	{
		goto FINAL;
	}

	// temp.zip의 내용 중 "tag*" 패턴을 만족시키는 파일만 enum
	ar = pInstance->EnumerateItems(L"c:\\temp\\temp.zip", &pResult, L"tag*");
	if (!SUCCEEDED(ar))
	{
		goto FINAL;
	}

	for (INT index = 0; index < pResult->pItemList->size(); index++)
	{
		ARCH_ITEM Item = (*pResult->pItemList)[index];
		wprintf(L"%s FileSize : %I64d PackSize : %I64d \n", Item.FileName.c_str(), Item.FileSize.QuadPart, Item.CompressedSize.QuadPart);
	}

	pInstance->FreeBuffer(pResult);

	wprintf(L"\n\n");

	// test.xlsx 파일을 test2.zip으로 압축
	ar = pInstance->InvokeZipCommand(L"a C:\\temp\\test2.zip \"c:\\temp\\test.xlsx\"", &pResult);
	if (!SUCCEEDED(ar))
	{
		wprintf(L"[FAILED] Fail to compress. %d\n", ar);
		wprintf(L"[ERROR] %S\n", pResult->StdOutput.c_str());
		pInstance->FreeBuffer(pResult);
		goto FINAL;
	}

	wprintf(L"%S\n", pResult->StdOutput.c_str());
	
	pInstance->FreeBuffer(pResult);

FINAL:
	if (pInstance)
	{
		pInstance->Uninitialize();
	}

	return 0;
}

