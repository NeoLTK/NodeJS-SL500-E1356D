#ifndef USINT
 #define USINT  unsigned short int   //2�ֽ��޷���
#endif
#ifndef UCHAR
 #define UCHAR  unsigned char        //1�ֽ��޷���
#endif
#ifndef UINT
 #define UINT   unsigned int         //4�ֽ��޷���
#endif

//#define UCHAR  unsigned char        //1�ֽ��޷���
//#define USINT  unsigned short int   //2�ֽ��޷���
//#define UINT   unsigned int         //4�ֽ��޷���





//��һ�ֽ�����ת��16�����ı��ַ���
extern AnsiString f_bytetohex(UCHAR *,int);

//����1�ֽ���������ֵ
extern UCHAR f_getxor(UCHAR *buff,int ilen);

//����16������ʽ���ַ�������ת��Ϊ�ֽ�����
extern int f_stringtobin(AnsiString s1,int str_len,UCHAR *buff);

//�ж�1�ַ����Ƿ�ȫ������,�Ƿ���0�����Ƿ�0
extern int f_string_is_number(AnsiString s1,int ilen);

//����16�ֽڸ�ʽ�ĵ�ǰ����ʱ�� "20030602224623"
extern AnsiString f_get_datetime(void);
