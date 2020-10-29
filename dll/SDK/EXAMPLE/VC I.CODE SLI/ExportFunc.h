#ifndef _EXPORT_FUNC_H_
#define _EXPORT_FUNC_H_



int (WINAPI* rf_init_com)(int port,long baud);
int (WINAPI* rf_get_snr)(unsigned short icdev,unsigned char *Snr);
int (WINAPI* rf_antenna_sta)(unsigned short icdev, unsigned char model);
int (WINAPI* rf_request)(unsigned short icdev, unsigned char model, unsigned short *TagType);

int (WINAPI* rf_anticoll)(unsigned short icdev, unsigned char bcnt, unsigned char *pSnr,unsigned char* pRLength);
int (WINAPI* rf_select)(unsigned short icdev,unsigned char *pSnr,unsigned char srcLen,unsigned char *Size);
int (WINAPI* rf_halt)(unsigned short icdev);
int (WINAPI* rf_M1_authentication2)(unsigned short icdev,unsigned char model,unsigned char block,unsigned char *key);
int (WINAPI* rf_M1_read)(unsigned short icdev, unsigned char block, unsigned char *pData,unsigned char *pLen);
int (WINAPI* rf_M1_write)(unsigned short icdev, unsigned char block, unsigned char *data);
int (WINAPI* rf_ClosePort)();

int (WINAPI* rf_init_type)(WORD icdev,unsigned char type);
int (WINAPI* ISO15693_Inventory)(unsigned short icdev, unsigned char *pData, unsigned char *pLen);
int (WINAPI* ISO15693_Stay_Quiet)(unsigned short icdev, unsigned char *UID);
int (WINAPI* ISO15693_Select)(unsigned short icdev, unsigned char *UID);
int (WINAPI* ISO15693_Reset_To_Ready)(unsigned short icdev, unsigned char model, unsigned char *UID);
int (WINAPI* ISO15693_Read)(unsigned short icdev, 
			     unsigned char  model,
                             unsigned char  *UID,
                             unsigned char  block,
                             unsigned char  number,
                             unsigned char  *Pdata,
                             unsigned char  *pLen);
int (WINAPI* ISO15693_Write)(unsigned short icdev, 
			      unsigned char  model,
			      unsigned char  *UID,
			      unsigned char  block, 
			      unsigned char *data);
int (WINAPI* ISO15693_Lock_Block)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char block);
int (WINAPI* ISO15693_Write_AFI)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char AFI);
int (WINAPI* ISO15693_Lock_AFI)(unsigned short icdev, unsigned char model, unsigned char *UID);
int (WINAPI* ISO15693_Write_DSFID)(unsigned short icdev, unsigned char model, unsigned char *UID, unsigned char DSFID);
int (WINAPI* ISO15693_Lock_DSFID)(unsigned short icdev, unsigned char model, unsigned char *UID);
int (WINAPI* ISO15693_Get_System_Information)(unsigned short icdev, 
					       unsigned char  model,
					       unsigned char  *UID,
					       unsigned char  *Pdata, 
						   unsigned char  *pLen);					       
int (WINAPI* ISO15693_Get_Block_Security)(unsigned short icdev,
					   unsigned char  model,
					   unsigned char  *UID,
					   unsigned char  block,
					   unsigned char  number, 
                                           unsigned char  *Pdata,
                                           unsigned char  *pLen);
int (WINAPI* ISO15693_Inventorys)(unsigned short icdev, unsigned char *pData, unsigned char *pLen);
#endif
