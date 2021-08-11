#include "pch.h"
#include "resource.h"
//#include "FileVersion.h"
#include "TreeCtrlXML.h"
 //using namespace tinyxml2;
CTreeCtrlXML::CTreeCtrlXML(void)
{
	ModifyStyle(0, TVS_EDITLABELS);
	ModifyStyle(0, TVS_DISABLEDRAGDROP);
	m_pDragImage = NULL;
	m_hitemDrag = NULL;
	m_hitemDrop = NULL;
	m_bLDragging = FALSE;
	
}

CTreeCtrlXML::~CTreeCtrlXML(void)
{
}
//IMPLEMENT_DYNAMIC(CTreeCtrlXML, CTreeCtrl)
BEGIN_MESSAGE_MAP(CTreeCtrlXML, CTreeCtrl)

	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CTreeCtrlXML::OnTvnBegindragTreeDrag)
	//ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, &CTreeCtrlXML::OnTvnBeginlabeledit)
	//ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, &CTreeCtrlXML::OnTvnEndlabeledit)
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////
void CTreeCtrlXML::SetItemFont(HTREEITEM hItem, LOGFONT& logfont)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		cf.color = (COLORREF)-1;
	cf.logfont = logfont;
	m_mapColorFont[hItem] = cf;
}

//////////////////////////////////////////////////////////////////////
void CTreeCtrlXML::SetItemBold(HTREEITEM hItem, BOOL bBold)
{
	SetItemState(hItem, bBold ? TVIS_BOLD : 0, TVIS_BOLD);
}

//////////////////////////////////////////////////////////////////////
void CTreeCtrlXML::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
}

//////////////////////////////////////////////////////////////////////
BOOL CTreeCtrlXML::GetItemFont(HTREEITEM hItem, LOGFONT* plogfont)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		return FALSE;
	if (cf.logfont.lfFaceName[0] == '\0')
		return FALSE;
	*plogfont = cf.logfont;
	return TRUE;

}

//////////////////////////////////////////////////////////////////////
BOOL CTreeCtrlXML::GetItemBold(HTREEITEM hItem)
{
	return GetItemState(hItem, TVIS_BOLD) & TVIS_BOLD;
}

//////////////////////////////////////////////////////////////////////
COLORREF CTreeCtrlXML::GetItemColor(HTREEITEM hItem)
{
	// Returns (COLORREF)-1 if color was not set
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		return (COLORREF)-1;
	return cf.color;

}

//////////////////////////////////////////////////////////////////////
void CTreeCtrlXML::OnPaint()
{
	CPaintDC dc(this);

	// Create a memory DC compatible with the paint DC
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rcClip, rcClient;
	dc.GetClipBox(&rcClip);
	GetClientRect(&rcClient);

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	memDC.SelectObject(&bitmap);

	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcClip);
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();

	// First let the control do its default drawing.
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);

	HTREEITEM hItem = GetFirstVisibleItem();

	int iItemCount = GetVisibleCount() + 1;
	while (hItem && iItemCount--)
	{
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;

		//if ( !(GetTreeCtrl().GetItemState( hItem, selflag ) & selflag ) 
		//	&& m_mapColorFont.Lookup( hItem, cf ))

		if ((GetItemState(hItem, selflag) & selflag)
			&& ::GetFocus() == m_hWnd)
			;
		else if (m_mapColorFont.Lookup(hItem, cf))
		{
			CFont* pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if (cf.logfont.lfFaceName[0] != '\0')
				logfont = cf.logfont;
			else {
				// No font specified, so use window font
				CFont* pFont = GetFont();
				pFont->GetLogFont(&logfont);
			}

			if (GetItemBold(hItem))
				logfont.lfWeight = 700;

			fontDC.CreateFontIndirect(&logfont);
			pFontDC = memDC.SelectObject(&fontDC);

			if (cf.color != (COLORREF)-1)
				memDC.SetTextColor(cf.color);
			else
				memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));


			CString sItem = GetItemText(hItem);

			GetItemRect(hItem, &rect, TRUE);
			memDC.SetBkColor(GetSysColor(COLOR_WINDOW));
			memDC.TextOut(rect.left +2, rect.top + 1, sItem);

			memDC.SelectObject(pFontDC);
		}
		hItem = GetNextVisibleItem(hItem);
	}


	dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC,
		rcClip.left, rcClip.top, SRCCOPY);

	memDC.DeleteDC();
	
}



BOOL CTreeCtrlXML::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_DROPFILES) {
		GetParent()->SendMessage(WM_DROPFILES, pMsg->wParam, pMsg->lParam);
		return TRUE; // eat it
	}

	return FALSE; // allow default processing
	//return CDialog::PreTranslateMessage(pMsg);
}
bool CTreeCtrlXML::LoadDef()
{

	HTREEITEM hItem;
	hItem = InsertItem(_T("Приложения"), TVI_ROOT);

	//<Item Name = "Приложения" Type = "container" Expand = "true"  Id = "11111111-e1e2-41d5-8fa5-4e4649897f77">

	node_data* nnode = new node_data();
	//node = (node_data*)0;
	//nnode->id = "11111111-e1e2-41d5-8fa5-4e4649897f77";
	//nnode->parent = "00000001-e45f-403a-a1a3-c3f4f5c98056";
	nnode->name = _T("Приложения");
	nnode->type = _T("container");
	nnode->title = _T("ROOT");
	nnode->expand = _T("true");
	nnode->icon = _T("folder");
	
	SetItemData(hItem, (DWORD_PTR)nnode);
	nnode = 0;

	SelectItem(hItem);
	return false;

}
bool CTreeCtrlXML::LoadFromXML(const CString& a_strFile)
{
	DeleteAllItems();
	//EmptyClipboard();
	node = NULL;

	XMLNode* xmlRoot = NULL;
	tinyxml2::XMLDocument xmlDoc;
	//USES_CONVERSION;
	//const char* cstr = (CT2A)a_strFile;
	if (XML_SUCCESS != xmlDoc.LoadFile((CT2A)a_strFile))
		return false;
	
	xmlRoot = xmlDoc.FirstChildElement();
	if (NULL == xmlRoot)
		return false;
	SetRedraw(FALSE);
	// Load our tree control
	Load(xmlRoot);
	xmlRoot = NULL;
	xmlDoc.Clear();// = NULL;
	SetRedraw(TRUE);
	Invalidate();
}



void CTreeCtrlXML::Load(tinyxml2::XMLNode* a_pNode )
{
	ASSERT( NULL != a_pNode );
	// Get node "Items" or root
	XMLNode* xmlRoot = a_pNode;
	XMLNode* xmlNode = NULL;

	if( NULL == xmlRoot)
		return;

	
	// Get first item
	xmlNode = xmlRoot->FirstChild();

	// Iterate all siblings
	while( NULL != xmlNode)
	{
		//strParent = "00000001-e45f-403a-a1a3-c3f4f5c98056";
		LoadItem(xmlNode, NULL );
		xmlNode = xmlNode->NextSibling();
	}
	a_pNode = NULL;
	xmlNode = NULL;
}


void CTreeCtrlXML::LoadItem(tinyxml2::XMLNode* a_pNode, HTREEITEM a_hTreeParent)
{
	ASSERT(NULL != a_pNode);

	XMLElement* pEl = a_pNode->ToElement();
	ASSERT(NULL != pEl);

	HTREEITEM hItem = NULL;
	XMLNode* pChild = NULL;
	bool bWithoutAttr = false;

	CString strAttr = _T("");
	if (pEl->Attribute("Name") == NULL) {
		if (pEl->GetText() != "") {
			bWithoutAttr = true;
			strAttr = pEl->GetText();
		} else {
			strAttr = a_pNode->Value();
		}
	} else {
		strAttr = pEl->Attribute("Name");
	}


	if (NULL == a_hTreeParent) {
		hItem = InsertItem(strAttr, TVI_ROOT);
	}
	else {
		hItem = InsertItem(strAttr, a_hTreeParent);
	}

	node_data* nnode = new node_data();
	//nnode->id = pEl->Attribute("Id");
	//nnode->parent = strParent;
	nnode->name = strAttr;
	nnode->type = pEl->Attribute("Type");
	nnode->title = pEl->Attribute("Title");
	nnode->path = pEl->Attribute("Path");
	nnode->icon = pEl->Attribute("Icon") == NULL ? "" : pEl->Attribute("Icon");
	nnode->expand = pEl->Attribute("Expand");

	//strParent = "";
	



	if (nnode->icon == "1c")
		SetItemImage(hItem, 1, 1);
	else if (nnode->icon == "medoc")
		SetItemImage(hItem, 2, 2);
	else if (nnode->icon == "rdp")
		SetItemImage(hItem, 3, 3);
	else if (nnode->icon == "app")
		SetItemImage(hItem, 4, 4);
	else if (nnode->icon == "mail")
		SetItemImage(hItem, 5, 5);
	else if (nnode->icon == "web")
		SetItemImage(hItem, 6, 6);
	else if (nnode->icon == "share")
		SetItemImage(hItem, 7, 7);
	else if (nnode->icon == "vcam")
		SetItemImage(hItem, 8, 8);
	else if (nnode->icon == "cmd")
		SetItemImage(hItem, 9, 9);
	else if (nnode->icon == "script")
		SetItemImage(hItem, 10, 10);
	else if (nnode->icon == "pshell")
		SetItemImage(hItem, 11, 11);
	else if (nnode->icon == "appsicon") {
		//CFileVersionInfo vers;
		//vers.Open(nnode->path);

		SHFILEINFOW shFileInfoW = {};
		UINT uFlags = SHGFI_ICON | SHGFI_SMALLICON;
		CString str = nnode->path;
		SHGetFileInfoW((CT2CW)str, FILE_ATTRIBUTE_NORMAL, &shFileInfoW, sizeof(SHFILEINFOW), uFlags);
		HICON hIcon = shFileInfoW.hIcon;
		if (hIcon != NULL) {
			m_imageList.Add(hIcon);
			int iItems = m_imageList.GetImageCount() - 1;
			SetItemImage(hItem, iItems, iItems);
		}
		else {
			SetItemImage(hItem, 4, 4);
		}
		//CString strDesc = "";
		//ASSERT(strDesc = vers.GetFileDescription());
		
	}
		
	else
		SetItemImage(hItem, 0, 0);


	SetItemData(hItem, (DWORD_PTR)nnode);
	
	pChild = a_pNode->FirstChild();

	while (pChild && !bWithoutAttr)
	{
		//strParent = nnode->id;

		LoadItem(pChild, hItem);
		pChild = pChild->NextSibling();
	}

	if (nnode->expand == "true")
		Expand(hItem, TVE_EXPAND);

	nnode = NULL;
	hItem = NULL;
	pEl = NULL;
	pChild = NULL;
	a_pNode = NULL;
	//strParent = "";
}

bool CTreeCtrlXML::SaveToXML(const CString& a_strFile)
{
	// Save XML
	tinyxml2::XMLDocument xmlDoc;
	XMLDeclaration* declaration = xmlDoc.NewDeclaration("xml version = \"1.0\" encoding = \"windows-1251\" standalone = \"yes\"");
	xmlDoc.InsertFirstChild(declaration);

	XMLNode* xmlRoot = xmlDoc.NewElement("Items");
	xmlDoc.InsertEndChild(xmlRoot);

	
	ASSERT(NULL != xmlRoot);

	XMLNode* xmlParent = xmlRoot;
	XMLNode* xmlNew = NULL;

	HTREEITEM hItem = GetRootItem();

	int iIndent = 0; int iLastIndent = 0;

	while (hItem)
	{
		iIndent = GetIndentLevel(hItem);

		int iDiff = iIndent - iLastIndent;
		if (iDiff > 0)
		{
			ASSERT(NULL != xmlNew);

			while (iDiff--)
				xmlNew = xmlNew->InsertEndChild(xmlDoc.NewElement("Item"));

			ASSERT(NULL != xmlNew);
			xmlParent = xmlNew->Parent();
		}
		else if (iDiff < 0)
		{
			iDiff--;					// Correct difference to get the right parent
			xmlParent = xmlNew;

			while (iDiff++ < 0)
				xmlParent = xmlParent->Parent();

			//ASSERT(NULL != pParent);
			xmlNew = xmlParent->InsertEndChild(xmlDoc.NewElement("Item"));
		}
		else
		{
			//ASSERT(NULL != pParent);
			xmlNew = xmlParent->InsertEndChild(xmlDoc.NewElement("Item"));
		}

		iLastIndent = iIndent;

		// Save current item
		node = (node_data*)GetItemData(hItem);

		XMLElement* pEl = xmlNew->ToElement();
		ASSERT(NULL != pEl);


		node->expand = "false";
		if (TVIS_EXPANDED & GetItemState(hItem, TVIS_EXPANDED))
			node->expand = "true";

		pEl->SetValue("Item");
		pEl->SetAttribute("Name", (CT2A)node->name);
		pEl->SetAttribute("Type", (CT2A)node->type);
		if (node->type == "application") pEl->SetAttribute("Path", (CT2A)node->path);
		if (node->type == "container") pEl->SetAttribute("Expand", (CT2A)node->expand);
		pEl->SetAttribute("Title", (CT2A)node->title);
		if (node->type == "application") pEl->SetAttribute("Icon", (CT2A)node->icon);
		//pEl->SetAttribute("Id", node->id);
		
		//delete node;
		// The next item, please ...
		hItem = GetNextItem(hItem);
	}


	CString strFile = a_strFile;

	return xmlDoc.SaveFile((CT2A)a_strFile);

	// Save XML
	
}

int CTreeCtrlXML::GetIndentLevel( HTREEITEM hItem )
{
	int iIndent = 0;

	while( (hItem = GetParentItem( hItem )) != NULL )
		iIndent++;

	return iIndent;
}

HTREEITEM CTreeCtrlXML::GetNextItem( HTREEITEM hItem )
{
	HTREEITEM hItemRet = NULL;

	if( false == ItemHasChildren( hItem ) )
	{
		while( ( hItemRet = GetNextSiblingItem( hItem ) ) == NULL )
		{
			if( ( hItem = GetParentItem( hItem ) ) == NULL )
				return NULL;
		}
	}
	else
	{
		return GetChildItem( hItem );
	}

	return hItemRet;
}



// Called when the user presses Ctrl+Shift+N Count entire tree
//int CTreeCtrlXML::CountSubtree(HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
//{
//	static int iCount;
//	if (op != OP_NONE)
//		iCount = 0;
//	else
//	{
//		iCount++;
//		hti = GetChildItem(hti);
//	}
//
//	while (hti != NULL)
//	{
//		CountSubtree(hti, OP_NONE);
//		if (op == OP_SUBTREE)
//			return iCount;
//		else
//		{
//			hti = GetNextSiblingItem(hti);
//		}
//	}
//	return iCount;
//}

//int CTreeCtrlXML::GetIndex()
//{
//	CString str;
//	int iCount = 0;
//	HTREEITEM hti, hti2;
//
//	hti = GetSelectedItem();
//	hti2 = GetRootItem();
//
//	for (size_t i = 0; i < GetCount(); i++) {
//		if (hti == hti2) break;
//		hti2 = GetNextItem(hti2);
//
//		iCount++;
//
//	}
//
//	return iCount;
//	//iCount = GetCount(); //CountSubtree(hti, OP_SUBTREE);
//	//str.Format("Number of item in Subtree: %d", iCount);
//	//AfxMessageBox(str);
//}
//
//void CTreeCtrlXML::ReIndex()
//{
////for (size_t i = 0; i < xml_data_v.size(); i++) {
//	//	xml_data_v[i].idx = i;
//	//}
//	//iCount = GetCount(); //CountSubtree(hti, OP_SUBTREE);
//	//str.Format("Number of item in Subtree: %d", iCount);
//	//AfxMessageBox(str);
//}
//
//CString CTreeCtrlXML::GetName(int index)
//{
//	CString strName = "";
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			strName = xml_data_v[i].name;
//			break;
//		}
//	}
//
//
//	return strName;
//}
//
//DWORD_PTR CTreeCtrlXML::GetData(HTREEITEM hItem)
//{
//	//node_data* node = (node_data*)GetItemData(hItem);
//	
//	return GetItemData(hItem);
//	//CString strName = node->id;// GetItemData(hti);// xmltree->id;
//}
////}
//
//
//CString CTreeCtrlXML::GetPath(int index)
//{
//	CString strPath;
//	strPath = "";
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			strPath = xml_data_v[i].path;
//			break;
//		}
//	}
//
//	return strPath;
//}
//
//CString CTreeCtrlXML::GetTitle(int index)
//{
//	CString strTitle;
//	strTitle = "";
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			strTitle = xml_data_v[i].id;
//			break;
//		}
//	}
//
//	return strTitle;
//}
//
//CString CTreeCtrlXML::GetIcon(int index)
//{
//	CString strIcon = "";
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			strIcon = xml_data_v[i].icon;
//			break;
//		}
//	}
//
//	return strIcon;
//}
//
//CString CTreeCtrlXML::GetExpand(int index)
//{
//	CString strExpang;
//	strExpang = "";
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			strExpang = xml_data_v[i].expand;
//			break;
//		}
//	}
//
//	return strExpang;
//}
//
//void CTreeCtrlXML::OnDeleteItem(int index)
//{
//	int iCount;
//	HTREEITEM hti;
//
//	hti = GetSelectedItem();
//	iCount = CountSubtree(hti, OP_SUBTREE);
//	
//	for (size_t i = 0; i < xml_data_v.size(); i++) {
//		if (index == xml_data_v[i].idx) {
//			xml_data_v.erase(xml_data_v.begin() + (index), xml_data_v.begin() + (index+iCount));
//			break;
//		}
//	}
//
//}
//
//void CTreeCtrlXML::OnInsertItem(int index)
//{
//	int iCount;
//
//	HTREEITEM hItem = GetSelectedItem();
//	HTREEITEM hSibling = GetPrevSiblingItem(hItem);
//
//	HTREEITEM hti;
//	hti = GetSelectedItem();
//	iCount = CountSubtree(hti, OP_NONE);
//
//	xml_data xml_d;
//	xml_d.idx = index;
//	xml_d.name = "New Item";
//	xml_d.type = "application";
//	xml_d.title = "";// "Title");
//	xml_d.path = "path";// pEl->Attribute("Path");
//	xml_d.icon = "APP";// pEl->Attribute("Type");
//	xml_d.expand = "false";// pEl->Attribute("Expand");
//	
//	
//	//for (size_t i = 0; i < xml_data_v.size(); i++) {
//	//	if (index == xml_data_v[i].idx) {
//			xml_data_v.insert(xml_data_v.begin() + (index + iCount), xml_d);
//	//		break;
//	//	}
//	//}
//			ReIndex();
//			SetItemImage(hti, 4, 4);
//}
//
//int CTreeCtrlXML::CountSubtree(HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
//{
//	static int iCount;
//	if (op != OP_NONE)
//		iCount = 0;
//	else
//	{
//		iCount++;
//		hti = GetChildItem(hti);
//	}
//
//	while (hti != NULL)
//	{
//		CountSubtree(hti, OP_NONE);
//		if (op == OP_SUBTREE)
//			return iCount;
//		else
//		{
//			hti = GetNextSiblingItem(hti);
//		}
//	}
//	return iCount;
//}
//void CTreeCtrlXML::OnTvnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
//	// TODO: добавьте свой код обработчика уведомлений
//	*pResult = 0;
//}
//
//
//void CTreeCtrlXML::OnTvnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
//	// TODO: добавьте свой код обработчика уведомлений
//	//был ли ввод нового текста?
//	if (pTVDispInfo->item.pszText == NULL) // не было, пользователь отменил его
//	{
//		*pResult = 0;
//		return;
//	}
//
//	// пусть у нас для примера нельзя, чтобы новое имя элемента было "The item"
//	CString sForbiddenName;
//	sForbiddenName = _T("The item");
//	// если пользователь ввел запрещенное имя для элемента - отвергнуть его
//	if (sForbiddenName.CompareNoCase(pTVDispInfo->item.pszText) == 0)
//	{
//		*pResult = 0;
//		return;
//	}
//	// иначе принять изменения
//	*pResult = 1;
//}




// CopyItem             - Copies an item to a new location
// Returns              - Handle of the new item
// hItem                - Item to be copied
// htiNewParent         - Handle of the parent for new item
// htiAfter             - Item after which the new item should be created
HTREEITEM CTreeCtrlXML::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent,
	HTREEITEM htiAfter /*= TVI_LAST*/)
{
	TV_INSERTSTRUCT         tvstruct;
	HTREEITEM                       hNewItem;
	CString                         sText;

	//node_data* node = new node_data();
	node = (node_data*)GetItemData(hItem);

	node_data* pnode = new node_data();
	pnode = (node_data*)GetItemData(htiNewParent);
	// get information of the source item
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE |
		TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	GetItem(&tvstruct.item);
	sText = GetItemText(hItem);

	tvstruct.item.cchTextMax = sText.GetLength();
	tvstruct.item.pszText = sText.LockBuffer();

	// Insert the item at proper location
	tvstruct.hParent = htiNewParent;
	tvstruct.hInsertAfter = htiAfter;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	hNewItem = InsertItem(&tvstruct);
	sText.ReleaseBuffer();
	
	

	node_data* nnode = new node_data();
	//CString str = CreateID();
	nnode->name = node->name;// m_tree.GetName(indexSelItem);// m_tree.GetItemText(hItem);
	nnode->path = node->path;// m_tree.GetPath(indexSelItem);
	nnode->title = node->title;// m_tree.GetTitle(indexSelItem);
	nnode->icon = node->icon;// m_tree.GetIcon(indexSelItem);
	nnode->expand = node->expand;// m_tree.GetExpand(indexSelItem);
	nnode->type = node->type;
	//nnode->id = str;// m_tree.CreateID();

	//node_data* pnode = new node_data();
	//pnode = (node_data*)GetParentItem(htiNewParent);
	//nnode->parent = pnode->id;

	// Now copy item data and item state.
	//SetItemData(hNewItem, GetItemData(hItem));
	SetItemData(hNewItem, (DWORD_PTR)nnode);
	//Destroy node;
	//delete pnode;
	//SetItemState(hNewItem, GetItemState(hItem, TVIS_STATEIMAGEMASK),
	//	TVIS_STATEIMAGEMASK);

	// Call virtual function to allow further processing in derived class
	OnItemCopied(hItem, hNewItem);
	nnode = 0;
	return hNewItem;
}


void CTreeCtrlXML::OnItemCopied(HTREEITEM /*hItem*/, HTREEITEM /*hNewItem*/)
{
	// Virtual function 
}


// CopyBranch           - Copies all items in a branch to a new location
// Returns              - The new branch node
// htiBranch            - The node that starts the branch
// htiNewParent - Handle of the parent for new branch
// htiAfter             - Item after which the new branch should be created
HTREEITEM CTreeCtrlXML::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent,	HTREEITEM htiAfter /*= TVI_LAST*/)
{
	HTREEITEM hChild;

	UINT state;
	state = GetItemState(htiBranch, TVIS_EXPANDED)& TVIS_EXPANDED;

	HTREEITEM hNewItem = CopyItem(htiBranch, htiNewParent, htiAfter);
	SetItemState(hNewItem, state, state);

	hChild = GetChildItem(htiBranch);
	while (hChild != NULL)
	{
		// recursively transfer all the items
		CopyBranch(hChild, hNewItem);
		hChild = GetNextSiblingItem(hChild);
	}
	return hNewItem;
}

//CString CTreeCtrlXML::CreateID()
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
void CTreeCtrlXML::OnTvnBegindragTreeDrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	POINT CursorPosition(pNMTreeView->ptDrag);
	m_hitemDrag = HitTest(CursorPosition);// pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;
	SelectItem(m_hitemDrag);
	//m_pDragImage = CreateDragImage(m_hitemDrag);  // get the image list for dragging
	// CreateDragImage() returns NULL if no image list
	// associated with the tree view control
	//if (!m_pDragImage)
	//	return;

	m_bLDragging = TRUE;
	//m_pDragImage->BeginDrag(0, CPoint(-15,-15));
	
	POINT pt = pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	//m_pDragImage->DragEnter(NULL, pt);
	SetCapture();
}

void CTreeCtrlXML::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM	hitem,hnitem;
	UINT		flags = NULL;

	if (m_nHoverTimerID)
	{
		KillTimer(m_nHoverTimerID);
		m_nHoverTimerID = 0;
	}

	if (m_bLDragging)
	{
		
		POINT pt = point;
		ClientToScreen(&pt);

		//CImageList::DragMove(pt);
		if ((hitem = HitTest(point, &flags)) != NULL && (TVHT_ONITEM & flags))
		{
			//CImageList::DragShowNolock(FALSE);
			//SelectDropTarget(hitem);
			if (htiDrop != hitem) {
				

				m_hitemDrop = hitem;
				HTREEITEM hti = GetParentItem(m_hitemDrop);
				bool bIsChildren = false;
				while (hti != NULL) {
					if (hti == m_hitemDrag) {
						bIsChildren = true;
						break;
					}
					hti = GetParentItem(hti);

				}
				SetInsertMark(hitem, TRUE);
				if (m_hitemDrag == m_hitemDrop || bIsChildren) {
					
					SetInsertMarkColor(RGB(255, 0, 0));
				}
				else {

					SetInsertMarkColor(RGB(47, 145, 207));
					//timer = true;
					SetTimer(m_nHoverTimerID, 2000, NULL);
					m_HoverPoint = point;
					
				}



				if (hnitem = GetPrevVisibleItem(hitem))
					EnsureVisible(hnitem);
				if (hnitem = GetNextVisibleItem(hitem))
					EnsureVisible(hnitem);

				htiDrop = hitem;
			}
			//CImageList::DragShowNolock(TRUE);
		}
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CTreeCtrlXML::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		//CImageList::DragLeave(this);
		//CImageList::EndDrag();
		ReleaseCapture();

		//delete m_pDragImage;
		SetInsertMark(NULL,1);
		// Remove drop target highlighting
		SelectDropTarget(NULL);

		
		if (m_hitemDrag == m_hitemDrop)
			return;

		HTREEITEM hti = GetParentItem(m_hitemDrop);
		while (hti != NULL) {
			if (hti == m_hitemDrag)
				return;
			hti = GetParentItem(hti);
			
		}

		// If Drag item is an ancestor of Drop item then return
		Expand(m_hitemDrop, TVE_EXPAND);
		HTREEITEM htiDrag, htiParent, htiDrop, htiAfter;
		htiDrag = m_hitemDrag;
		htiDrop = m_hitemDrop;
		htiAfter = m_hitemDrop;
		htiParent = GetParentItem(m_hitemDrop);
		if (ItemHasChildren(m_hitemDrop)) {
			htiParent = m_hitemDrop;
			htiAfter = TVI_FIRST;
		}
		
		//HTREEITEM htiParent = m_hitemDrop;

		//while ((htiParent = GetParentItem(m_hitemDrop)) != NULL)
		//{
		//	if (htiParent == m_hitemDrag) return;
		//}

		

		HTREEITEM htiNew = CopyBranch(htiDrag, htiParent, htiAfter);
		DeleteItem(m_hitemDrag);
		SelectItem(htiNew);
	}

}

void CTreeCtrlXML::OnTimer(UINT uTime)
{
	if (uTime == m_nHoverTimerID)
	{
		KillTimer(m_nHoverTimerID);
		m_nHoverTimerID = 0;

		HTREEITEM	trItem = 0;
		UINT		uFlag = 0;

		trItem = HitTest(m_HoverPoint, &uFlag);

		if (trItem)
		{
			//SelectItem(trItem);
			Expand(trItem, TVE_EXPAND);
		}
	}
	else
	{
		//CTreeCtrlXML::OnTimer(uTime);
	}
	//Expand(m_hitemDrop, TVE_EXPAND);
	//timer = false;
	
}