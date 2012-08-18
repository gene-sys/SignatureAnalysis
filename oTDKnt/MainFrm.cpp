// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "oTDK.h"
//#include "string.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "OTDKDoc.h"
#include "oTDKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
//
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(IDS_STRINGm, OnUpdateString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// индикаторы строки статуса
static UINT indicators[] =
{
	IDS_STRINGm,
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// начальное сообщение в статусную строку
	csTest = "Будь готов";
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// загрузка панели инструментов
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	m_wndReBar.SetBarStyle(m_wndReBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	// загрузка статусной строки
	CClientDC dc(this);
	SIZE size = dc.GetTextExtent(csTest);
	int index = m_wndStatusBar.CommandToIndex(IDS_STRINGm);
	m_wndStatusBar.SetPaneInfo(index,IDS_STRINGm, SBPS_NORMAL, size.cx);
	index = m_wndStatusBar.CommandToIndex(ID_SEPARATOR);
	m_wndStatusBar.SetPaneInfo(index,ID_SEPARATOR, SBPS_STRETCH, NULL);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;
    //начальные размеры двух подокон текущего документа
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(200, 200), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(COTDKView), CSize(200, 200), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	return CFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnUpdateString(CCmdUI *pCmdUI) 
{	//активизировать обновление статусной строки
	pCmdUI->Enable(); 
	//pCmdUI->SetText(csTest);
}

void CMainFrame::SetStatusBarMes(CString csT)
{
	CClientDC dc(this);
	csTest = csT;
	//взять текст для статусной строки
	SIZE size = dc.GetTextExtent(csTest);
	//формирование статусной строки
	int index = m_wndStatusBar.CommandToIndex(IDS_STRINGm);
	m_wndStatusBar.SetPaneInfo(index,IDS_STRINGm, SBPS_NORMAL, size.cx);
	//собственной вставка текста в статусную строку
	m_wndStatusBar.SetPaneText(index,csTest,TRUE);
	//m_wndStatusBar.UpdateData(NULL);
}

