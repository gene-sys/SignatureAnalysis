// FindNode.cpp : implementation file
//

#include "stdafx.h"
#include "oTDK.h"
#include "FindNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FindNode dialog


FindNode::FindNode(CWnd* pParent /*=NULL*/)
	: CDialog(FindNode::IDD, pParent)
{
	//{{AFX_DATA_INIT(FindNode)
	m_find = _T("");
	//}}AFX_DATA_INIT
}


void FindNode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FindNode)
	DDX_Text(pDX, IDC_EDITFIND, m_find);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FindNode, CDialog)
	//{{AFX_MSG_MAP(FindNode)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FindNode message handlers
