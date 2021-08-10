
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
	CRect rc_window;
	enum { IDD = IDD_APPsStarter_DIALOG};

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

	node_data* node = 0;

	HTREEITEM FindItem(CString name, HTREEITEM hti);

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
	//CImageList m_imageList;
	HICON m_hIcon;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CTreeCtrlXML m_tree;
	CStatic m_Title, m_statName, m_statTitle, m_statPath, m_statIcon, m_stat;
	CColorButton	m_btStart, m_btCancel, m_btMenu, m_btPath;
	CButton m_check;
	CEdit m_editName, m_editTitle, m_editPath;
//	CMFCButton m_btPath;
	CSmallIconComboBox m_cbIcon;
	CMenuModifier md_Popup;
	CMenuModifier md_Main;
	CToolBar    m_wndToolBar;

	void ReadReg();
	void WhriteReg();

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//afx_msg void OnPaint();
	
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
	afx_msg void OnCbnSelchangeComboIcon();
	afx_msg void OnTvnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnSetfocusEditName();
	//void LoadCSVFile();
	afx_msg void OnBnClickedButtonPath();
    afx_msg void OnBnClickedButtonMenu();

};

