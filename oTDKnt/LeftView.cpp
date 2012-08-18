// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "oTDK.h"

#include "OTDKDoc.h"
#include "LeftView.h"
#include "MainFrm.h"

#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString csNodeName = ""; //��� ���� ������

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// �������� ������� �������������� � ������
	csaCycle.RemoveAll();
	csaCycloStr.RemoveAll();
	m_mapColorFont.RemoveAll(); 
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CTreeView::OnDraw(pDC);
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

COTDKDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COTDKDoc)));
	return (COTDKDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{ 
	COTDKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//������� ��� ������ ����� ��������� �����
	GetTreeCtrl().DeleteAllItems(); //(TVI_ROOT);
	m_mapColorFont.RemoveAll(); csaCycle.RemoveAll(); csaCycloStr.RemoveAll();
	if (pDoc->bClose) {   // ���� ������� �������� ������� ����
		pDoc->bClose = FALSE;
		pDoc->iChkSig = FALSE;
		pDoc->iChkDia = FALSE;
		pDoc->iOpenSig = FALSE;
		pDoc->iChkWord=FALSE;
	}
	else {    //�������� ���������� ������ ������� ����� ���� ������ (���� ������� �����)
		int i,l, x=0; 
		//POSITION i1;
		CString str, str1, strX;
		char buf[2];
		BOOL bfound = TRUE;
		HTREEITEM ayp = NULL;
		//������ ����� ������� ����� ��������
		GetTreeCtrl().ModifyStyle(LVS_TYPEMASK,TVS_LINESATROOT | TVS_HASLINES |
										TVS_HASBUTTONS | TVS_EDITLABELS );
		//��������� �� ������� ��������
		l = pDoc->GetArrSize(); //�������� ������ ������� ���� ������� ����
		if (l > 0) {
			l--; 
			for (i = 0; i <= l; i++) { //��� ������� ������
				str = pDoc->GetItemValue(i); //��������� ��� ��� ������ ����� ������
				HTREEITEM otdel=GetTreeCtrl().InsertItem(str.GetBuffer(12)); 
				while (bfound == TRUE) { //��� ���� �������
					//���� ������ ������� ������� ������
					x++; itoa(x,buf,10); strX = buf + str;
					bfound = pDoc->secondsV.Lookup(strX,str1);
					if (str1 != "/") { //���� ��� �� ����� ����� �
						if (bfound) { //������� ��� ������, �� ��������� ��� � ������
							ayp = GetTreeCtrl().InsertItem(str1.GetBuffer(7),otdel);
							//��������� ������ �������� ����� ������� ������� �����
							csaCycle.Add(str);	csaCycle.Add(str1);
							//�������� gRecur ��� ������������ ��������� 
							//�������� ������ �����
							gRecur(str1, 1, ayp);	
							csaCycle.RemoveAll(); //�������� ������ ����� ��� ��������� �����
						}//end if
					}//end if
					else bfound = FALSE;
				}//end while
				bfound = TRUE; x=0;
			}//end for
		}//end if
		if (csaCycloStr.GetSize()!=0) {
			// ��������� � ������� ������ � ����
			for (int x=0; x<csaCycloStr.GetSize();x++) {
				pDoc->bbggrr.InsertAt(1,G_INFORMATION);
				pDoc->SetString(1,"����  " + csaCycloStr.GetAt(x) + " ����� ����",TRUE);
			} // next
			pDoc->UpdateAllViews(this); // �������� ����
		} // end if
	} // end else
}
//����������� ������� ���������� ������ ����� (���� �� ��������)
void CLeftView::gRecur(CString MyNameIs, int TotalStep, HTREEITEM hNode)
{
	char buf[2]; BOOL bCycle=FALSE;
	int i=0,iCycleSize;
	CString str1, strX,value;
	HTREEITEM ayp = NULL; BOOL bfound=TRUE;
	//����� ����� ��������
	//iTS = gTotalCount(MyNameIs);
	COTDKDoc* pDoc = GetDocument(); //����������� �� ������� ��������
	ASSERT_VALID(pDoc);
	//��� ���� ��������
	//while (TotalStep != (iTS + 1)) {
	while (bfound) {
		//����� ��� ������� ��� ����������� � ��������� ������� ����
		itoa(TotalStep,buf,10);		strX = buf + MyNameIs;
		bfound = pDoc->secondsV.Lookup(strX,str1);
		if (bfound) {
			//�������� �� ���� ��� ���������� �������
			iCycleSize = csaCycle.GetSize();
			for (i=0;i<iCycleSize;++i) {
				value=csaCycle.GetAt(i); //���� ���� ���������
				if (value.CompareNoCase(str1)==0) {
					str1 += "*"; bCycle = TRUE;//�� �������� ����
					if (bCycleCheck) {
						bool bx=false;
						for (int x=0;x<csaCycloStr.GetSize();x++) {
							if (str1.CompareNoCase(csaCycloStr.GetAt(x))==0) { bx=true; break;}
						}
						if (!bx) csaCycloStr.Add(str1);
					}
					break;
				}
			}; i=0;
			//
			if (str1 != "/") { //���� ��� ����� �����
				//�� ������������� ������� � ������
				ayp=GetTreeCtrl().InsertItem(str1.GetBuffer(7),hNode);
				if (bCycle)	bCycle=FALSE;//� ������ ����� �������� ������ �����
				else { 	
					csaCycle.Add(str1);  //��������� ������ ��� ������ ����� ����� �����
					gRecur(str1, 1, ayp);	//����������� ����� ��� ���������� ����
				} 
			}
		}
		TotalStep++;		
	}//while 
	//���� ����� ��������� �������� ������ �������� ����� (&& TotalStep == (iTS + 1))
	if (TotalStep > 1) csaCycle.RemoveAt(csaCycle.GetSize()-1);
}
//����� ���������� �������� ��� ������� (����������� � ���������) ����
int CLeftView::gTotalCount(CString MyNameIs)
{
	CString value,strX;
	int x = 0, y = 0;
	char buf[2];
	COTDKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	BOOL bfound = TRUE;
	while (bfound) {
		x++;
		itoa(x,buf,10);
		strX = buf + MyNameIs;
		bfound = pDoc->secondsV.Lookup(strX,value);
		if (bfound) y++;
	}
return y;
}
//��������� ������� ������������ � ������ ������� ������� ������
void CLeftView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CStdioFile Fl;
	CString s, csDS;
	LPTSTR ref;
	BOOL bDOrS = TRUE;
	COTDKDoc* pDoc = GetDocument(); //�������������� � �������� ���������
	ASSERT_VALID(pDoc);
	//���� ������ ������� ������
   	if (nChar == VK_SPACE && nRepCnt == 1) {
		//�������� � ��������� ������ � ������ ������������
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("����!");
		if (pDoc->iChkDia == 1) { s = "diatess.exe "; csDS = ".dia"; 
			bDOrS=FALSE;
		}
		else { s = "sigteze.exe "; csDS = ".sig"; bDOrS=TRUE; }
		csNodeName =GetTreeCtrl().GetItemText(GetTreeCtrl(). \
						GetNextItem(TVI_ROOT,TVGN_CARET)); //�������� ��� �������������� �����
		//�������� �� ����� �����
		if (csNodeName.Right(1).Compare("*") == 0)
				 csNodeName=csNodeName.Mid(0,csNodeName.GetLength()-1);
		//���� ���� �������� ������� ���� ���������, �� ��������� ������� ������������
		if (Fl.Open(csNodeName + csDS, CFile::modeRead)) {
			Fl.Close();	s += csNodeName;	s += csDS;
			ref = s.GetBuffer(s.GetLength());
			//������ tempo.s ����
			Fl.Open("tempo.s", CFile::modeCreate);		Fl.Close(); 
			//������ ����������� ����� ��������� � ��������� ����������
			gFuncTest(ref, bHideShowTest);	s = gResultTest(bDOrS);
			// ���������� ������ 2 	
			//���� ���� �� ������
			if (s != "") {
				//�������� ������ ������ ����� �
				pDoc->bbggrr.InsertAt(1,G_ALERT);
				//�������� �� ������
				pDoc->SetString(1,"������ � ���� " + csNodeName + ": " + s,TRUE);
				//�������� ��������� ���� ������� ������
				SetItemColor( GetTreeCtrl().GetSelectedItem(), RGB(255,0,0));
				GetTreeCtrl().SelectItem(
					GetTreeCtrl().GetChildItem(GetTreeCtrl().GetSelectedItem()));
				//������ ��������������� ����
				MessageBeep(MB_ICONEXCLAMATION);
			}
			else { //���� ���� ������
				//������ ������� ���� ���������
				pDoc->bbggrr.InsertAt(1,G_MESSAGE);
				//� ��������, ��� ��� ���������
				pDoc->SetString(1,"����� ����� ���� " + csNodeName,TRUE);
				//---------------��������� ����� ���� � ��� ��������-------
				HTREEITEM hItemGreen = GetTreeCtrl().GetSelectedItem();
				SetItemColor(hItemGreen , RGB(0,255,0));
				//����� ���� ����� ����� �� ����� ������ �
				//�� ����������� (���� �������������)
				/*hItemGreen = GetTreeCtrl().GetRootItem();
				while (hItemGreen != NULL) {
					gRecTreeColor(hItemGreen,csNodeName);
					hItemGreen = GetTreeCtrl().GetNextSiblingItem(hItemGreen);
				}*/
				gColorItem(hItemGreen);
				GetTreeCtrl().SelectItem(
					GetTreeCtrl().GetNextSiblingItem(hItemGreen));
				MessageBeep(MB_OK); //�������� ���������
				//-----------------___________________________--------------
			}//end else
		}//end if
		else { //���� ���� �������� ������� ���� �� ���������,
			//�������� �� ��������� ����� �������� ������� ����
			pDoc->bbggrr.InsertAt(1,G_INFORMATION);
			pDoc->SetString(1,"����� " + csNodeName + csDS + " ������������",TRUE);
			//���������� ���� � ��������������� ����
			SetItemColor( GetTreeCtrl().GetSelectedItem(), RGB(200,180,55));
			MessageBeep(MB_ICONASTERISK); //������ �������� ������
		}//end else
		pDoc->UpdateAllViews(this); // �������� ����
		//� ��������� ������ �������� �� ��������� ������������
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("���� �����");
	}//end if
	//���������� ���������� ���� ���� ������ ������ ������� (�� ������)
	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLeftView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// ���� �� ������ ������ ������ ���� �� ��������� ����
	GetTreeCtrl().SelectItem(GetTreeCtrl().HitTest(point,NULL));
	//�� ��������� �������� ������������ ��� ����, ��� ������ ��� ����� ������
	OnKeyDown(VK_SPACE, 1, NULL);
	CTreeView::OnRButtonDown(nFlags, point);
}
//��������������� ������� ��� ����������� �����
//������� � ������ ������ ����� ��� ������� ���� ��������� ����
void CLeftView::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
}
//�������������� ������ � ����������� � �������� ������ m_mapColorFont
//������� �� ������ �� ����������� ������������
void CLeftView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);

	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	memDC.SelectObject( &bitmap );
	
	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();
	


	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	//�������� ������ �� ����� ������
	HTREEITEM hItem = GetTreeCtrl().GetFirstVisibleItem();
	//HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	//������������ ���������� �����
	int n = GetTreeCtrl().GetVisibleCount()+1;
	while( hItem && n--) //��� ���� ����� ��������� �����
	{
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;
		//��������� ���� �� �������
		if ( !(GetTreeCtrl().GetItemState( hItem, selflag ) & selflag ) 
			&& m_mapColorFont.Lookup( hItem, cf ))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if( cf.logfont.lfFaceName[0] != '\0' ) 
			{
				logfont = cf.logfont;
			}
			else
			{
				// No font specified, so use window font
				CFont *pFont = GetFont();
				pFont->GetLogFont( &logfont );
			}

			//if( GetItemBold( hItem ) )	logfont.lfWeight = 700;
			fontDC.CreateFontIndirect( &logfont );
			pFontDC = memDC.SelectObject( &fontDC );

			if( cf.color != (COLORREF)-1 )
				memDC.SetTextColor( cf.color );

			CString sItem = GetTreeCtrl().GetItemText( hItem );

			GetTreeCtrl().GetItemRect( hItem, &rect, TRUE );
			memDC.SetBkColor( GetSysColor( COLOR_WINDOW ) );
			memDC.TextOut( rect.left+2, rect.top+1, sItem );
			
			memDC.SelectObject( pFontDC );
		}
		hItem = GetTreeCtrl().GetNextVisibleItem( hItem );
	}


	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, 
				rcClip.left, rcClip.top, SRCCOPY );
	
	// Do not call CTreeView::OnPaint() for painting messages
}
//��������� ����� ��� ���������� � ��������� ���� ������ � ��� ��������
//����������� �������
void CLeftView::gColorItem(HTREEITEM hItemGreen)
{
	HTREEITEM hItemChGreen = GetTreeCtrl().GetChildItem(hItemGreen); //����� ��������
	//��� ���� ��������� ��������
	if (hItemChGreen != NULL) {
		while (hItemChGreen != NULL) {
			SetItemColor(hItemChGreen , RGB(0,255,0)); //��������
			gColorItem(hItemChGreen);
			hItemChGreen = GetTreeCtrl().GetNextSiblingItem(hItemChGreen);
		}
	}
}
//����������� ����� � ���� �� ����������� ������������ �� ���� ������
//������. .���� �� �������������. ������� ����������� ������������ �� �������.
void CLeftView::gRecTreeColor(HTREEITEM hItemGreen, CString csNodeName)
{
	CString csNN = GetTreeCtrl().GetItemText(hItemGreen); //�������� �� ������
	//���� ��� ��������� ���� ��������� � �������, ��
	if (csNN.CompareNoCase(csNodeName) == 0) gColorItem(hItemGreen);
	HTREEITEM hItemChGreen = GetTreeCtrl().GetChildItem(hItemGreen);
	while (hItemGreen != NULL) {
		gRecTreeColor(hItemChGreen,csNodeName); //������ � ���������
		hItemChGreen = GetTreeCtrl().GetNextSiblingItem(hItemChGreen);
	}
}

void CLeftView::gFindItem(CString csFI) 
{
	//�������� ��� �������������� �����
	BOOL bt=FALSE;
	//� ��������� ������ �������� � ������ ������ ����
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("���� �����");
	HTREEITEM hItemCh=GetTreeCtrl().GetNextItem(TVI_ROOT,TVGN_CARET); // ����� ������� ����
	CString csNN = GetTreeCtrl().GetItemText(hItemCh); // ��� �������� ����
	while (hItemCh != NULL) {
		bt = gRecFind(hItemCh, csFI); // �������� ����������� �����
		if (bt) break; // ���� �����, �������
		hItemCh = GetTreeCtrl().GetNextSiblingItem(hItemCh); // ���� �� �����, ����� ��������� ����
	}
	//� ��������� ������ �������� �� ��������� ������ ����
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("���� �����");
}

BOOL CLeftView::gRecFind(HTREEITEM hItemG, CString csFN)
{
	BOOL bx=FALSE;
	CString csNN = GetTreeCtrl().GetItemText(hItemG); //�������� �� ������
	//���� ��� ��������� ���� �� ��������� � �������, ��
	if (csNN.CompareNoCase(csFN) != 0) { // ���������� � ������ �������������� ����
		HTREEITEM hItemCh = GetTreeCtrl().GetChildItem(hItemG); // ����� �������
		while (hItemCh != NULL) {
			bx=gRecFind(hItemCh,csFN); // ��������� ����������� �����
			if (bx) break; // ���� ����� �������
			hItemCh = GetTreeCtrl().GetNextSiblingItem(hItemCh); // �� �����, ����� ��������� ����
		}
		//bx=FALSE; // ���������� ����� ��������� ��������� ������ ��� ��������� ���� � ������
	}
	else { //�������� ��� ������ � �������
			bx = GetTreeCtrl().SelectItem(hItemG);
			bx= TRUE;
	}
	return bx;
}
