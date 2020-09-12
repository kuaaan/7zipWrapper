#include "StdAfx.h"

#include <strsafe.h>

#include <Shlwapi.h>
#pragma comment (lib, "shlwapi.lib")

#include "CxArchMgr.h"


extern int MY_CDECL Main
(
	int numArgs, const WCHAR* args[]
);

DWORD			CxArchMgr::m_TlsIndexInstance = (DWORD)-1;
DWORD			CxArchMgr::m_TlsIndexCurrentResult = (DWORD)-1;

CxArchMgr::CxArchMgr()
{
	m_codecs = NULL;
	m___externalCodecs = NULL;
	m_codecsReleaser = NULL;
	
	m_bInitialized = FALSE;

	m_CurrentProgressCount = 0;
}

ARESULT		CxArchMgr::Initialize(const WCHAR* PluginDir)
{
	ARESULT aResult = ARESULT_ERROR_UNSUCCESSFUL;
	WCHAR	szPluginDir[MAX_PATH] = { 0, };

	try {
		StringCchCopy(szPluginDir, _countof(szPluginDir), PluginDir);
		PathAddBackslash(szPluginDir);

		m_TlsIndexInstance = ::TlsAlloc();
		m_TlsIndexCurrentResult = ::TlsAlloc();

		m_codecs = new CCodecs;

		m___externalCodecs = new CExternalCodecs;
		m___externalCodecs->GetCodecs = m_codecs;
		m___externalCodecs->GetHashers = m_codecs;

		m_codecsReleaser = new CCodecs::CReleaser;
		m_codecsReleaser->Set(m_codecs);

		aResult = m_codecs->Load(szPluginDir);
		if (SUCCEEDED(aResult))
		{
			m_bInitialized = TRUE;
			aResult = ARESULT_ERROR_SUCCESS;
		}		
	}
	catch (...)
	{
		
	}

	if (FALSE == m_bInitialized)
	{
		::TlsFree(m_TlsIndexInstance);
		m_TlsIndexInstance = (DWORD)-1;

		::TlsFree(m_TlsIndexCurrentResult);
		m_TlsIndexCurrentResult = (DWORD)-1;

		delete m_codecsReleaser;

		m_codecsReleaser = NULL;
		m___externalCodecs = NULL;
		m_codecs = NULL;
	}

	return aResult;
}

ARESULT		CxArchMgr::Uninitialize()
{
	ARESULT	aResult = ARESULT_ERROR_UNSUCCESSFUL;

	if (FALSE == m_bInitialized)
	{
		aResult = ARESULT_FAIL_TO_NOT_INITIALIZED;
		goto FINAL;
	}

	m_bInitialized = FALSE;

	for (INT index = 0; index < 30; index++)
	{
		if (m_CurrentProgressCount <= 0)
		{
			break;
		}

		Sleep(100);
	}

	if (m_CurrentProgressCount <= 0)
	{
		aResult = ARESULT_STILL_ON_PROGRESS;
		m_bInitialized = TRUE;
		goto FINAL;
	}

	delete m_codecsReleaser;
	m_codecsReleaser = NULL;

	m_codecs = NULL;
	m___externalCodecs = NULL;

	::TlsFree(m_TlsIndexInstance);
	::TlsFree(m_TlsIndexCurrentResult);

	delete this;

	aResult = ARESULT_ERROR_SUCCESS;
	
FINAL:

	return aResult;
}

VOID			CxArchMgr::FreeBuffer(PARCH_RESULT pBuffer)
{
	if (NULL == pBuffer)
	{
		return;
	}

	if (pBuffer->pItemList)
	{
		delete pBuffer->pItemList;
	}

	delete pBuffer;

	return;
}

CxArchMgr&		CxArchMgr::GetInstanceInternal()
{
	return		*(CxArchMgr*)::TlsGetValue(CxArchMgr::m_TlsIndexInstance);
}

PARCH_RESULT	CxArchMgr::GetResultBuffer()
{
	return		(PARCH_RESULT)::TlsGetValue(CxArchMgr::m_TlsIndexCurrentResult);
}

IxArchMgr*		CxArchMgr::GetInstance()
{
	return		(IxArchMgr*)new CxArchMgr;
}

ARESULT		CxArchMgr::EnumerateItems(const WCHAR* ArchFilePath, OUT PARCH_RESULT* ppFound, OPTIONAL IN const WCHAR* WildCharPattern, OPTIONAL IN LONG MaxCount)
{
	wstring		CommandLine;
	WCHAR		ProcName[MAX_PATH] = { 0, };
	ARESULT	aResult = ARESULT_ERROR_UNSUCCESSFUL;
	LPCWSTR* Argv = NULL;
	INT			Argc = 0;
	PARCH_RESULT	pResult = NULL;

	::InterlockedIncrement(&m_CurrentProgressCount);

	if (FALSE == m_bInitialized)
	{
		aResult = ARESULT_FAIL_TO_NOT_INITIALIZED;
		goto FINAL;
	}

	if (ppFound)
	{
		pResult = new ARCH_RESULT;
		pResult->pItemList = new vector<ARCH_ITEM>;
		pResult->MaxCount = MaxCount;

		SetTlsInfo(pResult);
	}
	else {
		SetTlsInfo(NULL);
	}

	GetModuleFileNameW(NULL, ProcName, _countof(ProcName));

	CommandLine = (wstring)PathFindFileName(ProcName) + L" l \"" + ArchFilePath + L"\"";

	if (WildCharPattern)
	{
		CommandLine += (wstring)L" -i!" + WildCharPattern;
	}

	Argv = (LPCWSTR*)CommandLineToArgvW(CommandLine.c_str(), &Argc);
	if (NULL == Argv)
	{
		aResult = ARESULT_FAIL_TO_PARSE_ARGUMENTS;
		goto FINAL;
	}

	aResult = Main(Argc, Argv);

FINAL:

	if (aResult > 0)
	{
		aResult *= -1;
	}

	if (Argv)
	{
		LocalFree(Argv);
	}

	if (ppFound)
	{
		*ppFound = pResult;
	}

	::InterlockedDecrement(&m_CurrentProgressCount);

	return aResult;
}

ARESULT		CxArchMgr::InvokeZipCommand(const WCHAR* CommandLineArgs, OUT PARCH_RESULT* ppFound)
{
	wstring		CommandLine;
	WCHAR		ProcName[MAX_PATH] = { 0, };
	ARESULT	aResult = ARESULT_ERROR_UNSUCCESSFUL;
	LPCWSTR*	Argv = NULL;
	INT			Argc = 0;
	PARCH_RESULT	pResult = NULL;

	::InterlockedIncrement(&m_CurrentProgressCount);

	if (FALSE == m_bInitialized)
	{
		aResult = ARESULT_FAIL_TO_NOT_INITIALIZED;
		goto FINAL;
	}

	if (ppFound)
	{
		pResult = new ARCH_RESULT;
		pResult->pItemList = new vector<ARCH_ITEM>;
		pResult->MaxCount = 0;

		SetTlsInfo(pResult);
	}
	else {
		SetTlsInfo(NULL);
	}

	GetModuleFileNameW(NULL, ProcName, _countof(ProcName));

	CommandLine = (wstring)PathFindFileName(ProcName) + L" " + CommandLineArgs;

	Argv = (LPCWSTR*)CommandLineToArgvW(CommandLine.c_str(), &Argc);
	if (NULL == Argv)
	{
		aResult = ARESULT_FAIL_TO_PARSE_ARGUMENTS;
		goto FINAL;
	}

	aResult = Main(Argc, Argv);

FINAL:
	
	if (aResult > 0)
	{
		aResult *= -1;
	}

	if (Argv)
	{
		LocalFree(Argv);
	}

	if (ppFound)
	{
		*ppFound = pResult;
	}

	::InterlockedDecrement(&m_CurrentProgressCount);

	return aResult;
}

CCodecs* CxArchMgr::GetCodecs()
{
	return m_codecs;
}

CExternalCodecs& CxArchMgr::GetExternalCodecs()
{
	return *m___externalCodecs;
}

CCodecs::CReleaser& CxArchMgr::GetCodecsReleaser()
{
	return *m_codecsReleaser;
}

ARESULT				CxArchMgr::SetTlsInfo(PARCH_RESULT pResult)
{
	::TlsSetValue(m_TlsIndexInstance, this);
	::TlsSetValue(m_TlsIndexCurrentResult, pResult);

	return ARESULT_ERROR_SUCCESS;
}