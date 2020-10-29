#include <vcl.h>
#include "myfunc.h"
#include <strutils.hpp>
//����16�ֽڸ�ʽ�ĵ�ǰ����ʱ�� "20030602224623"
AnsiString f_get_datetime(void)
{
 AnsiString s1;
 DateTimeToString(s1,"yyyymmddhhnnss",Now());
 return s1;
}
//�ж�1�ַ����Ƿ�ȫ������,�Ƿ���0�����Ƿ�0
int f_string_is_number(AnsiString s1,int ilen)
{
 bool b1=false;int i;
 for(i=1;i<=ilen;i++)
 {
  if((MidStr(s1,i,1)>'\x39')||(MidStr(s1,i,1)<'\x30'))
  {
   b1=true;
   break;
  }
 }
 if(b1) return 1;
 else   return 0;

}
//��1�ֽ�����ת��Ϊ��Ӧ16�����ַ���
AnsiString f_bytetohex(UCHAR *buff,int ilen)
{
 AnsiString s1;
 int i;
 s1="";
 for(i=0;i<ilen;i++)
 {
   s1=s1+IntToHex(buff[i],2);
 };
 return s1;
}
//����1�ֽ���������ֵ
UCHAR f_getxor(UCHAR *buff,int ilen)
{
 UCHAR b1;int i;
 for(i=0,b1=0;i<ilen;i++)
 {
   b1=b1 ^ buff[i];
 };
 return b1;
}
//����16������ʽ���ַ�������ת��Ϊ�ֽ�����
int f_stringtobin(AnsiString s1,int str_len,UCHAR *buff)
{
 int i;AnsiString s2;
 for(i=0;i<str_len/2;i++)
 {
 s2= "0x" +MidStr(s1,i*2+1,2);
 buff[i]=StrToInt(s2);
 };
 return 0;
}
