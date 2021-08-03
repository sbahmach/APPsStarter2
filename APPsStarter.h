
// APPsStarter.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#define _WIN32_WINNT_MAXVER     0x0A00

// CAPPsStarterApp:
// See APPsStarter.cpp for the implementation of this class
//

class CAPPsStarterApp : public CWinApp
{
public:
	CAPPsStarterApp();
	
	//CCustomCommandLineInfo cmdInfo;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	DECLARE_MESSAGE_MAP()
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
};

extern CAPPsStarterApp theApp;


//
//class CCustomCommandLineInfo : public CCommandLineInfo
//{
//	CCustomCommandLineInfo()
//	{
//		//m_bAdmin = m_bOpen = m_bArg = FALSE;
//	}
//
//	//for convenience maintain 3 variables to indicate the param passed. 
//	//BOOL m_bAdmin;       //for /a
//	//BOOL m_bOpen;         //for /o
//	//BOOL m_bArg;         //for 
//
//	//public methods for checking these.
//public:
//	/*BOOL IsAdmin() { return m_bAdmin; };
//	BOOL IsOpen() { return m_bOpen; };
//	BOOL IsArg() { return m_bArg; };*/
//
//	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
//	{
//
//		/*if (0 == strcmp(pszParam, "/a"))
//		{
//			m_bAdmin = TRUE;
//		}
//		else if (0 == strcmp(pszParam, "/o"))
//		{
//			m_bOpen = TRUE;
//		}
//		else {
//			m_bArg = TRUE;
//		}*/
//		CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
//	}
//	friend class CAPPsStarterApp;
//};
