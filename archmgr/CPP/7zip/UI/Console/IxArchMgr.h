#pragma once

#include <windows.h>
#include <string>
#include <vector>
using namespace std;

typedef struct _ARCH_ITEM
{
	wstring		FileName;
	LARGE_INTEGER FileSize;	
	LARGE_INTEGER CompressedSize;
	FILETIME	FileTime;
	BOOL		IsDir;
} ARCH_ITEM, *PARCH_ITEM;

typedef struct _ARCH_RESULT
{
	wstring				ArchPath;
	wstring				ArchType;		// ex : "zip"
	LARGE_INTEGER		ArchFileSize;
	ULONG				MaxCount;
	BOOL				Aborted;

	vector<ARCH_ITEM>*	pItemList;
	string				StdOutput;
} ARCH_RESULT, *PARCH_RESULT;

#define		ARESULT		HRESULT

#define		ARESULT_ERROR_SUCCESS				0
#define		ARESULT_ERROR_UNSUCCESSFUL			-100
#define		ARESULT_FAIL_TO_NOT_INITIALIZED		-101
#define		ARESULT_FAIL_TO_LOAD_LIBRARY		-102
#define		ARESULT_STILL_ON_PROGRESS			-103
#define		ARESULT_FAIL_TO_PARSE_ARGUMENTS		-104

#define		ARESULT_ERROR_WARNING				-1
#define		ARESULT_ERROR_FATALERROR			-2
#define		ARESULT_ERROR_COMMANDLINE_OPTION_ERROR			-7
#define		ARESULT_ERROR_MEMORY_ERROR			-8
#define		ARESULT_ERROR_USER_BREAK_PROCESS	-255


class IxArchMgr
{
public:
	virtual ARESULT		Initialize(const WCHAR* PluginDir) = 0;

	virtual ARESULT		EnumerateItems(const WCHAR* ArchFilePath, OUT PARCH_RESULT* ppFound, OPTIONAL IN const WCHAR* WildCharPattern = NULL, OPTIONAL IN LONG MaxCount = 0) = 0;
	
	virtual ARESULT		InvokeZipCommand(const WCHAR* CommandLineArgs, OUT PARCH_RESULT* ppFound) = 0;

	virtual VOID			FreeBuffer(PARCH_RESULT pBuffer) = 0;

	virtual ARESULT		Uninitialize() = 0;
};

