; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Kinescope.h"

ClassCount=7
Class1=CKinescopeApp
Class2=CKinescopeDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_NAME_DIALOG
Resource4=IDD_CUT_DIALOG
Resource5=IDD_COALITION_DIALOG
Class4=CNameDlg
Resource6=IDD_FRAME_DIALOG
Class5=CCutDlg
Class6=CFrameDlg
Resource7=IDD_KINESCOPE_DIALOG
Class7=CCoalitionDlg
Resource8=IDR_LISTMENU

[CLS:CKinescopeApp]
Type=0
HeaderFile=Kinescope.h
ImplementationFile=Kinescope.cpp
Filter=N

[CLS:CKinescopeDlg]
Type=0
HeaderFile=KinescopeDlg.h
ImplementationFile=KinescopeDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CKinescopeDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=KinescopeDlg.h
ImplementationFile=KinescopeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KINESCOPE_DIALOG]
Type=1
Class=CKinescopeDlg
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350633600
Control5=IDC_BUTSELECT,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_LIST1,SysListView32,1350631427
Control8=IDC_STATIC,button,1342177287
Control9=IDC_FRAME,static,1342177287
Control10=IDC_PICTURE,static,1342177294
Control11=IDC_STATICPLACE,static,1342308352
Control12=IDC_EDIT3,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_CHECK1,button,1342242819
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352

[DLG:IDD_FRAME_DIALOG]
Type=1
Class=CFrameDlg
ControlCount=0

[MNU:IDR_LISTMENU]
Type=1
Class=?
Command1=ID_MENUPLAY
Command2=ID_MENUNAME
Command3=ID_MENUSAVE
Command4=ID_MENUTIME
Command5=ID_MENUDELETE
CommandCount=5

[DLG:IDD_NAME_DIALOG]
Type=1
Class=CNameDlg
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,button,1342177287

[CLS:CNameDlg]
Type=0
HeaderFile=NameDlg.h
ImplementationFile=NameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENUTIME
VirtualFilter=dWC

[DLG:IDD_CUT_DIALOG]
Type=1
Class=CCutDlg
ControlCount=11
Control1=IDC_STATICRATE,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_BUTGOTO,button,1342242816
Control4=IDC_BUTPREVIOUS,button,1342242816
Control5=IDC_BUTNEXT,button,1342242816
Control6=IDC_BUTCUT,button,1342242816
Control7=IDC_BUTEXIT,button,1342242816
Control8=IDC_STATICFRAME,static,1342177287
Control9=IDC_PICTURE,static,1342177294
Control10=IDC_BUTSTART,button,1342242816
Control11=IDC_BUTSTOP,button,1342242816

[CLS:CCutDlg]
Type=0
HeaderFile=CutDlg.h
ImplementationFile=CutDlg.cpp
BaseClass=CDialog
Filter=W
LastObject=CCutDlg
VirtualFilter=dWC

[CLS:CFrameDlg]
Type=0
HeaderFile=FrameDlg.h
ImplementationFile=FrameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFrameDlg

[DLG:IDD_COALITION_DIALOG]
Type=1
Class=CCoalitionDlg
ControlCount=8
Control1=IDC_LIST1,listbox,1352728835
Control2=IDC_BUTADD,button,1342242816
Control3=IDC_BUTDEL,button,1342242816
Control4=IDC_BUTCLEAR,button,1342242816
Control5=IDC_BUTUP,button,1342242816
Control6=IDC_BUTDOWN,button,1342242816
Control7=IDC_BUTCOALITION,button,1342242816
Control8=IDC_BUTEXIT,button,1342242816

[CLS:CCoalitionDlg]
Type=0
HeaderFile=CoalitionDlg.h
ImplementationFile=CoalitionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCoalitionDlg

