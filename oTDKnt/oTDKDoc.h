// oTDKDoc.h : interface of the COTDKDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include <afxtempl.h>

#if !defined(AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_)
#define AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COTDKDoc : public COleDocument
{
protected: // create from serialization only
	COTDKDoc();
	DECLARE_DYNCREATE(COTDKDoc)

// Attributes
public:	
	CString strFName;   //��� �����
	CStringArray HeadNode; //������ ����� ����� �������� ��������
	CStringArray glsV; //������ ������� ����
	CMapStringToString secondsV; //������ �������� ����
	CArray<COLORREF,COLORREF> bbggrr; //������ ������ ��������� �����
	int iOpenSig; //�������������� ��������� ������� ������� ������������
														//������ ��������
	int iChkSig; //�������������� ��������� ������� ������� ��������
														//������ ��������
	int iChkDia; //�������������� ��������� ������� ������� 
											//��������������� ��������
	int iChkWord; //�������������� ��������� ������� ������� ��������� Word
	//��������� ��� ������ ������� ���������� �������� � ������ ��������
	int iCount; // ���������� ������
	// ������� �������� � �������� ������
	struct stPos {
		DWORD dwPos1;
		DWORD dwPos2;
		DWORD dwPos3;
	}stPos;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COTDKDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL bClose; // ������� �������� ����� ������
	// �������� ������� ��������� � �������� �����
	DWORD gGetPosString(DWORD StartPos, CString csFF, CStdioFile* Fl);
	void RemovecsaItem(int x); //������� ������ �� ������� �������� ��������� �����
	CString GetcsaItem(int index); //������ ������ �� ������� �������� ��������� �����
	int GetcsaSize(); //������ ������� ��������� ��������� �����
	void AddString(CString s); //�������� ������ � ������ ��������� ��������� �����
	int GetArrSize(); //�������� ������ ������� ������� �����
		//������ �������� �� ������� ������� ���� �������� ����������� �������
	CString GetItemValue(UINT index); 
	void OnOpen(); // �������� ����� ������
	void SetString(int x, CString s, BOOL bTF); //���������� ������ ��� ������ � ������ �������� �����
	CString GetDate(); // ������ ������
	virtual ~COTDKDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void gGetNode();
	void gMesNode(int cnt);
	CString csDate; //��������� ������ � ������� ������
	CString strFileName;  // ��� ��������� ����� ������
	CStringArray csaDate; //������ ���������� ��������� �����
	//{{AFX_MSG(COTDKDoc)
	afx_msg void OnMakesig();
	afx_msg void OnUpdateMakesig(CCmdUI* pCmdUI);
	afx_msg void OnWord();
	afx_msg void OnUpdateWord(CCmdUI* pCmdUI);
	afx_msg void OnChksig();
	afx_msg void OnUpdateChksig(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDiap(CCmdUI* pCmdUI);
	afx_msg void OnDiap();
	afx_msg void OnCLOSEFILE();
	afx_msg void OnFindnode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL gRecTRW(int previndent, CString sLineKey, CArchive* ar);
	void gVlNode(char Perex[50], CString csOpa);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTDKDOC_H__97EA3B8B_9AEB_11D5_BD12_005004230E79__INCLUDED_)
