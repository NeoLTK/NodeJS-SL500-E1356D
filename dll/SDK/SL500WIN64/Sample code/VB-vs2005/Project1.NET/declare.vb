Option Strict Off
Option Explicit On
Module mo_declare
	'******************通讯命令******************************************************************
	'打开串口 int WINAPI rf_init_com(int port,long baud);
	Public Declare Function rf_init_com Lib "MasterRD.dll" (ByVal port As Integer, ByVal baud As Integer) As Integer
	'关闭串口 int WINAPI rf_ClosePort();
	Public Declare Function rf_ClosePort Lib "MasterRD.dll" () As Integer
	
	
	
	'******************************************MF1*****************************************
	'int WINAPI rf_request(unsigned short icdev, unsigned char model, unsigned short *TagType);
	Public Declare Function rf_request Lib "MasterRD.dll" (ByVal icdev As Short, ByVal model As Byte, ByRef TagType As Short) As Integer
	
	'int WINAPI rf_anticoll(unsigned short icdev, unsigned char bcnt, unsigned char *ppSnr,
	'unsigned char* pRLength);
	Public Declare Function rf_anticoll Lib "MasterRD.dll" (ByVal icdev As Short, ByVal bcnt As Byte, ByRef ppsnr As Byte, ByRef pRLength As Byte) As Integer
	
	'int WINAPI rf_select(unsigned short icdev,unsigned char *pSnr,unsigned char srcLen,
	'unsigned char *Size);
	Public Declare Function rf_select Lib "MasterRD.dll" (ByVal icdev As Short, ByRef pSnr As Byte, ByVal srclen As Byte, ByRef size As Byte) As Integer
	
	'int WINAPI rf_M1_authentication2(unsigned short icdev,unsigned char model,unsigned char block,
	'unsigned char *key);
	Public Declare Function rf_M1_authentication2 Lib "MasterRD.dll" (ByVal icdev As Short, ByVal model As Byte, ByVal block As Byte, ByRef key As Byte) As Integer
	
	'int WINAPI rf_M1_read(unsigned short icdev, unsigned char block, unsigned char *ppData,
	'unsigned char *pLen);
	Public Declare Function rf_M1_read Lib "MasterRD.dll" (ByVal icdev As Short, ByVal block As Byte, ByRef buff As Byte, ByRef pLen As Byte) As Integer
	
	'int WINAPI rf_M1_write(unsigned short icdev, unsigned char block, unsigned char *data);
	Public Declare Function rf_M1_write Lib "MasterRD.dll" (ByVal icdev As Short, ByVal block As Byte, ByRef buff As Byte) As Integer
	
	'int WINAPI rf_halt(unsigned short icdev);
	Public Declare Function rf_halt Lib "MasterRD.dll" (ByVal icdev As Short) As Integer
End Module