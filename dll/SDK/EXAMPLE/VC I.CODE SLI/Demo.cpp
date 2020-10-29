// Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"

#include "ExportFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoApp

BEGIN_MESSAGE_MAP(CDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoApp construction

CDemoApp::CDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDemoApp object

CDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDemoApp initialization

BOOL CDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	if(!LoadMasterRDLib()) 
		return FALSE;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	ReleaseMasterRDLib();
	return CWinApp::ExitInstance();
}

BOOL CDemoApp::LoadMasterRDLib()
{
	TCHAR szBuf[MAX_PATH];	
	GetModuleFileName(NULL, (LPTSTR)szBuf, MAX_PATH);
	*strrchr( szBuf, '\\' ) = 0;    
	strcat(szBuf, _T("\\MasterRD.Dll"));

	m_hInstMaster = LoadLibrary(szBuf);	 

	if(m_hInstMaster){
		(FARPROC&)rf_init_com           = GetProcAddress(m_hInstMaster,_T("rf_init_com"));
		(FARPROC&)rf_get_snr            = GetProcAddress(m_hInstMaster,_T("rf_get_snr"));

		(FARPROC&)rf_antenna_sta        = GetProcAddress(m_hInstMaster,_T("rf_antenna_sta"));
		(FARPROC&)rf_request            = GetProcAddress(m_hInstMaster,_T("rf_request"));
		(FARPROC&)rf_anticoll           = GetProcAddress(m_hInstMaster,_T("rf_anticoll"));
		(FARPROC&)rf_select             = GetProcAddress(m_hInstMaster,_T("rf_select"));
		(FARPROC&)rf_halt               = GetProcAddress(m_hInstMaster,_T("rf_halt"));

		(FARPROC&)rf_M1_authentication2 = GetProcAddress(m_hInstMaster,_T("rf_M1_authentication2"));
		(FARPROC&)rf_M1_read            = GetProcAddress(m_hInstMaster,_T("rf_M1_read"));
		(FARPROC&)rf_M1_write           = GetProcAddress(m_hInstMaster,_T("rf_M1_write"));

		(FARPROC&)rf_ClosePort          = GetProcAddress(m_hInstMaster,_T("rf_ClosePort"));
		
		(FARPROC&)rf_init_type          = GetProcAddress(m_hInstMaster,_T("rf_init_type"));
		(FARPROC&)ISO15693_Inventory          = GetProcAddress(m_hInstMaster,_T("ISO15693_Inventory"));
		(FARPROC&)ISO15693_Stay_Quiet          = GetProcAddress(m_hInstMaster,_T("ISO15693_Stay_Quiet"));
		(FARPROC&)ISO15693_Select          = GetProcAddress(m_hInstMaster,_T("ISO15693_Select"));
		(FARPROC&)ISO15693_Reset_To_Ready          = GetProcAddress(m_hInstMaster,_T("ISO15693_Reset_To_Ready"));
		(FARPROC&)ISO15693_Read          = GetProcAddress(m_hInstMaster,_T("ISO15693_Read"));
		(FARPROC&)ISO15693_Write          = GetProcAddress(m_hInstMaster,_T("ISO15693_Write"));
		(FARPROC&)ISO15693_Lock_Block          = GetProcAddress(m_hInstMaster,_T("ISO15693_Lock_Block"));
		(FARPROC&)ISO15693_Write_AFI          = GetProcAddress(m_hInstMaster,_T("ISO15693_Write_AFI"));
		(FARPROC&)ISO15693_Lock_AFI          = GetProcAddress(m_hInstMaster,_T("ISO15693_Lock_AFI"));
		(FARPROC&)ISO15693_Write_DSFID          = GetProcAddress(m_hInstMaster,_T("ISO15693_Write_DSFID"));
		(FARPROC&)ISO15693_Lock_DSFID          = GetProcAddress(m_hInstMaster,_T("ISO15693_Lock_DSFID"));
		(FARPROC&)ISO15693_Get_System_Information          = GetProcAddress(m_hInstMaster,_T("ISO15693_Get_System_Information"));
		(FARPROC&)ISO15693_Get_Block_Security          = GetProcAddress(m_hInstMaster,_T("ISO15693_Get_Block_Security"));
		(FARPROC&)ISO15693_Inventorys          = GetProcAddress(m_hInstMaster,_T("ISO15693_Inventorys"));
		
		
		if(
			NULL == rf_init_com           ||
			NULL == rf_antenna_sta    ||
			NULL == rf_request    ||
			NULL == rf_anticoll    ||
			NULL == rf_select    ||
			NULL == rf_halt    ||
			NULL == rf_M1_authentication2    ||
			NULL == rf_M1_read    ||
			NULL == rf_M1_write    ||
			NULL == rf_ClosePort ||
			NULL == rf_init_type||
			NULL == ISO15693_Inventory ||
			NULL == ISO15693_Stay_Quiet ||
			NULL == ISO15693_Select ||
			NULL == ISO15693_Reset_To_Ready ||
			NULL == ISO15693_Read ||
			NULL == ISO15693_Write ||
			NULL == ISO15693_Lock_Block ||
			NULL == ISO15693_Write_AFI ||
			NULL == ISO15693_Lock_AFI ||
			NULL == ISO15693_Get_System_Information ||
			NULL == ISO15693_Get_Block_Security ||
			NULL == ISO15693_Inventorys 
		     ){			
			AfxMessageBox(_T("Load MasterRD.dll failed !"));
			return FALSE;
		}
	}
	else{
		AfxMessageBox(_T("Load MasterRD.dll failed !"));
		return FALSE;
	}
  

	return TRUE;

}

void CDemoApp::ReleaseMasterRDLib()
{
	//Release masterRD.dll
	if(m_hInstMaster) 
		FreeLibrary(m_hInstMaster);
}