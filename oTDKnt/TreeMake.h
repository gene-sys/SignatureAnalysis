#if !defined(AFX_TREEMAKE_H__9AF683A0_38F8_11D6_826D_A5ED3144A338__INCLUDED_)
#define AFX_TREEMAKE_H__9AF683A0_38F8_11D6_826D_A5ED3144A338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeMake.h : header file
//
#include "Afxtempl.h"
/////////////////////////////////////////////////////////////////////////////
// CTreeMake dialog

class CTreeMake : public CDialog
{
// Construction
public:
	CTreeMake(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeMake)
	enum { IDD = IDD_TREES };
	CButton	m_OK;
	CString	m_namefile;
	BOOL	m_startnew;
	CString	m_CurrentNode;
	CString	m_Perexod;
	CString	m_EnterNode;
	CString	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMake)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void gOpenFile(CString csfPath); // открытие файла
	void gMadePerex(); //функ. создания переходов
	void gPereschet(); // функ. редактирования заведенных переходов
	void gVlNode(char Perex[50], CString csOpa); // вызывается из gLocalNode
	BOOL gLocalNode(CString cs, CStringArray* csa); // функ. поставки переходов в очередь
	BOOL Branch;  // новая ли ветвь
	UINT ibranch; //количество ветвей
	int poQueue;   // контроль очередности описания узлов
	CStringArray glsV; //массив очередности узлов
	CStringArray csaUch; //массив описанных участков
	CWnd* cwndEntrPer; // указатель имени текущего активного поля
	CEdit* cwndEdit; // указатель имени поля редактирования
	CFile theFile;  // класс открываемого файла
	// Generated message map functions
	//{{AFX_MSG(CTreeMake)
	virtual void OnOK();
	afx_msg void OnKillfocusEntr();
	afx_msg void OnStartnew();
	afx_msg void OnNewtree();
	afx_msg void OnSetfocusEntr();
	afx_msg void OnLoadtree();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnSetfocusPerex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEMAKE_H__9AF683A0_38F8_11D6_826D_A5ED3144A338__INCLUDED_)
