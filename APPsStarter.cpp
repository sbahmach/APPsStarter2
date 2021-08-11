
// APPsStarter.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "APPsStarter.h"
#include "APPsStarterDlg.h"
#include "AutoMessageBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAPPsStarterApp

BEGIN_MESSAGE_MAP(CAPPsStarterApp, CWinApp)
END_MESSAGE_MAP()


// CAPPsStarterApp constructior
CAPPsStarterApp::CAPPsStarterApp()
{
}



// The one and only CAPPsStarterApp object
CAPPsStarterApp theApp;

// CAPPsStarterApp initialization
BOOL CAPPsStarterApp::InitInstance()
{
	HANDLE hM = CreateMutex(NULL, FALSE, _T("{APPs-STARTER2-012}"));

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CString strMsg = _T("Программа уже запущена!\nЗапуск второй копии запрещен!");
		UINT nType = 0;
		UINT nHelpID = 0;
		UINT m_nTimeOut = 5;
		BOOL m_bShowProgress = TRUE;

		// use special flag MB_TIMED.
		nType |= MB_TIMED;

		nHelpID = MAKELONG(m_nTimeOut, m_bShowProgress);

		// additional time-out info
		CString strAddMsg;
		strAddMsg = _T("\n\nЧтобы закрыть это сообщение нажмите ОК, иначе\nсообщение будет автоматически закрыто через 5 сек\n\n\nХорошего дня!\n\n\n\n");
		strMsg += strAddMsg;

		int nRet = AfxMessageBox(strMsg, nType, nHelpID);

		HWND hWnd = FindWindow(NULL, _T("APPs STARTER")); // хэндл самого мессаджбокса

		::SetForegroundWindow(hWnd);
		::ShowWindow(hWnd, SW_SHOWNORMAL);

		if (hM != NULL) CloseHandle(hM);

		PostQuitMessage(0);
		CWinApp::ExitInstance();
	}
	else {

		/*INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);

		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&InitCtrls);*/

		CWinApp::InitInstance();


		/*AfxEnableControlcontainer();*/

		//CShellManager* pShellManager = new CShellManager;

		SetRegistryKey(_T("APPs STARTER"));
		

		CAPPsStarterDlg dlg;
		m_pMainWnd = &dlg;
		//dlg.SetWindowText("STARTER");
		int argc = 0;
		//AfxMessageBox("0");
		LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

		//AfxMessageBox("1");
		for (int i = 1; i < argc; ++i) {
			CString str;
			str = CW2A(argv[i]);
			//str.Format("%ws", argv[i].c_str());
			
			//AfxMessageBox(str);
			/*if (0 == strcmp(str, "/a")) {
				dlg.m_bAdminMode = 1;
			}
			else */if (0 == _tcscmp(str, _T("/n"))) {
				dlg.m_bNoSaveSettings = 1;
			}
			else {
				dlg.strCmdXmlFile = str;
				
			}
			
		}
		LocalFree(argv);
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
		ControlBarCleanUp();
#endif
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAPPsStarterApp::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt)
{
	CAutoMessageBox msgBox;

	if (MB_TIMED & nType)
	{
		// get show progress control
		BOOL bShowProgress = HIWORD(nIDPrompt);

		// get time-out in milliseconds
		UINT nTimeOut = LOWORD(nIDPrompt) * 1000;

		VERIFY(msgBox.Hook(nTimeOut, bShowProgress));

		// remove auto-close message box styles
		nType &= ~MB_TIMED;
		nIDPrompt = 0;
	}
	return CWinApp::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

void CAPPsStarterApp::OnMainEditFile()
{
    // TODO: добавьте свой код обработчика команд
}


void CAPPsStarterApp::OnMainSaveFile()
{
	// TODO: добавьте свой код обработчика команд
}
