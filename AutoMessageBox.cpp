// AutoMessageBox.cpp : implementation file
//

//#include "stdafx.h"
//#include "APPsStarter.h"
#include "pch.h"
#include "AutoMessageBox.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoMessageBox dialog

__declspec(thread) HHOOK CAutoMessageBox::m_hHook = NULL;
__declspec(thread) CAutoMessageBox* CAutoMessageBox::m_pWndThis = NULL;
__declspec(thread) HWND CAutoMessageBox::m_hWndThis = NULL;

CAutoMessageBox::CAutoMessageBox()
   : m_nTimeOut(0),
     m_nTimerStep(100),
     m_bShowProgress(FALSE),
     m_nElapsed(0)
     
{
	//{{AFX_DATA_INIT(CAutoMessageBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

   m_pWndThis = this;
}

CAutoMessageBox::~CAutoMessageBox()
{
   _Unhook();
   // reset static data
   m_hHook = NULL;
   m_hWndThis = NULL;
}

BOOL CAutoMessageBox::Hook(UINT nTimeOut, BOOL bShowProgress)
{
   ASSERT(NULL == m_hHook); // hook once per instance

   m_nTimeOut = nTimeOut;
   m_bShowProgress = bShowProgress;

   DWORD dwThreadID = ::GetCurrentThreadId();
   HINSTANCE hInstance = AfxGetInstanceHandle();

   m_hHook = ::SetWindowsHookEx(WH_CBT, 
         &CAutoMessageBox::HookProc, hInstance, dwThreadID);

   return m_hHook != NULL;
}

LRESULT CALLBACK CAutoMessageBox::HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
   switch(nCode)
   {
   case HCBT_CREATEWND: // a window is about to be created
      {
         LPCBT_CREATEWND lpCbtCreate = (LPCBT_CREATEWND)lParam;
         HWND hWnd = (HWND)wParam;
         
         if(WC_DIALOG == lpCbtCreate->lpcs->lpszClass
            && m_pWndThis->GetSafeHwnd() == NULL)
         {
            // Keep in mind the message box handle to subclass it later
            m_hWndThis = hWnd;
         }
         else if(NULL != m_hWndThis && NULL == m_pWndThis->GetSafeHwnd())
         {
            m_pWndThis->SubclassWindow(m_hWndThis);
         }
      }
      break;
   
   case HCBT_DESTROYWND: // a window is about to be destroyed
      {
         if(m_pWndThis->GetSafeHwnd() == (HWND)wParam) // it's our messge box
         {
            // so set back its default procedure
            m_pWndThis->UnsubclassWindow();
         }
      }
      break;
   }
   return ::CallNextHookEx(m_hHook, nCode, wParam, lParam);
}

void CAutoMessageBox::_Unhook()
{
   if(NULL != m_hHook)
   {
      ::UnhookWindowsHookEx(m_hHook);
      m_hHook = NULL;
   }
}

BOOL CAutoMessageBox::_AddProgressCtrl()
{
   const int nMrg = 2;
   const int nHeight = 5;

   CRect rcBox;
   GetWindowRect(rcBox);

   SetWindowPos(NULL, 0, 0, rcBox.Width(), 
      rcBox.Height(), SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

   GetClientRect(rcBox);
   CRect rcProgress(rcBox.left + nMrg, rcBox.bottom - nMrg - nHeight -81, 
      rcBox.right - nMrg, rcBox.bottom - nMrg-80);

   DWORD dwStyle = WS_CHILD|WS_VISIBLE|PBS_SMOOTH;
   return m_progress.Create(dwStyle, rcProgress, this, 0); 

}


BEGIN_MESSAGE_MAP(CAutoMessageBox, CDialog)
	//{{AFX_MSG_MAP(CAutoMessageBox)
	ON_WM_TIMER()
	//ON_WM_PAINT()
	//}}AFX_MSG_MAP
   ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoMessageBox message handlers

LRESULT CAutoMessageBox::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	SetWindowText(_T("STARTER"));
   if(m_nTimeOut > 0)
   {
      SetTimer(0, m_nTimerStep, NULL);
   }
   if(m_bShowProgress)
   {
      VERIFY(_AddProgressCtrl());
      m_progress.SetRange(0, m_nTimeOut);
      m_progress.SetPos(m_nElapsed);
	 // m_progress.SetBarColor(RGB(47, 145, 207));
	 // m_progress.SetBkColor(RGB(248, 218, 2));
	 // m_progress.ModifyStyle(0, PBM_SETMARQUEE);
   }
   //LOGFONT lf;                        // Used to create the CFont.

   //memset(&lf, 0, sizeof(LOGFONT));   // Clear out structure.
   //lf.lfHeight = 18;                  // Request a 20-pixel-high font
   //lf.lfItalic = 0;
   //lf.lfCharSet = DEFAULT_CHARSET;
   //strcpy_s(lf.lfFaceName, "Arial Narrow");    //    with face name "Arial".
   //CreateFontIndirect(&lf);    // Create the font.
   // Use the font to paint a control. This code assumes
   // a control named IDC_TEXT1 in the dialog box.


   //GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
   //SetFont(&m_font);

   return TRUE;
}

void CAutoMessageBox::OnPaint()
{
	
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);



		//ScreenToClient(rect);
		BITMAP bmp;
		HBITMAP hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
		::GetObject(hBmp, sizeof(bmp), &bmp);
		HDC hDC = ::CreateCompatibleDC(NULL);
		SelectObject(hDC, hBmp);
		::BitBlt(dc.m_hDC, 10, rect.bottom - 70, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
		CDialog::OnPaint();
	
}


void CAutoMessageBox::OnTimer(UINT_PTR nIDEvent)
{
	m_nElapsed += m_nTimerStep;

   if(m_bShowProgress)
   {
      m_progress.SetPos(m_nElapsed);
   }

   if(m_nElapsed >= m_nTimeOut)
   {
      KillTimer(0);
      ::EndDialog(m_hWnd, IDTIMEOUT);
   }
}

BOOL CAutoMessageBox::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   ::EndDialog(m_hWnd, LOWORD(wParam));
   return TRUE;   
}
