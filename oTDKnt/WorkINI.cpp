// WorkINI.cpp : implementation file
//

#include "stdafx.h"
#include "oTDK.h"
#include "WorkINI.h"
#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WorkINI dialog


WorkINI::WorkINI(CWnd* pParent /*=NULL*/)
	: CDialog(WorkINI::IDD, pParent)
{
	//{{AFX_DATA_INIT(WorkINI)
	m_CopyTemp = _T("");
	m_WorkDir = _T("");
	m_NumTest = 0;
	m_hide = FALSE;
	m_TempDia = _T("");
	m_NumDtest = 0;
	m_SamoCheck = FALSE;
	m_cycler = FALSE;
	//}}AFX_DATA_INIT
}


void WorkINI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WorkINI)
	DDX_Text(pDX, IDC_EDIT3, m_CopyTemp);
	DDX_Text(pDX, IDC_EDIT1, m_WorkDir);
	DDX_Text(pDX, IDC_EDIT4, m_NumTest);
	DDV_MinMaxInt(pDX, m_NumTest, 1, 3);
	DDX_Check(pDX, IDC_HIDETEST, m_hide);
	DDX_Text(pDX, IDC_EDIT5, m_TempDia);
	DDX_Text(pDX, IDC_EDIT6, m_NumDtest);
	DDV_MinMaxInt(pDX, m_NumDtest, 1, 5);
	DDX_Check(pDX, IDC_CHECK1, m_SamoCheck);
	DDX_Check(pDX, IDC_HIDETEST2, m_cycler);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WorkINI, CDialog)
	//{{AFX_MSG_MAP(WorkINI)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WorkINI message handlers
//Формирование строки результата работы теста
CString gResultTest(BOOL bDiaOrSig)
{
	CString s;
	CStdioFile Fl;
	int lenText, i;
	char buf[6], buf1[9], bufd[255]; 
	//unsigned int x; 
	BYTE x;
	//берем результат из файла tempo.s
	Fl.Open("tempo.s", CFile::typeBinary); //modeRead);
	lenText = (int)Fl.GetLength() + 1;
	// если имеем дело с сигнатрун.тестом, то здесь
	if (bDiaOrSig == TRUE) {
		if (lenText != 1) {
			Fl.Read(buf, lenText); i = 5; //lenText - 1;
			while (i >= 0) {
				x = (BYTE)buf[i];	_itoa(x, buf1, 16);
				if (strlen(buf1) == 1){ s += "0"; s += buf1[0]; }
				else { s+=buf1[0];  s += buf1[1]; }
				if (i == 2 || i == 4 ) s += "    "; //число пробелов влияет на сравнение
												//сигнатур 2ух проходов теста при записи сигнатур
				i--;
			}//while
		}//if 
		else s = "";
	} // иначе для диагностич. тестирования
	else {
		if (lenText != 1) {
			Fl.Read(bufd, lenText); i = 0; 
			while (i < lenText - 2) {
				for(int j = i + 4; j >= i; j--) {
					x = (BYTE)bufd[j];	_itoa(x, buf1, 16);
					if (j - i < 3) {
						if (strlen(buf1) == 1){ s += "0"; s += buf1[0]; }
						else { s += buf1[0];  s += buf1[1]; }
					}
				}// for
				i = i + 5; 
			}//while
		}//if 
		else s = "";
	}
	Fl.Close();
	return(s);
}
//Стартуем функциональный тест как отдельный процесс
void gFuncTest(LPTSTR ref, BOOL EnableShow)
{
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	LPTSTR lpszCommandLine;
	DWORD ExitCode;
	lpszCommandLine = ref;
	//memset(&StartupInfo,0,sizeof(STARTUPINFO)); // ?нужно ли это
	//StartupInfo.cb = sizeof(STARTUPINFO);       //
	::GetStartupInfo(&StartupInfo);
		//стартуем процесс
	//StartupInfo.hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (EnableShow != TRUE) {
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.wShowWindow = SW_HIDE; }
	::CreateProcess (NULL,
		lpszCommandLine, //командная строка
		NULL,     // атрибуты защиты
		NULL,     //
		FALSE,    
		0,         //CREATE_NEW_CONSOLE,
		NULL,     //использует среду вызывающего процесса
		NULL,     //тот же текущий каталог, что и у вызывающего процесса "C:\\Мои документы\\программы\\VCproject\\oTDK\\Debug"
		&StartupInfo,
		&ProcessInfo);  //получает инфу от процесса
	::GetExitCodeProcess(ProcessInfo.hProcess,&ExitCode);
	//Ждем окончания процесса
	::WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
}
//
void Sort(CStringArray* HN,UINT index) //сортировка массивов
{ //используется алгоритм полной пузырьковой сортировки
	UINT i,j; 
	CString w, copy;
	for(i=0; i<=index; i++) {
		for (j=0; j<index-i; j++) {
			w=HN->GetAt(j);
			copy = HN->GetAt(j+1);
			if (w.CompareNoCase(copy)>0) {
				HN->SetAt(j,copy); HN->SetAt(j+1,w);
			}
		}
	}
}
