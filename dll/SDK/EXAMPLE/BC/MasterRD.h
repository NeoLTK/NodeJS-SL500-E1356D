/******** ���ܣ���ȡ��̬��汾�� 2�ֽ� *******************/
//  ����: �ɹ�����0
/*********************************************************/
extern "C" int WINAPI lib_ver(unsigned int *nVer);


/******** ���ܣ�DES �㷨���ܺ��� *************************/
//  ������szOut:  ���ܽ�������ȵ��ڼ������ݳ���
//        szIn:   ��������
//        inlen:  �������ݳ���,8�ֽڵ�������
//        key:    ��Կ
//        keylen: ��Կ����,�������8�ֽڣ���3des,���С�ڵ���8�ֽڵ�des.���㲹��
//  ����: �ɹ�����0
/*********************************************************/
extern "C" int (WINAPI* des_encrypt)(unsigned char *szOut,unsigned char *szIn , unsigned int inlen,unsigned char *key,unsigned int keylen);


/******** ���ܣ�DES �㷨���ܺ��� *************************/
//  ������szOut:  ���ܽ�������ȵ��ڽ������ݳ���
//        szIn:   ��������
//        inlen:  �������ݳ���,8�ֽڵ�������
//        key:    ��Կ
//        keylen: ��Կ����,�������8�ֽڣ���3des,���С�ڵ���8�ֽڵ�des.���㲹��
//  ����: �ɹ�����0
/*********************************************************/
extern "C" int (WINAPI* des_decrypt)(unsigned char *szOut,unsigned char *szIn , unsigned int inlen,unsigned char *key,unsigned int keylen);


/******** ���ܣ���ʼ������ *******************************/
//  ������port�����ںţ�ȡֵΪ1��4
//        baud��ΪͨѶ������4800��115200
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_init_com(int port,long baud);


/******** ���ܣ�ָ���豸��ʶ *****************************/
//  ������icdev��ͨѶ�豸��ʶ����0-65536
//  ���أ��ɹ�����0
/*********************************************************/
extern "C" int WINAPI rf_init_device_number(unsigned short icdev);


/******** ���ܣ���ȡ�豸��ʶ *****************************/
//  ������Icdev��ͨѶ�豸��ʶ��
//  ���أ��ɹ�����0
/*********************************************************/
extern "C" int WINAPI rf_get_device_number(unsigned short *Icdev);


/******** ���ܣ�ȡ�ö�д����Ӳ���汾�ţ�2 �ֽ� ***********/
//  ������icdev��  ͨѶ�豸��ʶ��
//        Version����ŷ��ذ汾��Ϣ
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_get_model(unsigned short icdev,unsigned short *Version);


/******** ���ܣ�ȡ�ö�д������Ʒ���кţ�8 �ֽ� ***********/
//  ������icdev��ͨѶ�豸��ʶ��
//        Snr��  ��ŷ��ض�д������Ʒ���к�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_get_snr(unsigned short icdev,unsigned char *Snr);


/******** ���ܣ����� *************************************/
//  ������icdev��ͨѶ�豸��ʶ��
//        msec�� ����ʱ�ޣ���λ��10 ����
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_beep(unsigned short icdev,unsigned char msec);


/******** ���ܣ����ö�д����sam ��ͨѶ������ *************/
//  ������icdev��ͨѶ�豸��ʶ��
//        bound: sam �������ʣ�ȡֵΪ9600��38400
//  ���أ��ɹ��򷵻�0
//  ˵����bound=0:9600
//        bound=1:38400
/*********************************************************/
extern "C" int WINAPI rf_init_sam(unsigned short icdev,unsigned char bound);


/******* ���ܣ���λsam �� ********************************/
//  ������icdev�� ͨѶ�豸��ʶ��
//        pData�����صĸ�λ��Ϣ����
//        pMsgLg�����ظ�λ��Ϣ�ĳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_sam_rst(unsigned short icdev, unsigned char *pData,unsigned char *pMsgLg);
/*����
     unsigned int icdev;
     unsigned char pData[MAX_RF_BUFFER];
     unsigned char len;
     status = rf_sam_rst(icdev,pData,&len);
     
*/


/******** ���ܣ���SAM ������COS ���� *********************/
//  ������icdev��  ͨѶ�豸��ʶ��
//        command��cos ����
//        cmdLen:  cos �����
//        pDate�� ��Ƭ���ص����ݣ���SW1��SW2
//        pMsgLg�� �������ݳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_sam_cos(unsigned short icdev, unsigned char *command,unsigned char cmdLen ,unsigned char *pData,unsigned char* Length);
/*����
     unsigned char icdev;
     unsigned char* cmd;
     unsigned char pData[MAX_RF_BUFFER];
     unsigned char len;
     status = rf_sam_cos(icdev,cmd,sizeof(cmd),pData,&len);
     
*/


/*******  ���ܣ����ö�д�����ǽӴ�������ʽΪ *************/ 
//              ISO14443 TYPE A OR ISO14443 TYPE B
//  ������icdev��ͨѶ�豸��ʶ��
//        type:  ��д����������ʽ
//  ���أ��ɹ��򷵻�0
//  ˵����type='A':����ΪTYPE_A��ʽ
//        type='B':����ΪTYPE_B��ʽ
//        type='r':����ΪAT88RF020����ʽ
/*********************************************************/
extern "C" int WINAPI rf_init_type(unsigned short icdev,unsigned char type);


/*******  ���ܣ��رջ�������д�������߷��� ***************/
//  ������icdev��ͨѶ�豸��ʶ��
//        model������״̬
//  ���أ��ɹ��򷵻�0
//  ˵����model=0:�ر�����
//        model=1:��������
/*********************************************************/
extern "C" int WINAPI rf_antenna_sta(unsigned short icdev, unsigned char model);


/******** ���ܣ�ѰISO14443-3 TYPE_A �� *******************/
//  ������icdev��  ͨѶ�豸��ʶ��
//        model��  Ѱ��ģʽ
//        TagType�����ؿ�����ֵ
//  ���أ��ɹ��򷵻�0
//  ˵����mode=0x26:Ѱδ��������״̬�Ŀ�
//        mode=0x52:Ѱ����״̬�Ŀ�
/*********************************************************/
extern "C" int WINAPI rf_request(unsigned short icdev, unsigned char model, unsigned short *TagType);


/********* ���ܣ�ISO14443-3 TYPE_A ������ײ **************/
//  ������icdev��  ͨѶ�豸��ʶ��
//        bcnt��   �����к��ֽ�����ȡֵ4��7��10��Mifare ��ȡֵ4
//        pSnr��  ���صĿ����к�
//        pRLength:�����кų���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_anticoll(unsigned short icdev, unsigned char bcnt, unsigned char *pSnr,unsigned char* pRLength);
/*����int status
      unsigned char icdev;
      unsigned char snr[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_anticoll(icdev,4,snr,&len);      
*/


/******** ���ܣ�����һ��ISO14443-3 TYPE_A �� *************/
//  ������icdev��ͨѶ�豸��ʶ��
//        pSnr�� �����к�
//        srcLen:�����кų��ȣ�MifareOne����ֵ����4
//        Size�� ���ؿ�����
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_select(unsigned short icdev,unsigned char *pSnr,unsigned char srcLen,unsigned char *Size);


/******* ���ܣ������Ѽ����ISO14443-3 TYPE_A����������״̬*/
//  ������icdev��ͨѶ�豸��ʶ��
//  ���أ��ɹ��򷵻�0
/**********************************************************/
extern "C" int WINAPI rf_halt(unsigned short icdev);


/***** ���ܣ���ָ������Կ��֤Mifare One ��*****************/
//  ������icdev��ͨѶ�豸��ʶ��
//        model��������֤ģʽ
//        block��Ҫ��֤����ľ��Կ�ţ�0��63��
//        key��  ��Կ���ݣ�6 �ֽ�
//  ���أ��ɹ��򷵻�0
//  ˵����model=0x60:��֤A��Կ
//        model=0x61:��֤B��Կ
/**********************************************************/
extern "C" int WINAPI rf_M1_authentication2(unsigned short icdev,unsigned char model,unsigned char block,unsigned char *key);


/*******  ���ܣ���ȡMifare One ��һ������ ****************/
//  ������icdev�� ͨѶ�豸��ʶ��
//        block�� M1�����Կ�ţ�0��63��
//        pData����������
//        pLen:   �������ݵĳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_M1_read(unsigned short icdev, unsigned char block, unsigned char *pData,unsigned char *pLen);
/*����int status
      unsigned short icdev
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_M1_read(icdev,0,pData,&len);
      
*/


/*******  ���ܣ���Mifare One ����д��һ������ ************/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1�����Կ�ţ�0��63)
//        data�� д������ݣ�16 �ֽ�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_M1_write(unsigned short icdev, unsigned char block, unsigned char *data);


/*******  ���ܣ���Mifare One ��ĳһ������ʼ��ΪǮ�� *******/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1 �����ַ��0��63��
//        value����ʼֵ
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_M1_initval(unsigned short icdev, unsigned char block, long value);


/*******  ���ܣ���Mifare One Ǯ��ֵ **********************/
//  ������icdev�� ͨѶ�豸��ʶ��
//        block�� M1 �����ַ��0��63��
//        pValue�����ص�ֵ
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_M1_readval(unsigned short icdev, unsigned char block,long* pValue);


/*******  ���ܣ�Mifare One �ۿ� **************************/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1 �����ַ��0��63��
//        value��Ҫ�۵�ֵ
//  ���أ��ɹ��򷵻�0
//  ˵�����˺���ִ�гɹ��󣬽�������ڿ�Ƭ��BUFFER �ڣ�
//        ��δ��д��Ӧ������ݣ���Ҫ��������浽��Ƭ
//        ��Ӧ���������ִ��rf_M1_restore ����
/*********************************************************/
extern "C" int WINAPI rf_M1_decrement(unsigned short icdev, unsigned char block,long value);


/******** ���ܣ�Mifare One ��ֵ **************************/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1 �����ַ��0��63��
//        value��Ҫ���ӵ�ֵ
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_M1_increment(unsigned short icdev, unsigned char block,long value);


/******** ���ܣ�Mifare One ��ֵ�ش� **********************/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1 �����ַ��0��63��
//  ���أ��ɹ��򷵻�0
//  ˵�����ô˺�����ָ���Ŀ����ݴ��뿨��buffer��Ȼ�����
//        rf_M1transfer()������buffer �������ٴ��͵���һ����ȥ
/*********************************************************/
extern "C" int WINAPI rf_M1_restore(unsigned short icdev, unsigned char block);


/****** ���ܣ���Mifare One���ݴ��� ***********************/
//  ������icdev��ͨѶ�豸��ʶ��
//        block��M1 �����ַ��0��63��
//  ���أ��ɹ��򷵻�0
//  ˵�����ú�������increment��decrement��restore ����֮����á�
/*********************************************************/
extern "C" int WINAPI rf_M1_transfer(unsigned short icdev, unsigned char block);


/******** ���ܣ���λ����ISO14443-A ��׼��CPU �� **********/
//  ������icdev�� ͨѶ�豸��ʶ��
//        model:  Ѱ����ʽ
//        pDate�����صĸ�λ��Ϣ����
//        pMsgLg�����ظ�λ��Ϣ����
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_typea_rst(unsigned short icdev,unsigned char model,unsigned char *pData,unsigned char *pMsgLg);
/*����int status
      unsigned short icdev
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_typea_rst(icdev,0,pData,&len);      
*/


/******** ���ܣ������ISO14443-4��׼��CPU������COS ����***/
//  ������icdev��  ͨѶ�豸��ʶ��
//        command��cos ����
//        cmdLen:  cos �����
//        pDate�� ��Ƭ���ص����ݣ���SW1��SW2
//        pMsgLg�� �������ݳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_cos_command(unsigned short icdev,unsigned char *command,unsigned char cmdLen,unsigned char *pData,unsigned char* pMsgLg);
/*����int status
      unsigned short icdev
      unsigned char* cmd;
      unsigned char pData[MAX_RF_BUFFER];
      unsigned char len;
      status = rf_typea_cos(icdev,cmd,sizeof(cmd),pData,&len);      
*/


/******** ���ܣ��������ISO14443 TYPE_B ��׼�Ŀ� *********/
//  ������icdev�� ͨѶ�豸��ʶ��
//        model�� Ѱ����ʽ0��REQB,1=WUPB
//        pDate����Ƭ���ص�����
//        pMsgLg���������ݵĳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_atqb(unsigned short icdev,unsigned char model,unsigned char *pData,unsigned char *pMsgLg);
/*����int status
      int icdev
      unsigned char msglg
      unsigned char pDate[MAX_RF_BUFFER];
      status = rf_atqb(icdev,0,pDate,&msglg);      
*/

/******** ���ܣ�����һѡ�е�TYPE_B������HALT ״̬*********/
//  ������icdev��ͨѶ�豸��ʶ��
//        PUPI�� ��ƬΨһ��ʶ��
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_hltb(unsigned short icdev,unsigned long PUPI);
//??

/******** ���ܣ���֤AT88RF020 ������ *********************/
//  ������icdev��ͨѶ�豸��ʶ��
//        key��  ���룬8 �ֽ�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_at020_check(unsigned short icdev, unsigned char *key);


//******* ���ܣ���AT88RF020 ��һҳ���� *******************/
//  ������icdev�� ͨѶ�豸��ʶ��
//        page��  ҳ��ַ����0��31��
//        pDate�����ص�����
//        pMsgLen:�������ݵĳ���
//  ���أ��ɹ��򷵻�0
//  ˵����
/*********************************************************/
extern "C" int WINAPI rf_at020_read(unsigned short icdev, unsigned char page, unsigned char *pData,unsigned char* pMsgLen);
/*
����int status
    int icdev
    unsigned char pData[MAX_RF_BUFFER];
    unsigned char len;
    status = rf_at020_read(icdev,0,pData,&len);    
*/


/******** ���ܣ�дAT88RF020 ��һҳ���� *******************/
//  ������icdev��ͨѶ�豸��ʶ��
//        page�� ҳ��ַ����0��31��
//        Date�� Ҫд������ݣ�8 �ֽ�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_at020_write(unsigned short icdev, unsigned char page, unsigned char *data);
 

/******** ���ܣ�LOCK AT88RF020��**************************/
//  ������icdev��ͨѶ�豸��ʶ��
//        date�� ���ݣ�4 �ֽ�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_at020_lock(unsigned short icdev,unsigned char *data);


/******** ���ܣ�AT88RF020���������� **********************/
//  ������icdev��ͨѶ�豸��ʶ��
//        date�� ���ݣ�6 �ֽ�
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_at020_count(unsigned short icdev,unsigned char *data);


/******** ���ܣ�����AT88RF020 ������HALT ״̬ ************/
//  ������icdev��ͨѶ�豸��ʶ��
//  ���أ��ɹ��򷵻�0
/*********************************************************/
extern "C" int WINAPI rf_at020_deselect(unsigned short icdev);


/******** ���ܣ����ƵƵ���ɫ *****************************/
//  ������icdev��ͨѶ�豸��ʶ��
//        color: 0 ,Ϩ��
//               1 ,���
//               2 ,�̵�
//               3 ,�Ƶ�
//  ���أ��ɹ�����0
/*********************************************************/
extern "C" int WINAPI rf_light(unsigned short icdev,unsigned char color);



//******* ���ܣ��ͷ�memory *******************************/
//extern "C" void WINAPI rf_free(void* pData);


/******** ���ܣ��ر�Com�˿� ******************************/
//  ���أ��ɹ�����0
/*********************************************************/
extern "C" int WINAPI rf_ClosePort();


/******** ���ܣ�����״̬�� *******************************/
//  ���أ��������
/*********************************************************/
extern "C" int WINAPI rf_GetErrorMessage();


