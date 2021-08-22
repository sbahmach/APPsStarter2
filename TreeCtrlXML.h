
#pragma once

#include "afxcmn.h"
#include <vector>
#include "tinyxml2.h"
//#include "ToolTipCtrlExt.h"
using namespace tinyxml2;


class CTreeCtrlXML : public CTreeCtrl
{
private:
	UINT			m_nHoverTimerID;
	POINT			m_HoverPoint;
public:
	
	CTreeCtrlXML(void);

	virtual ~CTreeCtrlXML(void);
	void			SetItemFont(HTREEITEM, LOGFONT&);
	void			SetItemBold(HTREEITEM, BOOL);
	void			SetItemColor(HTREEITEM, COLORREF);
	BOOL			GetItemFont(HTREEITEM, LOGFONT*);
	BOOL			GetItemBold(HTREEITEM);
	COLORREF		GetItemColor(HTREEITEM);
public:
	CImageList m_imageList;
	std::vector<HICON> iconEXE;
	//HICON iconEXE;
	bool LoadFromXML( const CString& a_strFile );
	bool LoadDef();

	bool SaveToXML( const CString& a_strFile );

	struct node_data
	{
		CString name = _T("new item");
		CString path = _T("path");
		CString type = _T("application");
		CString title = _T("");
		//CString id = "";
		//CString parent = "";
		CString icon = _T("app");
		CString expand = _T("false");
		
	};

	node_data* node = 0;
	//CString strParent = "";

public:
	HTREEITEM htiDrop = NULL;
	
	//CString CreateID();
	
	//bool timer = false;

	HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent,	HTREEITEM htiAfter = TVI_LAST);

	virtual void OnItemCopied(HTREEITEM hItem, HTREEITEM hNewItem);

	HTREEITEM CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST);

protected:
	struct Color_Font {
		COLORREF color;
		LOGFONT  logfont;
	};
	void Load(tinyxml2::XMLNode* a_pNode);

	CImageList* m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM	m_hitemDrag, m_hitemDrop;

	CMap <void*, void*, Color_Font, Color_Font&> m_mapColorFont;
	
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void LoadItem(tinyxml2::XMLNode* a_pNode, HTREEITEM a_hTreeParent );

	int GetIndentLevel( HTREEITEM hItem );

	HTREEITEM GetNextItem( HTREEITEM hItem );

	

	DECLARE_MESSAGE_MAP()
public:


	//afx_msg void OnTvnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//afx_msg void OnTvnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnBegindragTreeDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR uTime);
};
