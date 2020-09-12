#pragma once
#include "IxArchMgr.h"
#include "LoadCodecs.h"
#include "CreateCoder.h"

class CxArchMgr : public IxArchMgr
{
public:
	CxArchMgr();

	virtual ARESULT		Initialize(const WCHAR* PluginDir);
	virtual ARESULT		Uninitialize();

	virtual ARESULT		EnumerateItems(const WCHAR* ArchFilePath, OUT PARCH_RESULT* ppFound, OPTIONAL IN const WCHAR* WildCharPattern = NULL, OPTIONAL IN LONG MaxCount = 0);

	virtual ARESULT		InvokeZipCommand(const WCHAR* CommandLineArgs, OUT PARCH_RESULT* ppFound);

	virtual VOID			FreeBuffer(PARCH_RESULT pBuffer);

	static IxArchMgr*		GetInstance();

	static CxArchMgr&		GetInstanceInternal();

	CCodecs*				GetCodecs();

	CExternalCodecs&		GetExternalCodecs();

	CCodecs::CReleaser&		GetCodecsReleaser();

	static PARCH_RESULT		GetResultBuffer();

protected:
	CCodecs*				m_codecs;
	CExternalCodecs*		m___externalCodecs;
	CCodecs::CReleaser*		m_codecsReleaser;

	static DWORD			m_TlsIndexInstance;
	static DWORD			m_TlsIndexCurrentResult;

	ARESULT				SetTlsInfo(PARCH_RESULT pResult);

	volatile LONG			m_CurrentProgressCount;

	BOOL					m_bInitialized;
};

