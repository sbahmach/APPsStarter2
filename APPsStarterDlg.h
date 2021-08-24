
// APPsStarterDlg.h : header file
//

#pragma once
//#include "afxcmn.h"
// Use our new class CTreeCtrlXML
#include <vector>
#include "TreeCtrlXML.h"
#include "ColorButton.h"
//#include "ToolTipCtrlExt.h"
#include "IconComboBox.h"
#include "CMenuModifier.h"


#define 	COLOR_MYDLG	RGB(193, 239, 255)



// CAPPsStarterDlg dialog
class CAPPsStarterDlg : public CDialog
{
// Construction
public:
	CAPPsStarterDlg(CWnd* pParent = nullptr);	// standard constructor
	HICON hIcon = NULL;
	CString strCmdXmlFile;
	CString strCurrentXML;
	CString strDefXMLFile = _T("defconf.xml");
	//CString GetVersionInfo(char* pstrFilePath, char* pstrType = TEXT("\\StringFileInfo\\041204b0\\FileVersion"));
	bool m_bNoSaveSettings = 0;
	HTREEITEM hSelItem = NULL;
	CFont m_font_Title;
	CFont m_font_StaticCtrls;
	CFont m_font_Tooltips;
	CBrush Brush_Main;
	//CRect rc_window;
	enum { IDD = IDD_APPsStarter_DIALOG};
	std::vector<HICON> iconBase;
	CImageList baseImageList;
	//CString CreateID();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPsStarter_DIALOG };
#endif
	LRESULT  OnDropFiles(WPARAM wParam, LPARAM lParam);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	struct node_data
	{
		CString name = _T("new item");
		CString path = _T("some path");
		CString type = _T("application");
		CString title = _T("");
		CString icon = _T("");
		CString expand = _T("false");
	};
	/*typedef struct THREADSTRUCT
	{
		CAPPsStarterDlg* _this;
	} THREADSTRUCT;*/

	//static UINT startThreadImport(LPVOID param); //запуск отрисовки перемещени€ в отдельном потоке (по€вление)
	//static UINT startThreadOut(LPVOID param); //запуск отрисовки перемещени€ в отдельном потоке (исчезновение)
	//void startImport(); // запуск отдельного потока
	//void startOut(); // запуск отдельного потока

	node_data* node = 0;

	HTREEITEM FindItem(CString name, HTREEITEM hti);
	void ShowControls(bool bShow);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnOpen();
	afx_msg void OnLoad();
	afx_msg void OnReload();
	afx_msg void OnStart();
	afx_msg void OnRunAs();
	afx_msg void OnInsertItem();
	afx_msg void OnDublicate();
	afx_msg void OnItemEdit();
	afx_msg void OnInsertFolder();
	afx_msg void OnImportApp();
	afx_msg void OnOpenWith();
	afx_msg void OnEdit();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnOpenDirectory();
	afx_msg void OnDeleteItem();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	void OnSortAZ();
	void OnSortZA();
	void SortTree(HTREEITEM htiParent, bool sortType = true);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

	DECLARE_MESSAGE_MAP()
	CString GetShellPropStringFromPath(LPCWSTR pPath, PROPERTYKEY const& key);
	//BOOL GetCurrentFileVersion(LPTSTR tszFileVer);
	//CToolTipCtrlExt m_ctrl_tooltip_ext;
	CImageList m_imageList;
	HICON m_hIcon;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//CTreeCtrlXML m_tree;
	//CStatic m_Title, m_statName, m_statTitle, m_statPath, m_statIcon, m_stat;
	//CColorButton	m_btStart, m_btCancel, m_btMenu, m_btPath;
	//CButton m_check;
	//CEdit m_editName, m_editTitle, m_editPath;
//	CMFCButton m_btPath;
	//CSmallIconComboBox m_cbIcon;
	CMenu md_Popup;
	CMenu md_Main;
	CToolBar    m_wndToolBar;

	void ReadReg();
	void WriteReg();

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//afx_msg void OnPaint();
	
	CFont m_font1, m_font2, m_font3;
	int iCurrentDPI = 96;
	int iOldDPI = 96;
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

	//CStatic m_stOnTop;
	CStatic m_stInfo;
	CStatic m_stMainTitle;
	CStatic m_stName;
	CStatic m_stTitle;
	CStatic m_stPath;
	CStatic m_stIcon;
	CColorButton m_ckOnTop;
	CColorButton m_btOK;
	CColorButton m_btCancel;
	CColorButton m_btImport;
	CColorButton m_btMenu;
	CEdit m_edName;
	CEdit m_edTitle;
	CEdit m_edPath;
	//CSmallIconComboBox m_cbIcon;
	CComboBoxEx m_cb2;
	CTreeCtrlXML m_tree;
	CRect rcWindowDef;
	void DynimicLayoutCalculate();
	void SetImageList();
	


public:
	
	//void TTokenizer(const CString& strFields, LPCWSTR strDelimiters, std::vector<CString>& arFields);
	void OnTvnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint ptMousePos);
	afx_msg void OnNMDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnKillfocusEditName();
	afx_msg void OnEnKillfocusEditTitle();
	afx_msg void OnEnKillfocusEditPath();
	//afx_msg void OnCbnSelchangeComboIcon();
	afx_msg void OnTvnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnSetfocusEditName();
	//void LoadCSVFile();
	afx_msg void OnBnClickedButtonPath();
    afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT nSide, LPRECT pRect);
	LRESULT OnDpiChanged(WPARAM wParam, LPARAM lParam);
	//LRESULT OnDpiChanged(WPARAM wParam, LPARAM lParam);
	
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton1();
};

