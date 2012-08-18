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
	cwndEntrPer=NULL;  // ��������� �������� ��������� ����
	glsV.RemoveAll(); // ������ ������� �������� ����� ������
	csaUch.RemoveAll(); // ������ �������� �������� (�����)
	Branch=FALSE; //����� ����� (FALSE) ��� ������ (TRUE)
	ibranch=0; // ����� �����
	poQueue = 0; //��������� �����������
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
// ����� ��  ����� �������� ������ ����������� ������
void CTreeMake::OnOK() 
{
	//if (MessageBox("�� ��������� ���� ������?"," ", MB_YESNO) == IDYES) {
		glsV.RemoveAll();
		csaUch.RemoveAll();
		if (theFile.GetFileName() != "") theFile.Close();
		CDialog::OnOK();		
	//}
}

void CTreeMake::OnKillfocusEntr() 
{
	UpdateData(TRUE);
	// ���� ������ ����� �����
	if (m_startnew == TRUE) {
		if (!m_EnterNode.IsEmpty()) {
			m_startnew = FALSE; //�������� ����� �����
			//m_EnterNode.Replace(".","_"); //������ ����� �� ������� �� ����������
			m_CurrentNode = m_EnterNode;
			csaUch.Add(m_EnterNode); //��������� ������ �������� ��������
			Branch=TRUE; ibranch++;
			UpdateData(FALSE);	
		}
	}
	else Branch=FALSE;
}
// ����� ������� ������ � �����
BOOL CTreeMake::PreTranslateMessage(MSG* pMsg) 
{
	ASSERT(m_hWnd != NULL);
	// ������ �� �������
	if(pMsg->message == WM_KEYDOWN)	{ //���� ������, �� ��� �������:
																				//����� (ENTER), ������ (ESCAPE) ��� F2
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE ||
					pMsg->wParam == VK_F2) {
			switch(pMsg->wParam) {
				case VK_RETURN: // ���� ��� ������� �����
					// ��� �� ������ 
					if (cwndEntrPer == GetDlgItem(IDC_ENTR)) {
						cwndEntrPer = GetDlgItem(IDC_PEREX); //��������� � ���� �������� ���������
						cwndEntrPer->SetFocus();
					}					
					else if (cwndEntrPer == GetDlgItem(IDC_PEREX)) gMadePerex();  //������������ ��������
					else if (cwndEntrPer == GetDlgItem(IDC_EDIT1)) gPereschet();  //������������� ��������� �������� ������
					break;
				case VK_ESCAPE:
					// ��� �� ������ 
					break;
				case VK_F2:
					//����� �� F2
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
	// �������� ����� ������� �����
	m_EnterNode = ""; m_CurrentNode = ""; m_Perexod = "";	
	
}

void CTreeMake::OnNewtree() 
{
	// ������� ����� ������	
	// ��������� ������� �������� ������ ������
	cwndEntrPer = GetDlgItem(IDC_ENTR);
	cwndEntrPer->EnableWindow(TRUE);
	cwndEntrPer = GetDlgItem(IDC_STARTNEW);
	cwndEntrPer->EnableWindow(TRUE);	
	cwndEntrPer = GetDlgItem(IDC_PEREX);
	cwndEntrPer->EnableWindow(TRUE);
	UpdateData(TRUE);
	//������� ���� ���� ���������
	CString fPath = strWR+ "\\"; 
	fPath += m_namefile;
	theFile.Open(fPath  + ".tre",CFile::modeCreate| CFile::modeWrite);
	CArchive arpoint(&theFile,CArchive::store);
	// ������ 2-� ������� (����� ���� ������)
	arpoint.WriteString("(c) ����, ���, ������ XXI ���� \r\n");
	arpoint.WriteString("�����   �������     �������\r\n");
	arpoint.Close();
	// ���� ��� ����������� �� ������
	m_edit+="(c)  ����, ���, ������ XXI ���� \r\n"; 	m_edit+="�����   �������     �������\r\n";
	UpdateData(FALSE);
	theFile.SeekToEnd();
}
// ����� ����� ���� � ���������� �������
BOOL CTreeMake::gLocalNode(CString cs, CStringArray *csa)
{
	for(int i=0; i<=csa->GetSize()-1; i++) {
		if (csa->GetAt(i) == cs) return(TRUE);
	}
	return(FALSE);
}
// ������� � ���� ����
void CTreeMake::OnSetfocusEntr() 
{
	cwndEntrPer = GetFocus();
	
}
// ����� ����� ���������� ������ � ������������ � ����
void CTreeMake::OnLoadtree() 
{
	//�������������� ������� - ������� ���� � �������� ����
	glsV.RemoveAll();	
	poQueue=0;
	csaUch.RemoveAll();
	if (theFile.GetFileName() != "") theFile.Close();
	//
	CFileDialog DlgOpen(TRUE,(LPCSTR)"tre", strWR + "\\*.tre", OFN_HIDEREADONLY,
												(LPCSTR)"BinTrees Files (*.tre)||");  
	// ����������� ����������� ������ ������ ����� Open 
	if(DlgOpen.DoModal()==IDOK) { 		// �������� ����� ��� ������ 
		gOpenFile(DlgOpen.GetPathName());
	} // if DlgOpen
}
// ������������ �������� ������� � �������� �������� (�����)
void CTreeMake::gVlNode(char Perex[], CString csOpa)
{
	char* strStop;
	CString csYe, csPerex;
	CStringArray csaM;
	int i, k=0;
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
				//����� ���� ��� �� �� ����� ������
				csPerex=csaM.GetAt(j-1);
				if (!gLocalNode(csPerex, &glsV)  && !gLocalNode(csPerex, &csaUch)) {
					//���� ����� �� ������, ��
					//��������� ������ �������� ���������������� ����
					//���������� ���� � ������� ���� ����� ������
					glsV.Add(csPerex);
				}
			}// end for
		}//end if strStop != "/"
		if (poQueue < glsV.GetSize()) {
			csaUch.Add(glsV.GetAt(poQueue)); 
			// ����� ������� � ������ ����
			m_CurrentNode = glsV.GetAt(poQueue); m_Perexod = ""; poQueue++; Branch = FALSE;
			m_startnew = FALSE; UpdateData(FALSE);	
		}
		else { //..����� �������� ������� � ����� �����
			m_CurrentNode = ""; m_Perexod = "";	m_EnterNode = ""; m_startnew = TRUE;	
			UpdateData(FALSE);	
			//cwndEntrPer = GetDlgItem(IDC_ENTR);	cwndEntrPer->SetFocus(); 
		}
}
// ������� ���������������� �������� ������ ������ ������������ ����
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
	//���� ���� ��������� �� �����, ��
	if (!m_CurrentNode.IsEmpty()) {
		csCurNode = m_CurrentNode; 
		//m_Perexod.Replace(".","_");
		// ������ ��������� � ����
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
		// ����� ������ � ����
		m_edit += s;  m_edit +="\r\n";
		//���� � �������� �� ������ ����� ����� (��������) - ���� /
		if (m_Perexod.Compare("/") != 0) {
			//csPerex=m_Perexod;
			strStop = strtok( m_Perexod.GetBuffer(m_Perexod.GetLength()), "," );
			//����������� ������������������ ��������� � ������
			while( strStop != NULL ) {
				k++;
				csaM.Add(strStop);
				strStop = strtok( NULL, "," );
			}//while
			for (int j=1; j<=k; j++) {
				//����� ���� ��� �� �� ����� ������
				csPerex=csaM.GetAt(j-1);
				if (!gLocalNode(csPerex, &glsV)  && !gLocalNode(csPerex, &csaUch)) {
					//���� ����� �� ������, ��
					//��������� ������ �������� ���������������� ����
					//���������� ���� � ������� ���� ����� ������
					glsV.Add(csPerex);
				}
			}// end for
		}//end if strStop != "/"
		if (poQueue < glsV.GetSize()) {
			csaUch.Add(glsV.GetAt(poQueue)); 
			// ����� ������� � ������ ����
			m_CurrentNode = glsV.GetAt(poQueue); m_Perexod = ""; poQueue++; Branch = FALSE; 
			m_startnew = FALSE; UpdateData(FALSE);	 
		}
		else { //..����� �������� ������� � ����� �����
			m_CurrentNode = ""; m_Perexod = "";	m_EnterNode = ""; m_startnew = TRUE;	
			UpdateData(FALSE);	
			cwndEntrPer = GetDlgItem(IDC_ENTR);	cwndEntrPer->SetFocus(); 
		}
	}//end if ���� ������� ����
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
		//��������� ������� ������
		struct {
			char sX;             //������ ������ ������������� ������ ������
			char Vetv[7];        //�����
			char Uchastok[12];   //������� �����
			char Perex[255];      //�������� �����
		}strV;
		long lX; int i;
		char *strStop;	CString csOpa, s;
		//��� ������� ������ ����������
		ar.ReadString(s);	//ar.ReadString(s);
		m_edit += s;  m_edit +="\r\n";
		while (ar.ReadString(s)) {//���� �� ����� ����� ������
			//ar.ReadString(s); //������ ������ � �����				
			m_edit += s;  m_edit +="\r\n";
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
					//case '.': csOpa += '_'; break;
					default: csOpa += strV.Uchastok[i];
				}//switch
			}//for
			//���� ������ ���������� ��� ������ �����
			if (lX > 0)  { ibranch++; m_EnterNode = csOpa; }
			csaUch.Add(csOpa); //��������� � ������ ���� ����� �����
			gVlNode(strV.Perex, csOpa);
			iStr++; //������� �����
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
