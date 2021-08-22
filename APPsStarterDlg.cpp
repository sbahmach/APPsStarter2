

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
#define INITIALX_96DPI 0 
#define INITIALY_96DPI 0 
#define INITIALWIDTH_96DPI 800
#define INITIALHEIGHT_96DPI 500
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
	CString strTarget = _T(" (x86):  ");
#ifdef _WIN64
	strTarget = _T(" (x64):  ");
#endif
	CString strVersion = _T("Version") + strTarget + stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_REVISION) "." stringify(VERSION_BUILD) " (" stringify(VERSION_DATE) " )";
	m_statVersion.SetWindowText(strVersion);
	return TRUE;
}

// CAPPsStarterDlg dialog

CAPPsStarterDlg::CAPPsStarterDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CAPPsStarterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	Brush_Main.CreateSolidBrush(RGB(255, 255, 255));

	/*LOGFONT lf_Title;
	memset(&lf_Title, 0, sizeof(LOGFONT));
	lf_Title.lfHeight = 36;
	lf_Title.lfWeight = FW_MEDIUM;
	lf_Title.lfCharSet = DEFAULT_CHARSET;
	_tcscpy(lf_Title.lfFaceName, _T("Arial Narrow"));
	m_font_Title.CreateFontIndirect(&lf_Title);*/
}

void CAPPsStarterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TREE1, m_tree);
	//DDX_Control(pDX, IDC_BUTTON_MENU, m_btMenu);
	//DDX_Control(pDX, IDC_BUTTON_START, m_btStart);
	//DDX_Control(pDX, IDC_BUTTON_PATH, m_btPath);
	//DDX_Control(pDX, IDCANCEL, m_btCancel);
	//DDX_Control(pDX, IDC_STATIC_1, m_Title);
	//DDX_Control(pDX, IDC_STATIC_2, m_stat);
	////DDX_Control(pDX, IDC_STATIC_PARENT, m_statParent);
	////DDX_Control(pDX, IDC_STATIC_ID, m_statID);
	//DDX_Control(pDX, IDC_STATIC_NAME, m_statName);
	//DDX_Control(pDX, IDC_STATIC_TITLE, m_statTitle);
	//DDX_Control(pDX, IDC_STATIC_PATH, m_statPath);
	//DDX_Control(pDX, IDC_STATIC_ICON, m_statIcon);
	//DDX_Control(pDX, IDC_CHECK1, m_check);
	//DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	//DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	//DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	////DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	////DDX_Control(pDX, IDC_EDIT_PARENT, m_editParent);
	//DDX_Control(pDX, IDC_COMBO_ICON, m_cbIcon);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_BUTTON_MENU, m_btMenu);
	DDX_Control(pDX, IDC_BUTTON_IMPORT, m_btImport);
	DDX_Control(pDX, IDC_CHECK_ONTOP, m_ckOnTop);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edName);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_edTitle);
	DDX_Control(pDX, IDC_EDIT_PATH, m_edPath);
	DDX_Control(pDX, IDC_COMBO_ICONS, m_cb2);
	//DDX_Control(pDX, IDC_COMBO_ICON, m_cbIcon);
	DDX_Control(pDX, IDC_STATIC_MAINTITLE, m_stMainTitle);
	//DDX_Control(pDX, IDC_STATIC_ONTOP, m_stOnTop);
	DDX_Control(pDX, IDC_STATIC_NAME, m_stName);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_stTitle);
	DDX_Control(pDX, IDC_STATIC_PATH, m_stPath);
	DDX_Control(pDX, IDC_STATIC_ICON, m_stIcon);
	DDX_Control(pDX, IDC_STATIC_INFO, m_stInfo);

	DDX_Control(pDX, IDC_TREE, m_tree);
}



BEGIN_MESSAGE_MAP(CAPPsStarterDlg, CDialog)
	
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DROPFILES, OnDropFiles)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnTvnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnNMDblclkTree1)
	ON_BN_CLICKED(IDOK, OnStart)
	ON_WM_CONTEXTMENU()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	//ON_WM_MOVE()
	//ON_WM_MOVING()
	ON_MESSAGE(WM_DPICHANGED, OnDpiChanged)
	//ON_MESSAGE(WM_DPICHANGED, OnDpiChanged)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_ONTOP, &CAPPsStarterDlg::OnBnClickedCheck1)

	ON_EN_KILLFOCUS(IDC_EDIT_NAME, &CAPPsStarterDlg::OnEnKillfocusEditName)
	ON_EN_KILLFOCUS(IDC_EDIT_TITLE, &CAPPsStarterDlg::OnEnKillfocusEditTitle)
	ON_EN_KILLFOCUS(IDC_EDIT_PATH, &CAPPsStarterDlg::OnEnKillfocusEditPath)
	//ON_CBN_SELCHANGE(IDC_COMBO_ICON, &CAPPsStarterDlg::OnCbnSelchangeComboIcon)

	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, &CAPPsStarterDlg::OnTvnEndlabeleditTree1)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE, &CAPPsStarterDlg::OnTvnBeginlabeleditTree1)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CAPPsStarterDlg::OnBnClickedButtonPath)
    ON_BN_CLICKED(IDC_BUTTON_MENU, &CAPPsStarterDlg::OnBnClickedButtonMenu)
	ON_CBN_SELCHANGE(IDC_COMBO_ICONS, &CAPPsStarterDlg::OnCbnSelchangeCombo2)
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

	SetWindowText(_T("APPs STARTER"));
	SetWindowLong(this->m_hWnd,
		GWL_STYLE,
		GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.LoadToolBar(BAR_MAIN);

	
	GetWindowRect(rcWindowDef);

	//iOldDPI = iCurrentDPI;
	iCurrentDPI = GetWindowDPI(m_hWnd);
	//iCurrentDPI = LOWORD(wParam);
	CString strInfo = _T("");
	strInfo.Format(_T("oldDPI: %d, curDPI: %d, W: %d, H: %d"), iOldDPI, iCurrentDPI, rcWindowDef.Width(), rcWindowDef.Height());
	if (m_stInfo) m_stInfo.SetWindowText(strInfo);
	//ShowWindow(SW_HIDE);
	/*CString strRC;
	strRC.Format(_T("W: %d, H: %d", rcWindowDef.Width(), rcWindowDef.Height()));
	MessageBox(strRC);*/
	
	//m_tree.ModifyStyle(0, TVS_DISABLEDRAGDROP);
	//UpdateData(FALSE);

	HTREEITEM hItem = m_tree.GetSelectedItem();

	/*m_cbIcon.InsertIcon(0, IDI_FOLDER, _T("folder"));
	m_cbIcon.InsertIcon(1, IDI_1C, _T("1c"));
	m_cbIcon.InsertIcon(2, IDI_MEDOC, _T("medoc"));
	m_cbIcon.InsertIcon(3, IDI_RDP, _T("rdp"));
	m_cbIcon.InsertIcon(4, IDI_APP, _T("app"));
	m_cbIcon.InsertIcon(5, IDI_MAIL, _T("mail"));
	m_cbIcon.InsertIcon(6, IDI_WEB, _T("web"));
	m_cbIcon.InsertIcon(7, IDI_SHARE, _T("share"));
	m_cbIcon.InsertIcon(8, IDI_VCAM, _T("vcam"));
	m_cbIcon.InsertIcon(9, IDI_CMD, _T("cmd"));
	m_cbIcon.InsertIcon(10, IDI_SCRIPT, _T("script"));
	m_cbIcon.InsertIcon(11, IDI_PSHELL, _T("pshell"));
	m_cbIcon.InsertIcon(12, IDI_APP, _T("appsicon"));*/

	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_FOLDER));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_1C));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_MEDOC));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_RDP));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_APP));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_MAIL));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_WEB));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_SHARE));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_VCAM));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_CMD));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_SCRIPT));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_PSHELL));
	iconBase.push_back(AfxGetApp()->LoadIcon(IDI_APP));

	SetImageList();

	m_tree.SetFocus();
	m_tree.SelectItem(hItem);

	

	//m_stTitle.SetFont(&m_font_Title);

	COLORREF col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected;

	col_BtnText_Disabled = RGB(200, 200, 200);
	col_BtnText = RGB(47, 145, 207);
	col_BtnText_IsHover = RGB(7, 105, 167);
	col_BtnText_Selected = RGB(255, 255, 255);
	col_BtnFace_Disabled = RGB(255, 255, 255);
	col_BtnFace = RGB(255, 255, 255);
	col_BtnFace_IsHover = RGB(201, 225, 255);
	col_BtnFace_Selected = RGB(47, 145, 207);
	col_BtnFrame_Disabled = RGB(200, 200, 200);
	col_BtnFrame = RGB(97, 195, 255);
	col_BtnFrame_IsHover = RGB(2, 100, 162);
	col_BtnFrame_Selected = RGB(255, 255, 255);

	//m_btStart.SetWindowText(_T("ЗАПУСТИТЬ"));
	m_btOK.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	//m_btMenu.SetWindowText(_T("МЕНЮ"));
	m_btMenu.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	//m_btPath.SetWindowText(_T("..."));
	m_btImport.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	//m_btCancel.SetWindowText(_T("ЗАКРЫТЬ"));
	m_btCancel.SetColor(col_BtnText_Disabled, col_BtnText, col_BtnText_IsHover, col_BtnText_Selected
		, col_BtnFace_Disabled, col_BtnFace, col_BtnFace_IsHover, col_BtnFace_Selected
		, col_BtnFrame_Disabled, col_BtnFrame, col_BtnFrame_IsHover, col_BtnFrame_Selected);

	m_tree.ModifyStyle(0, TVS_EDITLABELS);
	DragAcceptFiles(true);

	//m_cb1.SetCurSel(0);
	
	ReadReg();
	DynimicLayoutCalculate();

	OnOpen();
	CRect rcWin;
	GetWindowRect(&rcWin);
	InvalidateRect(&rcWin);
	/*CRect rc;
	CWnd* wnd = GetDlgItem(IDC_BUTTON_START);
	wnd->GetWindowRect(&rc);
	ScreenToClient(rc);
	rc.left -= 10* getSystemScaleFactor();
	wnd->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);*/
	//m_btStart.SetWindowPos
	//ShowWindow(SW_SHOW);
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
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAINTITLE) {
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
		CDialog::OnPaint();
		
	}
}

HCURSOR CAPPsStarterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAPPsStarterDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	__super::OnGetMinMaxInfo(lpMMI);


	lpMMI->ptMinTrackSize.x = MulDiv(INITIALWIDTH_96DPI, iCurrentDPI, 96);
	lpMMI->ptMinTrackSize.y = MulDiv(INITIALHEIGHT_96DPI, iCurrentDPI, 96);
}

void CAPPsStarterDlg::OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = m_tree.GetSelectedItem();

//////////////////////////////////////////////////////////////////////////////////// 
	// !!!!
	node = (node_data*)m_tree.GetItemData(hItem);
	CString strPath(node->path);
	m_stMainTitle.SetWindowText(node->title == _T("") ? node->name : node->title);
	m_edName.SetWindowText(node->name);
	m_edTitle.SetWindowText(node->title);
	//m_statID.SetWindowText(node->id);
	//m_statParent.SetWindowText(node->parent);

	if (node->type.MakeLower() == _T("container")) {
		m_edPath.EnableWindow(false);
		m_stPath.EnableWindow(false);
		m_stIcon.EnableWindow(false);
		m_edPath.SetWindowText(_T(""));
		m_btImport.EnableWindow(false);
		//m_cbIcon.EnableWindow(false);
		m_cb2.EnableWindow(false);
	}
	else {
		m_edPath.EnableWindow(true);
		m_stPath.EnableWindow(true);
		m_stIcon.EnableWindow(true);
		m_edPath.SetWindowText(node->path);
		//m_cbIcon.EnableWindow(true);
		m_cb2.EnableWindow(true);
		m_btImport.EnableWindow(true);
	}
	if (node->icon == _T("")) {
		//m_cbIcon.SetCurSelIcon(_T("folder"));
		int i = m_cb2.FindStringExact(0, _T("folder"));
		m_cb2.SetCurSel(i);
		//m_cb2.SelectString(0, _T("folder"));
		//m_cbIcon.SetCurSel(0);
	}
	else {
		//m_cbIcon.SetCurSelIcon(node->icon);
		int i = m_cb2.FindStringExact(0, node->icon);
		m_cb2.SetCurSel(i);
		//m_cbIcon.SetCurSel(1);
		//m_cbIcon.SetCurSel(1);
	}
	
	if (node->path.Compare(_T("")) == 0) {
		m_btOK.EnableWindow(FALSE);
	}
	else {
		m_btOK.EnableWindow(TRUE);
	}
	//m_cbIcon.SetCurSelIcon(node->icon == _T("") ? _T("folder") : node->icon);
	//m_btStart.EnableWindow(node->path == _T("") ? FALSE : TRUE);

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
	if (strCmdXmlFile.Right(4) != _T(".xml")) {
		strCmdXmlFile = strCmdXmlFile + _T(".xml");
	}

	if (m_tree.LoadFromXML(strCmdXmlFile))
	{
		strCurrentXML = strCmdXmlFile;
	}
	else if (m_tree.LoadFromXML(strDefXMLFile))
	{
		
		strCurrentXML = strDefXMLFile;
	}
	else if (m_tree.LoadFromXML(_T("..\\def.xml")))
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
	TCHAR szDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szDirectory);
	dlg.m_ofn.lpstrInitialDir = szDirectory;
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
	else if (m_tree.LoadFromXML(strDefXMLFile))
	{

		strCurrentXML = strDefXMLFile;
	}
	else if (m_tree.LoadFromXML(_T("..\\def.xml")))
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

void CAPPsStarterDlg::OnSave()
{
	//LoadCSVFile();
	m_tree.SaveToXML(_T("defconf.xml"));
}

void CAPPsStarterDlg::OnSaveAs()
{
	char strFilter[] = { "Text Files (*.xml)|*.xml|" };

	CFileDialog FileDlg(FALSE, CString(".xml"), NULL, OFN_DONTADDTORECENT | OFN_NOCHANGEDIR | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, CString(strFilter));
	CString strFileName = _T("");
	CString strFilePath = _T("");
	CString strFullPath = _T("");
	TCHAR szDirectory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szDirectory);
	FileDlg.m_ofn.lpstrInitialDir = szDirectory;
	if (FileDlg.DoModal() == IDOK) // this is the line which gives the errors
	{
		strFileName = FileDlg.GetFileName(); //filename
		strFilePath = FileDlg.GetFolderPath(); //filepath (folders)
		strFullPath = strFilePath + _T("\\") + strFileName;
		m_tree.SaveToXML(strFullPath);
	}
	
}

void CAPPsStarterDlg::OnEdit()
{
	CString strPath = _T("");
	if (strCurrentXML.Find('\\') != -1) {
		strPath = strCurrentXML;
	}
	else {
		TCHAR szDirectory[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szDirectory);
		strCurrentXML = _T("\\") + strCurrentXML;
		strPath = szDirectory + strCurrentXML;
	}
	
	if (strPath != "") {
		if (FILE* file = _tfopen(strPath, _T("r"))) {
			fclose(file);

			ShellExecute(GetSafeHwnd(), _T("open"), _T("rundll32.exe"), _T("shell32.dll,OpenAs_RunDLL ") + strPath, NULL, 1);
		}
		else {
			MessageBox(_T("Файл не найден! Неправильный путь!"));
		}
	}
}

void CAPPsStarterDlg::OnBnClickedCancel()
{
	WriteReg();
	CDialog::OnCancel();
}


void CAPPsStarterDlg::OnStart()
{

	HTREEITEM hItem = m_tree.GetSelectedItem();

	CString strPath = node->path;
	if (strPath != "")
			ShellExecute(GetSafeHwnd(), _T("open"), strPath, NULL, NULL, 1);
}

void CAPPsStarterDlg::OnRunAs()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath = node->path;
	if (strPath != "")
		ShellExecute(GetSafeHwnd(), _T("runas"), strPath, NULL, NULL, 1);
}

void CAPPsStarterDlg::OnOpenWith()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath = node->path;
	if (strPath != "") {
		if (FILE* file = _tfopen(strPath, _T("r"))) {
			fclose(file);
			ShellExecute(GetSafeHwnd(), _T("open"), _T("rundll32.exe"), _T("shell32.dll,OpenAs_RunDLL ") + strPath, NULL, 1);
		}
		else {
			MessageBox(_T("Файл не найден! Неправильный путь!"));
		}
	}
}

void CAPPsStarterDlg::OnOpenDirectory()
{
	HTREEITEM hItem = m_tree.GetSelectedItem();
	CString strPath;
	strPath = node->path;
	if (strPath != "") {
		if (FILE* file = _tfopen(strPath, _T("r"))) {
			fclose(file);
			strPath.Truncate(strPath.ReverseFind('\\'));
			ShellExecute(GetSafeHwnd(), _T("open"), strPath, NULL, NULL, 1);
		}
		else {
			MessageBox(_T("Файл не найден! Неправильный путь!"));
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

	if (node->type == _T("container")) {
		htiParent = m_tree.GetSelectedItem();
		hti = TVI_FIRST;
	}

	htiChild = m_tree.InsertItem(_T("New App"), htiParent, hti);
	m_tree.SetItemImage(htiChild, 4, 4);
	node_data* nnode = new node_data();
	//CString str = m_tree.CreateID();
	nnode->name = _T("New App");
	nnode->path = _T("path");
	nnode->title = _T("");
	nnode->icon = _T("app");
	nnode->expand = _T("");
	nnode->type = _T("application");
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

	if (node->type == _T("container")) {
		htiParent = m_tree.GetSelectedItem();
		hti = TVI_FIRST;
	}

	htiChild = m_tree.InsertItem(_T("New Folder"), htiParent, hti);
	m_tree.SetItemImage(htiChild, 0,0);
	node_data* nnode = new node_data();
	//CString str = m_tree.CreateID();
	nnode->name = _T("New Folder");
	nnode->path = _T("");
	nnode->title = _T("");
	nnode->icon = _T("folder");
	nnode->expand = _T("false");
	nnode->type = _T("container");
	//nnode->id = str;// m_tree.CreateID();
	//nnode->parent = node->id;
	m_tree.SetItemData(htiChild, (DWORD_PTR)nnode);
	nnode = 0;
	m_tree.EnsureVisible(htiChild);
	m_tree.EditLabel(htiChild);
	m_tree.Select(htiChild, TVGN_CARET);
}

void CAPPsStarterDlg::OnImportApp()
{
	m_tree.SetRedraw(FALSE);
	CString csRootPath(_T("С:\\Windows\\System32\\"));
	CString csFileDlgTitle = _T("Выберите файлы для импорта");
	//csFileDlgTitle.LoadString("File Open");


	//"All files (*.*)|*.*|"
	const TCHAR szFilter[] = _T("EXE Files (*.exe;*.bat;*cmd;*vbs;*rdp;*mmc)|*.exe;*.bat;*cmd;*vbs;*rdp;*mmc|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("EXE Files (*.exe;*.bat;*cmd;*vbs;*rdp;*mmc)"), NULL, OFN_DONTADDTORECENT | OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	dlg.m_ofn.lpstrTitle = csFileDlgTitle;
	dlg.m_ofn.lpstrInitialDir = csRootPath;
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos(dlg.GetStartPosition());
		while (pos)
		{
			CString csFileName(dlg.GetNextPathName(pos));
			CString csFileTitle = PathFindFileName(csFileName);
			PathRemoveExtension(csFileTitle.GetBuffer());
			csFileTitle.ReleaseBuffer();
			//implement ur fn to open the file accordingly


			HTREEITEM hti, htiChild, htiParent;
			hti = m_tree.GetSelectedItem();
			htiParent = m_tree.GetParentItem(hti);

			node = (node_data*)m_tree.GetItemData(hti);

			if (node->type == _T("container")) {
				htiParent = m_tree.GetSelectedItem();
				hti = TVI_FIRST;
			}

			htiChild = m_tree.InsertItem(_T("New App"), htiParent, hti);
			m_tree.SetItemImage(htiChild, 4, 4);
			node_data* nnode = new node_data();
			//CString str = m_tree.CreateID();
			nnode->name = _T("New App");
			nnode->path = _T("path");
			nnode->title = _T("");
			nnode->icon = _T("app");
			nnode->expand = _T("");
			nnode->type = _T("application");
			//nnode->id = str;// m_tree.CreateID();
			//nnode->parent = node->id;
			m_tree.SetItemData(htiChild, (DWORD_PTR)nnode);
			nnode = 0;
			m_tree.EnsureVisible(htiChild);
			m_tree.EditLabel(htiChild);
			m_tree.Select(htiChild, TVGN_CARET);


			//CString strP = dlg.GetPathName();
			//CFileVersionInfo vers;
			//vers.Open(strP);

			SHFILEINFOW shFileInfoW = {};
			UINT uFlags = SHGFI_ICON | SHGFI_SMALLICON;
			CString str = csFileName;
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


			LPCWSTR path = (CT2W )csFileName;
			CString strDesc2 = GetShellPropStringFromPath(path, PKEY_FileDescription);



			m_edPath.SetWindowText(csFileName);
			OnEnKillfocusEditPath();
			m_edName.SetWindowText(csFileTitle);
			OnEnKillfocusEditName();
			m_edTitle.SetWindowText(strDesc2);
			OnEnKillfocusEditTitle();
			if (strDesc2 == "")
				m_stMainTitle.SetWindowText(dlg.GetFileTitle());
			//m_cbIcon.SetCurSelIcon(_T("appsicon"));
			int i = m_cb2.FindStringExact(0, _T("appsicon"));
			m_cb2.SetCurSel(i);
			
			m_tree.SetFocus();

		}
	}

	//OnInsertItem();
	//OnBnClickedButtonPath();
	m_tree.SetRedraw(TRUE);
	m_tree.Invalidate();
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
				pMu->ModifyMenu(ID_MENU_EXPAND, MF_BYCOMMAND, ID_MENU_EXPAND, _T("Свернуть \tRight Left"));

			//try delete
			if (m_tree.ItemHasChildren(hSelectedItem)) {
				pMu->DeleteMenu(ID_MENU_RUN, MF_BYCOMMAND);
				pMu->DeleteMenu(ID_MENU_RUNAS, MF_BYCOMMAND);
				pMu->DeleteMenu(ID_MENU_OPENWITH, MF_BYCOMMAND );
				pMu->DeleteMenu(ID_MENU_OPENFOLDER, MF_BYCOMMAND );
				pMu->DeleteMenu(0, MF_SEPARATOR);
			}

			if ((_taccess(node->path, 00) == -1)) {

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
			COLORREF clrVertBar = RGB(201, 225, 255);

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
			case ID_MENU_IMPORT_APP:
				OnImportApp();
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
	bool bChecked = m_ckOnTop.GetCheck();
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
	CString strSection = NULL;

	WINDOWPLACEMENT* lwp;
	UINT nl;

	int iAlwaysOnTop = AfxGetApp()->GetProfileInt(strSection, _T("AlwaysOnTop"), 0);

	if (iAlwaysOnTop) {
		m_ckOnTop.SetCheck(1);
	}
	else {
		m_ckOnTop.SetCheck(0);
	}
	OnBnClickedCheck1();

	if (AfxGetApp()->GetProfileBinary(strSection, _T("WP"), (LPBYTE*)&lwp, &nl))
	{
		CRect r = lwp->rcNormalPosition;
		if (::MonitorFromRect(r, MONITOR_DEFAULTTONULL) != nullptr) {
			int w = max(lwp->rcNormalPosition.right - lwp->rcNormalPosition.left, INITIALWIDTH_96DPI);
			int h = max(lwp->rcNormalPosition.bottom - lwp->rcNormalPosition.top, INITIALHEIGHT_96DPI);
			//int iOldDPI = AfxGetApp()->GetProfileInt(strSection, _T("DPI"), 0);
			w = MulDiv(w, iCurrentDPI, 96);
			h = MulDiv(h, iCurrentDPI, 96);
			lwp->rcNormalPosition.right = lwp->rcNormalPosition.left + w;
			lwp->rcNormalPosition.bottom = lwp->rcNormalPosition.top + h;
			SetWindowPlacement(lwp);
		}
	}
	delete[] lwp;

	/*if (m_bNoSaveSettings) {
		return;
	}

	CString strSection = NULL;
	CWinApp* pApp = AfxGetApp();

	int iAlwaysOnTop;
	iAlwaysOnTop = pApp->GetProfileInt(strSection, _T("AlwaysOnTop"), 0);

	if (iAlwaysOnTop) {
		m_ckOnTop.SetCheck(1);
	}
	else {
		m_ckOnTop.SetCheck(0);
	}
	OnBnClickedCheck1();
		
	WINDOWPLACEMENT* lwp;
	UINT nl;

	if (pApp->GetProfileBinary(strSection, _T("WP"), (LPBYTE*)&lwp, &nl))
	{
		CRect r = lwp->rcNormalPosition;
		if (::MonitorFromRect(r, MONITOR_DEFAULTTONULL) != nullptr) {
			SetWindowPlacement(lwp);
			delete[] lwp;
		}
	}*/
}

void CAPPsStarterDlg::WriteReg()
{

	CString strSection = NULL;

	int iAlwaysOnTop = m_ckOnTop.GetCheck();
	AfxGetApp()->WriteProfileInt(strSection, _T("AlwaysOnTop"), iAlwaysOnTop);

	AfxGetApp()->WriteProfileInt(strSection, _T("DPI"), iCurrentDPI);

	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);
	int w = wp.rcNormalPosition.right - wp.rcNormalPosition.left;
	int h = wp.rcNormalPosition.bottom - wp.rcNormalPosition.top;
	w = MulDiv(w, 96, iCurrentDPI);
	h = MulDiv(h, 96, iCurrentDPI);
	wp.rcNormalPosition.right = wp.rcNormalPosition.left + w;
	wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + h;

	AfxGetApp()->WriteProfileBinary(strSection, _T("WP"), (LPBYTE)&wp, sizeof(wp));
	/*if (m_bNoSaveSettings) {
		return;
	}
	
	CString strSection = NULL;

	CWinApp* pApp = AfxGetApp();

	int iAlwaysOnTop;
	iAlwaysOnTop = m_ckOnTop.GetCheck();
	pApp->WriteProfileInt(strSection, _T("AlwaysOnTop"), iAlwaysOnTop);

	WINDOWPLACEMENT wp;
	GetWindowPlacement(&wp);

	pApp->WriteProfileBinary(strSection, _T("WP"), (LPBYTE)&wp, sizeof(wp));*/

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
		if (i == IDC_TREE) {
			OnDublicate();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == VK_RETURN)) //Ctrl + Enter
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnRunAs();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x4F))//Ctrl + O
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnOpenWith();
		}
		return TRUE;
	}
	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x4E))//Ctrl + N
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnInsertItem();
		}
		return TRUE;
	}
	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x59)) //ctrl + Y
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnSortAZ();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x55)) //ctrl + U
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnSortZA();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_CONTROL) < 0 && (pMsg->wParam == 0x52)) //ctrl + R
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnReload();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && (pMsg->wParam == 0x4F)) { //shft+O
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnOpenDirectory();
		}
		return TRUE;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000 && (pMsg->wParam == 0x4E)) { //shft+N
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			OnInsertFolder();
		}
		return TRUE;
	}

	if (pMsg->wParam == VK_F2) //F2
	{
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
			
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

	if ((pMsg->message == WM_KEYDOWN) && pMsg->wParam == VK_ESCAPE) {
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_EDIT_NAME) {
			m_edName.Undo();
			return TRUE;
		}
		if (i == IDC_EDIT_TITLE) {
			m_edTitle.Undo();
			return TRUE;
		}
		if (i == IDC_EDIT_PATH) {
			m_edPath.Undo();
			return TRUE;
		}
	}

	if ((pMsg->message == WM_KEYDOWN) && pMsg->wParam == VK_DELETE) {
		CWnd* pWnd = GetFocus();
		UINT i = pWnd->GetDlgCtrlID();
		if (i == IDC_TREE) {
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
			if (i == IDC_TREE) {
				OnMoveUp();
				return TRUE;
			}
		}
		if (pMsg->wParam == VK_DOWN)
		{
			CWnd* pWnd = GetFocus();
			UINT i = pWnd->GetDlgCtrlID();
			if (i == IDC_TREE) {
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
		(CT2W)szDroppedFile,// Droped File Name
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
	m_edName.GetWindowText(str);
	HTREEITEM hti;

	hti = m_tree.GetSelectedItem();
	

	node = (node_data*)m_tree.GetItemData(hti);
	node->name = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_tree.SetItemText(hti, str);// .SetWindowText(str);
	m_stMainTitle.SetWindowText(node->title == "" ? str : node->title);
}


void CAPPsStarterDlg::OnEnKillfocusEditTitle()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_edTitle.GetWindowText(str);

	HTREEITEM hti;
	hti = m_tree.GetSelectedItem();

	node = (node_data*)m_tree.GetItemData(hti);

	node->title = str;
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_stMainTitle.SetWindowText(str);


}


void CAPPsStarterDlg::OnEnKillfocusEditPath()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_edPath.GetWindowText(str);

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


//void CAPPsStarterDlg::OnCbnSelchangeComboIcon()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//	int i = m_cbIcon.GetCurSel();
//	HTREEITEM hti = m_tree.GetSelectedItem();
//
//	node = (node_data*)m_tree.GetItemData(hti);
//	switch (i) {
//	case 0:
//		node->icon = _T("folder");
//		break;
//	case 1:
//		node->icon = _T("1c");
//		break;
//	case 2:
//		node->icon = _T("medoc");
//		break;
//	case 3:
//		node->icon = _T("rdp");
//		break;
//	case 4:
//		node->icon = _T("app");
//		break;
//	case 5:
//		node->icon = _T("mail");
//		break;
//	case 6:
//		node->icon = _T("web");
//		break;
//	case 7:
//		node->icon = _T("share");
//		break;
//	case 8:
//		node->icon = _T("vcam");
//		break;
//	case 9:
//		node->icon = _T("cmd");
//		break;
//	case 10:
//		node->icon = _T("script");
//		break;
//	case 11:
//		node->icon = _T("pshell");
//		break;
//	case 12:
//		node->icon = _T("appsicon");
//		break;
//	default:
//		break;
//	}
//	m_tree.SetFocus();
//	m_tree.SetItemData(hti, (DWORD_PTR)node);
//	m_tree.SetItemImage(hti, i, i);
//}

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
	m_edName.SetWindowText(str);
	m_stMainTitle.SetWindowText(node->title == "" ? str : node->title);
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
	md_Popup.OnDrawItem(nIDCtl, lpDrawItemStruct, iCurrentDPI);
	md_Main.OnDrawItem(nIDCtl, lpDrawItemStruct, iCurrentDPI);

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CAPPsStarterDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	//must put class member menu at last
	md_Popup.OnMeasureItem(nIDCtl, lpMeasureItemStruct, iCurrentDPI);
	md_Main.OnMeasureItem(nIDCtl, lpMeasureItemStruct, iCurrentDPI);
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




void CAPPsStarterDlg::OnBnClickedButtonPath()
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

		node->icon = _T("appsicon");
		
		m_tree.SetItemData(hItem, (DWORD_PTR)node);


		LPCWSTR path = (CT2W)dlg.GetPathName();
		CString strDesc2 = GetShellPropStringFromPath(path, PKEY_FileDescription);

		

		m_edPath.SetWindowText(dlg.GetPathName());
		OnEnKillfocusEditPath();
		m_edName.SetWindowText(dlg.GetFileTitle());
		OnEnKillfocusEditName();
		m_edTitle.SetWindowText(strDesc2);
		OnEnKillfocusEditTitle();
		if (strDesc2 == "")
			m_stMainTitle.SetWindowText(dlg.GetFileTitle());
		//m_cbIcon.SetCurSelIcon(_T("appsicon"));
		int i = m_cb2.FindStringExact(0, _T("appsicon"));
		m_cb2.SetCurSel(i);
		m_tree.SetFocus();

		Invalidate();
	}
}


CString CAPPsStarterDlg::GetShellPropStringFromPath(LPCWSTR pPath, PROPERTYKEY const& key)
{
	CComPtr<IShellItem2> pItem;
	HRESULT hr = SHCreateItemFromParsingName(pPath, nullptr, IID_PPV_ARGS(&pItem));
	if (FAILED(hr))
		return  _T("");
	CComHeapPtr<WCHAR> pValue;
	hr = pItem->GetString(key, &pValue);
	if (FAILED(hr))
		return  _T("");
	CString newCString(pValue);
	return newCString;
}

void CAPPsStarterDlg::OnBnClickedButtonMenu()
{
    // TODO: добавьте свой код обработчика уведомлений
	CMenu mu;
	//if (mu != NULL) return;
	if (mu.LoadMenu(MU_MAIN) == 0)	return;

	CMenu* pMu = mu.GetSubMenu(0);
	if (pMu == 0)	return;

	
	COLORREF clrMenuBar = COLOR_MYDLG;
	//COLORREF clrVertBar = RGB(47, 145, 207);
	//COLORREF clrVertBar = RGB(200, 227, 244);
	COLORREF clrVertBar = RGB(201, 225, 255);

	md_Main.SetOwnerDraw(pMu, 0, &m_wndToolBar, 0, &clrMenuBar, &clrVertBar);

	CRect r;
	m_btMenu.GetClientRect(&r);
	m_btMenu.ClientToScreen(r);
	/*CPoint ptScreen, ptMenu;
	ptMenu.x = r.left;
	ptMenu.y = r.bottom;

	r.top = r.bottom;*/

	UINT nID = pMu->TrackPopupMenu(TPM_RETURNCMD, r.left, r.bottom, this);

	switch (nID) {
	case ID_MENU_IMPORT:
		OnLoad();
		break;
	case ID_MENU_IMPORT_DEF:
		//OnReload();
		WriteReg();
		break;
	case ID_MENU_EDIT:
		OnEdit();
		break;
	case ID_MENU_SAVE:
		OnSave();
		break;
	case ID_MENU_SAVE_AS:
		OnSaveAs();
		break;
	default:
		//MessageBox("Ахтунг!!!", "Yup!", MB_ICONINFORMATION);
		break;
	}
}

//UINT CAPPsStarterDlg::startThreadImport(LPVOID param)
//{
//	THREADSTRUCT* ts = (THREADSTRUCT*)param;
//	ts->_this->OnImportApp();
//	//ts->_this->SetTimer(TIMER_EASEIN, 10, NULL); // запускаем таймер появления
//
//	delete ts;
//	return 1;
//}
//
//UINT CAPPsStarterDlg::startThreadOut(LPVOID param)
//{
//	THREADSTRUCT* ts = (THREADSTRUCT*)param;
//	//ts->_this->StartTime = GetTickCount(); // фиксируем текущее время
//	//ts->_this->SetTimer(TIMER_EASEOUT, 10, NULL); // запускаем таймер исчезновения
//
//	delete ts;
//	return 1;
//}
//
//void CAPPsStarterDlg::startImport()
//{
//	THREADSTRUCT* _param = new THREADSTRUCT;
//	_param->_this = this;
//	AfxBeginThread(startThreadImport, _param); // запускаем отдельный поток
//
//}
//
//void CAPPsStarterDlg::startOut()
//{
//	THREADSTRUCT* _param = new THREADSTRUCT;
//	_param->_this = this;
//	AfxBeginThread(startThreadOut, _param); // запускаем отдельный поток
//}

void CAPPsStarterDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	DynimicLayoutCalculate();
}

void CAPPsStarterDlg::OnSizing(UINT nSide, LPRECT pRect)
{
	__super::OnSizing(nSide, pRect);

	CRect rc;
	GetWindowRect(&rc);

	int x = MulDiv(INITIALWIDTH_96DPI, iCurrentDPI, 96);
	int y = MulDiv(INITIALHEIGHT_96DPI, iCurrentDPI, 96);

	if (rc.Width() <= x || rc.Height() <= y) {
		return;
	}

	DynimicLayoutCalculate();
}

LRESULT CAPPsStarterDlg::OnDpiChanged(WPARAM wParam, LPARAM lParam)
{
	CRect rc, rcWin;
	iOldDPI = iCurrentDPI;
	iCurrentDPI = GetWindowDPI(m_hWnd);
	//iCurrentDPI = LOWORD(wParam);
	/*CString strInfo = _T("");
	strInfo.Format(_T("oldDPI: %d, curDPI: %d"), iOldDPI, iCurrentDPI);
	if (m_stInfo) m_stInfo.SetWindowText(strInfo);*/

	GetWindowRect(&rc);


	int dpiScaledWidth, dpiScaledHeight;
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	CString strInfo = _T("");
	strInfo.Format(_T("oldDPI: %d, curDPI: %d, W: %d, H: %d"), iOldDPI, iCurrentDPI, dpiScaledWidth, dpiScaledHeight);
	if (m_stInfo) m_stInfo.SetWindowText(strInfo);
	//m_stInfo.Invalidate();

	SetImageList();

	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild) {
		pwndChild->GetWindowRect(&rc);
		//pwndChild->EnableWindow(FALSE);
		dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
		dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
		
		pwndChild->SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);
		//if (pwndChild->GetDlgCtrlID() == IDC_COMBO_ICON) {
		//	m_cbIcon.SetItemHeight(-1, dpiScaledHeight);
		//	//m_cbIcon.SetItemHeight(0, dpiScaledHeight);
		//}
		pwndChild = pwndChild->GetNextWindow();
	};


	/*m_ckOnTop.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_ckOnTop.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_stOnTop.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_stOnTop.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_stMainTitle.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_stMainTitle.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_edName.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_edName.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_stName.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_stName.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_edTitle.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_edTitle.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_stTitle.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_stTitle.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_edPath.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_edPath.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_stPath.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_stPath.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_btOK.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_btOK.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_btCancel.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_btCancel.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_btMenu.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_btMenu.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	m_btImport.GetWindowRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_btImport.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	
	m_cbIcon.GetClientRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_cbIcon.SetItemHeight(-1, dpiScaledHeight);
	m_cbIcon.SetItemHeight(0, dpiScaledHeight);
	m_cbIcon.SetWindowPos(nullptr, rc.left, rc.top, dpiScaledWidth, dpiScaledHeight, SWP_NOZORDER | SWP_NOACTIVATE);*/
	/*m_cbIcon.GetClientRect(&rc);
	dpiScaledWidth = MulDiv(rc.Width(), iCurrentDPI, iOldDPI);
	dpiScaledHeight = MulDiv(rc.Height(), iCurrentDPI, iOldDPI);
	m_cbIcon.SetItemHeight(-1, dpiScaledHeight);
	m_cbIcon.SetItemHeight(0, dpiScaledHeight);
	m_cbIcon.Invalidate();*/
	DynimicLayoutCalculate();
	GetWindowRect(&rcWin);
	InvalidateRect(&rcWin);
	return 0;
}

void CAPPsStarterDlg::DynimicLayoutCalculate()
{
	int iOffset;

	iOffset = MulDiv(10, iCurrentDPI, 96);


	CRect rcCheckOnTop;
	CRect rcStaticInfo;
	CRect rcStaticMainTitle;
	CRect rcTree;
	CRect rcStaticName;
	CRect rcStaticTitle;
	CRect rcStaticPath;
	CRect rcStaticIcon;
	CRect rcEditName;
	CRect rcEditTitle;
	CRect rcEditPath;
	//CRect rcComboIcon;
	CRect rcCombo2;
	CRect rcButtonImport;
	CRect rcButtonMenu;
	CRect rcButtonOK;
	CRect rcButtonCancel;
	CRect rcWindow;

	GetClientRect(rcWindow);
	m_ckOnTop.GetClientRect(rcCheckOnTop);
	m_stInfo.GetClientRect(rcStaticInfo);
	m_stMainTitle.GetClientRect(rcStaticMainTitle);
	m_tree.GetClientRect(rcTree);
	m_stName.GetClientRect(rcStaticName);
	m_stTitle.GetClientRect(rcStaticTitle);
	m_stPath.GetClientRect(rcStaticPath);
	m_stIcon.GetClientRect(rcStaticIcon);
	m_edName.GetWindowRect(rcEditName);
	m_edTitle.GetWindowRect(rcEditTitle);
	m_edPath.GetWindowRect(rcEditPath);
	//m_cbIcon.GetWindowRect(rcComboIcon);
	m_cb2.GetWindowRect(rcCombo2);
	m_btImport.GetClientRect(rcButtonImport);
	m_btMenu.GetClientRect(rcButtonMenu);
	m_btOK.GetClientRect(rcButtonOK);
	m_btCancel.GetClientRect(rcButtonCancel);


	int h, w;

	h = rcCheckOnTop.Height();
	w = rcCheckOnTop.Width();
	rcCheckOnTop.left = rcWindow.right - w - iOffset;
	rcCheckOnTop.right = rcWindow.right - iOffset;
	rcCheckOnTop.top = rcWindow.top + iOffset;
	rcCheckOnTop.bottom = rcWindow.top + h + iOffset;
	m_ckOnTop.MoveWindow(rcCheckOnTop.left, rcCheckOnTop.top, rcCheckOnTop.Width(), rcCheckOnTop.Height());


	h = rcStaticInfo.Height();
	w = rcStaticInfo.Width();
	rcStaticInfo.left = iOffset;
	rcStaticInfo.right = rcCheckOnTop.left - iOffset;
	rcStaticInfo.top = rcCheckOnTop.top;
	rcStaticInfo.bottom = rcCheckOnTop.bottom;
	m_stInfo.MoveWindow(rcStaticInfo.left, rcStaticInfo.top, rcStaticInfo.Width(), rcStaticInfo.Height());

	h = rcStaticMainTitle.Height();
	w = rcStaticMainTitle.Width();
	rcStaticMainTitle.left = iOffset;
	rcStaticMainTitle.right = rcWindow.right - iOffset;
	rcStaticMainTitle.top = rcCheckOnTop.bottom;
	rcStaticMainTitle.bottom = rcCheckOnTop.bottom + h;
	m_stMainTitle.MoveWindow(rcStaticMainTitle.left, rcStaticMainTitle.top, rcStaticMainTitle.Width(), rcStaticMainTitle.Height());

	h = rcTree.Height();
	w = rcTree.Width();
	rcTree.left = iOffset;
	rcTree.right = rcTree.left + (long)(rcWindow.Width() / 2.3);// .left + w;
	rcTree.top = rcStaticMainTitle.bottom;
	rcTree.bottom = rcWindow.bottom - iOffset;
	m_tree.MoveWindow(rcTree.left, rcTree.top, rcTree.Width(), rcTree.Height());

	h = rcStaticName.Height();
	w = rcStaticName.Width();
	rcStaticName.left = rcTree.right + iOffset;
	rcStaticName.right = rcStaticName.left + w;
	rcStaticName.top = rcTree.top;
	rcStaticName.bottom = rcStaticName.top + h;
	m_stName.MoveWindow(rcStaticName.left, rcStaticName.top, rcStaticName.Width(), rcStaticName.Height());

	h = rcEditName.Height();
	w = rcEditName.Width();
	rcEditName.left = rcStaticName.right;
	rcEditName.right = rcWindow.right - iOffset;
	rcEditName.top = rcStaticName.top;
	rcEditName.bottom = rcEditName.top + h;
	m_edName.MoveWindow(rcEditName.left, rcEditName.top, rcEditName.Width(), rcEditName.Height());

	h = rcStaticTitle.Height();
	w = rcStaticTitle.Width();
	rcStaticTitle.left = rcTree.right + iOffset;
	rcStaticTitle.right = rcStaticTitle.left + w;
	rcStaticTitle.top = rcEditName.bottom + iOffset;
	rcStaticTitle.bottom = rcStaticTitle.top + h;
	m_stTitle.MoveWindow(rcStaticTitle.left, rcStaticTitle.top, rcStaticTitle.Width(), rcStaticTitle.Height());

	h = rcEditTitle.Height();
	w = rcEditTitle.Width();
	rcEditTitle.left = rcStaticTitle.right;
	rcEditTitle.right = rcWindow.right - iOffset;
	rcEditTitle.top = rcStaticTitle.top;
	rcEditTitle.bottom = rcEditTitle.top + h;
	m_edTitle.MoveWindow(rcEditTitle.left, rcEditTitle.top, rcEditTitle.Width(), rcEditTitle.Height());

	h = rcStaticPath.Height();
	w = rcStaticPath.Width();
	rcStaticPath.left = rcTree.right + iOffset;
	rcStaticPath.right = rcStaticPath.left + w;
	rcStaticPath.top = rcEditTitle.bottom + iOffset;
	rcStaticPath.bottom = rcStaticPath.top + h;
	m_stPath.MoveWindow(rcStaticPath.left, rcStaticPath.top, rcStaticPath.Width(), rcStaticPath.Height());

	h = rcButtonImport.Height();
	w = rcButtonImport.Width();
	rcButtonImport.right = rcWindow.right - iOffset;
	rcButtonImport.left = rcButtonImport.right - w;
	rcButtonImport.top = rcStaticPath.top;
	rcButtonImport.bottom = rcButtonImport.top + h;
	m_btImport.MoveWindow(rcButtonImport.left, rcButtonImport.top, rcButtonImport.Width(), rcButtonImport.Height());

	h = rcEditPath.Height();
	w = rcEditPath.Width();
	rcEditPath.left = rcStaticPath.right;
	rcEditPath.right = rcButtonImport.left - (iOffset / 2);
	rcEditPath.top = rcStaticPath.top;
	rcEditPath.bottom = rcEditPath.top + h;
	m_edPath.MoveWindow(rcEditPath.left, rcEditPath.top, rcEditPath.Width(), rcEditPath.Height());

	h = rcStaticIcon.Height();
	w = rcStaticIcon.Width();
	rcStaticIcon.left = rcTree.right + iOffset;
	rcStaticIcon.right = rcStaticIcon.left + w;
	rcStaticIcon.top = rcButtonImport.bottom + iOffset;
	rcStaticIcon.bottom = rcStaticIcon.top + h;
	m_stIcon.MoveWindow(rcStaticIcon.left, rcStaticIcon.top, rcStaticIcon.Width(), rcStaticPath.Height());

	/*h = rcComboIcon.Height();
	w = rcComboIcon.Width();
	rcComboIcon.left = rcEditPath.left;
	rcComboIcon.right = rcComboIcon.left + w;
	rcComboIcon.top = rcStaticIcon.top;
	rcComboIcon.bottom = rcComboIcon.top + h;*/
	//m_cbIcon.MoveWindow(rcComboIcon.left, rcComboIcon.top, rcComboIcon.Width(), rcComboIcon.Height());

	h = rcCombo2.Height();
	w = rcCombo2.Width();
	rcCombo2.left = rcEditPath.left;
	rcCombo2.right = rcCombo2.left + w;
	rcCombo2.top = rcStaticIcon.top;
	rcCombo2.bottom = rcCombo2.top + h;
	m_cb2.MoveWindow(rcCombo2.left, rcCombo2.top, rcCombo2.Width(), rcCombo2.Height());

	h = rcButtonMenu.Height();
	w = rcButtonMenu.Width();
	rcButtonMenu.right = rcCombo2.right;
	rcButtonMenu.left = rcCombo2.left;
	rcButtonMenu.top = rcCombo2.bottom + iOffset + iOffset;
	rcButtonMenu.bottom = rcButtonMenu.top + h;
	m_btMenu.MoveWindow(rcButtonMenu.left, rcButtonMenu.top, rcButtonMenu.Width(), rcButtonMenu.Height());

	

	h = rcButtonCancel.Height();
	w = rcButtonCancel.Width();
	rcButtonCancel.right = rcWindow.right - iOffset;
	rcButtonCancel.left = rcButtonCancel.right - w;
	rcButtonCancel.top = rcWindow.bottom - iOffset - h;
	rcButtonCancel.bottom = rcWindow.bottom - iOffset;
	m_btCancel.MoveWindow(rcButtonCancel.left, rcButtonCancel.top, rcButtonCancel.Width(), rcButtonCancel.Height());

	h = rcButtonOK.Height();
	w = rcButtonOK.Width();
	rcButtonOK.right = rcWindow.right - iOffset;
	rcButtonOK.left = rcButtonOK.right - w;
	rcButtonOK.top = rcButtonCancel.top - iOffset - h;
	rcButtonOK.bottom = rcButtonOK.top + h;
	m_btOK.MoveWindow(rcButtonOK.left, rcButtonOK.top, rcButtonOK.Width(), rcButtonOK.Height());

	//CFont* pFont = GetFont();
	//if (NULL != pFont)
	//{
		LOGFONT lf;
		//pFont->GetLogFont(&lf);
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfHeight = -MulDiv(24, iCurrentDPI, 72);
		lf.lfWeight = FW_MEDIUM;
		_tcscpy(lf.lfFaceName, _T("Arial Narrow"));
		m_font1.CreateFontIndirect(&lf);
	//}

	//CFont* pFont2 = GetFont();
	//if (NULL != pFont2)
	//{
		LOGFONT lf2;
		memset(&lf2, 0, sizeof(LOGFONT));
		//pFont2->GetLogFont(&lf);
		lf2.lfWeight = FW_EXTRALIGHT;
		_tcscpy(lf2.lfFaceName, _T("MS Shell Dlg 2"));
		//CString strFontName;
		//m_stInfo.GetWindowText(strFontName);

		//m_stInfo.SetWindowTextW(strFontName + lf.lfFaceName);
		lf2.lfHeight = -MulDiv(12, iCurrentDPI, 72);
		m_font2.CreateFontIndirect(&lf2);
	//}

	//CFont* pFont3 = GetFont();
	//if (NULL != pFont3)
	//{
		LOGFONT lf3;
		memset(&lf3, 0, sizeof(LOGFONT));
	//	pFont3->GetLogFont(&lf3);
		lf3.lfWeight = FW_EXTRALIGHT;
		_tcscpy(lf3.lfFaceName, _T("MS Shell Dlg 2"));
		/*CString strFontName;
		m_stInfo.GetWindowText(strFontName);

		m_stInfo.SetWindowTextW(strFontName + lf3.lfFaceName);*/
		lf3.lfHeight = -MulDiv(10, iCurrentDPI, 72);
		m_font3.CreateFontIndirect(&lf3);
	//}

	m_stMainTitle.SetFont(&m_font1);

	m_tree.SetFont(&m_font3);
	m_ckOnTop.SetFont(&m_font3);
	m_stName.SetFont(&m_font3);
	m_stTitle.SetFont(&m_font3);
	m_stPath.SetFont(&m_font3);
	m_stIcon.SetFont(&m_font3);
	m_stInfo.SetFont(&m_font3);
	m_cb2.SetFont(&m_font3);
	m_edName.SetFont(&m_font3);
	m_edTitle.SetFont(&m_font3);
	m_edPath.SetFont(&m_font3);
	m_btImport.SetFont(&m_font3);

	m_btOK.SetFont(&m_font2);
	m_btCancel.SetFont(&m_font2);
	m_btMenu.SetFont(&m_font2);

	Invalidate();
}

void CAPPsStarterDlg::OnCbnSelchangeCombo2()
{
	// TODO: добавьте свой код обработчика уведомлений
	int i = m_cb2.GetCurSel();
	HTREEITEM hti = m_tree.GetSelectedItem();

	node = (node_data*)m_tree.GetItemData(hti);
	switch (i) {
	case 0:
		node->icon = _T("folder");
		break;
	case 1:
		node->icon = _T("1c");
		break;
	case 2:
		node->icon = _T("medoc");
		break;
	case 3:
		node->icon = _T("rdp");
		break;
	case 4:
		node->icon = _T("app");
		break;
	case 5:
		node->icon = _T("mail");
		break;
	case 6:
		node->icon = _T("web");
		break;
	case 7:
		node->icon = _T("share");
		break;
	case 8:
		node->icon = _T("vcam");
		break;
	case 9:
		node->icon = _T("cmd");
		break;
	case 10:
		node->icon = _T("script");
		break;
	case 11:
		node->icon = _T("pshell");
		break;
	case 12:
		node->icon = _T("appsicon");
		break;
	default:
		break;
	}
	m_tree.SetFocus();
	m_tree.SetItemData(hti, (DWORD_PTR)node);
	m_tree.SetItemImage(hti, i, i);
}

void CAPPsStarterDlg::SetImageList()
{
	//m_imageList.Create(16, 16, ILC_COLOR, 2, 2);
	int iDpi = MulDiv(16, iCurrentDPI, 96);

	int iSel = m_cb2.GetCurSel();
	//m_cb2.SetCurSel(-1);
	//int iCount = m_cb2.GetCount();
	m_cb2.ResetContent();
	
	//CImageList baseImageList;
	

	baseImageList.Create(iDpi, iDpi, ILC_COLOR32 | ILC_MASK, 0, 0);

	m_tree.m_imageList.Create(iDpi, iDpi, ILC_MASK | ILC_COLOR32, 0, 0);
	m_imageList.Create(iDpi, iDpi, ILC_COLOR32 | ILC_MASK, 0, 0);

	for (int i = 0; i < iconBase.size(); i++)
	{
		m_tree.m_imageList.Add(iconBase[i]);
		m_imageList.Add(iconBase[i]);
	}

	for (int i = 0; i < m_tree.iconEXE.size(); i++)
	{
		m_tree.m_imageList.Add(m_tree.iconEXE[i]);
	}
	/*baseImageList.Add(AfxGetApp()->LoadIcon(IDI_FOLDER));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_1C));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_MEDOC));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_RDP));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_APP));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_MAIL));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_WEB));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_SHARE));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_VCAM));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_CMD));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_SCRIPT));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_PSHELL));
	baseImageList.Add(AfxGetApp()->LoadIcon(IDI_APP));*/

	/*HICON icon[13];
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
	icon[12] = AfxGetApp()->LoadIcon(IDI_APP);*/
	
	/*if (m_tree.m_imageList.GetImageCount() == 0) {
		m_tree.m_imageList.Create(iDpi, iDpi, ILC_MASK | ILC_COLOR32, 0, 0);
		for (int i = 0; i < baseImageList.GetImageCount(); i++)
		{
			m_tree.m_imageList.Add(baseImageList.ExtractIcon(i));
		}
	}*/
	/*else {
		std::vector<HICON> iconV;
		for (int i = 0; i < m_tree.m_imageList.GetImageCount(); i++)
		{
			iconV.push_back(m_tree.m_imageList.ExtractIcon(i));
		}
		m_tree.m_imageList.DeleteImageList();
		m_tree.m_imageList.Create(iDpi, iDpi, ILC_MASK | ILC_COLOR32, 0, 0);
		for (int i = 0; i < iconV.size(); i++)
		{
			m_tree.m_imageList.Add(iconV[i]);
		}
	}*/
	m_tree.SetImageList(&m_tree.m_imageList, TVSIL_NORMAL);
	m_tree.m_imageList.SetBkColor(0xffffff);



	//m_imageList.Create(iDpi, iDpi, ILC_COLOR32 | ILC_MASK, 0, 0);
	for (int i = 0; i < 13; i++)
	{
		
		m_imageList.Add(baseImageList.ExtractIcon(i));

		COMBOBOXEXITEM     cbi = { 0 };
		int                nItem;
		CString str;
		cbi.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

		switch (i)
		{
		case 0:
			str = _T("folder");
			break;
		case 1:
			str = _T("1c");
			break;
		case 2:
			str = _T("medoc");
			break;
		case 3:
			str = _T("rdp");
			break;
		case 4:
			str = _T("app");
			break;
		case 5:
			str = _T("mail");
			break;
		case 6:
			str = _T("web");
			break;
		case 7:
			str = _T("share");
			break;
		case 8:
			str = _T("vcam");
			break;
		case 9:
			str = _T("cmd");
			break;
		case 10:
			str = _T("script");
			break;
		case 11:
			str = _T("pshell");
			break;
		case 12:
			str = _T("appsicon");
			break;
		default:
			str = _T("");
			break;
		}

		cbi.iItem = -1;
		cbi.pszText = str.GetBuffer(str.GetLength());
		cbi.iImage = i;
		cbi.iSelectedImage = i;

		nItem = m_cb2.InsertItem(&cbi);
		ASSERT(nItem == 0);
	}

	
	m_cb2.SetImageList(&m_imageList);
	m_cb2.SetCurSel(iSel);
	//CString strCount;
	//strCount.Format(_T("%d  -  %d"), m_cb2.GetCount(), m_imageList.GetImageCount());
	//MessageBox(strCount);
	//m_cb2.RedrawWindow();

	//delete icon[13];
}