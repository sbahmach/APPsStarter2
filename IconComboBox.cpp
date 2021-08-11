/*
Module : ICONCOMBOBOX.CPP
Purpose: Defines the implementation for 2 MFC classes
         to implement an icon selection combo box
Created: PJN / 23-08-1998
History: PJN / 12-09-1998 1) Removed some files from the workspace which were not being used.
                          2) Updated workspace to use folders.
                          3) Added AddString, InsertString & DeleteString functions. These 
                          functions ASSERT to ensure that the icon combo box operates correctly
                          4) Added DeleteIcon function. This should be called instead of DeleteString
                          5) Modfied internal implementation of InsertIcon & AddIcon for both classes

Copyright (c) 1998 by PJ Naughter.  
All rights reserved.

*/


/////////////////////////////////  Includes  //////////////////////////////////
#include "pch.h"
#include "IconComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





////////////////////////////// Implementation /////////////////////////////////

//void DDX_CBIcon(CDataExchange* pDX, int nIDC, CString str)
//{
//	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
//	CSmallIconComboBox* pCombo = (CSmallIconComboBox*) CWnd::FromHandle(hWndCtrl);
//	ASSERT(pCombo);
//	ASSERT(pCombo->IsKindOf(RUNTIME_CLASS(CSmallIconComboBox)));
//
//	if (pDX->m_bSaveAndValidate)
//    nIconID = pCombo->GetCurSelIcon();
//	else
//	  pCombo->SetCurSelIcon(CString str);
//}






//IMPLEMENT_DYNAMIC(CSmallIconComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CSmallIconComboBox, CComboBox)
	//{{AFX_MSG_MAP(CSmallIconComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSmallIconComboBox::PreSubclassWindow() 
{
  //Let the parent do its thing
	CComboBox::PreSubclassWindow();

  //combo box must manage the strings
  //ASSERT(GetWindowLong(m_hWnd, GWL_STYLE) & CBS_HASSTRINGS);

  //combo box must be owner draw variable
  //ASSERT(GetWindowLong(m_hWnd, GWL_STYLE) & CBS_OWNERDRAWVARIABLE);

  //Set the Height of the combo box to just contain one small icon
  ::SendMessage(m_hWnd, CB_SETITEMHEIGHT, (WPARAM)-1, 18L);
}

int CSmallIconComboBox::AddIcon(UINT_PTR nIconID, CString str)
{
  //Load up the icon
  HICON hIcon = (HICON) LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(nIconID), IMAGE_ICON, 16, 16, 0);
  ASSERT(hIcon != NULL);
  if (hIcon == NULL)
    return -1;

  //Add it to the combo box
  int nOffset = CComboBox::AddString(_T(""));

	//Hive away the info in the item data field
	_IconComboData* pData = new _IconComboData;
	pData->m_hIcon = hIcon;
	pData->m_nIconID = nIconID;
	pData->str = str;
  SetItemData(nOffset, (DWORD_PTR) pData);

  //Return the offset at which it was added
	return nOffset;
}

int CSmallIconComboBox::InsertIcon(int nIndex, UINT_PTR nIconID, CString str)
{
  //Load up the icon
  HICON hIcon = (HICON) LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(nIconID), IMAGE_ICON, 16, 16, 0);
  ASSERT(hIcon != NULL);
  if (hIcon == NULL)
    return 0;

  //Add it to the combo box at the specified offset
  int nOffset = CComboBox::InsertString(nIndex, _T(""));

	//Hive away the info in the item data field
	_IconComboData* pData = new _IconComboData;
	pData->m_hIcon = hIcon;
	pData->m_nIconID = nIconID;
	pData->str = str;
  SetItemData(nOffset, (DWORD_PTR) pData);

  //Return the offset at which it was added
	return nOffset;
}

int CSmallIconComboBox::DeleteIcon(int nIndex)
{
  //just let the parent do its thing
  return CComboBox::DeleteString(nIndex);
}

//UINT CSmallIconComboBox::GetCurSelIcon() const
//{
//  int nSel = GetCurSel();
//	if (nSel == CB_ERR)
//	  return 0;
//
//	_IconComboData* pData = (_IconComboData*) GetItemData(nSel);
//  return pData->m_nIconID;
//}

void CSmallIconComboBox::SetCurSelIcon(CString str)
{
	//iterate through all the CB items and set the one which 
	//has the corresponding item data
	for (int i = 0; i < GetCount(); i++)
	{
		iconData = (_IconComboData*)GetItemDataPtr(i);
		if (iconData->str == str)
			SetCurSel(i);
	}

	
	/*if (str == "1c")
		 SetCurSel(1);
	else if (str == "medoc")
		SetCurSel(2);
	else if (str == "rdp")
		SetCurSel(3);
	else if (str == "app")
		SetCurSel(4);
	else if (str == "mail")
		SetCurSel(5);
	else if (str == "web")
		SetCurSel(6);
	else if (str == "share")
		SetCurSel(7);
	else if (str == "vcam")
		SetCurSel(8);
	else if (str == "cmd")
		SetCurSel(9);
	else if (str == "script")
		SetCurSel(10);
	else if (str == "pshell")
		SetCurSel(11);
	else
		SetCurSel(0);*/
}

void CSmallIconComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  lpMeasureItemStruct->itemHeight = 18;
}

void CSmallIconComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	ASSERT(lpDIS->CtlType == ODT_COMBOBOX);	

  //Create A CDC from the SDK struct passed in
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

  //If the item is selected, draw the selection background
	if ((lpDIS->itemState & ODS_SELECTED) &&                         
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// item has been selected - draw selection rectangle
		COLORREF crHilite = GetSysColor(COLOR_HIGHLIGHT);
		CBrush br(crHilite);
		pDC->FillRect(&lpDIS->rcItem, &br);
	}

  //If the item is not selected, draw a white background
	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		// Item has been de-selected -- remove selection rectangle
		CBrush br(RGB(255, 255, 255));
		pDC->FillRect(&lpDIS->rcItem, &br);
	}

  //Draw the icon
	iconData = (_IconComboData*) lpDIS->itemData;
	ASSERT(iconData != NULL);
	if (iconData && lpDIS->itemData != -1) {
		DrawIconEx(pDC->GetSafeHdc(), lpDIS->rcItem.left + 1, lpDIS->rcItem.top + 1, iconData->m_hIcon, 16, 16, 0, NULL, DI_NORMAL);
		CRect rect = lpDIS->rcItem;
		rect.left = lpDIS->rcItem.left + 25;
		pDC->SetBkMode(TRANSPARENT);
		if (iconData->str == _T("folder")) {
			pDC->SetTextColor(RGB(150, 150, 150));
		}
		else {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		pDC->DrawText(iconData->str, &rect, DT_TABSTOP | DT_VCENTER | DT_SINGLELINE);
	}
}

//void CSmallIconComboBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct) 
//{
//  //Free up any existing HICON's used for drawing
//	_IconComboData* pData = (_IconComboData*) GetItemData(lpDeleteItemStruct->itemID);
//	ASSERT(pData);
//	DestroyIcon(pData->m_hIcon);
//
//	//Free up our internal structure which is stored in the item data
//	delete pData;
//	
//	//Let the parent do its thing
//	CComboBox::DeleteItem(lpDeleteItemStruct);
//}

int CSmallIconComboBox::AddString(LPCTSTR /*lpszString*/)
{
	ASSERT(FALSE); //Use AddIcon not AddString
	return -1;
}

int CSmallIconComboBox::InsertString(int /*nIndex*/, LPCTSTR /*lpszString*/)
{
	ASSERT(FALSE); //Use InsertIcon not InsertString
	return -1;
}

int CSmallIconComboBox::DeleteString(int /*nIndex*/)
{
	ASSERT(FALSE); //Use DeleteIcon not DeleteString
	return -1;
}

