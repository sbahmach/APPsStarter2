// IconComboBox.h : header file
//
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

//////////////////////////////////////////////////////
//                                                  //
//                   CIconComboBox                  //
//                                                  //
// Copyright (c) Joel Wahlberg ENATOR Networks 1997 //
//               joel.wahlberg@enator.se            //
//                                                  //
//////////////////////////////////////////////////////

class CIconComboBox : public CComboBox
{
// Contruction/Destruction
public:
	CIconComboBox();
	virtual ~CIconComboBox();

// Attributes
public:
	CSize m_sizeIcon;

// Operations
public:
	virtual int AddIcon(LPCTSTR lpszIconFile);
	virtual int InsertIcon(int nIndex, LPCTSTR lpszIconFile);
	virtual int SelectIcon(LPCTSTR lpszIconFile);
	virtual int SelectIcon(int nIndex);
	virtual int DeleteIcon(LPCTSTR lpszIconFile);
	virtual int DeleteIcon(int nIndex);

// Implementation
protected:
	virtual void OnOutputIcon(LPDRAWITEMSTRUCT lpDIS, BOOL bSelected);

// Overrides
	virtual int AddString(LPCTSTR lpszString);
	virtual int InsertString(int nIndex, LPCTSTR lpszString);
	virtual int DeleteString(int nIndex);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};

#endif // _ICONCOMBOBOX_H_
