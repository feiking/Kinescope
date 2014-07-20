// Kinescope.h : main header file for the KINESCOPE application
//

#if !defined(AFX_KINESCOPE_H__103921AE_DB28_4BCD_A694_82CA94B7EA84__INCLUDED_)
#define AFX_KINESCOPE_H__103921AE_DB28_4BCD_A694_82CA94B7EA84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKinescopeApp:
// See Kinescope.cpp for the implementation of this class
//

class CKinescopeApp : public CWinApp
{
public:
	CKinescopeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKinescopeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKinescopeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KINESCOPE_H__103921AE_DB28_4BCD_A694_82CA94B7EA84__INCLUDED_)
