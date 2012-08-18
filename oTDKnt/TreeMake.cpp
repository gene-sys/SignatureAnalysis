// TreeMake.cpp : implementation file
//

#include "stdafx.h"
#include "afx.h"
#include "oTDK.h"
#include "TreeMake.h"
#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeMake dialog


CTreeMake::CTreeMake(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeMake::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeMake)
	m_namefile = _T("");
	m_startnew = FALSE;
	m_CurrentNode = _T("");
	m_Perexod = _T("");
	m_EnterNode = _T("");
	m_edit = _T("");
	//}}AFX_DATA_INIT
	cwndEntrPer=NULL;  // начальное значение указателя поля
	glsV.RemoveAll(); // массив очереди описания узлов дерева
	csaUch.RemoveAll(); // массив описания участков (узлов)
	Branch=FALSE; //новая ветвь (FALSE) или старая (TRUE)
	ibranch=0; // номер ветви
	poQueue = 0; //указатель очередности
}


void CTreeMake::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeMake)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Text(pDX, IDC_NAMEFILE, m_namefile);
	DDV_MaxChars(pDX, m_namefile, 8);
	DDX_Check(pDX, IDC_STARTNEW, m_startnew);
	DDX_Text(pDX, IDC_CURNODE, m_CurrentNode);
	DDX_Text(pDX, IDC_PEREX, m_Perexod);
	DDV_MaxChars(pDX, m_Perexod, 255);
	DDX_Text(pDX, IDC_ENTR, m_EnterNode);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeMake, CDialog)
	//{{AFX_MSG_MAP(CTreeMake)
	ON_EN_KILLFOCUS(IDC_ENTR, OnKillfocusEntr)
	ON_BN_CLICKED(IDC_STARTNEW, OnStartnew)
	ON_BN_CLICKED(IDC_NEWTREE, OnNewtree)
	ON_EN_SETFOCUS(IDC_ENTR, OnSetfocusEntr)
	ON_BN_CLICKED(IDC_LOADTREE, OnLoadtree)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_PEREX, OnSetfocusPerex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeMake message handlers
// выход из  формы описания нового логического дерева
void CTreeMake::OnOK() 
{
	//if (MessageBox("Вы сохранили файл дерева?"," ", MB_YESNO) == IDYES) {
		glsV.RemoveAll();
		csaUch.RemoveAll();
		if (theFile.GetFileName() != "") theFile.Close();
		CDialog::OnOK();		
	//}
}

void CTreeMake::OnKillfocusEntr() 
{
	UpdateData(TRUE);
	// если начало новой ветви
	if (m_startnew == TRUE) {
		if (!m_EnterNode.IsEmpty()) {
			m_startnew = FALSE; //начинаем новую ветвь
			//m_EnterNode.Replace(".","_"); //меняем точку на прочерк по соглашению
			m_CurrentNode = m_EnterNode;
			csaUch.Add(m_EnterNode); //формируем массив описания участков
			Branch=TRUE; ibranch++;
			UpdateData(FALSE);	
		}
	}
	else Branch=FALSE;
}
// опрос нажатия клавиш в форме
BOOL CTreeMake::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT(m_hWnd != NULL);
	// нажата ли клавиша
	if(pMsg->message == WM_KEYDOWN)	{ //если нажата, то это клавиши:
																				//ввода (ENTER), отмены (ESCAPE) или F2
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE ||
					pMsg->wParam == VK_F2) {
			switch(pMsg->wParam) {
				case VK_RETURN: // если это клавиша ввода
					// что то делаем 
					if (cwndEntrPer == GetDlgItem(IDC_ENTR)) {
						cwndEntrPer = GetDlgItem(IDC_PEREX); //переходим к полю описания переходов
						cwndEntrPer->SetFocus();
					}					
					else if (cwndEntrPer == GetDlgItem(IDC_PEREX)) gMadePerex();  //обрабатываем переходы
					else if (cwndEntrPer == GetDlgItem(IDC_EDIT1)) gPereschet();  //переформируем изменения описания дерева
					break;
				case VK_ESCAPE:
					// что то делаем 
					break;
				case VK_F2:
					//выход по F2
					OnOK();
					break;
			}
			//Draw(&DC);
			return TRUE;
		}
		return CDialog::PreTranslateMessage(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTreeMake::OnStartnew() 
{
	UpdateData(TRUE);
	// передаем номер текущей ветви
	m_EnterNode = ""; m_CurrentNode = ""; m_Perexod = "";	
	
}

void CTreeMake::OnNewtree() 
{
	// создать новое дерево	
	// разрешаем вводить описание ветвей дерева
	cwndEntrPer = GetDlgItem(IDC_ENTR);
	cwndEntrPer->EnableWindow(TRUE);
	cwndEntrPer = GetDlgItem(IDC_STARTNEW);
	cwndEntrPer->EnableWindow(TRUE);	
	cwndEntrPer = GetDlgItem(IDC_PEREX);
	cwndEntrPer->EnableWindow(TRUE);
	UpdateData(TRUE);
	//открыть файл куда сохранять
	CString fPath = strWR+ "\\"; 
	fPath += m_namefile;
	theFile.Open(fPath  + ".tre",CFile::modeCreate| CFile::modeWrite);
	CArchive arpoint(&theFile,CArchive::store);
	// первые 2-е строчки (могут быть любыми)
	arpoint.WriteString("(c) АЭХК, ЦРП, начало XXI века \r\n");
	arpoint.WriteString("ветвь   участок     переход\r\n");
	arpoint.Close();
	// тоже для отображения на экране
	m_edit+="(c)  АЭХК, ЦРП, начало XXI века \r\n"; 	m_edit+="ветвь   участок     переход\r\n";
	UpdateData(FALSE);
	theFile.SeekToEnd();
}
// поиск имени узла в переданном массиве
BOOL CTreeMake::gLocalNode(CString cs, CStringArray *csa)
{
	for(int i=0; i<=csa->GetSize()-1; i++) {
		if (csa->GetAt(i) == cs) return(TRUE);
	}
	return(FALSE);
}
// переход к полю вход
void CTreeMake::OnSetfocusEntr() 
{
	cwndEntrPer = GetFocus();
	
}
// вызов ранее описанного дерева и сохраненного в файл
void CTreeMake::OnLoadtree() 
{
	//подготавливаем массивы - выходов ТЭЗа и подузлов ТЭЗа
	glsV.RemoveAll();	
	poQueue=0;
	csaUch.RemoveAll();
	if (theFile.GetFileName() != "") theFile.Close();
	//
	CFileDialog DlgOpen(TRUE,(LPCSTR)"tre", strWR + "\\*.tre", OFN_HIDEREADONLY,
												(LPCSTR)"BinTrees Files (*.tre)||");  
	// отображение стандартной панели выбора файла Open 
	if(DlgOpen.DoModal()==IDOK) { 		// открытие файла для чтения 
		gOpenFile(DlgOpen.GetPathName());
	} // if DlgOpen
}
// формирование массивов очереди и описания участков (узлов)
void CTreeMake::gVlNode(char Perex[], CString csOpa)
{
	char* strStop;
	CString csYe, csPerex;
	CStringArray csaM;
	int i, k=0;
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
					//case '.': csYe += '_'; break;
					default: csYe += *strStop;
				}//switch				
				strStop++;
			}//for
		}//if
		k++;	csaM.Add(csYe);
		strStop = strtok( NULL, "," );
	}//while
		if (csYe.Compare("/") != 0) {
			for (int j=1; j<=k; j++) {
				//поиск узла был ли он ранее описан
				csPerex=csaM.GetAt(j-1);
				if (!gLocalNode(csPerex, &glsV)  && !gLocalNode(csPerex, &csaUch)) {
					//если ранее не описан, то
					//формируем массив подузлов соответствующего узла
					//запоминаем узел в массиве имен узлов дерева
					glsV.Add(csPerex);
				}
			}// end for
		}//end if strStop != "/"
		if (poQueue < glsV.GetSize()) {
			csaUch.Add(glsV.GetAt(poQueue)); 
			// здесь переход к новому узлу
			m_CurrentNode = glsV.GetAt(poQueue); m_Perexod = ""; poQueue++; Branch = FALSE;
			m_startnew = FALSE; UpdateData(FALSE);	
		}
		else { //..здесь написать переход к новой ветви
			m_CurrentNode = ""; m_Perexod = "";	m_EnterNode = ""; m_startnew = TRUE;	
			UpdateData(FALSE);	
			//cwndEntrPer = GetDlgItem(IDC_ENTR);	cwndEntrPer->SetFocus(); 
		}
}
// функция переформирования массивов записи дерева описываемого ТЭЗа
void CTreeMake::gPereschet()
{
	UpdateData(TRUE);	
	//AfxMessageBox(m_edit);
	theFile.SetLength(0);
	CArchive arpoint(&theFile,CArchive::store);
	arpoint.WriteString(m_edit);	arpoint.Close();
	theFile.Close();
	glsV.RemoveAll();		csaUch.RemoveAll();
	poQueue=0; ibranch=0;
	gOpenFile(m_namefile+".tre");
	cwndEntrPer = GetDlgItem(IDC_EDIT1);
}

void CTreeMake::OnSetfocusEdit1() 
{
	cwndEntrPer = GetDlgItem(IDC_EDIT1);
	
}

void CTreeMake::gMadePerex()
{
	char* strStop;
	CString s, csCurNode, csPerex;
	CStringArray csaM;
	char buf[2];
	int i, k=0;
	/* Establish string and get the first token: */
	UpdateData(TRUE);
	//если поле переходов не пусто, то
	if (!m_CurrentNode.IsEmpty()) {
		csCurNode = m_CurrentNode; 
		//m_Perexod.Replace(".","_");
		// запись переходов в файл
			theFile.SeekToEnd();
			CArchive arpoint(&theFile,CArchive::store);
			if (Branch) {
				Branch=FALSE; itoa(ibranch,buf,10);		s="    "; s+=buf;	for(i=s.GetLength(); i<8;i++) s+=" ";
				s+=csCurNode; 	for(i=s.GetLength(); i<20;i++) s+=" ";		s+=m_Perexod;
			}
			else {
				s = "        "; s+=csCurNode; 	for(i=s.GetLength(); i<20;i++) s+=" ";	s+=m_Perexod;
			}
			arpoint.WriteString(s+"\r\n");	arpoint.Close();
		// конец записи в файл
		m_edit += s;  m_edit +="\r\n";
		//если в переходе не указан конец ветви (подветви) - знак /
		if (m_Perexod.Compare("/") != 0) {
			//csPerex=m_Perexod;
			strStop = strtok( m_Perexod.GetBuffer(m_Perexod.GetLength()), "," );
			//преобразуем последовательность переходов в дерево
			while( strStop != NULL ) {
				k++;
				csaM.Add(strStop);
				strStop = strtok( NULL, "," );
			}//while
			for (int j=1; j<=k; j++) {
				//поиск узла был ли он ранее описан
				csPerex=csaM.GetAt(j-1);
				if (!gLocalNode(csPerex, &glsV)  && !gLocalNode(csPerex, &csaUch)) {
					//если ранее не описан, то
					//формируем массив подузлов соответствующего узла
					//запоминаем узел в массиве имен узлов дерева
					glsV.Add(csPerex);
				}
			}// end for
		}//end if strStop != "/"
		if (poQueue < glsV.GetSize()) {
			csaUch.Add(glsV.GetAt(poQueue)); 
			// здесь переход к новому узлу
			m_CurrentNode = glsV.GetAt(poQueue); m_Perexod = ""; poQueue++; Branch = FALSE; 
			m_startnew = FALSE; UpdateData(FALSE);	 
		}
		else { //..здесь написать переход к новой ветви
			m_CurrentNode = ""; m_Perexod = "";	m_EnterNode = ""; m_startnew = TRUE;	
			UpdateData(FALSE);	
			cwndEntrPer = GetDlgItem(IDC_ENTR);	cwndEntrPer->SetFocus(); 
		}
	}//end if есть текущий узел
	CString str; 
	cwndEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	cwndEdit->GetWindowText(str);
	cwndEdit->SetSel(str.GetLength() - 1, str.GetLength() - 1, FALSE);
}

void CTreeMake::OnSetfocusPerex() 
{
	cwndEntrPer = GetDlgItem(IDC_PEREX);	
	//CString cs; cs.
	//m_edit.
}

void CTreeMake::gOpenFile(CString csfPath)
{
		m_edit="";
		theFile.Open(csfPath,CFile::modeReadWrite);
		CString sLine = theFile.GetFileName();
		m_namefile = sLine.Left(sLine.GetLength()-4);
		//UpdateData(FALSE);
		CArchive ar(&theFile,CArchive::load);
		//
		if(!ar.ReadString(sLine)) return;	
		m_edit += sLine;  m_edit +="\r\n";
		UpdateData(FALSE);	
		cwndEntrPer = GetDlgItem(IDC_ENTR);
		cwndEntrPer->EnableWindow(TRUE);
		cwndEntrPer = GetDlgItem(IDC_STARTNEW);
		cwndEntrPer->EnableWindow(TRUE);	
		cwndEntrPer = GetDlgItem(IDC_PEREX);
		cwndEntrPer->EnableWindow(TRUE);
		UpdateData(TRUE);
		UINT iStr = 0;
		//структура анализа строки
		struct {
			char sX;             //первый символ анализируемой строки строки
			char Vetv[7];        //ветвь
			char Uchastok[12];   //участок ветви
			char Perex[255];      //переходы ветви
		}strV;
		long lX; int i;
		char *strStop;	CString csOpa, s;
		//две верхние строки пропускаем
		ar.ReadString(s);	//ar.ReadString(s);
		m_edit += s;  m_edit +="\r\n";
		while (ar.ReadString(s)) {//пока не конец файла дерева
			//ar.ReadString(s); //читаем строку и файла				
			m_edit += s;  m_edit +="\r\n";
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
					//case '.': csOpa += '_'; break;
					default: csOpa += strV.Uchastok[i];
				}//switch
			}//for
			//если начало записываем имя начала ветки
			if (lX > 0)  { ibranch++; m_EnterNode = csOpa; }
			csaUch.Add(csOpa); //добавляем в массив имен начал веток
			gVlNode(strV.Perex, csOpa);
			iStr++; //подсчет строк
		} // while
		ar.Close();		//theFile.Close();
}

//DEL void CTreeMake::OnChangeEdit1() 
//DEL {
//DEL 		//CEdit ce; ce.SetCaretPos()
//DEL 		CPoint point; CWnd* cw;
//DEL 		cw = GetDlgItem(IDC_EDIT1);
//DEL 		point =  cw->GetCaretPos();
//DEL 		point.y++; 
//DEL 		cw->SetCaretPos(point);
//DEL }
