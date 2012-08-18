// OTDKView.cpp : implementation file
//

#include <stdafx.h>
#include "oTDK.h"
#include "OTDKDoc.h"
#include "OTDKView.h"
#include "MainFrm.h"

#include "WwF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COTDKView

IMPLEMENT_DYNCREATE(COTDKView, CView)

COTDKView::COTDKView()
{
	bWhat=TRUE;
}

COTDKView::~COTDKView()
{
}


BEGIN_MESSAGE_MAP(COTDKView, CView)
	//{{AFX_MSG_MAP(COTDKView)
		ON_WM_KEYDOWN()
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COTDKView drawing

void COTDKView::OnDraw(CDC* pDC)
{
	LOGFONT logFont;
	logFont.lfHeight=18;
	logFont.lfWidth = 0;
	logFont.lfEscapement = 0;
	logFont.lfOrientation = 0;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfItalic = 0;
	logFont.lfUnderline = 0;
	logFont.lfStrikeOut = 0;
	logFont.lfCharSet = DEFAULT_CHARSET;
	logFont.lfQuality = PROOF_QUALITY;
	logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	UINT position = 0;
	int i=0;
	strcpy(logFont.lfFaceName, "Times New Roman");
	CFont font;
	CPoint point;
	//
	font.CreateFontIndirect(&logFont);
	COTDKDoc* pDoc = GetDocument();
	CFont* oldFont = pDC->SelectObject(&font);
	point = pDC->GetCurrentPosition();  
	position += point.y; 
	for (i=0; i <= pDoc->GetcsaSize()-1; i++) {
		pDC->SetTextColor(pDoc->bbggrr.GetAt(i)); //0x00bbggrr
		pDC->TextOut(1,position,pDoc->GetcsaItem(i));
		position += logFont.lfHeight;
	}
	CView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// COTDKView diagnostics

#ifdef _DEBUG
void COTDKView::AssertValid() const
{
	CView::AssertValid();
}

void COTDKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COTDKView message handlers

COTDKDoc* COTDKView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COTDKDoc)));	// ��������� ���� �� ����� ���������	
	return (COTDKDoc*)m_pDocument;				// ������� ���������.
}
void COTDKView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	COTDKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	//���� ������� ����� ������ ����� ��������
	if (nChar == VK_SPACE && pDoc->iOpenSig == 1 && nRepCnt == 1)  {
		if (!bWhat) bWhat=TRUE; 
	}
	//���� ������� ����� �������� ��� ���������� ��������
	if (nChar == VK_SPACE && pDoc->iChkSig == 1 && nRepCnt == 1) {
		if (bWhat) bWhat=FALSE;
	}
	//�������� �������� �� � ��������������� �������������
	if (pDoc->iChkDia == 1) gPressKeyDia(bWhat);
	else gPressKey(bWhat);
CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COTDKView::gAddSigInTest(CString csNameNode, CString csBuf, int iCountT)
{
	LPTSTR p=NULL; DWORD dwPosition=NULL;
	CString s1=' '; CStdioFile Fl;
	COTDKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); 
	s1 = csBuf.Mid(0,4);
	p =  s1.GetBuffer(4);
	//����� �������� ���� ��������� ������ � ������ ���������
	Fl.Open(csNameNode + ".sig", CFile::modeReadWrite); 
	if (iCountT == 1) {
		if (iCountTest==1) dwPosition = pDoc->gGetPosString(0, "ffff", &Fl);
		else dwPosition = pDoc->stPos.dwPos1;
	}
	else if (iCountT == 2) {
		if (iCountTest==2) {
			pDoc->stPos.dwPos1 = pDoc->gGetPosString(0, "ffff", &Fl);
			pDoc->stPos.dwPos2 = pDoc->gGetPosString(pDoc->stPos.dwPos1, "ffff", &Fl);
		}
		dwPosition = pDoc->stPos.dwPos2;
	}
	else {
		pDoc->stPos.dwPos1 = pDoc->gGetPosString(0, "ffff", &Fl);
		pDoc->stPos.dwPos2 = pDoc->gGetPosString(pDoc->stPos.dwPos1, "ffff", &Fl);
		pDoc->stPos.dwPos3 = pDoc->gGetPosString(pDoc->stPos.dwPos2, "ffff", &Fl);
		dwPosition = pDoc->stPos.dwPos3;
	}
	Fl.Seek((LONG)dwPosition-1, CFile::begin);
	Fl.Write(p,4); 	Fl.Close();
}

void COTDKView::gPressKey(BOOL bWhat)
{
CStdioFile Fl,FlNode;
CString csNameNode, s, csBuf, csValue;
BOOL CriticalExit = FALSE, bContin=FALSE;
CStringArray csaBuf;
//int iCountTest=3; 
UINT i=0;
LPTSTR ref;
COTDKDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc); 
//
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("������!");
	if (pDoc->iCount <= pDoc->HeadNode.GetSize()-1) {
		if (CriticalExit == FALSE)
						csNameNode = pDoc->HeadNode.GetAt(pDoc->iCount);
		else CriticalExit = FALSE;
		//��������� �������� ������ ��������� � ������ ����������
		if (Fl.Open(strTF, CFile::modeRead)) {
			//����������� �����
			if (bWhat) {
				FlNode.Open(csNameNode + ".sig", CFile::modeCreate);
				FlNode.Close();
				FlNode.Open(csNameNode + ".sig", CFile::modeWrite);
				while (Fl.GetPosition() < Fl.GetLength()) {
					Fl.ReadString(csBuf);
					FlNode.WriteString(csBuf + "\n");
				}//end while
				FlNode.Close();
			}
			Fl.Close(); 
			//
			s = "sigteze.exe ";	s += csNameNode; s += ".sig";
			ref = s.GetBuffer(s.GetLength());
			if (!bWhat) i=iCountTest; else i=1;
			//������ ����� ���������
			for (; i<=iCountTest; i++) {
				//������ tempo.s ����
				Fl.Open("tempo.s", CFile::modeCreate);	Fl.Close(); 
				gFuncTest(ref, bHideShowTest);
				csBuf = gResultTest(TRUE);
				csaBuf.Add(csBuf);
				//} //next
				//������ ���������� ������������
				if (!bWhat) {
					if (csBuf.GetLength() != 0) {
						pDoc->bbggrr.SetAt(1,G_ALERT);
						pDoc->SetString(1,"������������ " + csBuf,FALSE);
						Invalidate(TRUE);		
						if (AfxMessageBox("����������?", MB_YESNO) == IDNO ) CriticalExit = TRUE;
					}
				}
				else {
					gAddSigInTest(csNameNode, csBuf, iCountTest-(i-1));
				} // else 
			} // next
			if (bWhat) {
				if (gSigOneZero(&csaBuf)) {
					pDoc->bbggrr.SetAt(1,G_ALERT);
					pDoc->SetString(1,"���������� ������������ = 0 ��� 1",FALSE);
					Invalidate(TRUE); 
					if (AfxMessageBox("���������� ������������ = 0 ��� 1, ����������?",
																										MB_YESNO) == IDNO )	CriticalExit = TRUE;
				} // end if
				else {
					if (gSigNesov(&csaBuf)) {
						pDoc->bbggrr.SetAt(1,G_ALERT);
						pDoc->SetString(1,"������������ �������� ���� ��������",FALSE);
						Invalidate(TRUE); CriticalExit = TRUE;
					} // end if
				} // end else
			} // end if bWhat
			//������������ ������ ��������
			if (CriticalExit == FALSE) {
				pDoc->iCount++;
				if (pDoc->HeadNode.GetSize()-1 >= pDoc->iCount)
					csNameNode = pDoc->HeadNode.GetAt(pDoc->iCount);
			}
			if (pDoc->HeadNode.GetSize()-1 >= pDoc->iCount) {
				pDoc->bbggrr.InsertAt(1,G_WRITESIG);
				pDoc->SetString(1,"��������� ��� �� ���� " + csNameNode + 
													" � ������� ������",TRUE);
				MessageBeep(MB_OK);
			}
			else {
				pDoc->bbggrr.SetAt(1,G_MESSAGE);
				pDoc->SetString(1,"�������� ������ �������� ���������!", FALSE);
				pDoc->iOpenSig = 0; pDoc->HeadNode.RemoveAll();
			}
		}//end if copytemp.sig here
		else {
			pDoc->bbggrr.SetAt(1,G_INFORMATION);
			pDoc->SetString(1,"��� ����� ������� ��� �����������",FALSE);
		}
	}//end if HeadNode.GetSize
	else {
		pDoc->bbggrr.SetAt(1,G_MESSAGE);
		pDoc->SetString(1,"�������� ������ �������� ���������!", FALSE);
		pDoc->iOpenSig = 0; pDoc->HeadNode.RemoveAll();
	}
	Invalidate(TRUE);
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("���� �����");
	MessageBeep(MB_OK);
}

void COTDKView::gPressKeyDia(BOOL bWhat)
{
CStdioFile Fl,FlNode;
CString csNameNode, s, csBuf, csValue;
BOOL CriticalExit = FALSE, bContin=FALSE;
// ���������� ������ � ��������������� ������������
int iCDTest=iCountDTest;
int i=0;
LPTSTR ref;
CStringArray csaTestResult;
//
COTDKDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc); 
//
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("������!");
	if (pDoc->iCount <= pDoc->HeadNode.GetSize()-1) {
		if (CriticalExit == FALSE)
						csNameNode = pDoc->HeadNode.GetAt(pDoc->iCount);
		else CriticalExit = FALSE;
		//��������� �������� ������ ��������� � ������ ����������
		if (Fl.Open(strTD, CFile::modeRead)) {
			//����������� �����
			if (bWhat) {
				FlNode.Open(csNameNode + ".dia", CFile::modeCreate);
				FlNode.Close();  DWORD dwPosition=0; DWORD dwLen=Fl.GetLength();
				FlNode.Open(csNameNode + ".dia", CFile::modeWrite);
				while ( dwPosition < dwLen) {
					Fl.ReadString(csBuf); dwPosition = Fl.GetPosition();
					FlNode.WriteString(csBuf + "\n");
				}//end while
				FlNode.Close();
			}// bWhat
			Fl.Close();
			//
			s = "diatess.exe ";	s += csNameNode; s += ".dia";
			ref = s.GetBuffer(s.GetLength());
			//������ ����� ���������
			if (bWhat) {
				i=1; if (bAutoCheck) iCDTest++;
			}
			else i=iCDTest;
			
			for(; i<=iCDTest; i++) {
				//������ tempo.s ����
				Fl.Open("tempo.s", CFile::modeCreate);	Fl.Close(); 
				// ��������� ������������
				gFuncTest(ref, bHideShowTest);
				csBuf = gResultTest(FALSE); // ����� ���������
				// ���������� ��������� ������������ � ������� �����������
				if (csBuf.GetLength() != 0) {
					// ���� ���� ������ ��������
					csaTestResult.Add(csBuf);
					if (i==iCDTest && bAutoCheck) bWhat=FALSE;
					if (bWhat) {
						gAddDiaInTest(csNameNode, csBuf, i);
					}// end if bWhat
					else { // ����� ������ ��������, �������� � ������������ 
						if (AfxMessageBox("���� �� ������ - ������������, ����������?",
																								MB_YESNO) == IDNO ) CriticalExit = TRUE; 
					}
				}// �������� ���� ���� �����-�� �����������
			} // end for �� ���-�� ������
			// �������� �������� ���������� �������� �� 0
			if (bWhat) {
				if (gOneZero(&csaTestResult)) {
					if (AfxMessageBox("���������� ������������ = 0, ����������?",
																								MB_YESNO) == IDNO ) CriticalExit = TRUE; 
				}
			}
			//������������ ������ ��������
			// ������� � ���������� ����
			if (CriticalExit == FALSE) {
				pDoc->iCount++;
				if (pDoc->HeadNode.GetSize()-1 >= pDoc->iCount)
								csNameNode = pDoc->HeadNode.GetAt(pDoc->iCount);
			}
			if (pDoc->HeadNode.GetSize()-1 >= pDoc->iCount) {
				pDoc->bbggrr.InsertAt(1,G_WRITESIG);
				pDoc->SetString(1,"��������� ��� �� ���� " + csNameNode + 
													" � ������� ������",TRUE);
				MessageBeep(MB_OK);
			}
			else {
				pDoc->bbggrr.SetAt(1,G_MESSAGE);
				pDoc->SetString(1,"�������� ������ ����������� ���������!", FALSE);
				pDoc->iOpenSig = 0; pDoc->HeadNode.RemoveAll();
			}
		}//end if diagtemp.dia here
		else {
			pDoc->bbggrr.SetAt(1,G_INFORMATION);
			pDoc->SetString(1,"��� ����� ������� ��� �����������",FALSE);
		}
	}//end if HeadNode.GetSize
	else {
		pDoc->bbggrr.SetAt(1,G_MESSAGE);
		pDoc->SetString(1,"�������� ������ ����������� ���������!", FALSE);
		pDoc->iOpenSig = 0; pDoc->HeadNode.RemoveAll();
	}
	Invalidate(TRUE);
	((CMainFrame*) AfxGetApp()->m_pMainWnd)->SetStatusBarMes("���� �����");
	MessageBeep(MB_OK);
}

void COTDKView::gAddDiaInTest(CString csNameNode, CString csBuf, int iCountDT)
{
	LPTSTR p=NULL; DWORD dwPosSch = 0, dwPosO2 = 0; char buf[2];
	CString csS, csW, csNameOfFind; CStdioFile Fl; int iCycle = 0;
	int j = 0, x = 0; int i=1, k=0;
	COTDKDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	// ��������� ���� ����.����� ��� �������������. ����
	Fl.Open(csNameNode + ".dia", CFile::modeReadWrite); 
	//itoa - ������� ����� � ������
	// �������� # ����� 
	itoa(iCountDT,buf,10);
	csNameOfFind = "��������"; csNameOfFind +=  buf; 
	csNameOfFind.AnsiToOem(); // ��������� � OEM �������� 
	dwPosSch = pDoc->gGetPosString(0, csNameOfFind, &Fl);
	/*// �������� ����� ������� ���������� ������ � �����
	csNameOfFind = "�����������"; 	csNameOfFind.AnsiToOem(); 
	dwPosSch = pDoc->gGetPosString(dwPosSch, csNameOfFind, &Fl);
	//�������� ����� ������
	Fl.Seek((LONG)dwPosSch+10,CFile::begin);
	Fl.Read(buf, 2);	iCycle = atoi(buf);*/
	// ���� ��������� ������� �������� ����� = �1
	dwPosSch = pDoc->gGetPosString(dwPosSch, "o1=signatura", &Fl);
	// � � ��� ���� ��������� ������� ffff
	Fl.ReadString(csS); Fl.ReadString(csS); 
	dwPosSch = Fl.GetPosition();
	dwPosO2 = pDoc->gGetPosString(dwPosSch, "o2=counter", &Fl);
	Fl.ReadString(csS); Fl.ReadString(csS); 
	dwPosO2 = Fl.GetPosition();
	// ����� ����� ����� ���������� ����� ����� � ���������� ��� ��������
	//dwPosSch = (DWORD)Fl.Seek((LONG)1, CFile::current);
	iCycle = (int)csBuf.GetLength()/12;
	while(i <= iCycle) {
		// ����� ��� ������
		//j = j + 4;	
		csS = csBuf.Mid(j,4);
		// ����� ����� �����
		j = j + 4;	csW = csBuf.Mid(j,2); j = j + 2; 
		if (csW.Find("0a") == 0) csW = "10";
		else if	(csW.Find("0b") == 0) csW = "11";
		else if	(csW.Find("0c") == 0) csW = "12";
		else if	(csW.Find("0d") == 0) csW = "13";
		else if	(csW.Find("0e") == 0) csW = "14"; 
		else if	(csW.Find("0f") == 0) csW = "15";
		x = atoi(csW.GetBuffer(2));
		if (i == x + 1) {
			if (k == 0) {
				Fl.Seek((LONG)dwPosSch+x*6, CFile::begin);  
				if (i < iCycle) csS+="\n\r";
				p =  csS.GetBuffer(6); k = 1;
			}
			else {
				Fl.Seek((LONG)dwPosO2+x*6, CFile::begin);   
				if (i < iCycle) csS+="\n\r";
				p =  csS.GetBuffer(6); k = 0; i++;
			}
			Fl.WriteString(p); //Write(p,4); 
		}
		else while (i < x + 1) i++;	
	}// while i
	Fl.Close();
}
// �������� ������� ���-��� �������� �� "������" ����
// TRUE ���� ����� � �������
// FALSE ���� �� �����
BOOL COTDKView::gOneZero(CStringArray* csaRT)
{
	int j=0, l=0, x = 1;
	CString csCheck, csW="";
	// ������ ��� ���� ���� ������
	for(int i=0; i<=csaRT->GetSize()-1;i++) {
		// ����� ������ ��������� ������������ ��� �����.� �����
		csCheck = csaRT->GetAt(i);
		while(j <= csCheck.GetLength()) {
			if (x % 2 == 0) {	
				csW = csCheck.Mid(j,4);	if (csW.Find("0000") == -1) l++;  
			}
			j = j + 6; x++;
		}// while l
		j=0; x=1;
	}// for i
	if (l == 0) return(TRUE); // ���� 0000 
	else return(FALSE);
}
//
BOOL COTDKView::gSigOneZero(CStringArray* csaSOZ)
{
	CString csValue, csBuf;
	BOOL bRtn = FALSE; int x=0;
	for (int i=0; i<=csaSOZ->GetSize()-1; i++) {
		csBuf=csaSOZ->GetAt(i);
		csValue = csBuf.Mid(csBuf.GetLength()-4);
		if (csValue.CompareNoCase("0001") == 0 || csValue.CompareNoCase("0000") == 0) x++;
	}// next
	if (x==csaSOZ->GetSize()) bRtn= TRUE;
	return bRtn;
}

BOOL COTDKView::gSigNesov(CStringArray *csaSOZ)
{
	CString csBuf;
	BOOL bRtn = FALSE; int x=0;
	for (int i=0; i<=csaSOZ->GetSize()-1; i++) {
		csBuf=csaSOZ->GetAt(i);
		if (csBuf.GetLength()!=0) 
			if (csBuf.Mid(0,4).Find(csBuf.Mid(8,4)) != 0) x++;
	}// next
	if (x>0) bRtn= TRUE;
	return bRtn;
}
