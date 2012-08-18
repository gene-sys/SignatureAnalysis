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
	bbggrr.RemoveAll(); // ��������  ������ ����� �����
	bbggrr.Add(G_INFORMATION); //��������� ��������� ��� �������� ���������
	csaDate.RemoveAll(); // �������� ������ �������� �����
	csaDate.Add("�������� ������������ ����� ��� ������ � �� ���3-192!");
	stPos.dwPos1 = 0;
	stPos.dwPos2 = 0;
	stPos.dwPos3 = 0;
	iOpenSig = 0; //������ ������ ������������ ������ �������� 
	iChkSig = 0; //������ ������ �������� ������ �������� 
	iChkDia = 0; //������ ������ ��������������� ��������  
	iChkWord=0;
	iCount=0;
	strFileName = ""; //�������������� ������
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
// ������ ������
CString COTDKDoc::GetDate()
{
return csDate;	
}
//���������� ������ ��� ������ � ������ �������� �����
//� - � ����� ������, s - ���������� ������, bTF:
// - TRUE - �������� ������ � �������� �,
// - FALSE - �������� ������ ����� ������� � �������� �.
void COTDKDoc::SetString(int x, CString s, BOOL bTF)
{
	//csaDate.Add(s);
	if (bTF != TRUE)
		csaDate.SetAt(x,s);
	else
		csaDate.InsertAt(x,s,1);
	//csDate=s; 
}
//�������� ���� ����� ������ (������� ���������� (tre), ������� ����� (trw)
//���� �������� �������� ���������������� ����� ���� (sig)
void COTDKDoc::OnOpen()
{
	//BOOL bExitWhat;
	CStdioFile Fl;
	CString s;
	LPTSTR ref;
	// �������� ����������� ������ ������ ����� Open  r_Opn
	CFileDialog DlgOpen(TRUE,(LPCSTR)"tre", strWR + "\\*.tre", OFN_HIDEREADONLY,
			(LPCSTR)"BTrees Files (*.tre) |*.tre|WinTrees Files (*.trw) |*.trw| \
Signature Files (*.sig) |*.sig|Diagnostic Files (*.dia) |*.dia|");  
	// ����������� ����������� ������ ������ ����� Open 

	if(DlgOpen.DoModal()==IDOK)
	{ 
		// �������� ������� � �������� ����� ��� ������ 
		CStdioFile File(DlgOpen.GetPathName(),CFile::modeRead|CFile::typeText);  
		// ������ �� ����� ������ 
		//strFileName = " ~"; 
		strFileName = File.GetFileName();
	//�������� ��������� ����� � ���������
		HWND hWnd = GetActiveWindow();
		::SetWindowText(hWnd,csHead + strFileName);
		strFileName.MakeLower();
		//���� ������� ���� - �����������
		if (strstr(strFileName.GetBuffer(strFileName.GetLength()), ".sig") != NULL) {
			//��������� ��������������� ������������ ����
			COTDKDoc::strFName = "sigtess.exe ";
			COTDKDoc::strFName += File.GetFileName();
			ref = COTDKDoc::strFName.GetBuffer(strFName.GetLength());
			File.Close();
			//
			//������ ����� ����� ���������
			gFuncTest(ref, TRUE); //bHideShowTest);
			//
		}
		else if (strFileName.Find(".dia") != -1) {
			//��������� ��������������� ������������ ����
			COTDKDoc::strFName = "diatezzz.exe ";
			COTDKDoc::strFName += File.GetFileName();
			ref = COTDKDoc::strFName.GetBuffer(strFName.GetLength());
			File.Close();
			//������ ����� ����� ���������
			gFuncTest(ref, TRUE); //bHideShowTest);
			//
		}
		else if (strFileName.Find(".tre") != -1) { //���� ���������� ������ �������
			DWORD dwPosition = File.GetLength();
			UINT iStr = 0;
			//��������� ������� ������
			 struct {
				char sX;             //������ ������ ������������� ������ ������
				char Vetv[7];        //�����
				char Uchastok[12];   //������� �����
				char Perex[255];      //�������� �����
			}strV;
			long lX; int i;
			char *strStop;	CString csOpa;
			csOpa=File.GetFilePath(); csOpa=csOpa.Left(csOpa.ReverseFind('\\'));
			WritePrivateProfileString ("PATH", "WorkRoot", csOpa, r_Opn);
			//WorkINI WS;   // ������� ������ ������ ����������� ����
			//WS.m_WorkDir = 
			strWR=csOpa;
			//WS.UpdateData(FALSE); 
			//WS.Invalidate(NULL); 
			//��� ������� ������ ����������
			File.ReadString(s);	File.ReadString(s);
			//�������������� ������� - ������� ���� � �������� ����
			glsV.RemoveAll();	secondsV.RemoveAll();
			while (dwPosition > File.GetPosition()) {//���� �� ����� ����� ������
				File.ReadString(s); //������ ������ � �����				
				ZeroMemory(&strV,sizeof(strV)); //����������� ��� ����� ������
				strcpy(&strV.sX,s.GetBuffer(s.GetLength())); //��������� ����� ������
				lX = strtol(strV.Vetv,&strStop,0); //��������� �� ������ �����
				csOpa.Delete(1, csOpa.GetLength()); //������� ��� ������ �����
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
				if (lX > 0) { //���� ������ ���������� ��� ������ �����
					glsV.Add(csOpa); //��������� � ������ ���� ����� �����
					gVlNode(strV.Perex, csOpa);
				} //if
				else gVlNode(strV.Perex, csOpa);
				iStr++; //������� �����
			} // while
			//����� �������� ���������� ��������� ��� ������ �����
			csaDate.RemoveAll();			bbggrr.RemoveAll();
			bbggrr.Add(G_INFORMATION);
			AddString("#������������ �������������� �� ������ ������#");
			bbggrr.Add(G_INFORMATION);
			AddString("#��� ������ ������� '����'#");
			File.Close();
		}//else if
		else if (strFileName.Find(".trw") != -1) { //���� ��������� ����� ����� ��������
			CString sLine, sLineKey;
//			char buf[2];
			int iLineC=0;
			CArchive ar(&File,CArchive::load);
			if (ar.ReadString(sLine)) 
				 gRecTRW(0,sLine,&ar); //��������� ������� - ������� ���� � �������� ����
			ar.Close();
			File.Close();
			//����� �������� ���������� ��������� ��� ������ �����
			csaDate.RemoveAll();			bbggrr.RemoveAll();
			bbggrr.Add(G_INFORMATION);
			AddString("#������������ �������������� �� ������ ������#");
			bbggrr.Add(G_INFORMATION);
			AddString("#��� ������ ������� '����'#");
		}
		UpdateAllViews(NULL);    // �������� ����
	}//if DoModal
}
//������ �������� �� ������� ������� ���� �������� ����������� �������
CString COTDKDoc::GetItemValue(UINT index)
{
	CString str;
	str = glsV.GetAt(index);
return str;
}
//�������� ������ ������� ������� �����
int COTDKDoc::GetArrSize()
{
	return glsV.GetSize();

}
//������ ������ ��������� � ����� �������� (����������)
void COTDKDoc::gVlNode(char Perex[], CString csOpa)
{
	char* strStop;
	CString csOops, csYe, value;
	int i, x=0, y=0; BOOL bOK=TRUE;
	char buf[2];
	/* Establish string and get the first token: */
	strStop = strtok( Perex, "," );
	while( strStop != NULL ) {
		csYe.Delete(1, csYe.GetLength()); //������� ��� ������ �����
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
		secondsV.SetAt(csOops,csYe); //��������� ������ �������� ���������������� ����
		strStop = strtok( NULL, "," );
	}//while
}
//��������� ������ ��������� ��������� �����
void COTDKDoc::AddString(CString s)
{
	csaDate.Add(s);
}
//������ ������� ��������� ��������� �����
int COTDKDoc::GetcsaSize()
{
return csaDate.GetSize();
}
//������ ������ �� ������� �������� ��������� �����
CString COTDKDoc::GetcsaItem(int index)
{
	CString str;
	//str = &csaDate.ElementAt(index);
	str = csaDate.GetAt(index);	
return str;
}
//������� ������ �� ������� �������� ��������� �����
void COTDKDoc::RemovecsaItem(int x)
{
	csaDate.RemoveAt(x, 1);
}

//������� ������� ������ ������� �������� �� ������� = "ffff"
DWORD COTDKDoc::gGetPosString(DWORD StartPos, CString csFF, CStdioFile* Fl)
{
	CString csContact;
	//char buf[255];
	//LPTSTR x;
	BOOL bTF = TRUE;
	DWORD dwPosition = NULL;	
	if (csFF.GetLength() == 0) csFF = "ffff";
	Fl->Seek(StartPos,CFile::begin); //�������� ������ � ������ ����� ��������
	while (bTF) { //���� �� ����� �����
		bTF = Fl->ReadString(csContact); //��������� ������ ������
		//csContact.OemToAnsi();
		if (csContact.Find(csFF) != -1) { //���� ������ ������
			//����� ������� ������ �������
			dwPosition = Fl->GetPosition()-csContact.GetLength();
			break; //�������
		}//if
	}//while
	return dwPosition;
}
//������� ���������� � ������ ������� ������ (��� ������ ����)
//�������� ����� �������� ��� ������� ����
void COTDKDoc::OnMakesig() 
{
	CString csKey, csValue, csSD;
	CStdioFile Fl; 
	//COTDKView* clsV=NULL;
	iCount=0;
	HeadNode.RemoveAll();
	if (iOpenSig == 0) { //���� ������ ������ ������ �� �
		iOpenSig = 1; //������������� � ������� ����
		if (!secondsV.IsEmpty()) { //�������� �� ������� ����� ����
			POSITION pos = secondsV.GetStartPosition();				 
			while (pos != NULL) {
				secondsV.GetNextAssoc(pos, csKey, csValue);
				if (csKey.GetAt(0) == '1' && !(csKey.Mid(0,2).Compare("10") >= 0
					&& csKey.Mid(0,2).Compare("19") <= 0)) { 
					//��������� ��������� �� ��� ���� �������� ������� ����
					if (iChkDia == 0) csSD = ".sig";
					else csSD = ".dia";
					if (!Fl.Open(csKey.Mid(1) + csSD, CFile::modeRead)) {
							HeadNode.Add(csKey.Mid(1));
					}
					else Fl.Close();
				}
			}
			//�������� � ������ ������������ ����� �������� � ������� ����
			if (HeadNode.GetSize() > 0) {
				Sort(&HeadNode,HeadNode.GetSize()-1);
				bbggrr.InsertAt(1,G_WRITESIG);
				SetString(1,"��������� ��� �� ���� " + HeadNode.GetAt(0) + 
													" � ������� ������",TRUE);
			}
			else { //���� ��� ����� �������� ���� �������� �� ����
				bbggrr.SetAt(1,G_MESSAGE);
				SetString(1,"�������� ������ ��������(�����������) ���������!",FALSE);
				iOpenSig = 0; //�������� ������ ������ �������� ������ ��������
			}
		}
		else {
			bbggrr.InsertAt(1,G_INFORMATION);
			SetString(1,"������� ���� ������� ���� ������ ����",TRUE);
			iOpenSig = 0;
		}
		//��������� � �������� ����� ������� ����
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView(pos);
		UpdateAllViews(pView);		pView = GetNextView(pos);
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetActiveView(pView,TRUE);
		//pView->UpdateWindow();   
	}
	else { //���� ������ � ������� ���������, �������� ��
		iOpenSig = 0; iCount=0;
		HeadNode.RemoveAll();
	}
}

void COTDKDoc::OnUpdateMakesig(CCmdUI* pCmdUI) 
{
	// ��������� ���� ������ ������������ ������ �������� �
	//����������� �� ������� ������
	pCmdUI->SetCheck(iOpenSig);
}
//������� �������� ����� �������� ��� �����
BOOL COTDKDoc::gRecTRW(int previndent, CString sLineKey,CArchive* ar)
{
	int rasindent, indent; CString sLine, value,siKey;
	int baseindent = previndent; int iLineC;
	char buf[2]; BOOL bOpa = TRUE;
	CMapStringToString map;
	CMapStringToString mapLine;
	if (previndent == 0) {
		glsV.Add(sLineKey); //���������� ����� ���� � ������
		itoa(previndent,buf,10);
		map.SetAt(buf,sLineKey);
		mapLine.SetAt(sLineKey,"1");
		baseindent = previndent;
	}
	while (ar->ReadString(sLine)) { //���� ���� ������ �� �������� ������ ������
		for(indent=0;sLine[indent]=='\t';indent++);
		sLine=sLine.Right(sLine.GetLength()-indent);
		secondsV.SetAt("1" + sLine, "/"); //���������� ���� ����
		if (indent == 0) gRecTRW(0,sLine,ar); //break; //��������� � �������
		rasindent = indent - baseindent; //��������� ����� ��� �������
		if (rasindent == 0) { //���� ������ ���, ������ ��� ��������� ����
			//�� �� �������
			itoa(indent,buf,10);
			map.SetAt(buf,sLine); indent--; //���������� ���� � ������
			itoa(indent,buf,10);
			map.Lookup(buf,value); 
			mapLine.Lookup(value,siKey);
			iLineC = atoi(siKey); iLineC++; itoa(iLineC,buf,10);
			mapLine.SetAt(value,buf); //siKey);
			value=buf + value;
			secondsV.SetAt(value,sLine); //� ��� ���������� �������
			mapLine.SetAt(sLine,"1");
		}//end if rasindent == 0
		else if (rasindent < 0) { //���� �������� ������ ����� ����
			//������ ��� ������ �������� ������� ��� ������ ����� �����
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
		else if (rasindent == 1) { //���� ��� ������� �������� ���� (�������)
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
// ������ Word ����� ���� �� ���� 
void COTDKDoc::OnWord() 
{
ShellExecute(NULL, "open", strFileName.Mid(0,strFileName.GetLength()-3) + "doc",
             NULL, NULL, SW_SHOWNORMAL);
	
}
// ���������� �� ������ Word ����� ���� �� ����
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
	if (iChkSig == 0) { //���� ������ ������ ������ �� �
		iChkSig = 1; //������������� � ������� ����
		gGetNode(); //��������� ���� ��� ������ ������������
		Sort(&HeadNode,HeadNode.GetSize()-1);
		gMesNode(iCount); // ������� ��������� � ������ ������������
	}
	else { //���� ������ � ������� ���������, �������� ��
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
	if (iChkDia == 0) { //���� ������ ������ ������ �� �
		iChkDia = 1; //������������� � ������� ����
		bbggrr.InsertAt(1,G_INFORMATION);
		SetString(1,"��������� � ���������������� ������������",TRUE);
	}
	else {
		iChkDia = 0;
	}
	
}
// ������� ���� ������
void COTDKDoc::OnCLOSEFILE() 
{
	bClose=TRUE;
		HWND hWnd = GetActiveWindow();
		::SetWindowText(hWnd,csHead); strFileName = "";
	csaDate.RemoveAll();		
	bbggrr.RemoveAll();
	UpdateAllViews(NULL);    // �������� ����
}

void COTDKDoc::gGetNode()
{
	CString csKey, csValue;
	CStdioFile Fl; 
	//COTDKView* clsV=NULL;
	HeadNode.RemoveAll();
	if (!secondsV.IsEmpty()) { //�������� �� ������� ����� ����
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
		SetString(1,"������� ���� ������� ���� ������ ����",TRUE);
		iChkSig = 0;
	}
}

void COTDKDoc::OnFindnode() 
{
	FindNode dlgFN;
	dlgFN.DoModal(); // ��������� ������ �� ���� ����� �������� ����
	CString csFN=dlgFN.m_find; // �������� ��� �������� ����
	if (iChkSig==1) { // ���� �������  ����� �������� �����
		gGetNode(); // ��������� ������ ���� ����� ������
		Sort(&HeadNode,HeadNode.GetSize()-1);
		int count = HeadNode.GetSize(); // ����� ������ ����� �������
		for( int x=0; x<count; ++x) {
			if (csFN.CompareNoCase(HeadNode.GetAt(x))==0) break; // ���� ���� � �������
		}
		if (x!=count) iCount =x; // ���� ����� ���������� ������ ���������� ����
		// ����������� ���� �� ��������
		gMesNode(iCount); // ������� ��������� � ������ ������������
	}
	else { // ����� (�� ���. ����� ��������) ������ ����� ���� �� ������
		CLeftView* pView;
		pView=(CLeftView*)((CMainFrame*) AfxGetApp()->m_pMainWnd)->GetActiveView();
		pView->gFindItem(csFN); // ��������� ����� ����
	} // end else
	
}

void COTDKDoc::gMesNode(int cnt)
{
		//�������� � ������ ������������ ����� �������� � ������� ����
		if (HeadNode.GetSize() > 0) {
			bbggrr.InsertAt(1,G_WRITESIG);
			SetString(1,"��������� ��� �� ���� " + HeadNode.GetAt(cnt) + 
																					" � ������� ������",TRUE);
		}
		//��������� � �������� ����� ������� ����
		POSITION pos = GetFirstViewPosition();
		CView* pView = GetNextView(pos);
		UpdateAllViews(pView);		pView = GetNextView(pos);
		((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetActiveView(pView,TRUE);

}
