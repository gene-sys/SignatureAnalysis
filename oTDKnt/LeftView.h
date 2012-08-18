// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__97EA3B8F_9AEB_11D5_BD12_005004230E79__INCLUDED_)
#define AFX_LEFTVIEW_H__97EA3B8F_9AEB_11D5_BD12_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
class COTDKDoc;
// ����� ��� ��������� ����������� ������ ����
class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	COTDKDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void gFindItem(CString csFI);
	int gTotalCount(CString MyNameIs); //���������� �������� ������� ����
	//����������� ������� ���������� ������
	void gRecur(CString MyNameIs, int TotalStep, HTREEITEM hNode);
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	BOOL gRecFind(HTREEITEM hItemG, CString csFN);
	//��� ������������ ����� �� ����������� ������������
	struct Color_Font
	{
		COLORREF color;
		LOGFONT  logfont;
	};
	//���� ��� ������� ����
	CMap<void*, void*, Color_Font, Color_Font&> m_mapColorFont;
	void SetItemColor(HTREEITEM hItem, COLORREF color); //������� ���������� �����
	//{{AFX_MSG(CLeftView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStringArray csaCycle; //��� ��������� �������������� � ��������
	CStringArray csaCycloStr; // ��� ��������� � ������
	//����������� �������� ������� ����
	void gRecTreeColor(HTREEITEM hItemGreen,CString csNodeName);
	void gColorItem(HTREEITEM hItemGreen); // ����� �����
};

/*#ifndef _DEBUG  // debug version in LeftView.cpp
inline COTDKDoc* CLeftView::GetDocument()
   { return (COTDKDoc*)m_pDocument; }
#endif*/

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__97EA3B8F_9AEB_11D5_BD12_005004230E79__INCLUDED_)
