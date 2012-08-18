// oTDKDoc.cpp : implementation of the COTDKDoc class
//

#include "stdafx.h"
#include "oTDK.h"

#include "oTDKDoc.h"
#include "MainFrm.h"
#include "LeftView.h"
#include "OTDKView.h"
#include "WorkINI.h"
#include "FindNode.h"

#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// COTDKDoc
IMPLEMENT_DYNCREATE(COTDKDoc, COleDocument)

BEGIN_MESSAGE_MAP(COTDKDoc, COleDocument)
	//{{AFX_MSG_MAP(COTDKDoc)
	ON_COMMAND(ID_MAKESIG, OnMakesig)
	ON_UPDATE_COMMAND_UI(ID_MAKESIG, OnUpdateMakesig)
	ON_COMMAND(ID_WORD, OnWord)
	ON_UPDATE_COMMAND_UI(ID_WORD, OnUpdateWord)
	ON_COMMAND(ID_CHKSIG, OnChksig)
	ON_UPDATE_COMMAND_UI(ID_CHKSIG, OnUpdateChksig)
	ON_UPDATE_COMMAND_UI(ID_DIAP, OnUpdateDiap)
	ON_COMMAND(ID_DIAP, OnDiap)
	ON_COMMAND(CLOSEFILE, OnCLOSEFILE)
	ON_COMMAND(ID_FINDNODE, OnFindnode)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_COMMAND(ID_FILE_OPEN, OnOpen)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COTDKDoc construction/destruction

COTDKDoc::COTDKDoc()
{
	// Use OLE compound files
	EnableCompoundFile();
	bbggrr.RemoveAll(); // очистить  массив цвета строк
	bbggrr.Add(G_INFORMATION); //первичные сообщения при открытии программы
	csaDate.RemoveAll(); // очистить массив выводных строк
	csaDate.Add("Оболочка тестирования ТЭЗов для работы с ПО ТДК3-192!");
	stPos.dwPos1 = 0;
	stPos.dwPos2 = 0;
	stPos.dwPos3 = 0;
	iOpenSig = 0; //отжать кнопку формирования файлов сигнатур 
	iChkSig = 0; //отжать кнопку проверки файлов сигнатур 
	iChkDia = 0; //отжать кнопку диагностической проверки  
	iChkWord=0;
	iCount=0;
	strFileName = ""; //инициализируем строку
	strFName = ""; csDate = "";
	HeadNode.RemoveAll(); glsV.RemoveAll(); secondsV.RemoveAll();	
	bClose=FALSE;
}

COTDKDoc::~COTDKDoc()
{
}

BOOL COTDKDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COTDKDoc serialization

void COTDKDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// COTDKDoc diagnostics

#ifdef _DEBUG
void COTDKDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void COTDKDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COTDKDoc commands
// выдать строку
CString COTDKDoc::GetDate()
{
return csDate;	
}
//установить строку для вывода в массив выводных строк
//х - в какую строку, s - собственно строка, bTF:
// - TRUE - заменить строку с индексом х,
// - FALSE - вставить строку перед строкой с индексом х.
void COTDKDoc::SetString(int x, CString s, BOOL bTF)
{
	//csaDate.Add(s);
	if (bTF != TRUE)
		csaDate.SetAt(x,s);
	else
		csaDate.InsertAt(x,s,1);
	//csDate=s; 
}
//открытие трех видов файлов (деревья ураловские (tre), деревья новые (trw)
//файл сигнатур проверки функциональности всего ТЭЗа (sig)
void COTDKDoc::OnOpen()
{
	//BOOL bExitWhat;
	CStdioFile Fl;
	CString s;
	LPTSTR ref;
	// создание стандартной панели выбора файла Open  r_Opn
	CFileDialog DlgOpen(TRUE,(LPCSTR)"tre", strWR + "\\*.tre", OFN_HIDEREADONLY,
			(LPCSTR)"BTrees Files (*.tre) |*.tre|WinTrees Files (*.trw) |*.trw| \
Signature Files (*.sig) |*.sig|Diagnostic Files (*.dia) |*.dia|");  
	// отображение стандартной панели выбора файла Open 

	if(DlgOpen.DoModal()==IDOK)
	{ 
		// создание объекта и открытие файла для чтения 
		CStdioFile File(DlgOpen.GetPathName(),CFile::modeRead|CFile::typeText);  
		// чтение из файла строки 
		//strFileName = " ~"; 
		strFileName = File.GetFileName();
	//название открытого файла в заголовок
		HWND hWnd = GetActiveWindow();
		::SetWindowText(hWnd,csHead + strFileName);
		strFileName.MakeLower();
		//если открытй файл - сигнатурный
		if (strstr(strFileName.GetBuffer(strFileName.GetLength()), ".sig") != NULL) {
			//запускаем функциональлное тестирование ТЭЗа
			COTDKDoc::strFName = "sigtess.exe ";
			COTDKDoc::strFName += File.GetFileName();
			ref = COTDKDoc::strFName.GetBuffer(strFName.GetLength());
			File.Close();
			//
			//Запуск файла теста сигнатуры
			gFuncTest(ref, TRUE); //bHideShowTest);
			//
		}
		else if (strFileName.Find(".dia") != -1) {
			//запускаем функциональлное тестирование ТЭЗа
			COTDKDoc::strFName = "diatezzz.exe ";
			COTDKDoc::strFName += File.GetFileName();
			ref = COTDKDoc::strFName.GetBuffer(strFName.GetLength());
			File.Close();
			//Запуск файла теста сигнатуры
			gFuncTest(ref, TRUE); //bHideShowTest);
			//
		}
		else if (strFileName.Find(".tre") != -1) { //если ураловское дерево открыто
			DWORD dwPosition = File.GetLength();
			UINT iStr = 0;
			//структура анализа строки
			 struct {
				char sX;             //первый символ анализируемой строки строки
				char Vetv[7];        //ветвь
				char Uchastok[12];   //участок ветви
				char Perex[255];      //переходы ветви
			}strV;
			long lX; int i;
			char *strStop;	CString csOpa;
			csOpa=File.GetFilePath(); csOpa=csOpa.Left(csOpa.ReverseFind('\\'));
			WritePrivateProfileString ("PATH", "WorkRoot", csOpa, r_Opn);
			//WorkINI WS;   // создаем объект класса диалогового окна
			//WS.m_WorkDir = 
			strWR=csOpa;
			//WS.UpdateData(FALSE); 
			//WS.Invalidate(NULL); 
			//две верхние строки пропускаем
			File.ReadString(s);	File.ReadString(s);
			//подготавливаем массивы - выходов ТЭЗа и подузлов ТЭЗа
			glsV.RemoveAll();	secondsV.RemoveAll();
			while (dwPosition > File.GetPosition()) {//пока не конец файла дерева
				File.ReadString(s); //читаем строку и файла				
				ZeroMemory(&strV,sizeof(strV)); //освобождаем для новой строки
				strcpy(&strV.sX,s.GetBuffer(s.GetLength())); //формируем новую запись
				lX = strtol(strV.Vetv,&strStop,0); //проверяем на начало ветки
				csOpa.Delete(1, csOpa.GetLength()); //очищаем для нового имени
				for (i=0; i <= 11; i++) {
					switch(strV.Uchastok[i]) {
					case ',':
					case ':': 
					case ';':
					case ' ': break;
					case '.':
						csOpa += '_'; break;
					default: csOpa += strV.Uchastok[i];
					}//switch
				}//for
				if (lX > 0) { //если начало записываем имя начала ветки
					glsV.Add(csOpa); //добавляем в массив имен начал веток
					gVlNode(strV.Perex, csOpa);
				} //if
				else gVlNode(strV.Perex, csOpa);
				iStr++; //подсчет строк
			} // while
			//после открытия производим сообщение для начала работ
			csaDate.RemoveAll();			bbggrr.RemoveAll();
			bbggrr.Add(G_INFORMATION);
			AddString("#Тестирование осуществляется по кнопке ПРОБЕЛ#");
			bbggrr.Add(G_INFORMATION);
			AddString("#Или правой кнопкой 'мыши'#");
			File.Close();
		}//else if
		else if (strFileName.Find(".trw") != -1) { //если открываем новые файлы деревьев
			CString sLine, sLineKey;
//			char buf[2];
			int iLineC=0;
			CArchive ar(&File,CArchive::load);
			if (ar.ReadString(sLine)) 
				 gRecTRW(0,sLine,&ar); //формируем массивы - выходов ТЭЗа и подузлов ТЭЗа
			ar.Close();
			File.Close();
			//после открытия производим сообщение для начала работ
			csaDate.RemoveAll();			bbggrr.RemoveAll();
			bbggrr.Add(G_INFORMATION);
			AddString("#Тестирование осуществляется по кнопке ПРОБЕЛ#");
			bbggrr.Add(G_INFORMATION);
			AddString("#Или правой кнопкой 'мыши'#");
		}
		UpdateAllViews(NULL);    // обновить виды
	}//if DoModal
}
//выдает значение из массива выходов ТЭЗа согласно переданному индексу
CString COTDKDoc::GetItemValue(UINT index)
{
	CString str;
	str = glsV.GetAt(index);
return str;
}
//получить размер массива выходов ТЭЗов
int COTDKDoc::GetArrSize()
{
	return glsV.GetSize();

}
//анализ строки переходов в файле деревьев (ураловских)
void COTDKDoc::gVlNode(char Perex[], CString csOpa)
{
	char* strStop;
	CString csOops, csYe, value;
	int i, x=0, y=0; BOOL bOK=TRUE;
	char buf[2];
	/* Establish string and get the first token: */
	strStop = strtok( Perex, "," );
	while( strStop != NULL ) {
		csYe.Delete(1, csYe.GetLength()); //очищаем для нового имени
		if (strlen(strStop) > 0) {
			for (i=0; i <= 6; i++) {
				switch(*strStop) {
					case ',':
					case ':': 
					case ';':
					case ' ': break;
					case '.': csYe += '_'; break;
					default: csYe += *strStop;
				}//switch				
				strStop++;
			}//for
		}//if
		bOK = TRUE; y=0; x++; itoa(x,buf,10);
		csOops = buf + csOpa;
		secondsV.SetAt(csOops,csYe); //формируем массив подузлов соответствующего узла
		strStop = strtok( NULL, "," );
	}//while
}
//добавляет строку выводимых текстовых строк
void COTDKDoc::AddString(CString s)
{
	csaDate.Add(s);
}
//размер массива выводимых текстовых строк
int COTDKDoc::GetcsaSize()
{
return csaDate.GetSize();
}
//выдает строку из массива выводных текстовых строк
CString COTDKDoc::GetcsaItem(int index)
{
	CString str;
	//str = &csaDate.ElementAt(index);
	str = csaDate.GetAt(index);	
return str;
}
//удаляет строку из массива выводных текстовых строк
void COTDKDoc::RemovecsaItem(int x)
{
	csaDate.RemoveAt(x, 1);
}

//находит позицию строки массива сигнатур по шаблону = "ffff"
DWORD COTDKDoc::gGetPosString(DWORD StartPos, CString csFF, CStdioFile* Fl)
{
	CString csContact;
	//char buf[255];
	//LPTSTR x;
	BOOL bTF = TRUE;
	DWORD dwPosition = NULL;	
	if (csFF.GetLength() == 0) csFF = "ffff";
	Fl->Seek(StartPos,CFile::begin); //начинаем искать с начала файла сигнатур
	while (bTF) { //пока не конец файла
		bTF = Fl->ReadString(csContact); //считывает каждую строку
		//csContact.OemToAnsi();
		if (csContact.Find(csFF) != -1) { //если шаблон найден
			//берем позицию начала шаблона
			dwPosition = Fl->GetPosition()-csContact.GetLength();
			break; //выходим
		}//if
	}//while
	return dwPosition;
}
//функция вызываемая в случае нажатия кнопки (или выбора меню)
//создания файла сигнатур для каждого узла
void COTDKDoc::OnMakesig() 
{
	CString csKey, csValue, csSD;
	CStdioFile Fl; 
	//COTDKView* clsV=NULL;
	iCount=0;
	HeadNode.RemoveAll();
	if (iOpenSig == 0) { //если кнопка отжата нажать ее и
		iOpenSig = 1; //зафиксировать в нажатом виде
		if (!secondsV.IsEmpty()) { //проходим по массиву узлов ТЭЗа
			POSITION pos = secondsV.GetStartPosition();				 
			while (pos != NULL) {
				secondsV.GetNextAssoc(pos, csKey, csValue);
				if (csKey.GetAt(0) == '1' && !(csKey.Mid(0,2).Compare("10") >= 0
					&& csKey.Mid(0,2).Compare("19") <= 0)) { 
					//проверяем существет ли уже файл сигнатур данного узла
					if (iChkDia == 0) csSD = ".sig";
					else csSD = ".dia";
					if (!Fl.Open(csKey.Mid(1) + csSD, CFile::modeRead)) {
							HeadNode.Add(csKey.Mid(1));
					}
					else Fl.Close();
				}
			}
			//сообщаем о начале формирования файла сигнатур с данного узла
			if (HeadNode.GetSize() > 0) {
				Sort(&HeadNode,HeadNode.GetSize()-1);
				bbggrr.InsertAt(1,G_WRITESIG);
				SetString(1,"Поставьте щуп на узел " + HeadNode.GetAt(0) + 
													" и нажмите ПРОБЕЛ",TRUE);
			}
			else { //если все файлы сигнатур есть сообщаем об этом
				bbggrr.SetAt(1,G_MESSAGE);
				SetString(1,"Создание файлов сигнатур(диагностики) завершено!",FALSE);
				iOpenSig = 0; //отжимаем кнопку начала создания файлов сигантур
			}
		}
		else {
			bbggrr.InsertAt(1,G_INFORMATION);
			SetString(1,"Сначала надо открыть файл дерева ТЭЗа",TRUE);
			iOpenSig = 0;
		}
		//обновляем и передаем фокус правому виду
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView(pos);
		UpdateAllViews(pView);		pView = GetNextView(pos);
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetActiveView(pView,TRUE);
		//pView->UpdateWindow();   
	}
	else { //если кнопка в нажатом состоянии, отжимаем ее
		iOpenSig = 0; iCount=0;
		HeadNode.RemoveAll();
	}
}

void COTDKDoc::OnUpdateMakesig(CCmdUI* pCmdUI) 
{
	// установка вида кнопки формирования файлов сигнатур в
	//зависимости от нажатия кнопки
	pCmdUI->SetCheck(iOpenSig);
}
//функция загрузки новых деревьев для ТЭЗов
BOOL COTDKDoc::gRecTRW(int previndent, CString sLineKey,CArchive* ar)
{
	int rasindent, indent; CString sLine, value,siKey;
	int baseindent = previndent; int iLineC;
	char buf[2]; BOOL bOpa = TRUE;
	CMapStringToString map;
	CMapStringToString mapLine;
	if (previndent == 0) {
		glsV.Add(sLineKey); //записываем выход ТЭЗа в массив
		itoa(previndent,buf,10);
		map.SetAt(buf,sLineKey);
		mapLine.SetAt(sLineKey,"1");
		baseindent = previndent;
	}
	while (ar->ReadString(sLine)) { //пока файл дерева не закончен читаем строки
		for(indent=0;sLine[indent]=='\t';indent++);
		sLine=sLine.Right(sLine.GetLength()-indent);
		secondsV.SetAt("1" + sLine, "/"); //подготовка если вход
		if (indent == 0) gRecTRW(0,sLine,ar); //break; //переходим к подузлу
		rasindent = indent - baseindent; //вычисляем сдвиг для подузла
		if (rasindent == 0) { //если сдвига нет, значит это следующий узел
			//но не подузел
			itoa(indent,buf,10);
			map.SetAt(buf,sLine); indent--; //записываем узел в массив
			itoa(indent,buf,10);
			map.Lookup(buf,value); 
			mapLine.Lookup(value,siKey);
			iLineC = atoi(siKey); iLineC++; itoa(iLineC,buf,10);
			mapLine.SetAt(value,buf); //siKey);
			value=buf + value;
			secondsV.SetAt(value,sLine); //и для следующего подузла
			mapLine.SetAt(sLine,"1");
		}//end if rasindent == 0
		else if (rasindent < 0) { //если разность сдвига менше нуля
			//значит это начало старшего подузла или начало новой ветви
			itoa(indent,buf,10);
			map.SetAt(buf,sLine); 
			baseindent=indent; indent--; //+ rasindent;
			itoa(indent,buf,10);
			map.Lookup(buf,value);
			mapLine.Lookup(value,siKey);
			iLineC = atoi(siKey); iLineC++; itoa(iLineC,buf,10);
			mapLine.SetAt(value,buf); //siKey);
			value=buf + value;
			secondsV.SetAt(value,sLine);
		}//end if rasindent == -1
		else if (rasindent == 1) { //если это подузел текущего узла (подузла)
			itoa(indent,buf,10);				
			map.SetAt(buf,sLine);	
			baseindent=indent; indent--;
			itoa(indent,buf,10);
			map.Lookup(buf,value);
			mapLine.SetAt(value,"1");
			mapLine.Lookup(value,siKey);
			value=siKey + value;
			secondsV.SetAt(value,sLine);
		}//end if rasindent == 1
	}//end while readstring
	map.RemoveAll();
	mapLine.RemoveAll();
	return bOpa;
}
// запуск Word файла если он есть 
void COTDKDoc::OnWord() 
{
ShellExecute(NULL, "open", strFileName.Mid(0,strFileName.GetLength()-3) + "doc",
             NULL, NULL, SW_SHOWNORMAL);
	
}
// разрешение на запуск Word файла если он есть
void COTDKDoc::OnUpdateWord(CCmdUI* pCmdUI) 
{
	CFileFind theFile;
	CString strFileWord; 
	if (strFileName == "") iChkWord=0;
	else {
		strFileWord = strFileName.Mid(0,strFileName.GetLength()-3) + "doc";
		if(theFile.FindFile(strFileWord,0) != 0) iChkWord=1;
		else iChkWord=0;
	}
	pCmdUI->Enable(iChkWord);
}

void COTDKDoc::OnChksig() 
{
	iCount=0; 
	if (iChkSig == 0) { //если кнопка отжата нажать ее и
		iChkSig = 1; //зафиксировать в нажатом виде
		gGetNode(); //запросить узел для начала тестирования
		Sort(&HeadNode,HeadNode.GetSize()-1);
		gMesNode(iCount); // вывести сообщение о начале тестирования
	}
	else { //если кнопка в нажатом состоянии, отжимаем ее
		iChkSig = 0; iCount=0;
		HeadNode.RemoveAll();
	}
}

void COTDKDoc::OnUpdateChksig(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iChkSig);
	
}

void COTDKDoc::OnUpdateDiap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(iChkDia);
	
}

void COTDKDoc::OnDiap() 
{
	if (iChkDia == 0) { //если кнопка отжата нажать ее и
		iChkDia = 1; //зафиксировать в нажатом виде
		bbggrr.InsertAt(1,G_INFORMATION);
		SetString(1,"Переходим к диагностическому тестированию",TRUE);
	}
	else {
		iChkDia = 0;
	}
	
}
// закрыть файл дерева
void COTDKDoc::OnCLOSEFILE() 
{
	bClose=TRUE;
		HWND hWnd = GetActiveWindow();
		::SetWindowText(hWnd,csHead); strFileName = "";
	csaDate.RemoveAll();		
	bbggrr.RemoveAll();
	UpdateAllViews(NULL);    // обновить виды
}

void COTDKDoc::gGetNode()
{
	CString csKey, csValue;
	CStdioFile Fl; 
	//COTDKView* clsV=NULL;
	HeadNode.RemoveAll();
	if (!secondsV.IsEmpty()) { //проходим по массиву узлов ТЭЗа
		POSITION pos = secondsV.GetStartPosition();				 
		while (pos != NULL) {
			secondsV.GetNextAssoc(pos, csKey, csValue);
			if (csKey.GetAt(0) == '1' && !(csKey.Mid(0,2).Compare("10") >= 0
				&& csKey.Mid(0,2).Compare("19") <= 0)) { 
				HeadNode.Add(csKey.Mid(1));
			}
		}
	}
	else {
		bbggrr.InsertAt(1,G_INFORMATION);
		SetString(1,"Сначала надо открыть файл дерева ТЭЗа",TRUE);
		iChkSig = 0;
	}
}

void COTDKDoc::OnFindnode() 
{
	FindNode dlgFN;
	dlgFN.DoModal(); // запускаем запрос на ввод имени искомого узла
	CString csFN=dlgFN.m_find; // получаем имя искомого узла
	if (iChkSig==1) { // если включён  режим проверки узлов
		gGetNode(); // формируем массив всех узлов дерева
		Sort(&HeadNode,HeadNode.GetSize()-1);
		int count = HeadNode.GetSize(); // берем размер этого массива
		for( int x=0; x<count; ++x) {
			if (csFN.CompareNoCase(HeadNode.GetAt(x))==0) break; // ищем узел в массиве
		}
		if (x!=count) iCount =x; // если нашли выставляем индекс найденного узла
		// запрашиваем узел на проверку
		gMesNode(iCount); // вывести сообщение о начале тестирования
	}
	else { // иначе (не вкл. режим проверки) просто поиск узла по дереву
		CLeftView* pView;
		pView=(CLeftView*)((CMainFrame*) AfxGetApp()->m_pMainWnd)->GetActiveView();
		pView->gFindItem(csFN); // запускаем поиск узла
	} // end else
	
}

void COTDKDoc::gMesNode(int cnt)
{
		//сообщаем о начале формирования файла сигнатур с данного узла
		if (HeadNode.GetSize() > 0) {
			bbggrr.InsertAt(1,G_WRITESIG);
			SetString(1,"Поставьте щуп на узел " + HeadNode.GetAt(cnt) + 
																					" и нажмите ПРОБЕЛ",TRUE);
		}
		//обновляем и передаем фокус правому виду
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView(pos);
		UpdateAllViews(pView);		pView = GetNextView(pos);
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetActiveView(pView,TRUE);

}
