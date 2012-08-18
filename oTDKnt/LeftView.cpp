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

CString csNodeName = ""; //имя узла дерева

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
	// обнулять массивы зацикленностей и цветов
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
	//удаляем все записи перед открытием новых
	GetTreeCtrl().DeleteAllItems(); //(TVI_ROOT);
	m_mapColorFont.RemoveAll(); csaCycle.RemoveAll(); csaCycloStr.RemoveAll();
	if (pDoc->bClose) {   // если выбрана операция закрыть файл
		pDoc->bClose = FALSE;
		pDoc->iChkSig = FALSE;
		pDoc->iChkDia = FALSE;
		pDoc->iOpenSig = FALSE;
		pDoc->iChkWord=FALSE;
	}
	else {    //начинаем построение дерева обходом начал всех ветвей (имен выходов ТЭЗов)
		int i,l, x=0; 
		//POSITION i1;
		CString str, str1, strX;
		char buf[2];
		BOOL bfound = TRUE;
		HTREEITEM ayp = NULL;
		//задаем стиль выввода узлов деревьев
		GetTreeCtrl().ModifyStyle(LVS_TYPEMASK,TVS_LINESATROOT | TVS_HASLINES |
										TVS_HASBUTTONS | TVS_EDITLABELS );
		//настройка на текущий документ
		l = pDoc->GetArrSize(); //получаем размер массива всех выходов ТЭЗа
		if (l > 0) {
			l--; 
			for (i = 0; i <= l; i++) { //для каждого выхода
				str = pDoc->GetItemValue(i); //формируем его как начало ветви дерева
				HTREEITEM otdel=GetTreeCtrl().InsertItem(str.GetBuffer(12)); 
				while (bfound == TRUE) { //для всех выходов
					//ищем первый подузел данного выхода
					x++; itoa(x,buf,10); strX = buf + str;
					bfound = pDoc->secondsV.Lookup(strX,str1);
					if (str1 != "/") { //если это не конец ветви и
						if (bfound) { //подузел был найден, то вставляем его в дерево
							ayp = GetTreeCtrl().InsertItem(str1.GetBuffer(7),otdel);
							//формируем массив контроля цикла данными именами узлов
							csaCycle.Add(str);	csaCycle.Add(str1);
							//вызываем gRecur для формирования остальных 
							//подузлов данной ветви
							gRecur(str1, 1, ayp);	
							csaCycle.RemoveAll(); //обнуляем массив цикла для следующей ветви
						}//end if
					}//end if
					else bfound = FALSE;
				}//end while
				bfound = TRUE; x=0;
			}//end for
		}//end if
		if (csaCycloStr.GetSize()!=0) {
			// сообщение о наличии циклов в узле
			for (int x=0; x<csaCycloStr.GetSize();x++) {
				pDoc->bbggrr.InsertAt(1,G_INFORMATION);
				pDoc->SetString(1,"Узел  " + csaCycloStr.GetAt(x) + " имеет цикл",TRUE);
			} // next
			pDoc->UpdateAllViews(this); // обновить виды
		} // end if
	} // end else
}
//рекурсивная функция построения дерева ТЭЗов (одна из основных)
void CLeftView::gRecur(CString MyNameIs, int TotalStep, HTREEITEM hNode)
{
	char buf[2]; BOOL bCycle=FALSE;
	int i=0,iCycleSize;
	CString str1, strX,value;
	HTREEITEM ayp = NULL; BOOL bfound=TRUE;
	//взять число подузлов
	//iTS = gTotalCount(MyNameIs);
	COTDKDoc* pDoc = GetDocument(); //настроиться на текущий документ
	ASSERT_VALID(pDoc);
	//для всех подузлов
	//while (TotalStep != (iTS + 1)) {
	while (bfound) {
		//взять имя подузла для переданного в параметре функции узла
		itoa(TotalStep,buf,10);		strX = buf + MyNameIs;
		bfound = pDoc->secondsV.Lookup(strX,str1);
		if (bfound) {
			//проверка на цикл для выбранного подузла
			iCycleSize = csaCycle.GetSize();
			for (i=0;i<iCycleSize;++i) {
				value=csaCycle.GetAt(i); //если цикл обнаружен
				if (value.CompareNoCase(str1)==0) {
					str1 += "*"; bCycle = TRUE;//то оборвать цикл
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
			if (str1 != "/") { //если нет конца ветви
				//то устанавливаем подузел в дерево
				ayp=GetTreeCtrl().InsertItem(str1.GetBuffer(7),hNode);
				if (bCycle)	bCycle=FALSE;//в случае цикла сдвигаем массив цикла
				else { 	
					csaCycle.Add(str1);  //дополняем массив для поиска цикла новым узлом
					gRecur(str1, 1, ayp);	//рекурсивный вызов для следующего узла
				} 
			}
		}
		TotalStep++;		
	}//while 
	//если ветвь закончена очистить массив проверки цикла (&& TotalStep == (iTS + 1))
	if (TotalStep > 1) csaCycle.RemoveAt(csaCycle.GetSize()-1);
}
//поиск количества подузлов для данного (переданного в параметре) узла
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
//отработка функции тестирования в случае нажатия клавиши пробел
void CLeftView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CStdioFile Fl;
	CString s, csDS;
	LPTSTR ref;
	BOOL bDOrS = TRUE;
	COTDKDoc* pDoc = GetDocument(); //подсоединяемся к текущему документу
	ASSERT_VALID(pDoc);
	//если нажата клавиша пробел
   	if (nChar == VK_SPACE && nRepCnt == 1) {
		//сообщаем в статусную строку о начале тестирования
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("Тест!");
		if (pDoc->iChkDia == 1) { s = "diatess.exe "; csDS = ".dia"; 
			bDOrS=FALSE;
		}
		else { s = "sigteze.exe "; csDS = ".sig"; bDOrS=TRUE; }
		csNodeName =GetTreeCtrl().GetItemText(GetTreeCtrl(). \
						GetNextItem(TVI_ROOT,TVGN_CARET)); //получаем имя обрабатываемой ветви
		//проверка на обрыв цикла
		if (csNodeName.Right(1).Compare("*") == 0)
				 csNodeName=csNodeName.Mid(0,csNodeName.GetLength()-1);
		//если файл сигнатур данного узла обнаружен, то выполняем процесс тестирования
		if (Fl.Open(csNodeName + csDS, CFile::modeRead)) {
			Fl.Close();	s += csNodeName;	s += csDS;
			ref = s.GetBuffer(s.GetLength());
			//чистим tempo.s файл
			Fl.Open("tempo.s", CFile::modeCreate);		Fl.Close(); 
			//Запуск тесирования файла сигнатуры и получение результата
			gFuncTest(ref, bHideShowTest);	s = gResultTest(bDOrS);
			// установить строку 2 	
			//если тест НЕ прошел
			if (s != "") {
				//выделяем цветом ошибки текст и
				pDoc->bbggrr.InsertAt(1,G_ALERT);
				//сообщаем об ошибке
				pDoc->SetString(1,"Ошибка в узле " + csNodeName + ": " + s,TRUE);
				//выделяем ошибочный узел красным цветом
				SetItemColor( GetTreeCtrl().GetSelectedItem(), RGB(255,0,0));
				GetTreeCtrl().SelectItem(
					GetTreeCtrl().GetChildItem(GetTreeCtrl().GetSelectedItem()));
				//выдаем предупреждающий звук
				MessageBeep(MB_ICONEXCLAMATION);
			}
			else { //если тест прошел
				//задаем обычный цвет сообщения
				pDoc->bbggrr.InsertAt(1,G_MESSAGE);
				//и сообщаем, что все нормально
				pDoc->SetString(1,"Конец теста узла " + csNodeName,TRUE);
				//---------------установка цвета узла и его подузлов-------
				HTREEITEM hItemGreen = GetTreeCtrl().GetSelectedItem();
				SetItemColor(hItemGreen , RGB(0,255,0));
				//поиск всех таких узлов по всему дереву и
				//их окрашивание (пока приостановлен)
				/*hItemGreen = GetTreeCtrl().GetRootItem();
				while (hItemGreen != NULL) {
					gRecTreeColor(hItemGreen,csNodeName);
					hItemGreen = GetTreeCtrl().GetNextSiblingItem(hItemGreen);
				}*/
				gColorItem(hItemGreen);
				GetTreeCtrl().SelectItem(
					GetTreeCtrl().GetNextSiblingItem(hItemGreen));
				MessageBeep(MB_OK); //звуковое сообщение
				//-----------------___________________________--------------
			}//end else
		}//end if
		else { //если файл сигнатур данного узла НЕ обнаружен,
			//сообщаем об отсутсвии файла сигнатур данного узла
			pDoc->bbggrr.InsertAt(1,G_INFORMATION);
			pDoc->SetString(1,"Файла " + csNodeName + csDS + " несуществует",TRUE);
			//окрашиваем узел в соответствующий цвет
			SetItemColor( GetTreeCtrl().GetSelectedItem(), RGB(200,180,55));
			MessageBeep(MB_ICONASTERISK); //подаем звуковой сигнал
		}//end else
		pDoc->UpdateAllViews(this); // обновить виды
		//в статусной строке сообщить об окончании тестирования
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("Будь готов");
	}//end if
	//продолжить выполнение если были нажаты другие клавиши (не пробел)
	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CLeftView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// если мы нажали правую кнопку мыши на конретном узле
	GetTreeCtrl().SelectItem(GetTreeCtrl().HitTest(point,NULL));
	//то выполнить операцию тестирования для него, как еслибы был нажат пробел
	OnKeyDown(VK_SPACE, 1, NULL);
	CTreeView::OnRButtonDown(nFlags, point);
}
//вспомогательная функция для окрашивания узлов
//заносит в массив цветов узлов для данного узла указанный цвет
void CLeftView::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if( !m_mapColorFont.Lookup( hItem, cf ) )
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
}
//перерисовываем дерево в соответсвии с массивом цветов m_mapColorFont
//который мы задали по результатам тестирования
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

	//начинаем проход по всему дереву
	HTREEITEM hItem = GetTreeCtrl().GetFirstVisibleItem();
	//HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	//подсчитываем количество узлов
	int n = GetTreeCtrl().GetVisibleCount()+1;
	while( hItem && n--) //для всех узлов выполняем окрас
	{
		CRect rect;

		// Do not meddle with selected items or drop highlighted items
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;
		//подбираем цвет из массива
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
//установка цвета для указанного в параметре узла дерева и его подузлов
//рекурсивная функция
void CLeftView::gColorItem(HTREEITEM hItemGreen)
{
	HTREEITEM hItemChGreen = GetTreeCtrl().GetChildItem(hItemGreen); //поиск подузлов
	//для всех найденных подузлов
	if (hItemChGreen != NULL) {
		while (hItemChGreen != NULL) {
			SetItemColor(hItemChGreen , RGB(0,255,0)); //зеленить
			gColorItem(hItemChGreen);
			hItemChGreen = GetTreeCtrl().GetNextSiblingItem(hItemChGreen);
		}
	}
}
//окрашивание узлов в цвет по результатам тестирования по всем ветвям
//дерева. .Пока не задействована. Слишком перегружает тестирование по времени.
void CLeftView::gRecTreeColor(HTREEITEM hItemGreen, CString csNodeName)
{
	CString csNN = GetTreeCtrl().GetItemText(hItemGreen); //проходим по дереву
	//если имя заданного узла совпадает с текущим, то
	if (csNN.CompareNoCase(csNodeName) == 0) gColorItem(hItemGreen);
	HTREEITEM hItemChGreen = GetTreeCtrl().GetChildItem(hItemGreen);
	while (hItemGreen != NULL) {
		gRecTreeColor(hItemChGreen,csNodeName); //красим с подузлами
		hItemChGreen = GetTreeCtrl().GetNextSiblingItem(hItemChGreen);
	}
}

void CLeftView::gFindItem(CString csFI) 
{
	//получаем имя обрабатываемой ветви
	BOOL bt=FALSE;
	//в статусной строке сообщить о начале поиска узла
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("Идет поиск");
	HTREEITEM hItemCh=GetTreeCtrl().GetNextItem(TVI_ROOT,TVGN_CARET); // берем текущий узел
	CString csNN = GetTreeCtrl().GetItemText(hItemCh); // имя текущего узла
	while (hItemCh != NULL) {
		bt = gRecFind(hItemCh, csFI); // вызываем рекурсивный поиск
		if (bt) break; // если нашел, выходим
		hItemCh = GetTreeCtrl().GetNextSiblingItem(hItemCh); // если не нашел, берем следующий узел
	}
	//в статусной строке сообщить об окончании поиска узла
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("Будь готов");
}

BOOL CLeftView::gRecFind(HTREEITEM hItemG, CString csFN)
{
	BOOL bx=FALSE;
	CString csNN = GetTreeCtrl().GetItemText(hItemG); //проходим по дереву
	//если имя заданного узла не совпадает с текущим, то
	if (csNN.CompareNoCase(csFN) != 0) { // сравниваем с именем запрашиваемого узла
		HTREEITEM hItemCh = GetTreeCtrl().GetChildItem(hItemG); // берем подузел
		while (hItemCh != NULL) {
			bx=gRecFind(hItemCh,csFN); // запускаем рекурсивный поиск
			if (bx) break; // если нашел выходим
			hItemCh = GetTreeCtrl().GetNextSiblingItem(hItemCh); // не нашел, берем следующий узел
		}
		//bx=FALSE; // разрешение этого параметра позволяет искать все вхождения узла в дереве
	}
	else { //выделяем эту запись и выходим
			bx = GetTreeCtrl().SelectItem(hItemG);
			bx= TRUE;
	}
	return bx;
}
