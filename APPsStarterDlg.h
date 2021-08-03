
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

	CString strCmdXmlFile;
	CString strCurrentXML;
	const CString strDefXMLFile = "defconf.xml";

	bool m_bNoSaveSettings = 0;

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
		CString name = "new item";
		CString path = "some path";
		CString type = "application";
		CString title = "";
		//CString id = "";
		//CString parent = "";
		CString icon = "";
		CString expand = "false";

	};

	node_data* node = 0;
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
	afx_msg void OnOpenWith();
	afx_msg void OnEdit();
	afx_msg void OnSave();
	afx_msg void OnOpenDirectory();
	afx_msg void OnDeleteItem();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	void OnSortAZ();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

	DECLARE_MESSAGE_MAP()
	
	//CToolTipCtrlExt m_ctrl_tooltip_ext;
	CImageList m_imageList;
	HICON m_hIcon;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CTreeCtrlXML m_tree;
	CStatic m_Title;
	CStatic m_statName;
	CStatic m_statTitle;
	CStatic m_statPath;
	CStatic m_statIcon;
	CStatic m_statParent;
	CStatic m_statID;
	CColorButton	m_btStart;
	CColorButton	m_btLoad;
	CColorButton	m_btReload;
	CColorButton	m_btEdit;
	CColorButton	m_btSave;
	CColorButton	m_btCancel;
	CStatic m_stat;
	CButton m_check;
	CEdit m_editName;
	CEdit m_editTitle;
	CEdit m_editPath;
	CMFCButton m_btPath;
	//CEdit m_editID;
	//CEdit m_editParent;
	CSmallIconComboBox m_cbIcon;

	void ReadReg();
	void WhriteReg();

	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//afx_msg void OnPaint();
	CMenuModifier md_Popup;
	CToolBar    m_wndToolBar;
	//void P_ShowPopupMenu(UINT uMenuID, CPoint pt);
public:
	//int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//static int CALLBACK TreeCmpFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	//BOOL   SortChildrenCB(LPTVSORTCB   pSort);
	
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
	//afx_msg void OnTvnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeComboIcon();
	afx_msg void OnTvnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnSetfocusEditName();
	//void LoadCSVFile();
	afx_msg void OnBnClickedMfcbuttonPath();
};

