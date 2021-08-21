/*
Module : ICONCOMBOBOX.H
Purpose: Defines the interface for 2 MFC classes
         to implement an icon selection combo box
Created: PJN / 2-08-1998
History: None

Copyright (c) 1998 by PJ Naughter.  
All rights reserved.

*/
#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifndef __ICONCOMBOBOX_H__
#define __ICONCOMBOBOX_H__

class CSmallIconComboBox : public CComboBox
{
public:
//Methods
  int  AddIcon(UINT_PTR nIconID, CString str);
	int  InsertIcon(int nIndex, UINT_PTR nIconID, CString str);
  int  DeleteIcon(int nIndex);
  //UINT GetCurSelIcon() const;
	void  SetCurSelIcon(CString str);
  int  AddString(LPCTSTR lpszString);
  int  InsertString(int nIndex, LPCTSTR lpszString);
  int  DeleteString(int nIndex);

  ////////////////////////////// Locals /////////////////////////////////////////

  struct _IconComboData
  {
	  HICON m_hIcon = NULL;
	  UINT_PTR  m_nIconID = NULL;
	  CString str = _T("");
  };

  _IconComboData *iconData;
protected:

	int iCurrentDPI = 96;
	typedef HRESULT(WINAPI* PGetDpiForMonitor)(HMONITOR hmonitor, int dpiType, UINT* dpiX, UINT* dpiY);

	WORD GetWindowDPI(HWND hWnd)
	{
		HMODULE hShcore = LoadLibraryW(L"shcore");
		if (hShcore)
		{
			PGetDpiForMonitor pGetDpiForMonitor =
				reinterpret_cast<PGetDpiForMonitor>(GetProcAddress(hShcore, "GetDpiForMonitor"));
			if (pGetDpiForMonitor)
			{
				HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);
				UINT uiDpiX;
				UINT uiDpiY;
				HRESULT hr = pGetDpiForMonitor(hMonitor, 0, &uiDpiX, &uiDpiY);
				if (SUCCEEDED(hr))
				{
					return static_cast<WORD>(uiDpiX);
				}
			}
		}
		HDC hScreenDC = ::GetDC(nullptr);
		int iDpiX = GetDeviceCaps(hScreenDC, LOGPIXELSX);
		::ReleaseDC(0, hScreenDC);

		return static_cast<WORD>(iDpiX);
	}


	//{{AFX_VIRTUAL(CSmallIconComboBox)
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	//virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSmallIconComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//DECLARE_DYNAMIC(CSmallIconComboBox)
};

//DDX Support
//void DDX_CBIcon(CDataExchange* pDX, int nIDC, CString str);


#endif //__ICONCOMBOBOX_H__
