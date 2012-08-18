// oTDK.h : main header file for the OTDK application
//

#if !defined(AFX_OTDK_H__97EA3B85_9AEB_11D5_BD12_005004230E79__INCLUDED_)
#define AFX_OTDK_H__97EA3B85_9AEB_11D5_BD12_005004230E79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COTDKApp:
// See oTDK.cpp for the implementation of this class
//

class COTDKApp : public CWinApp
{
public:
	COTDKApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COTDKApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COTDKApp)
	afx_msg void OnAppAbout();
	afx_msg void OnWorkSpace();
	afx_msg void OnTrees();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void gWorkWithWINI(BOOL bWrite); // функ. работы с INI-файлом
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTDK_H__97EA3B85_9AEB_11D5_BD12_005004230E79__INCLUDED_)
