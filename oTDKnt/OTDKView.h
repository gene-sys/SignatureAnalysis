#if !defined(AFX_OTDKVIEW_H__97BD91FA_ACE1_11D5_BD12_005004230E79__INCLUDED_)
#define AFX_OTDKVIEW_H__97BD91FA_ACE1_11D5_BD12_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OTDKView.h : header file
//
#include "Afxcoll.h"
/////////////////////////////////////////////////////////////////////////////
// OTDKView view

class COTDKView : public CView
{
protected:
	COTDKView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COTDKView)

// Attributes
public:
// Operations
public:
	COTDKDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OTDKView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COTDKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(OTDKView)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL gSigOneZero(CStringArray* csaSOZ);
	BOOL gOneZero(CStringArray* csaRT);
	BOOL gSigNesov(CStringArray* csaSOZ);
	void gAddDiaInTest(CString csNameNode, CString csBuf, int iCountTest);
	void gPressKeyDia(BOOL bWhat);
	void gPressKey(BOOL bWhat);
	void gAddSigInTest(CString csNameNode, CString csBuf, int iCountTest);
	BOOL bWhat;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTDKVIEW_H__97BD91FA_ACE1_11D5_BD12_005004230E79__INCLUDED_)
