unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls,declaredll,strutils;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    le_xlh: TLabeledEdit;
    le_akey: TLabeledEdit;
    cb_kh: TComboBox;
    Label2: TLabel;
    le_sj: TLabeledEdit;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    lb_info: TLabel;
    Label3: TLabel;
    cb_port: TComboBox;
    Label4: TLabel;
    cb_baud: TComboBox;
    rg_key: TRadioGroup;
    procedure Button1Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  port,baud:integer;
implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
   i:integer;w1:word;b1:byte; buf1:array[0..200] of byte;s1:string;
begin
   port:=strtoint(trim(cb_port.Text ));
   baud:=strtoint(trim(cb_baud.Text ));
   //�򿪴���
   i:=rf_init_com(port,baud);
   if(i<>0)then
   begin
       lb_info.Caption:=' ��ʼ������ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   //Ѱ��
   i:=rf_request(0,$52,w1);
   if(i<>0)then
   begin
       lb_info.Caption:=' Ѱ��ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   // ����ײ ��buf1�������к�
   i:=rf_anticoll(0,4,buf1[0],b1);
   if(i<>0)then
   begin
       lb_info.Caption:=' ����ײʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   s1:='';
   for i:=0 to b1-1 do begin
       s1:=s1+inttohex(buf1[i],2);
   end;

   le_xlh.Text:=s1;
   lb_info.Caption:='����ײ�ɹ�';
   i:=rf_select(0,buf1[0],4,b1);
   if(i<>0)then
   begin
       lb_info.Caption:=' ѡ��ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   lb_info.Caption:='Ѱ���ɹ�';
end;

procedure TForm1.Button4Click(Sender: TObject);
var
    i:integer;
begin
   i:=rf_halt(0);
   if(i<>0)then
   begin
       lb_info.Caption:=' ������ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   lb_info.Caption:=' �����߳ɹ���';
end;

procedure TForm1.Button2Click(Sender: TObject);
var
   i,j:integer;b1,b_kh:byte; buf1,buf2:array[0..200] of byte;s1:string;
begin
   b_kh:=cb_kh.ItemIndex;
   s1:=trim(le_akey.Text );
   if(length(s1)<>12)then
   begin
       lb_info.Caption:=' ��Կ���Ȳ��ԣ����������룡';
       le_akey.SetFocus;
       exit;
   end;
   for i:=0 to 5 do begin
       val('$'+midstr(s1,i*2+1,2),buf2[i],j);
   end;
   //�ж���Կ����
   if(rg_key.ItemIndex =0)  then
   begin
      b1:=$60;
   end
   else
   begin
      b1:=$61;
   end;
   //��֤��Կ
   i:=rf_M1_authentication2(0,b1,b_kh,buf2[0]);
   if(i<>0)then
   begin
       lb_info.Caption:=' ��֤��Կʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   //����ʧ��
   i:=rf_M1_read(0,b_kh,buf1[0],b1);
   if(i<>0)then
   begin
       lb_info.Caption:=' ����ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   s1:='';
   for i:=0 to b1-1 do begin
       s1:=s1+inttohex(buf1[i],2);
   end;

   le_sj.Text:=s1;
   lb_info.Caption:=' �����ɹ���';
end;

procedure TForm1.Button3Click(Sender: TObject);
var
   i,j:integer;b1,b_kh:byte; buf1,buf2:array[0..200] of byte;s1:string;
begin
   b_kh:=cb_kh.ItemIndex;
   //�ж���Կ����
   s1:=trim(le_akey.Text );
   if(length(s1)<>12)then
   begin
       lb_info.Caption:=' ��Կ���Ȳ��ԣ����������룡';
       le_akey.SetFocus;
       exit;
   end;
   for i:=0 to 5 do begin
       val('$'+midstr(s1,i*2+1,2),buf2[i],j);
   end;

   s1:=trim(le_sj.Text );
   if(length(s1)<>32)then
   begin
       lb_info.Caption:=' ��д������ݳ��Ȳ��ԣ����������룡';
       le_sj.SetFocus;
       exit;
   end;
   for i:=0 to 15 do begin
       val('$'+midstr(s1,i*2+1,2),buf1[i],j);
   end;


   if(rg_key.ItemIndex =0)  then
   begin
      b1:=$60;
   end
   else
   begin
      b1:=$61;
   end;
   //��֤��Կ
   i:=rf_M1_authentication2(0,b1,b_kh,buf2[0]);
   if(i<>0)then
   begin
       lb_info.Caption:=' ��֤��Կʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   // д��ʧ��
   i:=rf_M1_write(0,b_kh,buf1[0]);
   if(i<>0)then
   begin
       lb_info.Caption:=' д��ʧ�ܣ�����ֵ��'+inttostr(i);
       exit;
   end;
   
   lb_info.Caption:=' д���ɹ���';

end;

end.
