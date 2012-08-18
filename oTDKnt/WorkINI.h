#if !defined(AFX_WORKINI_H__B1C6A421_C936_11D5_BD13_005004230E79__INCLUDED_)
#define AFX_WORKINI_H__B1C6A421_C936_11D5_BD13_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkINI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WorkINI dialog

class WorkINI : public CDialog
{
// Construction
public:
	WorkINI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(WorkINI)
	enum { IDD = IDD_WorkSpace };
	CString	m_CopyTemp;
	CString	m_WorkDir;
	int		m_NumTest;
	BOOL	m_hide;
	CString	m_TempDia;
	int		m_NumDtest;
	BOOL	m_SamoCheck;
	BOOL	m_cycler;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WorkINI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WorkINI)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKINI_H__B1C6A421_C936_11D5_BD13_005004230E79__INCLUDED_)
