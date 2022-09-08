/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2017 see Authors.txt
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

#include "pch.h"
#include "DialogImport.h"



 // CDialogImport dialog

IMPLEMENT_DYNAMIC(CDialogImport, CDialog)
CDialogImport::CDialogImport(CWnd* pParent /*=nullptr*/)
	: CDialog(CDialogImport::IDD, pParent)

{
	Brush_Main.CreateSolidBrush(RGB(255, 255, 255));
}

CDialogImport::~CDialogImport()
{
}

void CDialogImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PATH2, m_path);
	DDX_Control(pDX, IDC_EDIT_PATH2, m_pathctl);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
}

BOOL CDialogImport::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(_T("Параметры импорта"));

	//memset(&lf, 0, sizeof(LOGFONT));
	//lf.lfHeight = 24;// -MulDiv(24, iCurrentDPI, 72);
	//lf.lfWeight = FW_MEDIUM;
	//_tcscpy(lf.lfFaceName, _T("Arial Narrow"));
	//m_font_Title.CreateFontIndirect(&lf);



	//
	//m_pathctl.SetFont(&m_font_Title);

	//GetDlgItem(IDC_EDIT_PATH2)->SetFocus();
	//COLORREF col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
	//	, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
	//	, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected;

	//col_BtnText_Disabled = RGB(200, 200, 200);
	//col_BtnText = RGB(47, 145, 207);
	//col_BtnText_IsHover = RGB(47, 145, 207);
	//col_BtnText_Selected = RGB(248, 218, 2);
	//col_BtnFace_Disabled = RGB(255, 255, 255);
	//col_BtnFace = RGB(255, 255, 255);
	//col_BtnFace_IsHover = RGB(248, 218, 2);
	//col_BtnFace_Selected = RGB(47, 145, 207);
	//col_BtnFrame_Disabled = RGB(200, 200, 200);
	//col_BtnFrame = RGB(47, 145, 207);
	//col_BtnFrame_IsHover = RGB(47, 145, 207);
	//col_BtnFrame_Selected = RGB(248, 218, 2);

	//m_btOK.SetWindowText(_T("OK"));
	//m_btOK.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
	//	, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
	//	, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	//m_btCancel.SetWindowText(_T("Отмена"));
	//m_btCancel.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
	//	, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
	//	, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CDialogImport, CDialog)
	//ON_WM_CTLCOLOR()
	//ON_WM_PAINT()
	//ON_BN_CLICKED(IDOK, &CDialogImport::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT2, &CDialogImport::OnBnClickedButtonImport2)
	ON_BN_CLICKED(IDC_CHECK_RECURSIVE, &CDialogImport::OnBnClickedCheckRecursive)
END_MESSAGE_MAP()

// CDialogImport message handlers

HBRUSH CDialogImport::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetTextColor(RGB(47, 145, 207));
		break;
	case CTLCOLOR_EDIT:
		//pDC->SetBkColor(RGB(47, 145, 207));
		pDC->SetTextColor(RGB(0, 0, 0));
		break;
	case CTLCOLOR_DLG:
		pDC->SetTextColor(RGB(0, 0, 0));
		break;
	default:
		pDC->SetTextColor(RGB(0, 0, 0));
		break;
	}

	return Brush_Main;// CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CDialogImport::OnPaint()
{

	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect);

	BITMAP bmp;
	HBITMAP hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	::GetObject(hBmp, sizeof(bmp), &bmp);
	HDC hDC = ::CreateCompatibleDC(NULL);
	SelectObject(hDC, hBmp);
	::BitBlt(dc.m_hDC, 10, 5, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
	CDialog::OnPaint();

}

void CDialogImport::OnOK()
{
	__super::OnOK();

}

BOOL CDialogImport::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {

		OnOK();
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}




void CDialogImport::OnBnClickedButtonImport2()
{
	CFolderPickerDialog m_dlg;
	CString m_Folder;

	m_dlg.m_ofn.lpstrTitle = _T("Выбор каталога для поиска");
	m_dlg.m_ofn.lpstrInitialDir = _T("D:\\apps\\");
	if (m_dlg.DoModal() == IDOK) {
		m_Folder = m_dlg.GetPathName();   // Use this to get the selected folder name 
										  // after the dialog has closed

		// May need to add a '\' for usage in GUI and for later file saving, 
		// as there is no '\' on the returned name
		//m_Folder += _T("\\");
		UpdateData(FALSE);   // To show updated folder in GUI
		m_pathctl.SetWindowText(m_Folder);
		m_path = m_Folder;
		//strFolderPathImport = m_Folder
		//AfxMessageBox(m_Folder);
		Invalidate();
	}


}


void CDialogImport::OnBnClickedCheckRecursive()
{
	// TODO: добавьте свой код обработчика уведомлений
	// TODO: Add your control notification handler code here
	bool bChecked = m_ckRecursive.GetCheck();
	// First get the current Window Styles
	//LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	//m_ckRecursive.SetCheck(!bChecked);
	if (!bChecked) {
		m_ckRecursive.SetCheck(1);
		m_Recursive = 1;
		//SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else {
		m_ckRecursive.SetCheck(0);
		m_Recursive = 0;
		//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	Invalidate();
}
