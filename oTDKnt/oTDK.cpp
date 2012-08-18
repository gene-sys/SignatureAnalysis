// oTDK.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "oTDK.h"

#include "MainFrm.h"
#include "oTDKDoc.h"
#include "LeftView.h"
#include "TreeMake.h"
#include "WorkINI.h"

#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COTDKApp
// определение глобальных переменных
// используемых в программе
CString csHead = "Тестирование v1.80 ";
CString r_Opn =  "WorkSpace.ini"; //путь файла деревьев
CString strWR = "";
CString strTF = "";
CString strTD = "";
BOOL bHideShowTest = FALSE; //скрыть FALSE или показывать окно тесирования
BOOL bCycleCheck = FALSE; // проверять TRUE или не проверять FALSE дерево при открытии на наличие циклов
BOOL bAutoCheck = FALSE; //скрыть FALSE или показывать окно тесирования
int intNT = 0;
UINT iCountTest = 0; //количество тестов в файлах сигнатур (обычно 3)
UINT iCountDTest = 0; //количество тестов в файлах диатеста (обычно 5)
COLORREF G_WRITESIG = 0x00FF0000; //цвет формирования файлов сигнатур
COLORREF G_ALERT = 0x000000FF; //предупреждающий цвет
COLORREF G_INFORMATION = 0x00007A7A; //информационный цвет
COLORREF G_MESSAGE = 0x00010101; //цвет сообщений

BEGIN_MESSAGE_MAP(COTDKApp, CWinApp)
	//{{AFX_MSG_MAP(COTDKApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_WorkSpace, OnWorkSpace)
	ON_COMMAND(IDD_TREES, OnTrees)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COTDKApp construction

COTDKApp::COTDKApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COTDKApp object

COTDKApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COTDKApp initialization

BOOL COTDKApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	// формирование рабочего окна программы
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COTDKDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLeftView));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW); //показать программу после загрузки в память
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetWindowText(csHead); //вписать название программы в заголовок окна
	gWorkWithWINI(FALSE); //обработать (считать) ini-файл
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//класс для вызова диалогового окна сообщения "О программе"
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void COTDKApp::OnAppAbout()
{
	CAboutDlg aboutDlg; //вызов сообщения "О программе"
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COTDKApp message handlers
//функция работы с ini-файлом через диалоговое окно в меню настроек
void COTDKApp::OnWorkSpace() 
{
	WorkINI WS;   // создаем объект класса диалогового окна
	WS.m_WorkDir = strWR; //.Mid(0,strWR.GetLength()-6);
	WS.m_CopyTemp = strTF;
	WS.m_TempDia = strTD;
	WS.m_NumTest = iCountTest;
	WS.m_NumDtest = iCountDTest; 
	WS.m_SamoCheck =  bAutoCheck;
	WS.m_hide = bHideShowTest;
	WS.m_cycler = bCycleCheck;
	if (WS.DoModal()==IDOK ) {
		strWR = WS.m_WorkDir;
		strTF = WS.m_CopyTemp;
		strTD = WS.m_TempDia;
		iCountTest = WS.m_NumTest;
		iCountDTest = WS.m_NumDtest;
		bHideShowTest = WS.m_hide;
		bCycleCheck = WS.m_cycler;
		bAutoCheck = WS.m_SamoCheck;
		gWorkWithWINI(TRUE);
		//CString strWRtempo = strWR + "\\*.tre";
		//r_Opn = strWRtempo;
	}
	else {
		//AfxMessageBox("Cancel");     // пользователь выбрал Cansel	
	}
}
//обработка INI-файла: запись или чтение
void COTDKApp::gWorkWithWINI(BOOL bWrite)
{
	CStdioFile myFile;
	CString strTempo;
	CHAR inBuf[255];
	CString pszFileName = r_Opn; //имя INI-файла всегда это
	//
	CFileException fileException; //
	//если найден INI-файл, то
	if ( !myFile.Open( pszFileName, CStdioFile::modeReadWrite |
								CStdioFile::typeText), &fileException )
	{
		TRACE( "Файл %s необнаружен в текушем каталоге, error = %u\n",
									pszFileName, fileException.m_cause );
	};
	pszFileName = myFile.GetFilePath(); //берем имя файла с путем и
	r_Opn=pszFileName;
	myFile.Close(); 
	//если задана запись (т.е. применить изменения), то
	if (bWrite) { //пишем в соответствующие пункты соответствующие значения
		WritePrivateProfileString ("PATH", "WorkRoot", strWR, pszFileName);
		WritePrivateProfileString ("PATH", "LastFile", "", pszFileName);
		WritePrivateProfileString ("TEMPLATE", "TemplFile", strTF, pszFileName);
		WritePrivateProfileString ("TEMPLATE", "TemplDia", 	strTD, pszFileName);
		CString strTemp;
		strTemp.Format("%d",iCountTest);
		WritePrivateProfileString ("TEMPLATE", "NumTest", strTemp, pszFileName);
		strTemp.Format("%d",iCountDTest);
		WritePrivateProfileString ("TEMPLATE", "NumDtest", strTemp, pszFileName);
		strTemp.Format("%d",bAutoCheck);
		WritePrivateProfileString ("TEMPLATE", "AutoCheck", strTemp, pszFileName);
		strTemp.Format("%d",bHideShowTest);
		WritePrivateProfileString ("TEST", "HideShow", strTemp, pszFileName); 
		strTemp.Format("%d",bCycleCheck);
		WritePrivateProfileString ("TEST", "CycleCheck", strTemp, pszFileName); 
	}
	else { //если чтение (при открытии), то счтиываем соответствующие значения
	  GetPrivateProfileString ("PATH", "WorkRoot", "", inBuf, 255, pszFileName);   
	  strWR = inBuf;
	  GetPrivateProfileString ("TEMPLATE", "TemplFile", "", inBuf, 255, pszFileName); 
	  strTF = inBuf;
	  GetPrivateProfileString ("TEMPLATE", "TemplDia", "", inBuf, 255, pszFileName); 
	  strTD = inBuf;
	  GetPrivateProfileString ("TEMPLATE", "NumTest", "", inBuf, 255, pszFileName);
	  intNT = atoi(inBuf);
	  iCountTest = intNT;
	  GetPrivateProfileString ("TEMPLATE", "NumDtest", "", inBuf, 255, pszFileName);
	  iCountDTest = atoi(inBuf);
	  GetPrivateProfileString ("TEMPLATE", "AutoCheck", "", inBuf, 255, pszFileName);
	  bAutoCheck = (BOOL)atoi(inBuf);
	  GetPrivateProfileString ("TEST", "HideShow", "", inBuf, 255, pszFileName); 
	  bHideShowTest = (BOOL)atoi(inBuf);
	  GetPrivateProfileString ("TEST", "CycleCheck", "", inBuf, 255, pszFileName); 
	  bCycleCheck = (BOOL)atoi(inBuf);
	}
}

void COTDKApp::OnTrees() 
{
	CTreeMake CTM;  //открыть диалоговое окно создания новых фалов деревьев
	CTM.m_namefile = "filename";
	CTM.m_startnew = TRUE; 
	CTM.DoModal();
}

