// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MifareOne读写例子.h"
#include "MainDlg.h"

#include "ExportFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BAUD_NUMBER  7
int BaudValue[BAUD_NUMBER] ={ 9600,14400,19200,28800,38400,57600,115200};
/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hInstMaster = NULL;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_EDIT_DATA, m_edit_data);
	DDX_Control(pDX, IDC_EDIT_KEY, m_edit_key);
	DDX_Control(pDX, IDC_EDIT_SERIAL, m_edit_serial);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_WRITE, OnButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_HALT, OnButtonHalt)

	ON_CBN_SELCHANGE(IDC_COMBO_PORT, OnSelchangeComboPortBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_RAUD, OnSelchangeComboPortBaud)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//load masterrd.dll to app
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
			NULL == rf_ClosePort 
		     ){			
			AfxMessageBox(_T("Load MasterRD.dll failed !"));
			return FALSE;
		}
	}
	else{
		AfxMessageBox(_T("Load MasterRD.dll failed !"));
		return FALSE;
	}


	//选择A密钥
	((CButton*)GetDlgItem(IDC_RADIO_KEYA))->SetCheck(TRUE);

	//初始化combo数据
	CComboBox *pMassCBB = (CComboBox*)GetDlgItem(IDC_COMBO_MASS);
	CString str;

	for( int i = 0 ;i < 64;i++){		
		str.Format(_T("%d"), i);
		pMassCBB->AddString( str);		
		pMassCBB->SetItemData(i, i);		
	} 

	pMassCBB->SetCurSel(0);
	///////////////////////////////
	//设置edit长度限制	
	m_edit_key.SetLimitTextEx(6);
	m_edit_data.SetLimitTextEx(16);

	//////////////////////////////
	//初始化串口ComboBox
	CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	for( i = 0 ;i < 4;i++){		
		str.Format(_T("%d"), i+1);
		pPortCBB->AddString( str);		
		pPortCBB->SetItemData(i, i+1);		
	} 

	pPortCBB->SetCurSel(0);

	CComboBox *pRaudCBB = (CComboBox*)GetDlgItem(IDC_COMBO_RAUD);
	for( i = 0 ;i < BAUD_NUMBER;i++){		
		str.Format(_T("%d"), BaudValue[i]);
		pRaudCBB->AddString( str);		
		pRaudCBB->SetItemData(i, BaudValue[i]);		
	} 
	pRaudCBB->SetCurSel(2);
	



	//打开串行端口
	int state = 1;	
	//port : com1
    //baud : 19200
    state = rf_init_com(1,19200);

	if(state != LIB_SUCCESS){
		rf_ClosePort();			
		MessageBox("不能正确打开端口!","Error",MB_OK|MB_ICONERROR);
		return FALSE;
	}
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint() 
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
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CMainDlg::DestroyWindow() 
{
	//关闭串行端口
    rf_ClosePort();	
	//释放masterRD.dll
	if(m_hInstMaster) FreeLibrary(m_hInstMaster);
	
	return CDialog::DestroyWindow();
}

//************* 寻卡 **************//
void CMainDlg::OnButtonSearch() 
{
	WORD icdev = 0x0000;
	unsigned char mode = 0x52;
	int status;
	unsigned short TagType;
	unsigned char bcnt = 0x04;//mifare 卡都用4
	unsigned char Snr[MAX_RF_BUFFER];
	unsigned char len;
	unsigned char Size;
	
	status = rf_request(icdev,mode,&TagType);//搜寻所有的卡
	if(status) {//出错
		m_edit_serial.SetWindowText("");
		return ;
	}
	
	status = rf_anticoll(icdev,bcnt,Snr,&len);//返回卡的序列号
	if(status || len != 4) { //出错
		m_edit_serial.SetWindowText("");
		return ;
	}
	
	status = rf_select(icdev,Snr,len,&Size);//锁定一张ISO14443-3 TYPE_A 卡
	if(status) {//出错
		m_edit_serial.SetWindowText("");
		return ;
	}
	
	m_edit_serial.SetWindowTextEx(Snr,len);	
}

//************* 读 *************//   
void CMainDlg::OnButtonRead() 
{
	WORD icdev = 0x0000;
	unsigned char mode = 0x60;
	unsigned char secnr = 0x00;
	int state;
	CString strKey;	
	unsigned char pData[MAX_RF_BUFFER];
	unsigned char cLen;

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_KEYA);
	if((pButton->GetCheck())){//A密钥
		mode = 0x60; //密钥
	}
	else{//B密钥
		mode = 0x61; //密钥
	}

	m_edit_key.GetWindowTextEx(strKey);
	if(m_edit_key.GetTextLenEx() != 6){
		MessageBox(_T("请在密钥区输入6个字节的密钥"),_T("Error"),MB_OK|MB_ICONERROR);
		return ;
	}

	//选择的块号
	CComboBox *pCBB = (CComboBox*)GetDlgItem(IDC_COMBO_MASS);
	int nSel = pCBB->GetCurSel();
	secnr = (unsigned char)(pCBB->GetItemData(nSel));	

	//用指定的密钥验证Mifare One 卡某一扇区
	state = rf_M1_authentication2(icdev,mode,(secnr/4)*4,(unsigned char*)strKey.GetBuffer(strKey.GetLength()));
	if(state){
		MessageBox(_T("验证密钥错"),_T("Error"),MB_OK|MB_ICONERROR);
		m_edit_data.SetWindowText("");
		return;	
	}
	//读取Mifare One 卡一块数据
	state = rf_M1_read(icdev,secnr,pData,&cLen);
	if(state || cLen != 16){
		MessageBox(_T("读卡错"),_T("Error"),MB_OK|MB_ICONERROR);
		m_edit_data.SetWindowText("");
		return;	
	}

	m_edit_data.SetWindowTextEx(pData,16);
}

//************* 写 *************//
void CMainDlg::OnButtonWrite() 
{
	WORD icdev = 0x0000;
	unsigned char mode = 0x60;
	unsigned char secnr = 0x00;
	int state;
	CString strKey,strEdit;	
	unsigned char Data[16];	

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_KEYA);
	if((pButton->GetCheck())){//A密钥
		mode = 0x60; //密钥		
	}
	else{//B密钥
		mode = 0x61; //密钥
	}

	m_edit_key.GetWindowTextEx(strKey);
	if(m_edit_key.GetTextLenEx() != 6){
		MessageBox(_T("请在密钥区输入6个字节的密钥"),_T("Error"),MB_OK|MB_ICONERROR);
		return ;
	}

	//选择的扇区号
	CComboBox *pCBB = (CComboBox*)GetDlgItem(IDC_COMBO_MASS);
	int nSel = pCBB->GetCurSel();
	secnr = (unsigned char)(pCBB->GetItemData(nSel));	
	
	
	//======================
	//用指定的密钥验证Mifare One 卡某一扇区
	state = rf_M1_authentication2(icdev,mode,(secnr/4)*4,(unsigned char*)strKey.GetBuffer(strKey.GetLength()));
	if(state){
		MessageBox(_T("验证密钥错"),_T("Error"),MB_OK|MB_ICONERROR);
		return;	
	}

	//取得数据区的数据
	m_edit_data.GetWindowTextEx(strEdit);			
	memcpy(Data,strEdit.GetBuffer(strEdit.GetLength()),strEdit.GetLength());
	//写mifare one卡的某一扇区  
	state = rf_M1_write(icdev,secnr,Data);
	if(state){
		MessageBox(_T("写卡错"),_T("Error"),MB_OK|MB_ICONERROR);
		return;	
	}
}

//************* 休眠 *************//
void CMainDlg::OnButtonHalt() 
{
	WORD icdev = 0x0000;
	int state;

	state = rf_halt(icdev);
	if(state){
		MessageBox(_T("HALT错"),_T("Error"),MB_OK|MB_ICONERROR);
	}	
}


void CMainDlg::OnSelchangeComboPortBaud()
{	
	CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	CComboBox *pBaudCBB = (CComboBox*)GetDlgItem(IDC_COMBO_RAUD);
	
	int nPort = pPortCBB->GetItemData(pPortCBB->GetCurSel());
	int nBaud = pBaudCBB->GetItemData(pBaudCBB->GetCurSel());

	//关闭串行端口
    rf_ClosePort();	

	//打开串行端口
	int state = 1;	
	
    state = rf_init_com(nPort,nBaud);

	if(state != LIB_SUCCESS){
		rf_ClosePort();			
		MessageBox("不能正确打开端口!","Error",MB_OK|MB_ICONERROR);
		return ;
	}	
}
