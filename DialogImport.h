#pragma once
/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2018 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <afxwin.h>
#include "ColorButton.h"
#include "Resource.h"

class CDialogImport : public CDialog
{
	DECLARE_DYNAMIC(CDialogImport)


public:
	CDialogImport(CWnd* pParent = nullptr);
	virtual ~CDialogImport();

	CString m_path;
	CEdit m_pathctl;
	CColorButton m_ckRecursive;
	bool m_Recursive;
	CBrush Brush_Main;
	CFont m_font_Title;
	enum { IDD = IDD_DIALOG_IMPORT};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	CColorButton	m_btOK;
	CColorButton	m_btCancel;
	LOGFONT lf, lf2, lf3;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	virtual void OnOK();

	afx_msg void OnBnClickedButtonImport2();
	afx_msg void OnBnClickedCheckRecursive();
};
