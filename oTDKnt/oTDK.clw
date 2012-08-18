; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COTDKDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "oTDK.h"
LastPage=0

ClassCount=11
Class1=COTDKApp
Class2=COTDKDoc
Class3=COTDKView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_WorkSpace
Resource2=IDD_TREES
Class5=CLeftView
Class6=CAboutDlg
Class7=C0TDKView
Class8=OTDKView
Resource3=IDR_MAINFRAME
Class9=WorkINI
Class10=CTreeMake
Resource4=IDD_ABOUTBOX
Class11=FindNode
Resource5=IDD_DIALOGFIND

[CLS:COTDKApp]
Type=0
HeaderFile=oTDK.h
ImplementationFile=oTDK.cpp
Filter=N
LastObject=IDD_TREES
BaseClass=CWinApp
VirtualFilter=AC

[CLS:COTDKDoc]
Type=0
HeaderFile=oTDKDoc.h
ImplementationFile=oTDKDoc.cpp
Filter=N
LastObject=IDD_TREES
BaseClass=COleDocument
VirtualFilter=ODC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CLOSEFILE



[CLS:CLeftView]
Type=0
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=T
LastObject=CLeftView
BaseClass=CTreeView
VirtualFilter=VWC

[CLS:CAboutDlg]
Type=0
HeaderFile=oTDK.cpp
ImplementationFile=oTDK.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDD_TREES
Command2=ID_FILE_OPEN
Command3=CLOSEFILE
Command4=ID_APP_EXIT
Command5=ID_FINDNODE
Command6=ID_WorkSpace
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_WORD
Command10=ID_DIAP
Command11=ID_MAKESIG
Command12=ID_CHKSIG
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FINDNODE
Command2=ID_WorkSpace
Command3=IDD_TREES
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_APP_EXIT
CommandCount=6

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDD_TREES
Command2=ID_FILE_OPEN
Command3=ID_FINDNODE
Command4=ID_DIAP
Command5=ID_MAKESIG
Command6=ID_CHKSIG
Command7=ID_WORD
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:C0TDKView]
Type=0
HeaderFile=0TDKView.h
ImplementationFile=0TDKView.cpp
BaseClass=CView
Filter=C

[DLG:IDD_WorkSpace]
Type=1
Class=WorkINI
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1484849280
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT3,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT4,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_HIDETEST,button,1342242819
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342194439
Control14=IDC_EDIT5,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308364
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308364
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT6,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_CHECK1,button,1342242819
Control23=IDC_HIDETEST2,button,1342242819
Control24=IDC_STATIC,static,1342308352

[CLS:WorkINI]
Type=0
HeaderFile=WorkINI.h
ImplementationFile=WorkINI.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_HIDETEST2

[DLG:IDD_TREES]
Type=1
Class=CTreeMake
ControlCount=16
Control1=IDOK,button,1342242816
Control2=IDC_ENTR,edit,1484853384
Control3=IDC_PEREX,edit,1484853388
Control4=IDC_STARTNEW,button,1476460547
Control5=IDC_NAMEFILE,edit,1350635648
Control6=IDC_LOADTREE,button,1342242816
Control7=IDC_STATIC,static,1342312960
Control8=IDC_STATIC,static,1342312960
Control9=IDC_CURNODE,edit,1476464776
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_NEWTREE,button,1342242816
Control16=IDC_EDIT1,edit,1353782276

[CLS:CTreeMake]
Type=0
HeaderFile=TreeMake.h
ImplementationFile=TreeMake.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CURNODE
VirtualFilter=dWC

[DLG:IDD_DIALOGFIND]
Type=1
Class=FindNode
ControlCount=2
Control1=IDC_EDITFIND,edit,1342242816
Control2=IDC_STATIC,static,1342308352

[CLS:FindNode]
Type=0
HeaderFile=FindNode.h
ImplementationFile=FindNode.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLOSEFILE

