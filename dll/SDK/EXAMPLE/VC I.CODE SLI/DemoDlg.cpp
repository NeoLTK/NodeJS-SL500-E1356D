// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************************************/
#define BAUD_NUMBER  7
int BaudValue[BAUD_NUMBER] ={ 9600,14400,19200,28800,38400,57600,115200};


//
//return successful result
#define  LIB_SUCCESS      0  
//return failed result
#define  LIB_FAILED       1
#define MAX_RF_BUFFER     1024
//extern  {
extern int (WINAPI* rf_init_com)(int port,long baud);
extern int (WINAPI* rf_ClosePort)();
extern int (WINAPI* rf_init_type)(WORD icdev,unsigned char type);
extern int (WINAPI* ISO15693_Inventory)(unsigned short icdev, unsigned char *pData, unsigned char *pLen);
extern int (WINAPI* ISO15693_Stay_Quiet)(unsigned short icdev, unsigned char *UID);
extern int (WINAPI* ISO15693_Select)(unsigned short icdev, unsigned char *UID);
extern int (WINAPI* ISO15693_Reset_To_Ready)(unsigned short icdev, unsigned char model, unsigned char *UID);
extern int (WINAPI* ISO15693_Read)(unsigned short icdev, 
			     unsigned char  model,
                             unsigned char  *UID,
                             unsigned char  block,
                             unsigned char  number,
                             unsigned char  *Pdata,
                             unsigned char  *pLen);
extern int (WINAPI* ISO15693_Write)(unsigned short icdev, 
			      unsigned char  model,
			      unsigned char  *UID,
			      unsigned char  block, 
			      unsigned char *data);
extern int (WINAPI* ISO15693_Lock_Block)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char block);
extern int (WINAPI* ISO15693_Write_AFI)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char AFI);
extern int (WINAPI* ISO15693_Lock_AFI)(unsigned short icdev, unsigned char model, unsigned char *UID);
extern int (WINAPI* ISO15693_Write_DSFID)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char DSFID);
extern int (WINAPI* ISO15693_Lock_DSFID)(unsigned short icdev, unsigned char model, unsigned char *UID);
extern int (WINAPI* ISO15693_Get_System_Information)(unsigned short icdev, 
					       unsigned char  model,
					       unsigned char  *UID,
					       unsigned char  *Pdata, 
						   unsigned char  *pLen);					       
extern int (WINAPI* ISO15693_Get_Block_Security)(unsigned short icdev,
					   unsigned char  model,
					   unsigned char  *UID,
					   unsigned char  block,
					   unsigned char  number, 
                                           unsigned char  *Pdata,
                                           unsigned char  *pLen);
extern int (WINAPI* ISO15693_Inventorys)(unsigned short icdev, unsigned char *pData, unsigned char *pLen);
//}
/***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_EDIT_STATUS, m_edit_status);
	DDX_Control(pDX, IDC_EDIT_DATA, m_edit_data);
	DDX_Control(pDX, IDC_EDIT_UID4, m_edit_uid4);
	DDX_Control(pDX, IDC_EDIT_UID3, m_edit_uid3);
	DDX_Control(pDX, IDC_EDIT_UID2, m_edit_uid2);
	DDX_Control(pDX, IDC_EDIT_UID1, m_edit_uid1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECTDEVICE, OnButtonConnectdevice)
	ON_BN_CLICKED(IDC_BUTTON_READCARD, OnButtonReadcard)
	ON_BN_CLICKED(IDC_BUTTON_WRITECARD, OnButtonWritecard)
	ON_BN_CLICKED(IDC_BUTTON_LOCKCARD, OnButtonLockcard)
	ON_BN_CLICKED(IDC_BUTTON_INVENTORY, OnButtonInventory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bConnectDevice = FALSE;
	//////////////////////////////
	int i;
	CString str;
	CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	for( i = 0 ;i < 8;i++){		
		str.Format(_T("%d"), i+1);
		pPortCBB->AddString( str);		
		pPortCBB->SetItemData(i, i+1);		
	} 
	pPortCBB->SetCurSel(0);

	//
	CComboBox *pRaudCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
	for( i = 0 ;i < BAUD_NUMBER;i++){		
		str.Format(_T("%d"), BaudValue[i]);
		pRaudCBB->AddString( str);		
		pRaudCBB->SetItemData(i, BaudValue[i]);		
	} 
	pRaudCBB->SetCurSel(2);

	//
	((CButton*)GetDlgItem(IDC_RADIO_UID1))->SetCheck(TRUE);

	//
	CComboBox *pBlockCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BLOCK);
	for( i = 0 ;i < 28;i++){		
		str.Format(_T("%d"), i);
		pBlockCBB->AddString( str);		
		pBlockCBB->SetItemData(i, i);		
	} 
	pBlockCBB->SetCurSel(0);

	//
	m_edit_uid1.SetLimitTextEx(8);
	m_edit_uid1.SetOnlyRead(TRUE);

	m_edit_uid2.SetLimitTextEx(8);
	m_edit_uid2.SetOnlyRead(TRUE);

	m_edit_uid3.SetLimitTextEx(8);
	m_edit_uid3.SetOnlyRead(TRUE);

	m_edit_uid4.SetLimitTextEx(8);
	m_edit_uid4.SetOnlyRead(TRUE);

	m_edit_data.SetLimitTextEx(4);
	m_edit_status.SetLimitTextEx(1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}


void CDemoDlg::OnButtonConnectdevice() 
{
	// TODO: Add your control notification handler code here

	int state ;	
	if(!m_bConnectDevice)
	{
		//Open port
		
		CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
		int thePort = pPortCBB->GetItemData(pPortCBB->GetCurSel());	

		//
		CComboBox *pRaudCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BAUD);
		int theBaud = pRaudCBB->GetItemData(pRaudCBB->GetCurSel());
		//port : com1
		//baud : 19200
		state = rf_init_com(thePort,theBaud);

		if(state != LIB_SUCCESS){
			rf_ClosePort();			
			MessageBox("Open port failed!","Error",MB_OK|MB_ICONERROR);
			return;
		}

		((CButton*)GetDlgItem(IDC_BUTTON_CONNECTDEVICE))->SetWindowText("Disconnect");
		m_bConnectDevice = TRUE;
	}
	else
	{
		rf_ClosePort();	

		((CButton*)GetDlgItem(IDC_BUTTON_CONNECTDEVICE))->SetWindowText("Connect");
		m_bConnectDevice = FALSE;
		
	}
	
	
}

void CDemoDlg::OnButtonInventory() 
{
	WORD icdev = 0x0000;
	int status;		
	unsigned char pData[MAX_RF_BUFFER];
	unsigned char len;
	unsigned char type = 0x31;	

	if(!m_bConnectDevice){		
		MessageBox("Not connect device","Error",MB_OK|MB_ICONERROR);
		return;
	}

	status = rf_init_type(icdev,type);
    if(status){		
		MessageBox("rf_init_type failed","Error",MB_OK|MB_ICONERROR);
		return;
	}

	m_edit_uid1.SetWindowText("");
	m_edit_uid2.SetWindowText("");
	m_edit_uid3.SetWindowText("");
	m_edit_uid4.SetWindowText("");
	
	 status = ISO15693_Inventorys(icdev,pData,&len);
	 if(status){		 
		 MessageBox("ISO15693_Inventorys failed","Error",MB_OK|MB_ICONERROR);
		 return;
	 }     
 
	 for(int i = 0 ;i < len /9;i++ ){

		 if(i == 0)
			 m_edit_uid1.SetWindowTextEx(&pData[9 * i + 1],8);
		 if(i == 1) 
			 m_edit_uid2.SetWindowTextEx(&pData[9 * i + 1],8);
		 if(i == 2) 
			 m_edit_uid3.SetWindowTextEx(&pData[9 * i + 1],8);
		 if(i == 3) 
			 m_edit_uid4.SetWindowTextEx(&pData[9 * i + 1],8);

	 }	 

	  MessageBox("INVENTORY success","Success",MB_OK|MB_ICONASTERISK);
}

void CDemoDlg::OnButtonReadcard() 
{
	// TODO: Add your control notification handler code here
	WORD icdev = 0x0000;
	int status;	
	unsigned char model = 0x02;
	unsigned char UID[8];
	unsigned char  block = 0;
    unsigned char  number;	
	unsigned char pData[MAX_RF_BUFFER];	
	unsigned char len;
	
	CString strUIDEdit;

	if(!m_bConnectDevice){		
		MessageBox("Not connect device","Error",MB_OK|MB_ICONERROR);
		return;
	}


    memset(pData,0,MAX_RF_BUFFER);

	if(((CButton*)GetDlgItem(IDC_RADIO_UID1))->GetCheck())
		m_edit_uid1.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID2))->GetCheck())
		m_edit_uid2.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID3))->GetCheck())
		m_edit_uid3.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID4))->GetCheck())
		m_edit_uid4.GetWindowTextEx(strUIDEdit);

	if(strUIDEdit.GetLength ()  != 8){
		MessageBox("UID number is less than 8 bytes","Error",MB_OK|MB_ICONERROR);
		return;
	}

	memcpy(UID,strUIDEdit.GetBuffer(strUIDEdit.GetLength()),strUIDEdit.GetLength());


	//	
	block = 0;        
	CComboBox *pBlockCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BLOCK);
	block = (unsigned char)pBlockCBB->GetItemData(pBlockCBB->GetCurSel());	
	
		
	len = 0 ;	
	number = 0x01;
	status = ISO15693_Read(icdev,model,UID,block,number,pData,&len);
	if(status || len < 4){
		 MessageBox("ISO15693_Read failed","Error",MB_OK|MB_ICONERROR);			 
		 return;
	}
	m_edit_data.SetWindowTextEx(pData,len);
	
	
	//---------------------------//		
	number = 0x01;
	status = ISO15693_Get_Block_Security(icdev,model,UID,block,number,pData,&len);
	if(status || len != 0x01){
		 MessageBox("ISO15693_Get_Block_Security failed","Error",MB_OK|MB_ICONERROR);	
		 return;
	}
	m_edit_status.SetWindowTextEx(pData,len);

	 MessageBox("Read success","Success",MB_OK|MB_ICONASTERISK);
}

void CDemoDlg::OnButtonWritecard() 
{
	// TODO: Add your control notification handler code here
	WORD icdev = 0x0000;
	int status;	
	unsigned char model = 0x02;
	unsigned char UID[8];	  
	CString strUIDEdit;
	unsigned char pData[MAX_RF_BUFFER];
	unsigned char  block = 0;

	if(!m_bConnectDevice){		
		MessageBox("Not connect device","Error",MB_OK|MB_ICONERROR);
		return;
	}
	
	if(((CButton*)GetDlgItem(IDC_RADIO_UID1))->GetCheck())
		m_edit_uid1.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID2))->GetCheck())
		m_edit_uid2.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID3))->GetCheck())
		m_edit_uid3.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID4))->GetCheck())
		m_edit_uid4.GetWindowTextEx(strUIDEdit);


	if(strUIDEdit.GetLength() != 8) {
		MessageBox("UID number is less than 8 bytes","Error",MB_OK|MB_ICONERROR);
		return;
	}
	memcpy(UID,strUIDEdit.GetBuffer(strUIDEdit.GetLength()),strUIDEdit.GetLength());

	block = 0;        
	CComboBox *pBlockCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BLOCK);
	block = (unsigned char)pBlockCBB->GetItemData(pBlockCBB->GetCurSel());	
	
	m_edit_data.GetWindowTextEx(strUIDEdit);	
	if(strUIDEdit.GetLength() != 4)
	{
		MessageBox("Data is less than 4 bytes","Error",MB_OK|MB_ICONERROR);
		return;
	}
	memcpy(pData,strUIDEdit.GetBuffer(strUIDEdit.GetLength()),strUIDEdit.GetLength());
	pData[strUIDEdit.GetLength()] = '\0';
	status = ISO15693_Write(icdev,model,UID,block,(unsigned char*)pData);
		
	if(status){
		MessageBox("ISO15693_Write failed","Error",MB_OK|MB_ICONERROR);
		 return;
	}

	 MessageBox("Write success","Success",MB_OK|MB_ICONASTERISK);

}

void CDemoDlg::OnButtonLockcard() 
{
	// TODO: Add your control notification handler code here
	WORD icdev = 0x0000;
	int status;	
	unsigned char model = 0x02;
	unsigned char UID[8];
	unsigned char  block = 0;
	CString strUIDEdit;

	if(!m_bConnectDevice){		
		MessageBox("Not connect device","Error",MB_OK|MB_ICONERROR);
		return;
	}

	if(((CButton*)GetDlgItem(IDC_RADIO_UID1))->GetCheck())
		m_edit_uid1.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID2))->GetCheck())
		m_edit_uid2.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID3))->GetCheck())
		m_edit_uid3.GetWindowTextEx(strUIDEdit);
	else if(((CButton*)GetDlgItem(IDC_RADIO_UID4))->GetCheck())
		m_edit_uid4.GetWindowTextEx(strUIDEdit);

		if(strUIDEdit.GetLength() != 8) {
		MessageBox("UID number is less than 8 bytes","Error",MB_OK|MB_ICONERROR);
		return;
	}
	memcpy(UID,strUIDEdit.GetBuffer(strUIDEdit.GetLength()),strUIDEdit.GetLength());


	CComboBox *pBlockCBB = (CComboBox*)GetDlgItem(IDC_COMBO_BLOCK);
	block = (unsigned char)pBlockCBB->GetItemData(pBlockCBB->GetCurSel());

	status = ISO15693_Lock_Block(icdev,model,UID,block);
	if(status){
		MessageBox("ISO15693_Lock_Block failed","Error",MB_OK|MB_ICONERROR);
		 return;
	}

	 MessageBox("Lock success","Success",MB_OK|MB_ICONASTERISK);
}


