

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "APPsStarter.h"
#include "APPsStarterDlg.h"
//#include "DialogPass.h"
#include "stdbool.h"
#include "sys/stat.h"
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "ver_revision.h"
#include "ver_build.h"
//#include "FileVersion.h"
#include <Propkey.h>
//#include <afxwin.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define APPWM_ICONNOTIFY (WM_APP + 1)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
		CStatic m_statVersion;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VERSION, m_statVersion);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_statVersion.SetWindowText(L"APPsStarter Version: " stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_REVISION) "." stringify(VERSION_BUILD));
	return TRUE;
}

// CAPPsStarterDlg dialog

CAPPsStarterDlg::CAPPsStarterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CAPPsStarterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	Brush_Main.CreateSolidBrush(RGB(255, 255, 255));

	LOGFONT lf_Title;
	memset(&lf_Title, 0, sizeof(LOGFONT));
	lf_Title.lfHeight = 36;
	lf_Title.lfWeight = FW_MEDIUM;
	lf_Title.lfCharSet = DEFAULT_CHARSET;
	_tcscpy(lf_Title.lfFaceName, _T("Arial Narrow"));
	m_font_Title.CreateFontIndirect(&lf_Title);
}

void CAPPsStarterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_BUTTON_START, m_btStart);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_btLoad);
	DDX_Control(pDX, IDC_BUTTON_RELOAD, m_btReload);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btSave);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_btEdit);
	DDX_Control(pDX, IDC_MFCBUTTON_PATH, m_btPath);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_STATIC_1, m_Title);
	DDX_Control(pDX, IDC_STATIC_2, m_stat);
	//DDX_Control(pDX, IDC_STATIC_PARENT, m_statParent);
	//DDX_Control(pDX, IDC_STATIC_ID, m_statID);
	DDX_Control(pDX, IDC_STATIC_NAME, m_statName);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_statTitle);
	DDX_Control(pDX, IDC_STATIC_PATH, m_statPath);
	DDX_Control(pDX, IDC_STATIC_ICON, m_statIcon);
	DDX_Control(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	//DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	//DDX_Control(pDX, IDC_EDIT_PARENT, m_editParent);
	DDX_Control(pDX, IDC_COMBO_ICON, m_cbIcon);
}



BEGIN_MESSAGE_MAP(CAPPsStarterDlg, CDialog)
	
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DROPFILES, OnDropFiles)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, OnReload)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnSave)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnTvnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnNMDblclkTree1)
	ON_BN_CLICKED(IDC_BUTTON_START, OnStart)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnEdit)
	ON_WM_CONTEXTMENU()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CAPPsStarterDlg::OnBnClickedCheck1)

	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CAPPsStarterDlg::OnEnKillfocusEditName)
	ON_EN_KILLFOCUS(IDC_EDIT_TITLE, &CAPPsStarterDlg::OnEnKillfocusEditTitle)
	ON_EN_KILLFOCUS(IDC_EDIT_PATH, &CAPPsStarterDlg::OnEnKillfocusEditPath)
	ON_CBN_SELCHANGE(IDC_COMBO_ICON, &CAPPsStarterDlg::OnCbnSelchangeComboIcon)

	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CAPPsStarterDlg::OnTvnEndlabeleditTree1)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &CAPPsStarterDlg::OnTvnBeginlabeleditTree1)
	ON_BN_CLICKED(IDC_MFCBUTTON_PATH, &CAPPsStarterDlg::OnBnClickedMfcbuttonPath)
END_MESSAGE_MAP()


// CAPPsStarterDlg message handlers
BOOL CAPPsStarterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetWindowText(L"APPs STARTER");
	SetWindowLong(this->m_hWnd,
		GWL_STYLE,
		GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.LoadToolBar(BAR_MAIN);

	COLORREF clrMenuBar = COLOR_MYDLG;
	COLORREF clrVertBar = RGB(0, 192, 192);

	CMenu* pMenu = GetMenu();

	HTREEITEM hItem = m_tree.GetSelectedItem();

	m_cbIcon.InsertIcon(0, IDI_FOLDER, L"folder");
	m_cbIcon.InsertIcon(1, IDI_1C, L"1c");
	m_cbIcon.InsertIcon(2, IDI_MEDOC, L"medoc");
	m_cbIcon.InsertIcon(3, IDI_RDP, L"rdp");
	m_cbIcon.InsertIcon(4, IDI_APP, L"app");
	m_cbIcon.InsertIcon(5, IDI_MAIL, L"mail");
	m_cbIcon.InsertIcon(6, IDI_WEB, L"web");
	m_cbIcon.InsertIcon(7, IDI_SHARE, L"share");
	m_cbIcon.InsertIcon(8, IDI_VCAM, L"vcam");
	m_cbIcon.InsertIcon(9, IDI_CMD, L"cmd");
	m_cbIcon.InsertIcon(10, IDI_SCRIPT, L"script");
	m_cbIcon.InsertIcon(11, IDI_PSHELL, L"pshell");
	m_cbIcon.InsertIcon(12, IDI_APP, L"appsicon");

	m_tree.SetFocus();
	m_tree.SelectItem(hItem);

	HICON icon[13];
	icon[0] = AfxGetApp()->LoadIcon(IDI_FOLDER);
	icon[1] = AfxGetApp()->LoadIcon(IDI_1C);
	icon[2] = AfxGetApp()->LoadIcon(IDI_MEDOC);
	icon[3] = AfxGetApp()->LoadIcon(IDI_RDP);
	icon[4] = AfxGetApp()->LoadIcon(IDI_APP);
	icon[5] = AfxGetApp()->LoadIcon(IDI_MAIL);
	icon[6] = AfxGetApp()->LoadIcon(IDI_WEB);
	icon[7] = AfxGetApp()->LoadIcon(IDI_SHARE);
	icon[8] = AfxGetApp()->LoadIcon(IDI_VCAM);
	icon[9] = AfxGetApp()->LoadIcon(IDI_CMD);
	icon[10] = AfxGetApp()->LoadIcon(IDI_SCRIPT);
	icon[11] = AfxGetApp()->LoadIcon(IDI_PSHELL);
	icon[12] = AfxGetApp()->LoadIcon(IDI_APP);

	m_tree.m_imageList.Create(16, 16, ILC_MASK | ILC_COLOR32, 0, 0);
	m_tree.m_imageList.SetBkColor(0xffffff);
	for (int i = 0; i < 13; i++)
	{
		m_tree.m_imageList.Add(icon[i]);
	}

	m_tree.SetImageList(&m_tree.m_imageList, TVSIL_NORMAL);

	m_Title.SetFont(&m_font_Title);

	COLORREF col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected;

	col_BtnText_Disabled = RGB(200, 200, 200);
	col_BtnText = RGB(47, 145, 207);
	col_BtnText_IsHover = RGB(47, 145, 207);
	col_BtnText_Selected = RGB(255, 255, 255);
	col_BtnFace_Disabled = RGB(255, 255, 255);
	col_BtnFace = RGB(255, 255, 255);
	col_BtnFace_IsHover = RGB(193, 239, 255);
	col_BtnFace_Selected = RGB(47, 145, 207);
	col_BtnFrame_Disabled = RGB(200, 200, 200);
	col_BtnFrame = RGB(97, 195, 255);
	col_BtnFrame_IsHover = RGB(2, 100, 162);
	col_BtnFrame_Selected = RGB(255, 255, 255);

	m_btStart.SetWindowText(L"ЗАПУСТИТЬ");
	m_btStart.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_btLoad.SetWindowText(L"OPEN XML...");
	m_btLoad.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_btReload.SetWindowText(L"RELOAD");
	m_btReload.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_btSave.SetWindowText(L"SAVE");
	m_btSave.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_btEdit.SetWindowText(L"EDIT XML");
	m_btEdit.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_btCancel.SetWindowText(L"ЗАКРЫТЬ");
	m_btCancel.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	this->GetWindowRect(rc_window);

	ReadReg();
	DragAcceptFiles(true);

	OnOpen();

	return TRUE;
}


void CAPPsStarterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

HBRUSH CAPPsStarterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_1) {
			pDC->SetTextColor(RGB(47, 145, 207));
		}
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

void CAPPsStarterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		PostMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		/*CRect rect;
		GetClientRect(&rect);

		BITMAP bmp;
		HBITMAP hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
		::GetObject(hBmp, sizeof(bmp), &bmp);
		HDC hDC = ::CreateCompatibleDC(NULL);
		SelectObject(hDC, hBmp);
		::BitBlt(dc.m_hDC, 10, 5, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
		CDialog::OnPaint();*/


		

			CFont* pFt = dc.SelectObject(CFont::FromHandle((HFONT)::GetStockObject(ANSI_FIXED_FONT)));
			int iBkMode = dc.SetBkMode(TRANSPARENT);

			CRect rc;
			GetClientRect(&rc);
			

			//==================================================
			/*CString cs = "Right click and double click to show 2 popup menus.\n"
				"Visit Help for help-contents.\n\n"
				"Don't forget:\n"
				"First pixel of tool bar stands for transparent color.\n\n";
			dc.DrawText(cs, &rc, 0);*/
			/*int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);
			DrawIconEx(dc, rc.left, rc.top, hIcon, 16, 16, 0, nullptr, DI_NORMAL);*/

			//==================================================
			dc.SetBkMode(iBkMode);
			dc.SelectObject(pFt);
		
	}
}

HCURSOR CAPPsStarterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAPPsStarterDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = rc_window.Width();
	lpMMI->ptMinTrackSize.y = rc_window.Height();
}

void CAPPsStarterDlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = m_tree.GetSelectedItem();

//////////////////////////////////////////////////////////////////////////////////// 
	// !!!!
	node = (node_data*)m_tree.GetItemData(hItem);

	m_Title.SetWindowText(node->title == "" ? node->name : node->title);
	m_editName.SetWindowText(node->name);
	m_editTitle.SetWindowText(node->title);
	//m_statID.SetWindowText(node->id);
	//m_statParent.SetWindowText(node->parent);

	if (node->type.MakeLower() == L"container") {
		m_editPath.EnableWindow(false);
		m_statPath.EnableWindow(false);
		m_statIcon.EnableWindow(false);
		m_editPath.SetWindowText(L"");
		m_btPath.EnableWindow(false);
		m_cbIcon.EnableWindow(false);
	}
	else {
		m_editPath.EnableWindow(true);
		m_statPath.EnableWindow(true);
		m_statIcon.EnableWindow(true);
		m_editPath.SetWindowText(node->path);
		m_cbIcon.EnableWindow(true);
		m_btPath.EnableWindow(true);
	}
	
	m_cbIcon.SetCurSelIcon(node->icon == L"" ? L"folder" : node->icon);
	m_btStart.EnableWindow(m_btStart && node->path == "" ? FALSE : TRUE);

	*pResult = 0;
}


void CAPPsStarterDlg::OnNMDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	UINT nFlags = NULL;
	CPoint curPoint;
	GetCursorPos(&curPoint);
	m_tree.ScreenToClient(&curPoint);
	HTREEITEM hItemSel = m_tree.HitTest(curPoint, &nFlags);
	if (hItemSel != NULL && !m_tree.ItemHasChildren(hItemSel))
	{
		OnStart();
		*pResult = 1;
	}
	else
		*pResult = 0;
	
}

void CAPPsStarterDlg::OnOpen()
{
	if (strCmdXmlFile.Right(4) != L".xml") {
		strCmdXmlFile = strCmdXmlFile + L".xml";
	}

	if (m_tree.LoadFromXML(strCmdXmlFile))
	{
		strCurrentXML = strCmdXmlFile;
	}
	else if (m_tree.LoadFromXML(strDefXMLFile))
	{
		
		strCurrentXML = strDefXMLFile;
	}
	else {
		m_tree.LoadDef();
	}
	m_tree.SetFocus();
	m_tree.PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
	HTREEITEM hItem = m_tree.GetRootItem();
	hItem = m_tree.GetChildItem(hItem);
	if (hItem == NULL)
		hItem = m_tree.GetRootItem();
	m_tree.SelectItem(hItem);
}

void CAPPsStarterDlg::OnLoad()
{
	const TCHAR szFilter[] = _T("XML Files (*.xml)|*.xml|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("xml"), NULL, OFN_DONTADDTORECENT | OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString sFilePath;
	TCHAR szDirectory[MAX_PATH] = L"";
	::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
	//dlg.m_ofn.lpstrInitialDir = szDirectory;
	if (dlg.DoModal() == IDOK)
	{
		sFilePath = dlg.GetPathName();
		if (sFilePath != "") {
			if (m_tree.LoadFromXML(sFilePath))
			{
				strCurrentXML = sFilePath;
				m_tree.SetFocus();
				m_tree.PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
				HTREEITEM hItem = m_tree.GetRootItem();
				hItem = m_tree.GetChildItem(hItem);
				if (hItem == NULL)
					hItem = m_tree.GetRootItem();
				m_tree.SelectItem(hItem);
			}
		}
	}
}

void CAPPsStarterDlg::OnReload()
{
	if (m_tree.LoadFromXML(strCmdXmlFile))
	{
		strCurrentXML = strCmdXmlFile;
	}
	else
	{
		m_tree.LoadFromXML(strDefXMLFile);
		strCurrentXML = strDefXMLFile;
	}
	m_tree.SetFocus();
	m_tree.PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
	HTREEITEM hItem = m_tree.GetRootItem();
	hItem = m_tree.GetChildItem(hItem);
	if (hItem == NULL) 
		hItem = m_tree.GetRootItem();
	m_tree.SelectItem(hItem);
	
}

void CAPPsStarterDlg::OnSave()
{
	//LoadCSVFile();
	m_tree.SaveToXML(L"save.xml");
}

void CAPPsStarterDlg::OnEdit()
{
	CString strPath = L"";
	if (strCurrentXML.Find('\\') != -1) {
		strPath = strCurrentXML;
	}
	else {
		TCHAR szDirectory[MAX_PATH] = L"";
		::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory);
		strCurrentXML = L"\\" + strCurrentXML;
		strPath = szDirectory + strCurrentXML;
	}
	
	if (strPath != "") {
		if (FILE* file = _wfopen(strPath, L"r")) {
			fclose(file);

			ShellExecute(GetSafeHwnd(), L"open", _T("rundll32.exe"), _T("shell32.dll,OpenAs_RunDLL ") + strPath, NULL, 1);
		}
		else {
			MessageBox(L"Файл не найден! Неправильный путь!");
		}
	}
}

void CAPPsStarterDlg::OnBnClickedCancel()
{
	WhriteReg();
	CDialog::OnCancel();
}


void CAPPsStarterDlg::OnStart()
{

	HTREEITEM hItem = m_tree.GetSelectedItem();

	CString strPath = node->path;
	if (strPath != "")
			ShellExecute(GetSafeHwnd(), L"open", strPath, NULL, NULL, 1);
}

void CAPPsStarterDlg::OnRunAs()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath = node->path;
	if (strPath != "")
		ShellExecute(GetSafeHwnd(), L"runas", strPath, NULL, NULL, 1);
}

void CAPPsStarterDlg::OnOpenWith()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath = node->path;
	if (strPath != "") {
		if (FILE* file = _wfopen(strPath, L"r")) {
			fclose(file);
			ShellExecute(GetSafeHwnd(), L"open", _T("rundll32.exe"), _T("shell32.dll,OpenAs_RunDLL ") + strPath, NULL, 1);
		}
		else {
			MessageBox(L"Файл не найден! Неправильный путь!");
		}
	}
}

void CAPPsStarterDlg::OnOpenDirectory()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath;
	strPath = node->path;
	if (strPath != "") {
		if (FILE* file = _wfopen(strPath, L"r")) {
			fclose(file);
			strPath.Truncate(strPath.ReverseFind('\\'));
			ShellExecute(GetSafeHwnd(), L"open", strPath, NULL, NULL, 1);
		}
		else {
			MessageBox(L"Файл не найден! Неправильный путь!");
		}
	}
}

void CAPPsStarterDlg::OnDeleteItem()
{
	HTREEITEM htiDel, htiNextSel;
	htiDel = m_tree.GetSelectedItem();
	if (htiDel == m_tree.GetRootItem())
		return;
	htiNextSel = m_tree.GetNextSiblingItem(htiDel);
	if (htiNextSel == NULL) {
		htiNextSel = m_tree.GetPrevSiblingItem(htiDel);
		if (htiNextSel == NULL) {
			htiNextSel = m_tree.GetParentItem(htiDel);
		}
	}

	m_tree.DeleteItem(htiDel);
	m_tree.SelectItem(htiNextSel);
}



void CAPPsStarterDlg::OnDublicate()
{
	
	HTREEITEM hti, htiParent, htiNew;
	hti = m_tree.GetSelectedItem();
	htiParent = m_tree.GetParentItem(hti);
	if (htiParent == NULL) 
		return;

	m_tree.CopyBranch(hti, htiParent, hti);

	htiNew = m_tree.GetNextSiblingItem(hti);
	m_tree.EnsureVisible(htiNew);
	m_tree.EditLabel(htiNew);
	m_tree.Select(htiNew, TVGN_CARET);
}

void CAPPsStarterDlg::OnItemEdit()
{

	HTREEITEM hti;
	hti = m_tree.GetSelectedItem();
	
	m_tree.EditLabel(hti);
	m_tree.Select(hti, TVGN_CARET);


}
//CString CAPPsStarterDlg::CreateID()
//{
//	GUID guid;
//	HRESULT hr = CoCreateGuid(&guid);
//	//HRESULT hr = CoCreateGuid(pGuid);
//
//	CString str = "";
//	str.Format("%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
//		guid.Data1,
//		guid.Data2,
//		guid.Data3,
//		guid.Data4[0],
//		guid.Data4[1],
//		guid.Data4[2],
//		guid.Data4[3],
//		guid.Data4[4],
//		guid.Data4[5],
//		guid.Data4[6],
//		guid.Data4[7]);
//	return str;
//}

void CAPPsStarterDlg::OnInsertItem()
{
	HTREEITEM hti, htiChild, htiParent;
	hti = m_tree.GetSelectedItem();
	htiParent = m_tree.GetParentItem(hti);

	node = (node_data*)m_tree.GetItemData(hti);

	if (node->type == L"container") {
		htiParent = m_tree.GetSelectedItem();
		hti = TVI_FIRST;
	}

	htiChild = m_tree.InsertItem(L"New App", htiParent, hti);
	m_tree.SetItemImage(htiChild, 4, 4);
	node_data* nnode = new node_data();
	//CString str = m_tree.CreateID();
	nnode->name = "New App";
	nnode->path = "path";
	nnode->title = "";
	nnode->icon = "app";
	nnode->expand = "";
	nnode->type = "application";
	//nnode->id = str;// m_tree.CreateID();
	//nnode->parent = node->id;
	m_tree.SetItemData(htiChild, (DWORD_PTR)nnode);
	nnode = 0;
	m_tree.EnsureVisible(htiChild);
	m_tree.EditLabel(htiChild);
	m_tree.Select(htiChild, TVGN_CARET);
}

void CAPPsStarterDlg::OnInsertFolder()
{

	HTREEITEM hti, htiChild, htiParent;
	hti = m_tree.GetSelectedItem();
	htiParent = m_tree.GetParentItem(hti);

	node = (node_data*)m_tree.GetItemData(hti);

	if (node->type == "container") {
		htiParent = m_tree.GetSelectedItem();
		hti = TVI_FIRST;
	}

	htiChild = m_tree.InsertItem(L"New Folder", htiParent, hti);
	m_tree.SetItemImage(htiChild, 0,0);
	node_data* nnode = new node_data();
	//CString str = m_tree.CreateID();
	nnode->name = "New Folder";
	nnode->path = "";
	nnode->title = "";
	nnode->icon = "folder";
	nnode->expand = "false";
	nnode->type = "container";
	//nnode->id = str;// m_tree.CreateID();
	//nnode->parent = node->id;
	m_tree.SetItemData(htiChild, (DWORD_PTR)nnode);
	nnode = 0;
	m_tree.EnsureVisible(htiChild);
	m_tree.EditLabel(htiChild);
	m_tree.Select(htiChild, TVGN_CARET);
}

void CAPPsStarterDlg::OnSortAZ()
{
	HTREEITEM hti, htiParent;
	hti = m_tree.GetSelectedItem();
	htiParent = m_tree.GetParentItem(hti);
	if (m_tree.ItemHasChildren(hti)) 
		htiParent = hti;

	hSelItem = hti;
	SortTree(htiParent, false);

	if (hSelItem != NULL)
		m_tree.SelectItem(hSelItem);

	m_tree.EnsureVisible(hSelItem);

	hSelItem = NULL;
}

void CAPPsStarterDlg::OnSortZA()
{
	HTREEITEM hti, htiParent;
	hti = m_tree.GetSelectedItem();
	htiParent = m_tree.GetParentItem(hti);
	if (m_tree.ItemHasChildren(hti))
		htiParent = hti;

	hSelItem = hti;
	SortTree(htiParent, true);

	if (hSelItem != NULL)
		m_tree.SelectItem(hSelItem);

	m_tree.EnsureVisible(hSelItem);

	hSelItem = NULL;
}

HTREEITEM CAPPsStarterDlg::FindItem(CString name, HTREEITEM hRoot)
{
	HTREEITEM htiChild = m_tree.GetChildItem(hRoot);
	while (htiChild != NULL)
	{
		CString text = m_tree.GetItemText(htiChild);
		if (text.Compare(name) == 0) {
			return htiChild;
		}
		htiChild = m_tree.GetNextSiblingItem(htiChild);
	}

	return NULL;
}

void CAPPsStarterDlg::SortTree(HTREEITEM htiParent, bool sortType /*= true*/)
{
	HTREEITEM htiChild, htiChildChild;
	std::vector<CString> items;
	bool bSel = false;

	m_tree.SetRedraw(FALSE);

	htiChild = m_tree.GetChildItem(htiParent);
	int i = 0;
	while (htiChild != NULL)
	{
		i++;
		CString text = m_tree.GetItemText(htiChild);
		items.emplace_back(text);
		htiChild = m_tree.GetNextSiblingItem(htiChild);
	}
	items.reserve(i);

	if (!items.empty()) {
		sort(items.begin(), items.end(), [](const CString& a, const CString& b) {
			return (StrCmpLogicalW((CT2CW)a, (CT2CW)b) < 0);
			});

		HTREEITEM htiMove = NULL;

		for (size_t i = 0; i <= items.size() - 1; i++) {
			CString str = items[i];
			htiMove = FindItem(str, htiParent);
			if (htiMove == hSelItem) bSel = true;
			if (htiMove == NULL) return;

			HTREEITEM htiSort;
			sortType ? htiSort = TVI_FIRST : htiSort = TVI_LAST;
			HTREEITEM htiNewItem = m_tree.CopyBranch(htiMove, htiParent, htiSort); //TVI_FIRST = sort desc; TVI_LAST = sort asc
			if (bSel) hSelItem = htiNewItem;
			bSel = false;
			m_tree.DeleteItem(htiMove);
		}
	}

	htiChildChild = m_tree.GetChildItem(htiParent);
	while (htiChildChild != NULL)
	{
		SortTree(htiChildChild, sortType);
		htiChildChild = m_tree.GetNextSiblingItem(htiChildChild);
	}

	m_tree.SetRedraw(TRUE);
	m_tree.Invalidate();
}

void CAPPsStarterDlg::OnContextMenu(CWnd* pWnd, CPoint ptMousePos)
{

	CPoint ptScreen;
	if (GetCursorPos(&ptScreen))
	{
		CPoint ptClient(ptScreen);
		m_tree.ScreenToClient(&ptClient);

		UINT flags = 0;
		HTREEITEM hTreeItem = m_tree.HitTest(ptClient, &flags);
		if (hTreeItem)
			m_tree.SelectItem(hTreeItem);
		else
			hTreeItem = NULL;
		CString strPath, strName;
		HTREEITEM hSelectedItem = m_tree.GetSelectedItem();
		// The user hasn't clicked on any item.
		if (hTreeItem != NULL)
		{
			
			CMenu mu;
			//if (mu != NULL) return;
			if (mu.LoadMenu(MU_POPUP) == 0)	return;

			CMenu* pMu = mu.GetSubMenu(0);
			if (pMu == 0)	return;

			strName = node->name;
			BOOL bExpanded = (TVIS_EXPANDED & m_tree.GetItemState(hSelectedItem, TVIS_EXPANDED));
			if (bExpanded)
				pMu->ModifyMenu(ID_MENU_EXPAND, MF_BYCOMMAND, ID_MENU_EXPAND, L"Свернуть \tRight Left");

			//try delete
			if (m_tree.ItemHasChildren(hSelectedItem)) {
				pMu->DeleteMenu(ID_MENU_RUN, MF_BYCOMMAND);
				pMu->DeleteMenu(ID_MENU_RUNAS, MF_BYCOMMAND);
				pMu->DeleteMenu(ID_MENU_OPENWITH, MF_BYCOMMAND );
				pMu->DeleteMenu(ID_MENU_OPENFOLDER, MF_BYCOMMAND );
				pMu->DeleteMenu(0, MF_SEPARATOR);
			}

			if ((_waccess(node->path, 00) == -1)) {

				pMu->DeleteMenu(ID_MENU_OPENWITH, MF_BYCOMMAND);
				pMu->DeleteMenu(ID_MENU_OPENFOLDER, MF_BYCOMMAND);
			}

			if (!m_tree.ItemHasChildren(hSelectedItem)) {

				pMu->DeleteMenu(ID_MENU_EXPAND, MF_BYCOMMAND);
				pMu->DeleteMenu(0, MF_SEPARATOR);
			}


			COLORREF clrMenuBar = COLOR_MYDLG;
			//COLORREF clrVertBar = RGB(47, 145, 207);
			//COLORREF clrVertBar = RGB(200, 227, 244);
			COLORREF clrVertBar = RGB(255, 255, 255);

			md_Popup.SetOwnerDraw(pMu, 0, &m_wndToolBar, 0, &clrMenuBar, &clrVertBar);

			UINT nID = pMu->TrackPopupMenu(TPM_RETURNCMD, ptScreen.x, ptScreen.y, this);
			
			
			switch (nID) {
			case ID_MENU_RUN:
				OnStart();
				break;
			case ID_MENU_RUNAS:
				OnRunAs();
				break;
			case ID_MENU_OPENWITH:
				OnOpenWith();
				break;
			case ID_MENU_OPENFOLDER:
				OnOpenDirectory();
				break;
			case ID_MENU_EXPAND:
				if (bExpanded) {
					m_tree.Expand(hSelectedItem, TVE_COLLAPSE);
				}
				else {
					m_tree.Expand(hSelectedItem, TVE_EXPAND);
				}
				break;
			case ID_MENU_CLONE:
				OnDublicate();
				break;
			case ID_MENU_RENAME:
				OnItemEdit();
				break;
			case ID_MENU_DELETE:
				OnDeleteItem();
				break;
			case ID_MENU_ADDAPP:
				OnInsertItem();
				break;
			case ID_MENU_ADDFOLDER:
				OnInsertFolder();
				break;
			case ID_MENU_SORT_AZ:
				OnSortAZ();
				break;
			case ID_MENU_SORT_ZA:
				OnSortZA();
				break;
			case ID_MENU_MOVEUP:
				OnMoveUp();
				break;
			case ID_MENU_MOVEDOWN:
				OnMoveDown();
				break;
			
			default:
				//MessageBox("Ахтунг!!!", "Yup!", MB_ICONINFORMATION);
				break;
			}

		}
	}
}

void CAPPsStarterDlg::OnOK()
{
	OnStart();
}

void CAPPsStarterDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	bool bChecked = m_check.GetCheck();
	// First get the current Window Styles
	LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	if (!bChecked) {
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
	else {
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

void CAPPsStarterDlg::ReadReg()
{
	if (m_bNoSaveSettings) {
		return;
	}

	CString strSection = NULL;
	CString strAlwaysOnTop = L"AlwaysOnTop";
	CString strWindowHight = L"WindowHight";
	CString strWindowWidth = L"WindowWidth";
	CString strOffsetX = L"OffsetX";
	CString strOffsetY = L"OffsetY";
	CString strShowCmd = L"ShowCmd";
	CWinApp* pApp = AfxGetApp();

	int iAlwaysOnTop, iWindowHight, iWindowWidth, iOffsetX, iOffsetY, iShowCmd;
	iAlwaysOnTop = pApp->GetProfileInt(strSection, strAlwaysOnTop, 0);

	if (iAlwaysOnTop) {
		m_check.SetCheck(1);

	}
	else {
		m_check.SetCheck(0);
	}
	OnBnClickedCheck1();

	iWindowHight = pApp->GetProfileInt(strSection, strWindowHight, 0);
	iWindowWidth = pApp->GetProfileInt(strSection, strWindowWidth, 0);
	iOffsetX = pApp->GetProfileInt(strSection, strOffsetX, 0);
	iOffsetY = pApp->GetProfileInt(strSection, strOffsetY, 0);

	iShowCmd = pApp->GetProfileInt(strSection, strShowCmd, 1);

	if ((iOffsetX == 0 && iOffsetY == 0)) { // first start app?
		CenterWindow();
	}
	else if ((iOffsetX < 0 && iOffsetY < 0)) { //winow is minimized
		ShowWindow(SW_SHOWNORMAL);
	}
	else {
		ShowWindow(SW_HIDE);
		SetWindowPos(0, iOffsetX, iOffsetY, iWindowWidth, iWindowHight, SWP_NOZORDER);
		if (iShowCmd == 2) {
			ShowWindow(SW_SHOWMINIMIZED);
		}
		else if (iShowCmd == 3) {
			ShowWindow(SW_SHOWMAXIMIZED);
		}
		else {
			ShowWindow(SW_SHOWNORMAL);
		}
	}
}

void CAPPsStarterDlg::WhriteReg()
{
	if (m_bNoSaveSettings) {
		return;
	}
	
	CString strSection = NULL;
	CString strAlwaysOnTop = L"AlwaysOnTop";
	CString strWindowHight = L"WindowHight";
	CString strWindowWidth = L"WindowWidth";
	CString strOffsetX = L"OffsetX";
	CString strOffsetY = L"OffsetY";
	CString strShowCmd = L"ShowCmd";

	CWinApp* pApp = AfxGetApp();

	int iAlwaysOnTop, iWindowHight, iWindowWidth, iOffsetX, iOffsetY, iShowCmd;
	iAlwaysOnTop = m_check.GetCheck();
	pApp->WriteProfileInt(strSection, strAlwaysOnTop, iAlwaysOnTop);

	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	RECT rcNormalPosition = wp.rcNormalPosition;
	
	//pApp->DelRegTree
	CRect r;
	this->GetWindowRect(r);
	iWindowHight = rcNormalPosition.bottom - rcNormalPosition.top;
	pApp->WriteProfileInt(strSection, strWindowHight, iWindowHight);
	iWindowWidth = rcNormalPosition.right - rcNormalPosition.left;
	pApp->WriteProfileInt(strSection, strWindowWidth, iWindowWidth);
	iOffsetX = rcNormalPosition.left;
	pApp->WriteProfileInt(strSection, strOffsetX, iOffsetX);
	iOffsetY = rcNormalPosition.top;
	pApp->WriteProfileInt(strSection, strOffsetY, iOffsetY);
	iShowCmd = wp.showCmd;
	pApp->WriteProfileInt(strSection, strShowCmd, iShowCmd);
}

BOOL CAPPsStarterDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_tree.GetEditControl() && (pMsg->wParam == VK_RETURN  || pMsg->wParam == VK_ESCAPE	)) //edit tree control item and Enter or Eacape
	{
		
		::DispatchMessage(pMsg);
		//m_tree.SetFocus();
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x44)) //Ctrl + D
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnDublicate();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == VK_RETURN)) //Ctrl + Enter
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnRunAs();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x4F))//Ctrl + O
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnOpenWith();
		}
		return TRUE;
	}
	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x4E))//Ctrl + N
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnInsertItem();
		}
		return TRUE;
	}
	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x59)) //ctrl + Y
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnSortAZ();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x55)) //ctrl + U
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnSortZA();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x52)) //ctrl + R
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnReload();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && (pMsg->wParam == 0x4F)) { //shft+O
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnOpenDirectory();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && (pMsg->wParam == 0x4E)) { //shft+N
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnInsertFolder();
		}
		return TRUE;
	}

	if (pMsg->wParam == VK_F2) //F2
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			
			HTREEITEM hSelectedItem = m_tree.GetSelectedItem();
			if (hSelectedItem != NULL)
				m_tree.EditLabel(hSelectedItem);
		}
		return TRUE;
	}

	if ((pMsg->message == WM_KEYDOWN) && pMsg->wParam == VK_RETURN) {
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_EDIT_NAME) {
			OnEnKillfocusEditName();
			m_tree.SetFocus();
			return TRUE;
		}
		if (i == IDC_EDIT_TITLE) {
			OnEnKillfocusEditTitle();
			m_tree.SetFocus();
			return TRUE;
		}
		if (i == IDC_EDIT_PATH) {
			OnEnKillfocusEditPath();
			m_tree.SetFocus();
			return TRUE;
		}


	}

	if ((pMsg->message == WM_KEYDOWN) && pMsg->wParam == VK_DELETE) {
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE1) {
			OnDeleteItem();
			return TRUE;
		}
		//m_tree.SetFocus();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0)
	{
		if (pMsg->wParam == VK_UP)
		{
			CWnd* pWnd = GetFocus();
			UINT i = pWnd->GetDlgCtrlID();
			if (i == IDC_TREE1) {
				OnMoveUp();
				return TRUE;
			}
		}
		if (pMsg->wParam == VK_DOWN)
		{
			CWnd* pWnd = GetFocus();
			UINT i = pWnd->GetDlgCtrlID();
			if (i == IDC_TREE1) {
				OnMoveDown();
				return TRUE;
			}
		}
		
	}
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CAPPsStarterDlg::OnDropFiles(WPARAM wParam, LPARAM lParam)
{

	TCHAR	szDroppedFile[MAX_PATH];
	HDROP	hDrop;
	int     nFiles;
	CString csString;

	hDrop = (HDROP)wParam;
	UpdateData();

	nFiles = DragQueryFileW(hDrop,		// Struture Identifier
		0,			// -1 to Drop more than one file
		szDroppedFile,// Droped File Name
		MAX_PATH);

	if (m_tree.LoadFromXML(szDroppedFile))
	{
		strCurrentXML = szDroppedFile;

		m_tree.SetFocus();
		m_tree.PostMessage(WM_VSCROLL, SB_PAGEUP, 0);
		HTREEITEM hItem = m_tree.GetRootItem();
		hItem = m_tree.GetChildItem(hItem);
		if (hItem == NULL)
			hItem = m_tree.GetRootItem();
		m_tree.SelectItem(hItem);
		return 1;
	}
	return 0;
}

void CAPPsStarterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// This is to moving the Dialog by clicking any where on the dialog
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}


void CAPPsStarterDlg::OnEnKillfocusEditName()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_editName.GetWindowText(str);
	HTREEITEM hti;

	hti = m_tree.GetSelectedItem();
	

	node = (node_data*)m_tree.GetItemData(hti);
	node->name = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_tree.SetItemText(hti, str);// .SetWindowText(str);
	m_Title.SetWindowText(node->title == "" ? str : node->title);
}


void CAPPsStarterDlg::OnEnKillfocusEditTitle()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_editTitle.GetWindowText(str);

	HTREEITEM hti;
	hti = m_tree.GetSelectedItem();

	node = (node_data*)m_tree.GetItemData(hti);

	node->title = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_Title.SetWindowText(str);


}


void CAPPsStarterDlg::OnEnKillfocusEditPath()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_editPath.GetWindowText(str);

	HTREEITEM hti;
	hti = m_tree.GetSelectedItem();

	node = (node_data*)m_tree.GetItemData(hti);

	node->path = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);

}

//void CAPPsStarterDlg::OnTvnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: добавьте свой код обработчика уведомлений
//	
//	*pResult = 0;
//}


void CAPPsStarterDlg::OnCbnSelchangeComboIcon()
{
	// TODO: добавьте свой код обработчика уведомлений
	int i = m_cbIcon.GetCurSel();
	HTREEITEM hti = m_tree.GetSelectedItem();

	node = (node_data*)m_tree.GetItemData(hti);
	switch (i) {
	case 0:
		node->icon = "folder";
		break;
	case 1:
		node->icon = "1c";
		break;
	case 2:
		node->icon = "medoc";
		break;
	case 3:
		node->icon = "rdp";
		break;
	case 4:
		node->icon = "app";
		break;
	case 5:
		node->icon = "mail";
		break;
	case 6:
		node->icon = "web";
		break;
	case 7:
		node->icon = "share";
		break;
	case 8:
		node->icon = "vcam";
		break;
	case 9:
		node->icon = "cmd";
		break;
	case 10:
		node->icon = "script";
		break;
	case 11:
		node->icon = "pshell";
		break;
	case 12:
		node->icon = "appsicon";
		break;
	default:
		break;
	}
	m_tree.SetFocus();
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_tree.SetItemImage(hti, i, i);
}

void CAPPsStarterDlg::OnMoveUp()
{
	HTREEITEM htiMove, htiParent, htiPrev, hti;
	htiMove = m_tree.GetSelectedItem();
	htiPrev = m_tree.GetPrevSiblingItem(htiMove);
	if (htiPrev == NULL) return;
	htiPrev = m_tree.GetPrevSiblingItem(htiPrev);
	if (htiPrev == NULL) htiPrev = TVI_FIRST;
	htiParent = m_tree.GetParentItem(htiMove);
	hti = m_tree.CopyBranch(htiMove, htiParent, htiPrev);
	m_tree.SelectItem(hti);
	
	m_tree.DeleteItem(htiMove);
}

void CAPPsStarterDlg::OnMoveDown()
{

	HTREEITEM htiMove, htiParent, htiNext, hti;
	htiMove = m_tree.GetSelectedItem();
	htiNext = m_tree.GetNextSiblingItem(htiMove);
	if (htiNext == NULL) return;
	
	htiParent = m_tree.GetParentItem(htiMove);
	hti = m_tree.CopyBranch(htiMove, htiParent, htiNext);
	m_tree.SelectItem(hti);

	m_tree.DeleteItem(htiMove);
}

void CAPPsStarterDlg::OnTvnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}
void CAPPsStarterDlg::OnTvnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	if (pTVDispInfo->item.pszText == NULL) // не было, пользователь отменил его
	{
		*pResult = 0;
		return;
	}
	// TODO: добавьте свой код обработчика уведомлений
	
	HTREEITEM hti;

	hti = m_tree.GetSelectedItem();
	CString str;
	str = pTVDispInfo->item.pszText;

	node = (node_data*)m_tree.GetItemData(hti);
	node->name = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	//m_tree.SetItemText(hti, str);// .SetWindowText(str);
	m_editName.SetWindowText(str);
	m_Title.SetWindowText(node->title == "" ? str : node->title);
	// пусть у нас для примера нельзя, чтобы новое имя элемен
	// иначе принять изменения
	*pResult = 1;
}





void CAPPsStarterDlg::OnEnSetfocusEditName()
{
	// TODO: добавьте свой код обработчика уведомлений

}



void CAPPsStarterDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//must put class member menu at last
	md_Popup.OnDrawItem(nIDCtl, lpDrawItemStruct);

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CAPPsStarterDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	//must put class member menu at last
	md_Popup.OnMeasureItem(nIDCtl, lpMeasureItemStruct);

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

//void CAPPsStarterDlg::TTokenizer(const CString& strFields, LPCWSTR strDelimiters, std::vector<CString>& arFields)
//{
//	arFields.clear();
//
//	int curPos = 0;
//	CString token = strFields.Tokenize((LPCSTR)strDelimiters, curPos);
//	while (!token.IsEmpty()) {
//		arFields.push_back(token);
//		token = strFields.Tokenize((LPCSTR)strDelimiters, curPos);
//	}
//}

//void CAPPsStarterDlg::LoadCSVFile()
//{
//	m_tree.DeleteAllItems();
//	
//	HTREEITEM htiParent, htiChild;
//	htiParent = m_tree.InsertItem("Приложения", TVI_ROOT);
//
//	//<Item Name = "Приложения" Type = "container" Expand = "true"  Id = "11111111-e1e2-41d5-8fa5-4e4649897f77">
//
//	node_data* nnode = new node_data();
//	//node = (node_data*)0;
//	//nnode->id = "11111111-e1e2-41d5-8fa5-4e4649897f77";
//	//nnode->parent = "00000001-e45f-403a-a1a3-c3f4f5c98056";
//	nnode->name = "Приложения";
//	nnode->type = "container";
//	nnode->title = "ROOT";
//	nnode->expand = "true";
//	nnode->icon = "folder";
//
//	m_tree.SetItemData(htiParent, (DWORD_PTR)nnode);
//	//nnode = 0;
//	//m_tree.SelectItem(hItem);
//	//m_tree.Expand(hItem, TVE_EXPAND);
//	
//
//	
//	std::vector<CString> arStrokes;
//
//	CString str="";
//	CFile file;
//	if (file.Open("CSVfile.txt", CFile::modeRead))
//
//	{
//
//		int len = file.GetLength();
//
//		file.Read(str.GetBuffer(len), len);
//
//		str.ReleaseBuffer();
//
//	}
//
//
//
//	TTokenizer(str, L"\r\n", arStrokes);
//	
//	//HTREEITEM hItem = m_tree.GetRootItem();
//	//HTREEITEM hNewItem;
//	for (size_t i = 0; i < arStrokes.size()-1; i++) {
//		std::vector<CString> arFields;
//		TTokenizer(arStrokes[i], L";", arFields);
//		node_data* pnode = new node_data();
//		//HTREEITEM hItem = NULL;
//		//if (NULL == a_hTreeParent) {
//		//pnode->id = arFields[5];
//		//pnode->parent = "";
//		pnode->name = arFields[0];
//		pnode->type = arFields[1];
//		pnode->title = arFields[3];
//		pnode->path = arFields[2];
//		pnode->icon = arFields[4];
//		//pnode->expand = "true";
//		//hti = m_tree.GetSelectedItem();
//		htiChild = m_tree.InsertItem(pnode->name, htiParent, TVI_LAST);
//		//}
//		//else {
//		//	hItem = InsertItem(strAttr, a_hTreeParent);
//		//}
//
//		
//		
//
//		//strParent = "";
//
//		if (pnode->icon == "1c")
//			m_tree.SetItemImage(htiChild, 1, 1);
//		else if (pnode->icon == "medoc")
//			m_tree.SetItemImage(htiChild, 2, 2);
//		else if (pnode->icon == "rdp")
//			m_tree.SetItemImage(htiChild, 3, 3);
//		else if (pnode->icon == "app")
//			m_tree.SetItemImage(htiChild, 4, 4);
//		else if (pnode->icon == "mail")
//			m_tree.SetItemImage(htiChild, 5, 5);
//		else if (pnode->icon == "web")
//			m_tree.SetItemImage(htiChild, 6, 6);
//		else if (pnode->icon == "share")
//			m_tree.SetItemImage(htiChild, 7, 7);
//		else if (pnode->icon == "vcam")
//			m_tree.SetItemImage(htiChild, 8, 8);
//		else if (pnode->icon == "cmd")
//			m_tree.SetItemImage(htiChild, 9, 9);
//		else if (pnode->icon == "script")
//			m_tree.SetItemImage(htiChild, 10, 10);
//		else if (pnode->icon == "pshell")
//			m_tree.SetItemImage(htiChild, 11, 11);
//		else
//			m_tree.SetItemImage(htiChild, 0, 0);
//
//		//arFields.clear();
//		m_tree.SetItemData(htiChild, (DWORD_PTR)pnode);
//		//hti = hNewItem;
//		nnode = NULL;
//	}
//	m_tree.SetFocus();
//	m_tree.Expand(htiParent, TVE_EXPAND);
//}
// parse strokes




void CAPPsStarterDlg::OnBnClickedMfcbuttonPath()
{
	// TODO: добавьте свой код обработчика уведомлений
	const TCHAR szFilter[] = _T("All Files (*.*)|*.*|EXE Files (*.exe;*.bat;*cmd;*vbs;*rdp;*mmc)|*.exe;*.bat;*cmd;*vbs;*rdp;*mmc||");
	CFileDialog dlg(TRUE, _T("*.*"), NULL, OFN_DONTADDTORECENT | OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strP = dlg.GetPathName();
		//CFileVersionInfo vers;
		//vers.Open(strP);
		
		SHFILEINFOW shFileInfoW = {};
		UINT uFlags = SHGFI_ICON | SHGFI_SMALLICON;
		CString str = dlg.GetPathName();
		SHGetFileInfoW((CT2CW)str, FILE_ATTRIBUTE_NORMAL, &shFileInfoW, sizeof(SHFILEINFOW), uFlags);
		hIcon = shFileInfoW.hIcon;

		HTREEITEM hItem = m_tree.GetSelectedItem();
		int nImage, nSelectedImage;

		m_tree.GetItemImage(hItem, nImage, nSelectedImage);
		
		m_tree.m_imageList.Add(hIcon);
		int iItems = m_tree.m_imageList.GetImageCount() - 1;
		m_tree.SetItemImage(hItem, iItems, iItems);

		node->icon = "appsicon";
		
		m_tree.SetItemData(hItem, (DWORD_PTR)node);


		LPCWSTR path = (CT2W)dlg.GetPathName();
		CString strDesc2 = GetShellPropStringFromPath(path, PKEY_FileDescription);

		

		m_editPath.SetWindowText(dlg.GetPathName());
		OnEnKillfocusEditPath();
		m_editName.SetWindowText(dlg.GetFileTitle());
		OnEnKillfocusEditName();
		m_editTitle.SetWindowText(strDesc2);
		OnEnKillfocusEditTitle();
		if (strDesc2 == "")
			m_Title.SetWindowText(dlg.GetFileTitle());
		m_cbIcon.SetCurSelIcon(L"appsicon");

		m_tree.SetFocus();

		Invalidate();
	}
}


CString CAPPsStarterDlg::GetShellPropStringFromPath(LPCWSTR pPath, PROPERTYKEY const& key)
{
	CComPtr<IShellItem2> pItem;
	HRESULT hr = SHCreateItemFromParsingName(pPath, nullptr, IID_PPV_ARGS(&pItem));
	if (FAILED(hr))
		;
	CComHeapPtr<WCHAR> pValue;
	hr = pItem->GetString(key, &pValue);
	if (FAILED(hr))
		;
	return (CString)(pValue);
}