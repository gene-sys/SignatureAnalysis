#if !defined(AFX_FINDNODE_H__E3CDCB64_1269_11D7_9ABB_005004230E79__INCLUDED_)
#define AFX_FINDNODE_H__E3CDCB64_1269_11D7_9ABB_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindNode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FindNode dialog

class FindNode : public CDialog
{
// Construction
public:
	FindNode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FindNode)
	enum { IDD = IDD_DIALOGFIND };
	CString	m_find;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FindNode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FindNode)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDNODE_H__E3CDCB64_1269_11D7_9ABB_005004230E79__INCLUDED_)
