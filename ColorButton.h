#pragma once
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "TrackControl.h" 



/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
	// Construction
public:
	CColorButton();
	virtual ~CColorButton();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	void SetColor(
		COLORREF col_BtnText_Disabled,
		COLORREF col_BtnText,
		COLORREF col_BtnText_IsHover,
		COLORREF col_BtnText_Selected,
		COLORREF col_BtnFace_Disabled,
		COLORREF col_BtnFace,
		COLORREF col_BtnFace_IsHover,
		COLORREF col_BtnFace_Selected,
		COLORREF col_BtnFrame_Disabled,
		COLORREF col_BtnFrame,
		COLORREF col_BtnFrame_IsHover,
		COLORREF col_BtnFrame_Selected
		);

	bool m_bHover = false;
	BOOLEAN IsHover()
	{
		return m_bHover;
	}
	void Redraw();
	void OnHoverLeave();
	void OnHoverEnter();

private:
	COLORREF m_col_BtnText_Disabled;
	COLORREF m_col_BtnText;
	COLORREF m_col_BtnText_IsHover;
	COLORREF m_col_BtnText_Selected;
	COLORREF m_col_BtnFace_Disabled;
	COLORREF m_col_BtnFace;
	COLORREF m_col_BtnFace_IsHover;
	COLORREF m_col_BtnFace_Selected;
	COLORREF m_col_BtnFrame_Disabled;
	COLORREF m_col_BtnFrame;
	COLORREF m_col_BtnFrame_IsHover;
	COLORREF m_col_BtnFrame_Selected;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();


};

