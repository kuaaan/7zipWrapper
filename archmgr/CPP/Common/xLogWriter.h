#ifndef __COMMON_LOG__H__
#define __COMMON_LOG__H__

#include <stdio.h>
#include <windows.h>
#include <TCHAR.H>
#include <strsafe.h>

#include "yvals.h"
#include "shlwapi.h"

#include <vector>
using namespace std;

// #define _X_ASYNC_FILELOG
//#define		_XLOG_DBGOUTPUTSTRING
//#define		_SET_LOGPATH_XCOMMONDIR

#pragma comment(lib, "shlwapi.lib")

//#define _CONSOLE_LOG

//#define _PREREAD_LOG

#define _ERROR_LOG
//#define _INFO_LOG
//#define _CONTEXT_LOG
//#define _RESOURCE_LOG

//#define _INFO_LOG
//#define _LOCALCOPY_LOG
//#define _LOCAL_IO_LOG
//#define _ACL_LOG
#define _IO_LOG
//#define _DRM_LOG

//#define _FILE_LOG
//#define _CONTEXT_LOG

#ifdef _DEBUG
//#define _FILE_LOG
#endif


#define		PmonLog			xErrorLog
#define		PmonCoreLog		xErrorLog

#define		VssLog(...)			g_LogWriter.Trace(L"sensor.shadowcopy.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)


//#define		DnsLog(...)			g_LogWriter.Trace(L"sensor.dnslog.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		DnsLog(...)			/##/

#define		CompressLog(...)			g_LogWriter.Trace(L"sensor.compress.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		UploadCheckLog(...)			g_LogWriter.Trace(L"sensor.fileupload.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		xCommonLog(...)			g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		OutlookLog(...)		g_LogWriter.Trace(L"sensor.outlook.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define		DropEventLog(...)		g_LogWriter.Trace(L"sensor.dropevent.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		DropEventLog(...)		/##/

//#define		InsertProcLog(...)		g_LogWriter.Trace(L"sensor.InsertProc.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		InsertProcLog(...)		/##/

//#define		DeleteProcLog(...)		g_LogWriter.Trace(L"sensor.DeleteProc.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		DeleteProcLog(...)		/##/

//#define		RegisterFile(...)		g_LogWriter.Trace(L"sensor.RegisterFile.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		RegisterFile(...)		/##/

//#define		InflowCheck(...)		g_LogWriter.Trace(L"sensor.InflowCheck.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		InflowCheck(...)		/##/

#define		QueryPlanLog(...)		g_LogWriter.Trace(L"sensor.queryplan.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define		ProcMemLog(...)	g_LogWriter.Trace(L"sensor.ProcMem.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		ProcMemLog(...)		/##/

//#define		SystemFileLog(...)	g_LogWriter.Trace(L"sensor.Systemfile.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		SystemFileLog(...)		/##/

#define		RelatedLog(...)		g_LogWriter.Trace(L"sensor.related.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define		RelatedLog(...)		/##/

#define		FileLog(...)		/##/
//#define		FileLog(...) g_LogWriter.Trace(L"sensor.FileLog.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		SeqLog(...)		/##/
//#define		SeqLog(...) g_LogWriter.Trace(L"sensor.Seq.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		AnalyzeLog(...) /##/
//#define		AnalyzeLog(...) g_LogWriter.Trace(L"sensor.analyze.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		NotifyLog(...) g_LogWriter.Trace(L"sensor.notify.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		BypassProcLog(...) g_LogWriter.Trace(L"sensor.bypassproc.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define		BypassKernelLog(...) g_LogWriter.Trace(L"sensor.bypasskernel.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define		PipeLog(...) g_LogWriter.Trace(L"sensor.pipe.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define MainRegLog(...) g_LogWriter.Trace(L"sensor.mainreg.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define MainRegLog(...)  /##/

//#define ImportantLog(...) g_LogWriter.Trace(L"sensor.important.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ImportantLog(...) /##/

#define TimeLog(...) g_LogWriter.Trace(L"sensor.time.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define OpenProcessLog(...) g_LogWriter.Trace(L"sensor.openprocess.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define OpenProcessLog(...) /##/

#define		CrawlingLog(...) g_LogWriter.Trace(L"sensor.crawling.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define	CrawlingLog(...) /##/

#define ZoneIdLog(...) /##/
//#define ZoneIdLog(...) g_LogWriter.Trace(L"sensor.zoneid.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define FileTransferLog(...) g_LogWriter.Trace(L"sensor.filetransfer.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define FileTransferLog(...) /##/

//#define CheckDupLog(...) g_LogWriter.Trace(L"sensor.dup.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define CheckDupLog(...)  /##/

//#define ProcGuidLog(...) g_LogWriter.Trace(L"sensor.processguid.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ProcGuidLog(...) /##/

#define BlockLog(...) g_LogWriter.Trace(L"sensor.block.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define BlockLog(...) /##/

#define PipeLog(...) g_LogWriter.Trace(L"sensor.pipe.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define PipeLog(...)		/##/


//#define InflowLog(...)		g_LogWriter.Trace(L"sensor.inflow.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define InflowLog(...)		/##/

//#define FileListLog(...)		g_LogWriter.Trace(L"sensor.filelist.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define FileListLog(...)		/##/

//#define DocListLog(...)		g_LogWriter.Trace(L"sensor.doclist.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define DocListLog(...)		/##/

#define PathConvLog(...) g_LogWriter.Trace(L"sensor.pathconv.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define InjectionLog(...) g_LogWriter.Trace(L"sensor.injection.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define SingletonLog(...) g_LogWriter.Trace(L"sensor.singleton.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define XbaLog(...) g_LogWriter.Trace(L"sensor.xba.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ProcMonLog(...) g_LogWriter.Trace(L"sensor.procmon.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define PathLog(...) /##/
//#define PathLog(...) g_LogWriter.Trace(L"sensor.path.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define ReqLog(...) g_LogWriter.Trace(L"sensor.sensorreq.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define	FalsePositiveLog(...) g_LogWriter.Trace(L"sensor.xba.falsepositive.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define ProcLog(...) g_LogWriter.Trace(L"sensor.processdb.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ProcLog(...) /##/

#define HashLog(...)  /##/
//#define HashLog(...) g_LogWriter.Trace(L"sensor.hash.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define RegHash(...) /##/
//#define RegHash(...) g_LogWriter.Trace(L"sensor.reghash.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define GetHash(...) /##/
//#define GetHash(...) g_LogWriter.Trace(L"sensor.gethash.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define CatCertLog(...) g_LogWriter.Trace(L"sensor.catcert.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define FileHashLog(...) g_LogWriter.Trace(L"sensor.filehash.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define FileHashLog(...) /##/


#define HashFailLog(...) g_LogWriter.Trace(L"sensor.filehash.fail.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define EventLog(...) g_LogWriter.Trace(L"sensor.eventlog.log", LOG_CRITICAL, L"", L"", 0, GetLastError(), __VA_ARGS__)
//#define EventLog(...)  /##/

#define ExploitLog(...) g_LogWriter.Trace(L"sensor.exploit.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define DetectLog(...) g_LogWriter.Trace(L"sensor.xba.detect.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

//#define StackLog(...) g_LogWriter.Trace(L"sensor.stack.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define StackLog(...) /##/

#define AsmLog(...) /##/
//#define AsmLog(...) g_LogWriter.Trace(L"sensor.asm.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define ModuleLog(...) g_LogWriter.Trace(L"sensor.module.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ModuleLog(...) /##/

#define FileTimeLog(...) g_LogWriter.Trace(L"sensor.filetime.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define ShReloadLog(...) g_LogWriter.Trace(L"sensor.shreload.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define ShReloadLog(...) /##/

#ifndef _NO_EXCEPTION_LOG
#define ExceptionLog(...) g_LogWriter.Trace(L"exception.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define ExceptionLog(...) /##/
#endif

#ifdef _RESOURCE_LOG
#define ResourceLog(...) g_LogWriter.Trace(L"resource.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define ResourceLog(...) /##/
#endif

#ifdef _IOTRACE_LOG
	#ifdef _UNICODE
		#define PwIoTrace(...) g_LogWriter.Trace(L"sensor.iotrace.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
	#else
		#ifndef PwIoTrace
			#define PwIoTrace(...) g_LogWriter.Trace("sensor.iotrace.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#endif
	#endif
#else 
	#define PwIoTrace(...) /##/
#endif

#ifdef _CACHE_LOG
#define CacheLog(...) g_LogWriter.Trace(L"sensor.cache.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define CacheLog(...) /##/
#endif

#ifdef _CONTEXT_LOG
#define ContextLog(...) g_LogWriter.Trace(L"sensor.context.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define ContextLog(...) /##/
#endif

#ifdef _PERFORMANCE_LOG
#define DurationLog(...) g_LogWriter.Trace(L"sensor.duration.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define DurationLog(...) /##/
#endif

#ifdef _DIRSIZE_LOG
#define DirSizeLog(...) g_LogWriter.Trace(L"sensor.dirsize.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else 
#define DirSizeLog(...) /##/
#endif

#ifdef _FILE_LOG
	#ifdef _UNICODE
		#define xTrace(...) g_LogWriter.Trace(NULL, LOG_DEBUG, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xLog(...) g_LogWriter.Trace(NULL, LOG_INFORM, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xErrorLog(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#ifndef PwIoTrace
			#define PwIoTrace(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#endif
	#else
		#define xTrace(...) g_LogWriter.Trace(NULL, LOG_DEBUG, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xLog(...) g_LogWriter.Trace(NULL, LOG_INFORM, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xErrorLog(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#ifndef PwIoTrace
			#define PwIoTrace(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#endif
	#endif

	#define PwMsgBox(...)	g_LogWriter.MsgBox(NULL, MB_OK, __VA_ARGS__)
	#define PwShowLog()		g_LogWriter.ShowLog()
	#define	PwSetLogLevel(X)	g_LogWriter.SetLogLevel(X)
#else
#ifdef _INFO_LOG
	#ifdef _UNICODE
		#define xErrorLog(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xLog(...) g_LogWriter.Trace(NULL, LOG_INFORM, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#ifndef PwIoTrace
			#define PwIoTrace(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
		#endif
	#else
		#define xErrorLog(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#define xLog(...) g_LogWriter.Trace(NULL, LOG_INFORM, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#ifndef PwIoTrace
			#define PwIoTrace(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
		#endif
	#endif

	#define xTrace(...) /##/

#else
	#ifdef _ERROR_LOG
		#ifdef _UNICODE
			#define xErrorLog(...) g_LogWriter.Trace(NULL, LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
			#ifndef PwIoTrace
				#define PwIoTrace(...) g_LogWriter.Trace("sensor.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
			#endif
		#else
			#define xErrorLog(...) g_LogWriter.Trace("sensor.log", LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
			#ifndef PwIoTrace
				#define PwIoTrace(...) g_LogWriter.Trace("sensor.log", LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
			#endif
		#endif

		#define xLog(...) /##/
		#define xTrace(...) /##/

	#else
		// 아무것도 정의안된 경우
		#define xErrorLog(...) /##/
		#define xLog(...) /##/
		#define xTrace(...) /##/

		#ifndef PwIoTrace
			#define PwIoTrace(...) /##/
		#endif
	#endif	// #ifdef _ERROR_LOG

#endif	// #ifdef _INFO_LOG

#endif	// #ifdef _FILE_LOG


#ifndef _SKIP_INJECTION_LOG
#ifdef _UNICODE
#define AntiInjectionLog(...) g_LogWriter.Trace(L"sensor.antiinjection.log", LOG_CRITICAL, L"", L"", 0, 0, __VA_ARGS__)
#else
#define AntiInjectionLog(...) g_LogWriter.Trace("sensor.antiinjection.log", LOG_CRITICAL, "", "", 0, 0, __VA_ARGS__)
#endif
#else 
#define AntiInjectionLog(...) /##/
#endif


#define DelayLog(...)		g_LogWriter.Trace(L"sensor.delay.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#define SqlLog(...)		g_LogWriter.Trace(L"sensor.sql.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)

#ifndef _SKIP_FILTER_POLICY_LOG
#ifdef _UNICODE
#define FilterLog(...) g_LogWriter.Trace(L"sensor.filterpolicy.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#else
#define FilterLog(...) g_LogWriter.Trace("sensor.filterpolicy.log", LOG_CRITICAL, __FUNCTION__, __FILE__, __LINE__, GetLastError(), __VA_ARGS__)
#endif
#else if
#define FilterLog(...) /##/
#endif
#define DelayLog(...)		g_LogWriter.Trace(L"sensor.delay.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
#define CrawlerLog(...)		g_LogWriter.Trace(L"sensor.crawler.log", LOG_CRITICAL, __FUNCTIONW__, __FILEW__, __LINE__, GetLastError(), __VA_ARGS__)
//#define SqlLog(...)		/##/


#ifdef _X_NO_LOG
#undef			xErrorLog
#define			xErrorLog(...)				/##/
#undef			InjectionLog
#define			InjectionLog(...)			/##/
#undef			xLog
#define			xLog(...)					/##/
#undef			xTrace
#define			xTrace(...)					/##/
#undef			DelayLog
#define			DelayLog(...)				/##/
#endif



#ifdef _FILE_LOG
	#define MAX_LOGFILE_SIZE		10240000
#else
	#define MAX_LOGFILE_SIZE		1024000
#endif

#define		LOG_DIRECTORY_NAME L"VWormHole"

enum AD_LOG_LEVEL
{
	LOG_DEBUG = 0,
	LOG_INFORM,
	LOG_CRITICAL
};

#define	DEFAULT_LOGLEVEL	LOG_INFORM

#define		LOG_BACKUP_DAYS		3
#define		LOG_SETTING_CHECK_PERIOD_MILLISECOND		(5 * 60 * 1000)

#define		X_LOGBUF_SIZE		(16*1024)

class CLogWriter
{
public:
	CLogWriter();
	~CLogWriter();

protected:
 	static TCHAR	m_szLogPath[MAX_PATH];	//full path of log file.
 	static TCHAR	m_szLogDir[MAX_PATH];	//full path of log file.
	static INT		m_nLogLevel;

	CRITICAL_SECTION	m_Crit;
	vector<PVOID>		m_MemoryPool;
	TCHAR*	GetWideBuffer();
	CHAR*	GetAnsiBuffer();
	VOID	ReturnBuffer(PVOID	pBuffer);

public:
	void	DeleteLogFile();
	void	SetLogPath(HINSTANCE hInstance, PCTSTR pUseThisPath);
	PTSTR	GetLogPath(PTSTR ptszBuf, int nBufLen);
	void	SetLogLevel(INT nLogLevel);
	void	ShowLog();
	void	BackupLog(const WCHAR*		pszLogPath = NULL);

	int		Trace(LPCTSTR pszLogFileName, INT nErrorLevel, LPCTSTR pszFuncName, LPCTSTR pszFilePath, DWORD LineNumber, DWORD dwLastError, PCTSTR ptszFormat, ...);
	//int		PwDbgOut(INT nErrorLevel, LPCTSTR pszFuncName, LPCTSTR pszFilePath, DWORD dwLineNumber, DWORD dwLastError, PCTSTR ptszFormat, ...);
	int		MsgBox(HWND hwndParent, UINT uType, PCTSTR ptszFormat, ...);

	int		DeleteOldLogs(LPCTSTR pszLogFileName, DWORD BackupDays = LOG_BACKUP_DAYS);
	int		AddDayToSystemTime(LPSYSTEMTIME  pSystemTime, LONG AddDay);
	
	static	BOOL	CheckLogSettings();
	static	BOOL	IsFileExists(const WCHAR* pszFileName);

	static	BOOL	m_bWriteDetailLog;
	static	BOOL	m_bWriteIoLog;
	static	DWORD	m_LogSettingCheckTime;
	static	DWORD	m_SessionId;
	
	static HANDLE	m_InitThread;
	static BOOL		m_bInitialized;


};

extern CLogWriter g_LogWriter;



#endif

