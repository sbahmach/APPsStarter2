

#ifndef CMenuModifier_h_hsgdacvgshtrytry6yrt644446gfhgh
#define CMenuModifier_h_hsgdacvgshtrytry6yrt644446gfhgh

#include <afxtempl.h>
#include <afxwin.h>
// padding around image (L=left,T=top, ...)
#define IMG_PADL	6
#define IMG_PADR	7
#define IMG_PADT	4
#define IMG_PADB	4

// diatance from text to vertical bar
#define TXT_DIS		8

#define RGB3(a)	RGB(a,a,a)

#ifndef OBM_CHECK
#define OBM_CHECK 32760
#endif

class CMenuModifier
{
class BitmapBuffer;
class BitmapUnit;
class MenuUser;
class MenuUserArray;

public:
	CMenuModifier();
	virtual ~CMenuModifier();

public:	//must be used
	BOOL SetOwnerDraw(CMenu*pMenu,BOOL bMainMenu,CToolBar*pBar=0,int iImageStyle=CMenuModifier::FLAT,
						COLORREF*pClrMenuBar=0,COLORREF*pClrVertBar=0,COLORREF*pClrSelected=0);
	BOOL OnMeasureItem(int nIDCtl,MEASUREITEMSTRUCT*pMIS, int dpi);
	BOOL OnDrawItem(int nIDCtl,DRAWITEMSTRUCT*pDIS, int dpi);

public:	//optional function
	void SetChechedItemStyle(BOOL bUseObmBitmap)
	{
		b_UseObmBitmap=bUseObmBitmap;
	}

public:
	static int GetRowBytes(int iBmpW,int iBitsPix)
	{
		int iRowByte=iBmpW*iBitsPix/8;
		while(iRowByte%4)	iRowByte++;
		return iRowByte;
	}

private:
	void P_AddUserImage(CToolBar*pBar);
	void P_AddUserItem(CMenu*pMenu,int iPos,BOOL bTop);

	void P_SetOwnerDrawLoop(CMenu*pMenu,BOOL bTop,CToolBar*pBar);

	void P_DrawMenuBar(CDC*pDC,CRect rcItem,DRAWITEMSTRUCT*pDIS);
	void P_DrawSeparator(CDC*pDC,CRect rcItem);
	void P_DrawSubMenu(CDC*pDC,CRect rcItem,DRAWITEMSTRUCT*pDIS);

	void P_FillBkgnd(CDC*pDC,CRect rcItem,COLORREF clrBk);
	void P_DrawImage(CDC*pDC,CRect rcItem,MenuUser*pUser,BOOL bDisabled,BOOL bChecked);

	int	P_GetImageIndex(MenuUser*pUser,CToolBar*pBar);
	void P_CreateUserImage(MenuUser*pUser,CToolBar*pBar,CSize&siImg,const BITMAP&bmp,BitmapBuffer&bufLarger);
	void P_GetBitsColor(BYTE*pbClr,COLORREF clr,int iBitsPix);

	BOOL P_NearWhiteColor(BYTE*pbClr,int iBitsPix);

	void P_DrawSunkenBorder(CDC*pDC,CRect rc);

	void P_DeleteAll();

	//================================================
private:
	class BitmapBuffer	//bitmap bits buffer
	{
	public:
		BitmapBuffer()			{pBuf=0;	iLen=0;}
		BitmapBuffer(int iLenIn)	{iLen=0;	pBuf=new BYTE[iLenIn];	if(pBuf)iLen=iLenIn;}
		~BitmapBuffer()			{Delete();}

		void Delete()			{delete []pBuf;	pBuf=0;	iLen=0;}
		BOOL Create(int iLenIn)	{Delete();	pBuf=new BYTE[iLenIn];	if(pBuf==0) return 0; iLen=iLenIn; return 1;}
		int GetLength()			{return iLen;}
		operator BYTE*()		{return pBuf;}

	private:
		BYTE*pBuf;
		int iLen;
	};

	class BitmapUnit	//
	{
	public:
		BOOL CreateBuffer(const CSize&siImgIn,const int iBitsPix);
		BOOL DrawImage(CDC*pDC,CPoint pt,const CSize&siImg,int iBitsPix,BOOL bDisabled);

	public:
		BitmapBuffer bufE;	//enabled image
		BitmapBuffer bufD;	//disabled image
	};

	class MenuUser
	{
	public:
		MenuUser()
		{
			bSeparator		=0;
			bTop			=0;
			iCmd			=0;
		}
		~MenuUser()
		{
		}

	public:
		CString csText;
		BYTE	bSeparator;
		BYTE	bTop;

		int		iCmd;
		
		BitmapUnit	img;
	};

	//Owner-draw is identified by item, sorted array makes find faster
	class MenuUserArray:public CArray<MenuUser*,MenuUser*>
	{
	public:
		MenuUserArray();
		~MenuUserArray();
		void DeleteAll();

		void InsertInSort(MenuUser*pUser);
		int FindInSort(const MenuUser*pUser,BOOL&bFind);
		BOOL HasTheItem(const MenuUser*pUser);

	private:
		//binary find
		int P_FindInSortLoop(int i0,int i1,const MenuUser*pUserFind,BOOL&bFind);
	};

	//OBM_CHECK box
	class ObmChecked
	{
	public:
		void LoadBitmap();
		void DrawObmCheckBox(CDC*pDC,CRect rc);

	private:
		CBitmap bmp_Chk;
		CSize	si_Bmp;
	};

public:
	enum
	{
		FLAT,
		SUNKEN_WHITE,
		SUNKEN_BLACK,
		SUNKEN_BOTH,
		RAISED_WHITE,
		RAISED_BLACK,
		RAISED_BOTH,
	};

private:
	COLORREF	clr_MenuBar;
	COLORREF	clr_Item;	
	COLORREF	clr_VertBar;
	COLORREF	clr_TextEnabled;		
	COLORREF	clr_TextDisabled;
	COLORREF	clr_Separator;
	COLORREF	clr_Selected;
	COLORREF	clr_SelectBorder;

	//---------------------------
	CSize	si_Head;	//size on vertical bar
	CSize	si_Img2;	//size of bitmap with 2 extra pixels
	int		i_BitsPix;	//bitmap bits of a pixel

	BOOL	b_UseObmBitmap;
	int		i_ImageStyle;

	//---------------------------
	ObmChecked		obm_Checked;
	MenuUserArray	ary_Item;
};

//=============================== MenuUserArray functions
inline
CMenuModifier::MenuUserArray::MenuUserArray()
{
}

inline
CMenuModifier::MenuUserArray::~MenuUserArray()
{
	DeleteAll();
}

inline
void CMenuModifier::MenuUserArray::DeleteAll()
{
	INT_PTR i,iNum=GetSize();
	for(i=0;i<iNum;i++)	delete GetAt(i);
	RemoveAll();
}

inline
void CMenuModifier::MenuUserArray::InsertInSort(MenuUser*pUser)
{
	BOOL bFind;
	int iFind=FindInSort(pUser,bFind);
	InsertAt(iFind,pUser);
}

inline
int CMenuModifier::MenuUserArray::FindInSort(const MenuUser*pUser,BOOL&bFind)
{
	bFind=0;
	return P_FindInSortLoop(0,(int)GetSize()-1,pUser,bFind);
}

inline
BOOL CMenuModifier::MenuUserArray::HasTheItem(const MenuUser*pUser)
{
	BOOL bFind;
	FindInSort(pUser,bFind);
	return bFind;
}

inline
int CMenuModifier::MenuUserArray::P_FindInSortLoop(int i0,int i1,const MenuUser*pUserFind,BOOL&bFind)
{
	if(i0>i1)	return i0;

	MenuUser*pUser;

	pUser=GetAt(i0);
	if(pUser==pUserFind)	{bFind=1; return i0;}
	if(pUser>pUserFind)		return i0;
	if(i0==i1)				return i0+1;

	pUser=GetAt(i1);
	if(pUser==pUserFind)	{bFind=1; return i1;}
	if(pUser<pUserFind)		return i1+1;
	if(i1==i0+1)			return i1;

	int im=(i0+i1)/2;
	pUser=GetAt(im);
	if(pUser==pUserFind)	{bFind=1; return im;}
	if(pUser>pUserFind)		{i0++; i1=im-1;}
	else					{i0=im+1; i1--;}

	return P_FindInSortLoop(i0,i1,pUserFind,bFind);
}


//=============================== BitmapUnit functions
inline
BOOL CMenuModifier::BitmapUnit::CreateBuffer(const CSize&siImg2,const int iBitsPix)
{
	const int iRowByte=CMenuModifier::GetRowBytes(siImg2.cx,iBitsPix);
	int iSize=iRowByte*siImg2.cy;

	if(bufE.Create(iSize)==0)	return 0;
	if(bufD.Create(iSize)==0)
	{
		bufE.Delete();
		return 0;
	}
	return 1;
}

inline
BOOL CMenuModifier::BitmapUnit::DrawImage(CDC*pDC,CPoint pt,const CSize&siImg,int iBitsPix,BOOL bDisabled)
{
	if(bufE.GetLength()==0)	return 0;

	BITMAPINFOHEADER bih;
	memset(&bih,0,sizeof(BITMAPINFOHEADER));

	bih.biSize		=sizeof(BITMAPINFOHEADER);
	bih.biWidth		=siImg.cx;
	bih.biHeight	=-siImg.cy;
	bih.biBitCount	=iBitsPix;
	bih.biSizeImage	=bufE.GetLength();
	bih.biPlanes	=1;

	BYTE*pbBmp;
	if(bDisabled)	pbBmp=(BYTE*)bufD;
	else			pbBmp=(BYTE*)bufE;

	int iScan=::SetDIBitsToDevice(pDC->m_hDC,	
						pt.x,pt.y, 
						siImg.cx,siImg.cy,
						0,0,	
						0,siImg.cy,
						pbBmp,
						(BITMAPINFO*)&bih,
						DIB_RGB_COLORS);

	return (iScan>0)?1:0;
}

//=============================== CMenuModifier::ObmChecked functions
inline 
void CMenuModifier::ObmChecked::LoadBitmap()
{
	bmp_Chk.LoadOEMBitmap(OBM_CHECK);

	BITMAP		bmp;
	memset(&bmp,0,sizeof(BITMAP));
	bmp_Chk.GetBitmap(&bmp);
	si_Bmp=CSize(bmp.bmWidth,bmp.bmHeight);
}

inline 
void CMenuModifier::ObmChecked::DrawObmCheckBox(CDC*pDC,CRect rc)
{
	const CPoint ptBmp=CPoint(rc.left+(rc.Width()-si_Bmp.cx)/2+1,rc.top+(rc.Height()-si_Bmp.cy)/2);
	const CRect rcBmp(ptBmp,si_Bmp);

	pDC->SetBkColor(RGB(255,255,255));

	CRect rcBd=rcBmp;
	rcBd.DeflateRect(-3,-2,-2,-2);
	pDC->FillRect(&rcBd,&CBrush(RGB3(255)));

	pDC->DrawState(ptBmp,si_Bmp,bmp_Chk,DSS_NORMAL);

	pDC->Draw3dRect(&rcBd,RGB3(0),RGB3(255));
	rcBd.DeflateRect(1,1);
	pDC->Draw3dRect(&rcBd,RGB3(220),RGB3(220));
}

//=============================== main class functions

inline
CMenuModifier::CMenuModifier()
{
	//DWORD dwVersion		=GetVersion();
	//WORD wLow=LOBYTE(LOWORD(dwVersion));

	clr_MenuBar	=::GetSysColor(COLOR_3DFACE);
	clr_VertBar	=clr_MenuBar;

	clr_TextEnabled		=GetSysColor(COLOR_MENUTEXT);
	clr_TextDisabled	=GetSysColor(COLOR_GRAYTEXT);

	clr_Separator		= RGB3(160);
	clr_SelectBorder	= RGB(47, 145, 207); // RGB3(200);
	clr_Selected		= RGB(201, 225, 255); //RGB3(230);
	clr_Item			= RGB3(255);

	//-------------------------------
	b_UseObmBitmap	=1;
}

inline
CMenuModifier::~CMenuModifier()
{
	P_DeleteAll();
}

inline
void CMenuModifier::P_DeleteAll()
{
	ary_Item.DeleteAll();

	//set default
	b_UseObmBitmap	=1;
}

inline
int CMenuModifier::P_GetImageIndex(MenuUser*pUser,CToolBar*pBar)
{
	if(pBar==0)	return -1;
	if(pUser->iCmd<=0)	return -1;

	UINT i,iNum=pBar->GetCount();
	int iCmdT;
	int iIndex=0;

	for(i=0;i<iNum;i++)
	{
		iCmdT=pBar->GetItemID(i);
		if(iCmdT<=0)	continue;

		if(iCmdT==pUser->iCmd)	return iIndex;
		iIndex++;
	}
	return -1;
}

inline
void CMenuModifier::P_AddUserImage(CToolBar*pBar)
{
	if(pBar==0)	return;

	CToolBarCtrl&ctrl=pBar->GetToolBarCtrl();
	CImageList*pImg=ctrl.GetImageList();
	if(pImg==0)	return;
	const int iNumImg=pImg->GetImageCount();
	if(iNumImg==0)	return;

	//-------------------- whole image-list bitmap
	IMAGEINFO inf;
	if(pImg->GetImageInfo(0,&inf)==0)	return;

	HBITMAP&hBmp=inf.hbmImage;
	BITMAP bmp;
	memset(&bmp,0,sizeof(BITMAP));
	if(GetObject(hBmp,sizeof(BITMAP),&bmp)==0)	return;

	//computer system setting
	if((bmp.bmBitsPixel!=16)&&(bmp.bmBitsPixel!=32))	return;

	i_BitsPix=bmp.bmBitsPixel;

	const int iNumByte=bmp.bmWidthBytes*bmp.bmHeight;
	BitmapBuffer bs1000(iNumByte+1000);
	if(bs1000.GetLength()==0)	return;
	const int iNumCopy=::GetBitmapBits(hBmp,iNumByte+1000,(BYTE*)bs1000);
	if(iNumCopy!=iNumByte)		return;
	CSize siImg(inf.rcImage.right-inf.rcImage.left,inf.rcImage.bottom-inf.rcImage.top);

	//large 64 x 75, small 16 x 15
	INT_PTR i,iNum=ary_Item.GetSize();
	MenuUser*pUser;
	for(i=0;i<iNum;i++)
	{
		pUser=ary_Item.GetAt(i);
		P_CreateUserImage(pUser,pBar,siImg,bmp,bs1000);
	}
}

inline
void CMenuModifier::P_CreateUserImage(MenuUser*pUser,CToolBar*pBar,CSize&siImg0,const BITMAP&bmp,BitmapBuffer&bufLarger)
{
	if(pBar==0)	return;

	const int iImgIndex=P_GetImageIndex(pUser,pBar);
	if(iImgIndex<0)	return;

	const int iBitsPix		=bmp.bmBitsPixel;
	const int iRowByteLarge	=bmp.bmWidthBytes;

	if(pUser->img.CreateBuffer(si_Img2,iBitsPix)==0)	return;

	const int iRowBytes2=GetRowBytes(si_Img2.cx,iBitsPix);

	//----------- colors
	BYTE btBitsOne[4];
	memcpy(btBitsOne,(BYTE*)bufLarger,4);

	BYTE btClrVert[4];
	P_GetBitsColor(btClrVert,clr_VertBar,iBitsPix);

	const int iBytesPix=iBitsPix/8;

	const int iLenBuf=pUser->img.bufE.GetLength();
	BitmapBuffer bufT(iLenBuf);

	//-------------
	const BYTE*pbTemplate	=(BYTE*)bufT;
	const BYTE*pbEnabled	=(BYTE*)pUser->img.bufE;
	const BYTE*pbDisabled	=(BYTE*)pUser->img.bufD;

	const int iImgW0=siImg0.cx;
	const int iImgH0=siImg0.cy;

	const int iImgW2=si_Img2.cx;
	const int iImgH2=si_Img2.cy;

	//not include align bytes
	const int iRowBytes0=iImgW0*iBytesPix;

	int ix,iy;

	//==================== step 1: copy transparent color to all buffers
	BYTE*pbT,*pbT0=(BYTE*)pbTemplate;
	for(iy=0;iy<iImgH2;iy++)
	{
		pbT=pbT0;
		for(ix=0;ix<iImgW2;ix++)
		{
			::memcpy(pbT,btBitsOne,iBytesPix);
			pbT+=iBytesPix;
		}
		pbT0+=iRowBytes2;
	}

	memcpy((BYTE*)pbEnabled,	pbTemplate,iLenBuf);
	memcpy((BYTE*)pbDisabled,	pbTemplate,iLenBuf);

	//-----------------
	BYTE*pbS0,*pbS;

	//==================== step 2: copy source color to template buffer
	const int iImgByteW0=iImgW0*iBitsPix/8;
	const int iNumClm=iRowByteLarge/iImgByteW0;

	const int iRow=iImgIndex/iNumClm;
	const int iClm=iImgIndex%iNumClm;

	pbS0=((BYTE*)bufLarger)+(iRowByteLarge*iRow*iImgH0+iImgByteW0*iClm);
	pbT0=(BYTE*)pbTemplate+(iRowBytes2+iBytesPix);

	for(iy=0;iy<iImgH0;iy++)
	{
		pbS=pbS0;
		pbT=pbT0;
		for(ix=0;ix<iRowBytes0;ix++)
		{
			*pbT=*pbS;
			pbS++;
			pbT++;
		}
		pbT0+=iRowBytes2;
		pbS0+=iRowByteLarge;
	}

	//-------------------------
	const int iBytesMove=iRowBytes2+iBytesPix;
	BYTE btClrWhite[4];
	P_GetBitsColor(btClrWhite,RGB3(255),iBitsPix);
	BYTE btClrBlack[4];
	P_GetBitsColor(btClrBlack,RGB3(0),iBitsPix);
	BYTE btClrDark[4];
	P_GetBitsColor(btClrDark,RGB3(128),iBitsPix);

	//==================== step 3: copy enabled image

	//3-1. 3D
	if(i_ImageStyle!=FLAT)
	{
		int iMoveW,iMoveB;
		switch(i_ImageStyle)
		{
		case SUNKEN_WHITE:	iMoveW=+iBytesMove;	iMoveB=0;			break;
		case SUNKEN_BLACK:	iMoveW=0;			iMoveB=-iBytesMove;	break;
		case SUNKEN_BOTH:	iMoveW=+iBytesMove;	iMoveB=-iBytesMove;	break;

		case RAISED_WHITE:	iMoveW=-iBytesMove;	iMoveB=0;			break;
		case RAISED_BLACK:	iMoveW=0;			iMoveB=+iBytesMove;	break;
		case RAISED_BOTH:	iMoveW=-iBytesMove;	iMoveB=+iBytesMove;	break;

		//	SUNKEN_BOTH
		default:	iMoveW=+iBytesMove;	iMoveB=-iBytesMove;	break;
		}

		pbS0=(BYTE*)pbTemplate+iBytesMove;
		pbT0=(BYTE*)pbEnabled+iBytesMove;

		for(iy=0;iy<iImgH0;iy++)
		{
			pbS=pbS0;
			pbT=pbT0;
			for(ix=0;ix<iImgW0;ix++)
			{
				if(::memcmp(pbS,btBitsOne,iBytesPix)==0)
				{
					//do nothing
				}
				else
				if(P_NearWhiteColor(pbS,iBitsPix))
				{
					//do nothing
				}
				else
				{
					::memcpy(pbT+iMoveW,btClrWhite,iBytesPix);
					::memcpy(pbT+iMoveB,btClrDark,iBytesPix);
				}
				pbS+=iBytesPix;
				pbT+=iBytesPix;
			}
			pbT0+=iRowBytes2;
			pbS0+=iRowBytes2;
		}
	}

	//3-2. copy source
	pbS0=(BYTE*)pbTemplate;
	pbT0=(BYTE*)pbEnabled;

	for(iy=0;iy<iImgH2;iy++)
	{
		pbS=pbS0;
		pbT=pbT0;
		for(ix=0;ix<iImgW2;ix++)
		{
			if(::memcmp(pbS,btBitsOne,iBytesPix)==0)
			{
				//do nothing
			}
			else
			{
				::memcpy(pbT,pbS,iBytesPix);
			}
			pbS+=iBytesPix;
			pbT+=iBytesPix;
		}
		pbS0+=iRowBytes2;
		pbT0+=iRowBytes2;
	}

	//3-3. transparent
	pbT0=(BYTE*)pbEnabled;

	for(iy=0;iy<iImgH2;iy++)
	{
		pbT=pbT0;
		for(ix=0;ix<iImgW2;ix++)
		{
			if(::memcmp(pbT,btBitsOne,iBytesPix)==0)
			{
				::memcpy(pbT,btClrVert,iBytesPix);
			}
			pbT+=iBytesPix;
		}
		pbT0+=iRowBytes2;
	}

	//==================== step 4: copy disabled image
	pbS0=(BYTE*)pbTemplate+iBytesMove;
	pbT0=(BYTE*)pbDisabled+iBytesMove;

	//4-1. white
	for(iy=0;iy<iImgH0;iy++)
	{
		pbS=pbS0;
		pbT=pbT0;
		for(ix=0;ix<iImgW0;ix++)
		{
			if(::memcmp(pbS,btBitsOne,iBytesPix)==0)
			{
				//do nothing
			}
			else
			if(P_NearWhiteColor(pbS,iBitsPix))
			{
				//do nothing
			}
			else
			{
				::memcpy(pbT+iBytesMove,btClrWhite,iBytesPix);
			}
			pbS+=iBytesPix;
			pbT+=iBytesPix;
		}
		pbT0+=iRowBytes2;
		pbS0+=iRowBytes2;
	}

	//4-2. dark
	pbS0=(BYTE*)pbTemplate+iBytesMove;
	pbT0=(BYTE*)pbDisabled+iBytesMove;

	for(iy=0;iy<iImgH0;iy++)
	{
		pbS=pbS0;
		pbT=pbT0;
		for(ix=0;ix<iImgW0;ix++)
		{
			if(::memcmp(pbS,btBitsOne,iBytesPix)==0)
			{
				//do nothing
			}
			else
			if(P_NearWhiteColor(pbS,iBitsPix))
			{
				//do nothing
			}
			else
			{
				::memcpy(pbT,btClrDark,iBytesPix);
			}
			pbS+=iBytesPix;
			pbT+=iBytesPix;
		}
		pbT0+=iRowBytes2;
		pbS0+=iRowBytes2;
	}

	//4-3. transparent
	pbT0=(BYTE*)pbDisabled;

	for(iy=0;iy<iImgH2;iy++)
	{
		pbT=pbT0;
		for(ix=0;ix<iImgW2;ix++)
		{
			if(::memcmp(pbT,btBitsOne,iBytesPix)==0)
			{
				::memcpy(pbT,btClrVert,iBytesPix);
			}
			pbT+=iBytesPix;
		}
		pbT0+=iRowBytes2;
	}
}

inline
void CMenuModifier::P_GetBitsColor(BYTE*pbClr,COLORREF clr,int iBitsPix)
{
	BYTE btR=GetRValue(clr);
	BYTE btG=GetGValue(clr);
	BYTE btB=GetBValue(clr);

	if(iBitsPix==32)
	{
		*pbClr=btB;	pbClr++;
		*pbClr=btG;	pbClr++;
		*pbClr=btR;
	}
	else
	if(iBitsPix==16)
	{
		unsigned short*pi=(unsigned short*)pbClr;
	
		btR>>=3;
		btG>>=3;
		btB>>=3;

		*pi=0x7FFF&((btR<<10)|(btG<<5)|btB);
	}
}

inline
BOOL CMenuModifier::P_NearWhiteColor(BYTE*pbClr,int iBitsPix)
{
	//RGB(192,192,192) or over
	if(iBitsPix==32)
	{
		if((pbClr[0]>=0xC0)&&(pbClr[1]>=0xC0)&&(pbClr[2]>=0xC0))	return 1;
	}
	else
	if(iBitsPix==16)
	{
		unsigned short iv=*(unsigned short*)pbClr;

		//if((iv&0x7C00>=0x6000)&&(iv&0x03E0>=0x0300)&&(iv&0x001F>=0x0018))	
			return 1;
	}
	return 0;
}

inline
void CMenuModifier::P_AddUserItem(CMenu*pMenu,int iPos,BOOL bTop)
{
	MenuUser*pUser=new MenuUser;
	ary_Item.InsertInSort(pUser);

	pMenu->GetMenuString(iPos,pUser->csText,MF_BYPOSITION);
	pUser->bTop			=bTop;

	pUser->iCmd			=pMenu->GetMenuItemID(iPos);
	
	UINT uState	=pMenu->GetMenuState(iPos,MF_BYPOSITION);
	if(bTop==0)	
	{
		if(pUser->iCmd==0)
		{
			pUser->bSeparator	=(uState&MF_SEPARATOR)?1:0;   
		}
	}

	//------------------------------------------------------------------
	//note
	UINT uUse=MF_DISABLED|MF_GRAYED|MF_CHECKED;//MF_SEPARATOR|MF_MENUBREAK|MF_MENUBARBREAK;
	UINT uNew=MF_BYPOSITION|MF_OWNERDRAW;
	uNew|=(uState&uUse);

	pMenu->ModifyMenu(iPos,uNew,pUser->iCmd,(LPCTSTR)pUser);
}

inline
BOOL CMenuModifier::SetOwnerDraw(CMenu*pMenu,BOOL bMainMenu,CToolBar*pBar,int iImageStyle,COLORREF*pClrMenuBar,
								 COLORREF*pClrVertBar,COLORREF*pClrSelected)
{
	if(pMenu==0)	return 0;

	P_DeleteAll();

	if(pClrMenuBar)		clr_MenuBar	=*pClrMenuBar;
	if(pClrVertBar)		clr_VertBar	=*pClrVertBar;
	if(pClrSelected)	clr_Selected=*pClrSelected;

	i_ImageStyle=iImageStyle;

	obm_Checked.LoadBitmap();

	CImageList*pImgBar=0;

	if(pBar)
	{
		CToolBarCtrl&ctrl=pBar->GetToolBarCtrl();
		pImgBar=ctrl.GetImageList();
		if(pImgBar==0)	return 0;
	}

	if(pImgBar)
	{
		if(pImgBar->GetImageCount()==0)	return 0;

		IMAGEINFO imgInf;
		pImgBar->GetImageInfo(0,&imgInf);
		CRect rc=imgInf.rcImage;
		si_Head=rc.Size();
		si_Head.cx+=2;
		si_Head.cy+=2;

		si_Img2=si_Head;
	}
	else
	{
		si_Head=CSize(15,15);
	}

	si_Head.cx+=(IMG_PADL+IMG_PADR);
	si_Head.cy+=(IMG_PADT+IMG_PADB);
	
	P_SetOwnerDrawLoop(pMenu,bMainMenu,pBar);
	P_AddUserImage(pBar);

	return 1;
}

inline
void CMenuModifier::P_SetOwnerDrawLoop(CMenu*pMenu,BOOL bTop,CToolBar*pBar)
{
	if(pMenu==0)	return;

	int i,iNum=pMenu->GetMenuItemCount();
	for(i=0;i<iNum;i++)
	{
		P_AddUserItem(pMenu,i,bTop);
	}

	CMenu*pSub;
	for(i=0;i<iNum;i++)
	{
		pSub=pMenu->GetSubMenu(i);
		if(pSub)	P_SetOwnerDrawLoop(pSub,0,pBar);
	}
}

inline
BOOL CMenuModifier::OnMeasureItem(int nIDCtl,MEASUREITEMSTRUCT*pMIS, int dpi)
{
	//LPMENUITEM lpItem = (LPMENUITEM)lpMIS->itemData;
	if(nIDCtl!=0)	return	0;
	if(pMIS->CtlType!=ODT_MENU)	return	0;

	const MenuUser*pUser=(MenuUser*)pMIS->itemData;
	if(ary_Item.HasTheItem(pUser)==0)	return	0;

	if(pUser->bSeparator)
	{
		pMIS->itemHeight	= MulDiv(6, dpi, 96);
	}
	else
	if(pUser->csText.GetLength())
	{
		HDC hDC=::GetDC(0);
		CDC*pDC=CDC::FromHandle(hDC);
		CFont*pFt=CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
		// First get the dialog font
		//LOGFONT lf;
		//pFt->GetLogFont(&lf);

		// change the parameters
		//lf.lfHeight = 20;
		// .....

		// create your own font
		//CFont font;
		//font.CreateFontIndirect(&lf);

		// select your font
		//CFont* pOldFont = pDC->SelectObject(&font);

		// use your font (pDC-&gt;TextOut(), ...)

		//// remember to reselect the old font
		//pDC - &gt; SelectObject(pOldFont);
		//CFont* pFont3 = ::GetFont();
		//	LOGFONT lf;
		//	memset(&lf, 0, sizeof(LOGFONT));
		//	pFt->GetLogFont(&lf);
		//	lf.lfHeight = -MulDiv(15, dpi, 72);
		//	CFont m_font3;
		//	m_font3.CreateFontIndirect(&lf);
		//
		CFont* pFtOld = pDC->SelectObject(pFt);

		/*CSize siTxt=pDC->GetTextExtent(pUser->csText);*/
			const CString strText(pUser->csText);
			CRect r;
			r.right = r.left + MulDiv(r.Width(), dpi, 72);
			r.bottom = r.top + MulDiv(r.Height(), dpi, 72);
			pDC->DrawText(strText, &r, DT_SINGLELINE | DT_CALCRECT | DT_VCENTER);
			CSize size(r.Size());

		pDC->SelectObject(pFtOld);
		::ReleaseDC(0,hDC);

		/*pMIS->itemHeight	=si_Head.cy;
		pMIS->itemWidth		=siTxt.cx;

		if(pUser->bTop)	pMIS->itemWidth+=4;
		else			pMIS->itemWidth+=(si_Head.cx+TXT_DIS);*/

		static int m_CYMENU = MulDiv(::GetSystemMetrics(SM_CYMENU), dpi, 72);

		pMIS->itemWidth = size.cx + m_CYMENU * 2;
		if (strText.Find('\t') > 0) {
			pMIS->itemWidth += m_CYMENU * 2 + m_CYMENU;

		}
		pMIS->itemHeight = size.cy + MulDiv(12, dpi, 72);
	}
	else
	{
		pMIS->itemWidth= MulDiv(20, dpi, 72);
	}
	return 1;
}

inline
void CMenuModifier::P_FillBkgnd(CDC*pDC,CRect rcItem,COLORREF clrBk)
{
	CRect rc;

	rc=rcItem;
	rc.right=rc.left+si_Head.cx;
	pDC->FillRect(&rc,&CBrush(clr_VertBar));

	rc=rcItem;
	rc.left+=si_Head.cx;
	pDC->FillRect(&rc,&CBrush(clrBk));
}

//********************************************* draw

inline
BOOL CMenuModifier::OnDrawItem(int nIDCtl,DRAWITEMSTRUCT*pDIS, int dpi)
{
	if(nIDCtl!=0)	return 0;
	if(pDIS->CtlType!=ODT_MENU)	return 0;

	const MenuUser*pUser=(MenuUser*)pDIS->itemData;
	if(ary_Item.HasTheItem(pUser)==0)	return 0;


	CDC*pDC		=CDC::FromHandle(pDIS->hDC);
	CFont* pFt = CFont::FromHandle((HFONT)::GetStockObject(DEFAULT_GUI_FONT));
	// First get the dialog font
	LOGFONT lf;
	pFt->GetLogFont(&lf);

	// change the parameters
	lf.lfHeight = -MulDiv(lf.lfHeight, dpi, 72);
	lf.lfWeight = FW_LIGHT;
	// .....

	// create your own font
	CFont font;
	font.CreateFontIndirect(&lf);

	// select your font
	CFont* pOldFont = pDC->SelectObject(&font);

	// use your font (pDC-&gt;TextOut(), ...)

	// remember to reselect the old font
	

	RECT&rcItem=pDIS->rcItem;

	int iBkMode=pDC->SetBkMode(TRANSPARENT);

	if(pUser->bTop)			P_DrawMenuBar(pDC,rcItem,pDIS);
	else
	if(pUser->bSeparator)	P_DrawSeparator(pDC,rcItem);
	else					P_DrawSubMenu(pDC,rcItem,pDIS);

	pDC->SetBkMode(iBkMode);
	pDC->SelectObject(pOldFont);
	return 1;
}

inline
void CMenuModifier::P_DrawMenuBar(CDC*pDC,CRect rcItem,DRAWITEMSTRUCT*pDIS)
{
	MenuUser*pUser=(MenuUser*)pDIS->itemData;
	COLORREF	clrTxt=clr_TextEnabled;

	const UINT uState=pDIS->itemState;
	BOOL bDisabled	=((uState&ODS_DISABLED)||(uState&ODS_GRAYED))?1:0;
	if(bDisabled)
	{
		clrTxt=clr_TextDisabled;
	}

	CRect rc=rcItem;
	pDC->FillRect(&rc,&CBrush(clr_MenuBar));

	if(pUser->csText.GetLength())
	{
		COLORREF clrTextOld=pDC->SetTextColor(clrTxt);

		CRect rcTxt=pDIS->rcItem;
		UINT uDT=DT_VCENTER|DT_SINGLELINE|DT_EXPANDTABS;

		pDC->DrawText(pUser->csText,&rcTxt,uDT|DT_CENTER);

		pDC->SetTextColor(clrTextOld);
	}

	if(bDisabled)	return;

	if(uState&ODS_SELECTED)	
	{
		pDC->Draw3dRect(&pDIS->rcItem,RGB(0,0,0),RGB(255,255,255));
	}
	else
	if(uState==0x140)	
	{
		pDC->Draw3dRect(&pDIS->rcItem,RGB(255,255,255),RGB(0,0,0));
	}
}

inline
void CMenuModifier::P_DrawSeparator(CDC*pDC,CRect rcItem)
{
	P_FillBkgnd(pDC,rcItem,clr_Item);

	CRect rcT=rcItem;
	rcT.left+=si_Head.cx;

	int iX0=rcT.left+2;
	int iX1=rcT.right-2;
	int iY=(rcT.top+rcT.bottom)/2;

	CPen pen0(PS_SOLID,1,clr_Separator);
	CPen pen1(PS_SOLID,1,RGB(255,255,255));

	CPen*pPenOld=pDC->SelectObject(&pen0);
	pDC->MoveTo(iX0,iY-1);
	pDC->LineTo(iX1,iY-1);

	pDC->SelectObject(&pen1);
	pDC->MoveTo(iX0,iY+1);
	pDC->LineTo(iX1,iY+1);

	pDC->SelectObject(pPenOld);
}

inline
void CMenuModifier::P_DrawSubMenu(CDC*pDC,CRect rcItem,DRAWITEMSTRUCT*pDIS)
{
	if(pDIS->itemAction==0)	return;

	MenuUser*pUser=(MenuUser*)pDIS->itemData;

	const UINT uState=pDIS->itemState;

	const BOOL bDisabled=((uState&ODS_DISABLED)||(uState&ODS_GRAYED))?1:0;
	const BOOL bChecked	=(uState&ODS_CHECKED)?1:0;

	CString strText, strR;
	strText = pUser->csText;
	const int pos = strText.Find('\t');
	if (pos > 0) {
		strR = strText.Right(strText.GetLength() - pos);
		strText = strText.Left(pos);
	}

	
	static int m_CXMENUCHECK = ::GetSystemMetrics(SM_CXMENUCHECK);
	



	if(bDisabled)
	{
		P_FillBkgnd(pDC,rcItem,clr_Item);
	}
	else
	if(uState&ODS_SELECTED)	
	{
		P_FillBkgnd(pDC,rcItem,clr_Selected);
	}
	else
	{
		P_FillBkgnd(pDC,rcItem,clr_Item);
	}

	if(pUser->csText.GetLength())
	{
		COLORREF clrTextOld;
		
		CRect rcTxt = rcItem;
		rcTxt.left+=(si_Head.cx+TXT_DIS);
		rcTxt.right = rcItem.right - 7;
		//const UINT uDT=DT_VCENTER|DT_SINGLELINE|DT_EXPANDTABS;

		if(bDisabled==0)
		{
			clrTextOld=pDC->SetTextColor(clr_TextEnabled);
			//pDC->DrawText(pUser->csText,&rcTxt,uDT);
			pDC->DrawText(strText, &rcTxt, DT_SINGLELINE | DT_EXPANDTABS | DT_LEFT | DT_VCENTER);
			if (!strR.IsEmpty()) {
				//rcTxt.right -= 7;
				pDC->DrawText(strR, &rcTxt, DT_SINGLELINE | DT_EXPANDTABS | DT_RIGHT | DT_VCENTER);
			}
		}
		else
		{
			clrTextOld=pDC->SetTextColor(RGB(255,255,255));
			CRect rc=rcTxt;
			rc.OffsetRect(1,1);
			//pDC->DrawText(pUser->csText,&rc,uDT);
			pDC->DrawText(strText, &rc, DT_SINGLELINE | DT_EXPANDTABS | DT_LEFT | DT_VCENTER);
			if (!strR.IsEmpty()) {
				//rc.right -= 7;
				pDC->DrawText(strR, &rc, DT_SINGLELINE | DT_EXPANDTABS | DT_RIGHT | DT_VCENTER);
			}

			pDC->SetTextColor(clr_TextDisabled);
			//pDC->DrawText(pUser->csText,&rcTxt,uDT);
			pDC->DrawText(strText, &rcTxt, DT_SINGLELINE | DT_EXPANDTABS | DT_LEFT | DT_VCENTER);
			if (!strR.IsEmpty()) {
				//rcTxt.right -= 7;
				pDC->DrawText(strR, &rcTxt, DT_SINGLELINE | DT_EXPANDTABS | DT_RIGHT | DT_VCENTER);
			}
		}

		pDC->SetTextColor(clrTextOld);
	}

	if(bDisabled==0)
	{
		if(uState&ODS_SELECTED)	
		{
			CRect rcBord=pDIS->rcItem;
			rcBord.DeflateRect(0,1,1,1);
			pDC->Draw3dRect(&rcBord,clr_SelectBorder,clr_SelectBorder);
		}
	}
	P_DrawImage(pDC,rcItem,pUser,bDisabled,bChecked);
}

inline
void CMenuModifier::P_DrawImage(CDC*pDC,CRect rcItem,MenuUser*pUser,BOOL bDisabled,BOOL bChecked)
{
	CRect rc=rcItem;
	rc.right=rc.left+si_Head.cx;
	rc.DeflateRect(IMG_PADL,IMG_PADT,IMG_PADR,IMG_PADB);

	if(bChecked&&b_UseObmBitmap)
	{
		obm_Checked.DrawObmCheckBox(pDC,rc);
		return;
	}

	BOOL b=pUser->img.DrawImage(pDC,rc.TopLeft(),si_Img2,i_BitsPix,bDisabled);
	if(bChecked)
	{
		if(b)
		{
			rc.top--;
			rc.right++;
			P_DrawSunkenBorder(pDC,rc);
		}
		else
		{
			obm_Checked.DrawObmCheckBox(pDC,rc);
		}
	}
}

inline 
void CMenuModifier::P_DrawSunkenBorder(CDC*pDC,CRect rc)
{
	rc.DeflateRect(-3,-2,-2,-2);
	pDC->Draw3dRect(&rc,RGB3(0),RGB3(255));
	rc.DeflateRect(1,1);
	pDC->Draw3dRect(&rc,RGB3(192),RGB3(192));
}

#undef IMG_PADL
#undef IMG_PADR
#undef IMG_PADT
#undef IMG_PADB

#undef TXT_DIS

#undef RGB3

#endif

