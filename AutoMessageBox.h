#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

/////////////////////////////////////////////////////////////////////////////
// CAutoMessageBox dialog

#ifndef MB_TIMED
#define MB_TIMED   0x80000000
#endif
#ifndef IDTIMEOUT
#define IDTIMEOUT  32000
#endif

class CAutoMessageBox : public CDialog
{
   // Attributes
   UINT m_nTimeOut;
   BOOL m_bShowProgress;
   const UINT m_nTimerStep;
   UINT m_nElapsed;

   // Hook info
   static __declspec(thread) HHOOK m_hHook;
   static __declspec(thread) CAutoMessageBox* m_pWndThis;
   static __declspec(thread) HWND m_hWndThis;

   // Additional controls
   CProgressCtrl m_progress;

// Construction
public:
	CAutoMessageBox();
   ~CAutoMessageBox();
   //CFont m_font;
// Operations
public:
   BOOL Hook(UINT nTimeOut, BOOL bShowProgress);
private:
   static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
   
// Dialog Data
	//{{AFX_DATA(CAutoMessageBox)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoMessageBox)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAutoMessageBox)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
private:
   void _Unhook();
   BOOL _AddProgressCtrl();

};
