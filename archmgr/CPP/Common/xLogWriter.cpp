/**   
@file    LogWriter.cpp
@date    2009/09/16
@author  김태형(kuaaan@peepleware.co.kr)
@brief   구버젼의 구조체 정의 모음
*/

#include "stdafx.h"
#pragma warning (disable:4995)


#include "xLogWriter.h"

#ifdef	_SET_LOGPATH_XCOMMONDIR
#include "CxCommonApi.h"
#endif

#include <process.h>

#ifndef _X_NO_LOG

#pragma comment(lib, "Advapi32.lib")

typedef struct _X_FILELOG_ITEM
{
	const WCHAR* pszLogFileName;
	CHAR		szBuffer[MAX_PATH * 4];
} X_FILELOG_ITEM, *PX_FILELOG_ITEM;

CLogWriter g_LogWriter;

BOOL	CLogWriter::m_bWriteDetailLog = FALSE;
BOOL	CLogWriter::m_bWriteIoLog = FALSE;

DWORD	CLogWriter::m_LogSettingCheckTime = 0;

TCHAR	CLogWriter::m_szLogPath[MAX_PATH] = {0,};	//full path of log file.
TCHAR	CLogWriter::m_szLogDir[MAX_PATH] = {0,};	//parents dir of log file.
INT		CLogWriter::m_nLogLevel = LOG_DEBUG;
DWORD	CLogWriter::m_SessionId = 0;

HANDLE	CLogWriter::m_InitThread = NULL;
BOOL	CLogWriter::m_bInitialized = FALSE;

//CRITICAL_SECTION	CLogWriter::m_Crit;
//vector<PVOID>		CLogWriter::m_MemoryPool;

CLogWriter::CLogWriter()
{
	SetLogPath(NULL, NULL);
	::ProcessIdToSessionId(GetCurrentProcessId(), &m_SessionId);

	::InitializeCriticalSection(&m_Crit);
}

CLogWriter::~CLogWriter()
{
	BOOL	bResult = FALSE;
	DWORD	dwResult = 0;
	vector<PVOID>::iterator	iter;

	::EnterCriticalSection(&m_Crit);
	
	iter = m_MemoryPool.begin();

	while (iter != m_MemoryPool.end())
	{
		delete *iter;
		iter = m_MemoryPool.erase(iter);
	}

	::LeaveCriticalSection(&m_Crit);

	::DeleteCriticalSection(&m_Crit);		// LogWriter의 Free 후 다른 소멸자에서 로그 작성이 시도될 수도 있다.
}

TCHAR*	CLogWriter::GetWideBuffer()
{
	PVOID		pBuffer = NULL;
	
	::EnterCriticalSection(&m_Crit);

	if (m_MemoryPool.empty())
	{
		pBuffer = new WCHAR[X_LOGBUF_SIZE];
		goto FINAL;
	}

	pBuffer = m_MemoryPool.back();
	m_MemoryPool.pop_back();

FINAL:

	::LeaveCriticalSection(&m_Crit);

	return (TCHAR*)pBuffer;
}

CHAR*	CLogWriter::GetAnsiBuffer()
{
	return (CHAR*)GetWideBuffer();
}

VOID	CLogWriter::ReturnBuffer(PVOID	pBuffer)
{
	::EnterCriticalSection(&m_Crit);
	m_MemoryPool.push_back(pBuffer);
	::LeaveCriticalSection(&m_Crit);
}

void	CLogWriter::BackupLog(const WCHAR*		pszLogPath)
{
	TCHAR	backupFilePath[MAX_PATH];
	const	WCHAR*		pszLogFilePath = NULL;
	SYSTEMTIME			LocalTime = {0,};

	ZeroMemory(backupFilePath, sizeof backupFilePath);
	if (pszLogPath == NULL)
	{
		pszLogFilePath = m_szLogPath;
	} else {
		pszLogFilePath = pszLogPath;
	}

	GetLocalTime(&LocalTime);
	//_snwprintf_s(backupFilePath, MAX_PATH - 1, _TRUNCATE, TEXT("%s.bak"), pszLogFilePath);
	_snwprintf_s(backupFilePath, MAX_PATH - 1, _TRUNCATE, TEXT("%s.%04d%02d%02d_%02d%02d%02d.%d.bak"), pszLogFilePath, LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay, LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond, LocalTime.wMilliseconds);

	MoveFileEx(pszLogFilePath, backupFilePath, MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING);
	SetFileAttributes(backupFilePath, FILE_ATTRIBUTE_ARCHIVE);
		
	DeleteOldLogs(pszLogFilePath);
}


void	CLogWriter::DeleteLogFile()
{
	SetFileAttributes(m_szLogPath, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(m_szLogPath);
}

void	CLogWriter::SetLogPath(HINSTANCE hInstance, PCTSTR pUseThisPath)
{
	DWORD	dwSessionId = 0;
	WCHAR		szLogName[MAX_PATH] = {0,};
	DWORD		cchWritten = 0 ;
	DWORD		bResult = 0 ;
	WCHAR		szTempPath[MAX_PATH] = {0,};

	if(pUseThisPath)
	{
		ExpandEnvironmentStrings(pUseThisPath, szTempPath, _countof(szTempPath));
		lstrcpyn(m_szLogPath, szTempPath, MAX_PATH);
		lstrcpyn(m_szLogDir, szTempPath, MAX_PATH);		
		PathRemoveFileSpec(m_szLogDir);

		if (PathIsDirectory(m_szLogDir) == FALSE)
		{
			CreateDirectory(m_szLogDir, NULL);
		}
	}
	else
	{
		TCHAR	LogFileName[MAX_PATH] = {0,};

		GetModuleFileName(hInstance, m_szLogDir, MAX_PATH - 4);
		PathRemoveFileSpec(m_szLogDir);
#ifdef	_SET_LOGPATH_XCOMMONDIR
		CxCommonApi::GetxCommonDir(m_szLogDir, MAX_PATH);
#endif
		PathAppend(m_szLogDir, L"logs");

		if (PathIsDirectory(m_szLogDir) == FALSE)
		{
			CreateDirectory(m_szLogDir, NULL);
		}

		GetModuleFileName(hInstance, LogFileName, MAX_PATH - 4);
		StringCchCat(LogFileName, _countof(LogFileName), L".log");
		StringCchPrintf(m_szLogPath, MAX_PATH, L"%s\\%s", m_szLogDir, PathFindFileName(LogFileName));

		// GetSessionLogFileName 시 GetUserName을 호출할 때 LoaderLock 관련 데드락이 발생하는 경우가 있어서 1초 타임아웃을 주기 위해 비동기로 구현함. (특히 Injection되는 DLL의 경우 해당)
		// GetSessionLogFileNameAsync(m_szLogPath, _countof(m_szLogPath));
	}
}

PTSTR	CLogWriter::GetLogPath(PTSTR ptszBuf, int nBufLen)
{
	lstrcpyn(ptszBuf, m_szLogPath, nBufLen);
	return ptszBuf;
}


/*
void	CLogWriter::ShowLog()
{
	if(((INT_PTR)ShellExecute(NULL, TEXT("open"), m_szLogPath, NULL, NULL, SW_SHOW)) <= 32)
	{
		TCHAR					cmdLine[1024];
		STARTUPINFO				si;
		PROCESS_INFORMATION		pi;

		ZeroMemory(cmdLine, sizeof cmdLine);
		_snwprintf_s(cmdLine, 1023, _TRUNCATE, TEXT("notepad %s"), m_szLogPath);

		ZeroMemory(&si, sizeof si);
		si.cb = sizeof(STARTUPINFO);
		CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}
*/

/*
int		CLogWriter::MsgBox(HWND hwndParent, UINT uType, PCTSTR ptszFormat, ...)
{
	va_list		argptr;
	TCHAR		tszBuf[1024], path[MAX_PATH], *ptstr;
	const int	nBufLen = 1023;

	ZeroMemory(tszBuf, sizeof tszBuf);

	if(ptszFormat && *ptszFormat)
	{
		va_start(argptr, ptszFormat);
		_vsnwprintf_s(tszBuf, nBufLen, ptszFormat, argptr);
		va_end(argptr);
	}
	else
		tszBuf[0] = 0;

	GetModuleFileName(NULL, path, MAX_PATH);
	ptstr = _tcsrchr(path, '\\');

	return MessageBox(hwndParent, tszBuf, ptstr ? ptstr + 1 : path, uType);
}
*/

void	CLogWriter::SetLogLevel(INT nLogLevel)
{
	m_nLogLevel = nLogLevel;
}

int		CLogWriter::Trace(PCTSTR pszLogFileName, INT nErrorLevel, LPCTSTR pszFuncName, LPCTSTR pszFilePath, DWORD dwLineNumber, DWORD dwLastError, PCTSTR ptszFormat, ...)
{
	TCHAR*			pszMemoryBuf = GetWideBuffer();
	ULONG			cchBuf = X_LOGBUF_SIZE;
	CHAR*			pszFileBuf = GetAnsiBuffer();
	const int		nBufLen = 1023;
	int				nLen = 0;
	va_list			argptr;
	SYSTEMTIME		stime;
	HANDLE			hFile = INVALID_HANDLE_VALUE;
	DWORD			dwBytesWritten = 0;
	TCHAR*			pFileName = NULL;
	TCHAR			szLogPath[MAX_PATH] = {0,};
	const WCHAR*	pszLogPath = NULL;
	
	if (nErrorLevel < m_nLogLevel)
	{
		goto FINAL;
	}

	if (pszFilePath == NULL)
	{
		goto FINAL;
	}

	ZeroMemory(pszMemoryBuf, cchBuf);

	pFileName = StrRChr(pszFilePath, NULL, L'\\');
	if (pFileName == NULL)
	{
		pFileName = (TCHAR*)pszFilePath;
	} else
	{
		pFileName++;
	}

	if(ptszFormat && *ptszFormat)
	{
		GetLocalTime(&stime);

		nLen = _snwprintf_s(pszMemoryBuf, cchBuf, _TRUNCATE, TEXT("[%d:%d] %04u-%02u-%02u %02u:%02u:%02u.%03u [0x%X(%d) %s] "),
			GetCurrentProcessId(), m_SessionId, stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds,
			GetCurrentThreadId(), dwLastError, pszFuncName);

		va_start(argptr, ptszFormat);
		nLen += _vsnwprintf_s(pszMemoryBuf + nLen, cchBuf - 2 - nLen, _TRUNCATE, ptszFormat, argptr);
		va_end(argptr);
	}
	nLen += _snwprintf_s(pszMemoryBuf + nLen, cchBuf - nLen, _TRUNCATE, TEXT("\r\n"));
	
#ifdef _UNICODE
	WideCharToMultiByte(CP_ACP, NULL, pszMemoryBuf, -1, pszFileBuf, cchBuf, NULL, NULL);
#else
	StringCchCopy(pszFileBuf, cchBuf, pszMemoryBuf);
#endif

#ifdef _XLOG_DBGOUTPUTSTRING
	OutputDebugString(pszMemoryBuf);
#else
	if (pszLogFileName == NULL)
	{
		hFile = CreateFile(m_szLogPath, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
		pszLogPath = m_szLogPath;
	} else {
		if (m_szLogDir[0] == NULL)
		{
			SetLogPath(NULL, NULL);
		}

		StringCchCopy(szLogPath, _countof(szLogPath), m_szLogDir);
		PathAppend(szLogPath, pszLogFileName);
//		GetSessionLogFileName(szLogPath, _countof(szLogPath));

		hFile = CreateFile(szLogPath, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
		pszLogPath = szLogPath;
	}

	if(hFile != INVALID_HANDLE_VALUE)
	{
		if(GetFileSize(hFile, NULL) > MAX_LOGFILE_SIZE)
		{
			CloseHandle(hFile);
			BackupLog(pszLogPath);
			hFile = CreateFile(pszLogPath, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
			if(hFile == INVALID_HANDLE_VALUE)
			{ 
				goto FINAL;
			}
		}

		SetFilePointer(hFile, 0, NULL, FILE_END);
		WriteFile(hFile, (LPCVOID)pszFileBuf, (DWORD)strlen(pszFileBuf) * sizeof(pszFileBuf[0]), &dwBytesWritten, NULL);
		CloseHandle(hFile);
	}
#endif

FINAL:
	if (pszFileBuf)
	{
		ReturnBuffer(pszFileBuf);
	}

	if (pszMemoryBuf)
	{
		ReturnBuffer(pszMemoryBuf);
	}

	return dwBytesWritten;
}



//int		CLogWriter::PwDbgOut(INT nErrorLevel, LPCTSTR pszFuncName, LPCTSTR pszFilePath, DWORD dwLineNumber, DWORD dwLastError, PCTSTR ptszFormat, ...)
//{
//	TCHAR			tszBuf[1024 * 4] = {0,};
//	CHAR			szBuffer[1024 * 4] = {0,};
//	const int		nBufLen = 1023;
//	int				nLen = 0;
//	va_list			argptr;
//	SYSTEMTIME		stime;
//	DWORD			dwBytesWritten = 0;
//	TCHAR*			pFileName = NULL;
//
//	if (nErrorLevel < m_nLogLevel)
//		return FALSE;
//
//	ZeroMemory(tszBuf, _countof(tszBuf));
//
//	if (pszFilePath == NULL)
//	{
//		return FALSE;
//	}
//
//	pFileName = StrRChr(pszFilePath, NULL, L'\\');
//	if (pFileName == NULL)
//	{
//		pFileName = (TCHAR*)pszFilePath;
//	} else
//	{
//		pFileName++;
//	}
//
//	if(ptszFormat && *ptszFormat)
//	{
//		GetLocalTime(&stime);
//
//		nLen = _snwprintf_s(tszBuf, _countof(tszBuf), _TRUNCATE, TEXT("%04u-%02u-%02u %02u:%02u:%02u.%03u [%s 0x%08X(0x%08X)] "), 
//									stime.wYear, stime.wMonth, stime.wDay, stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds,
//									pszFuncName, GetCurrentThreadId(), dwLastError);
//
//		va_start(argptr, ptszFormat);
//		nLen += _vsnwprintf_s(tszBuf + nLen, _countof(tszBuf) - 2 - nLen, _TRUNCATE, ptszFormat, argptr);
//		va_end(argptr);
//	}
//
//	nLen += _snwprintf_s(tszBuf + nLen, _countof(tszBuf) - nLen, _TRUNCATE, TEXT("\r\n"));
//
//#ifdef _UNICODE
//	WideCharToMultiByte(CP_ACP, NULL, tszBuf, -1, szBuffer, _countof(szBuffer), NULL, NULL);
//#else
//	StringCchCopy(szBuffer, _countof(szBuffer), tszBuf);
//#endif
//
//	OutputDebugString(tszBuf);
//
//	return dwBytesWritten;
//}


#define _SECOND ((ULONGLONG) 10000000)
#define _MINUTE (60 * _SECOND)
#define _HOUR   (60 * _MINUTE)
#define _DAY    (24 * _HOUR)

int		CLogWriter::AddDayToSystemTime(LPSYSTEMTIME  pSystemTime, LONG AddDay)
{
	FILETIME		FileTime = {0,};
	ULARGE_INTEGER	Diff = {0,};
	ULARGE_INTEGER	FileTimeBuffer = {0,};

	SystemTimeToFileTime(pSystemTime, &FileTime);

	Diff.QuadPart = (ULONGLONG)AddDay * _DAY;

	FileTimeBuffer.LowPart = FileTime.dwLowDateTime;
	FileTimeBuffer.HighPart = FileTime.dwHighDateTime;

	FileTimeBuffer.QuadPart += Diff.QuadPart;

	FileTime.dwLowDateTime = FileTimeBuffer.LowPart;
	FileTime.dwHighDateTime = FileTimeBuffer.HighPart;

	FileTimeToSystemTime(&FileTime, pSystemTime);

	return ERROR_SUCCESS;
}

int		CLogWriter::DeleteOldLogs(LPCTSTR pszLogFileName, DWORD BackupDays)
{
	WCHAR		szLogPath[MAX_PATH] = {0,};
	WCHAR		szFindPath[MAX_PATH] = {0,};
	WCHAR		szDeletePath[MAX_PATH] = {0,};
	int			nResult = 0;
	SYSTEMTIME		SystemTime = {0,};
	SYSTEMTIME		CurrentTime = {0,};
	WCHAR		szCurrentBackupName[MAX_PATH] = {0,};
	
	WIN32_FIND_DATA		FindData = {0,};
	HANDLE				hFind = INVALID_HANDLE_VALUE;

	do 
	{
		StringCchCopy(szLogPath, _countof(szLogPath), m_szLogPath);

		if (pszLogFileName)
		{
			PathRemoveFileSpec(szLogPath);
			PathAppend(szLogPath, pszLogFileName);
		}
		
		GetLocalTime(&CurrentTime);
		AddDayToSystemTime(&CurrentTime, -1 * BackupDays);

		_snwprintf_s(szCurrentBackupName, _countof(szCurrentBackupName), _TRUNCATE, TEXT("%s.%04d%02d%02d_%02d%02d%02d.%d.bak"), 
						szLogPath, CurrentTime.wYear, CurrentTime.wMonth, CurrentTime.wDay, CurrentTime.wHour, CurrentTime.wMinute, CurrentTime.wSecond, CurrentTime.wMilliseconds);

		_snwprintf_s(szFindPath, _countof(szFindPath), _TRUNCATE, TEXT("%s.*_*.*.bak"), szLogPath);

		hFind = ::FindFirstFile(szFindPath, &FindData);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			nResult = ERROR_SUCCESS;
			continue;
		}

		do 
		{
			StringCchCopy(szDeletePath, _countof(szDeletePath), m_szLogDir);
			PathAppend(szDeletePath, FindData.cFileName);

			if (_wcsicmp(szDeletePath, szCurrentBackupName) < 0)
			{
				::DeleteFile(szDeletePath);
			}
		} while (::FindNextFile(hFind, &FindData));

		nResult = ERROR_SUCCESS;
	} while (FALSE);
	
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
	}

	return nResult;
}

BOOL		CLogWriter::CheckLogSettings()
{
	WCHAR		szDetailSettingCheckPath[MAX_PATH];

	if (GetTickCount() - m_LogSettingCheckTime < LOG_SETTING_CHECK_PERIOD_MILLISECOND)
	{
		return TRUE;
	}
	
	StringCchCopy(szDetailSettingCheckPath, _countof(szDetailSettingCheckPath), m_szLogDir);
	PathAppend(szDetailSettingCheckPath, L"MakeDetailLog");

	if (PathFileExists(szDetailSettingCheckPath))
	{
		m_bWriteDetailLog = TRUE;
	} else {
		m_bWriteDetailLog = FALSE;
	}

	StringCchCopy(szDetailSettingCheckPath, _countof(szDetailSettingCheckPath), m_szLogDir);
	PathAppend(szDetailSettingCheckPath, L"MakeIoLog");

	if (PathFileExists(szDetailSettingCheckPath))
	{
//		PmonLog(L"MakeIoLog flag is found");
		m_bWriteIoLog = TRUE;
	} else {
//		PmonLog(L"MakeIoLog flag is NOT found : %s", szDetailSettingCheckPath);
		m_bWriteIoLog = FALSE;
	}

	m_LogSettingCheckTime = GetTickCount();

	return TRUE;
}

BOOL	CLogWriter::IsFileExists(const WCHAR* pszFileName)
{
	WCHAR		szFilePath[MAX_PATH] = {0,};

	StringCchCopy(szFilePath, _countof(szFilePath), CLogWriter::m_szLogDir);
	PathAppend(szFilePath, pszFileName);

	if (PathFileExists(szFilePath))
	{
		return TRUE;
	} else {
		return FALSE;
	}
}

#endif