#include "pch.h"
//#include "stdafx.h"
#include "ColorButton.h"

/////////////////////////////////////////////////////////////////////////////
// CMyClass

CColorButton::CColorButton()
{
	m_col_BtnText_Disabled = RGB(62, 62, 65);
	m_col_BtnText = RGB(104, 104, 104);
	m_col_BtnText_IsHover = RGB(158, 158, 158);
	m_col_BtnText_Selected = RGB(239, 235, 239);
	m_col_BtnFace_Disabled = RGB(30, 30, 30);
	m_col_BtnFace = RGB(30, 30, 30);
	m_col_BtnFace_IsHover = RGB(45, 45, 45);
	m_col_BtnFace_Selected = RGB(62, 62, 66);
	m_col_BtnFrame_Disabled = RGB(0, 0, 0);
	m_col_BtnFrame = RGB(104, 104, 104);
	m_col_BtnFrame_IsHover = RGB(158, 158, 158);
	m_col_BtnFrame_Selected = RGB(239, 235, 239);
}

CColorButton::~CColorButton()
{

}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyClass message handlers

void CColorButton::OnHoverEnter()
{
	//Redraw();
	Invalidate();
}

void CColorButton::OnHoverLeave()
{
	//Redraw();
	Invalidate();

}

void CColorButton::OnMouseMove(UINT nFlags, CPoint point)
{

	//start tracking of Hover and Leave Event
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = 10;
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}

void CColorButton::OnMouseLeave()
{
	if (m_bHover == true) {
		m_bHover = false;
		Invalidate();
	}
	
	CButton::OnMouseLeave();
}

void CColorButton::OnMouseHover(UINT nFlags, CPoint point)
{

	if (m_bHover == false) {
		m_bHover = true;
		Invalidate();
	}
	
	CButton::OnMouseHover(nFlags, point);
}

void CColorButton::Redraw()
{
	RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE);
	//Invalidate();
	//UpdateWindow();
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT uStyle = DFCS_BUTTONPUSH;

	CDC dc;
	RECT rect;
	dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC
	dc.SetBkMode(TRANSPARENT);
	rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.

	UINT state = lpDrawItemStruct->itemState;  //This defines the state of the Push button either pressed or not. 

	if ((state & ODS_DISABLED))
	{
		dc.SetTextColor(m_col_BtnText_Disabled);     //Setting the Text Color
		dc.FillSolidRect(&rect, m_col_BtnFace_Disabled);//Here you can define the required color to appear on the Button.
		dc.Draw3dRect(&rect, m_col_BtnFrame_Disabled, m_col_BtnFrame_Disabled);
		dc.SetBkColor(m_col_BtnFace_Disabled);   //Setting the Text Background color
	}
	else if ((state & ODS_SELECTED))
	{
		dc.SetTextColor(m_col_BtnText_Selected);     //Setting the Text Color
		dc.FillSolidRect(&rect, m_col_BtnFace_Selected);//Here you can define the required color to appear on the Button.
		dc.Draw3dRect(&rect, m_col_BtnFrame_Selected, m_col_BtnFrame_Selected);
		dc.SetBkColor(m_col_BtnFace_Selected);   //Setting the Text Background color
	}
	else if (m_bHover)
	{
		dc.SetTextColor(m_col_BtnText_IsHover);     //Setting the Text Color
		dc.FillSolidRect(&rect, m_col_BtnFace_IsHover);//Here you can define the required color to appear on the Button.
		dc.Draw3dRect(&rect, m_col_BtnFrame_IsHover, m_col_BtnFrame_IsHover);
		dc.SetBkColor(m_col_BtnFace_IsHover);   //Setting the Text Background color
	}
	else {
		dc.SetTextColor(m_col_BtnText);     //Setting the Text Color
		dc.FillSolidRect(&rect, m_col_BtnFace);//Here you can define the required color to appear on the Button.
		dc.Draw3dRect(&rect, m_col_BtnFrame, m_col_BtnFrame);
		dc.SetBkColor(m_col_BtnFace);   //Setting the Text Background color
	}

	if ((state & ODS_FOCUS)) {
		rect.top ++;rect.left ++;rect.right --;rect.bottom --;
		dc.Draw3dRect(&rect, m_col_BtnFrame_IsHover, m_col_BtnFrame_IsHover);
	}


	TCHAR buffer[MAX_PATH];           //To store the Caption of the button.
	ZeroMemory(buffer, MAX_PATH);     //Intializing the buffer to zero
	::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH); //Get the Caption of Button Window 

	dc.DrawText(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); //Redraw the  Caption of Button Window 

	dc.Detach();  // Detach the Button DC
}

void CColorButton::SetColor(
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
	)
{
	m_col_BtnText_Disabled = col_BtnText_Disabled;
	m_col_BtnText = col_BtnText;
	m_col_BtnText_IsHover = col_BtnText_IsHover;
	m_col_BtnText_Selected = col_BtnText_Selected;
	m_col_BtnFace_Disabled = col_BtnFace_Disabled;
	m_col_BtnFace = col_BtnFace;
	m_col_BtnFace_IsHover = col_BtnFace_IsHover;
	m_col_BtnFace_Selected = col_BtnFace_Selected;
	m_col_BtnFrame_Disabled = col_BtnFrame_Disabled;
	m_col_BtnFrame = col_BtnFrame;
	m_col_BtnFrame_IsHover = col_BtnFrame_IsHover;
	m_col_BtnFrame_Selected = col_BtnFrame_Selected;
}