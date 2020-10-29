using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;


using System.Runtime.InteropServices;



namespace Mifare1K
{     

    public partial class Mifare_1K : Form
    {
        [DllImport("kernel32.dll")]
        static extern void Sleep(int dwMilliseconds);

        [DllImport("MasterRD.dll")]
        static extern int lib_ver(ref uint pVer);

        [DllImport("MasterRD.dll")]
        static extern int rf_init_com(int port, int baud);

        [DllImport("MasterRD.dll")]
        static extern int rf_ClosePort();

        [DllImport("MasterRD.dll")]
        static extern int rf_antenna_sta(short icdev,byte mode);

        [DllImport("MasterRD.dll")]
        static extern int rf_init_type(short icdev,byte type);

        [DllImport("MasterRD.dll")]
        static extern int rf_request(short icdev, byte mode,ref ushort pTagType);

        [DllImport("MasterRD.dll")]
        static extern int rf_anticoll(short icdev, byte bcnt, IntPtr pSnr, ref byte pRLength);

        [DllImport("MasterRD.dll")]
        static extern int rf_select(short icdev, IntPtr pSnr, byte srcLen, ref sbyte Size);

        [DllImport("MasterRD.dll")]
        static extern int rf_halt(short icdev);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_authentication2(short icdev,byte mode,byte secnr,IntPtr key);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_initval(short icdev,byte adr,Int32 value);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_increment(short icdev,byte adr,Int32 value);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_decrement(short icdev,byte adr,Int32 value);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_readval(short icdev,byte adr,ref Int32 pValue);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_read(short icdev,byte adr,IntPtr pData,ref byte pLen);

        [DllImport("MasterRD.dll")]
        static extern int rf_M1_write(short icdev,byte adr,IntPtr pData);
        
       
        //
        bool bConnectedDevice;/*是否连接上设备*/

        static char[] hexDigits = { 
            '0','1','2','3','4','5','6','7',
            '8','9','A','B','C','D','E','F'};

        public static byte GetHexBitsValue(byte ch)
        {
            byte sz= 0;
            if (ch <= '9' && ch >= '0')
                sz = (byte)(ch - 0x30);
            if (ch <= 'F' && ch >= 'A')
                sz = (byte)(ch - 0x37);
            if (ch <= 'f' && ch >= 'a')
                sz = (byte)(ch - 0x57);

            return sz;
        }
        //

        #region byteHEX
        /// <summary>
        /// 单个字节转字字符.
        /// </summary>
        /// <param name="ib">字节.</param>
        /// <returns>转换好的字符.</returns>
        public static String byteHEX(Byte ib)
        {
            String _str = String.Empty;
            try
            {
                char[] Digit = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
			    'B', 'C', 'D', 'E', 'F' };
                char[] ob = new char[2];
                ob[0] = Digit[(ib >> 4) & 0X0F];
                ob[1] = Digit[ib & 0X0F];
                _str = new String(ob);
            }
            catch (Exception)
            {
                new Exception("对不起有错。");
            }
            return _str;

        }
        #endregion

        public static string ToHexString(byte[] bytes)
        {
            String hexString=String.Empty;
            for(int i = 0 ;i < bytes.Length;i++)
                hexString += byteHEX(bytes[i]);

            return hexString;
        }



        public static byte[] ToDigitsBytes(string theHex)
        {
            byte[] bytes = new byte[theHex.Length / 2 + (((theHex.Length % 2) > 0)?1:0)];
            for (int i = 0; i < bytes.Length;i++ )
            {
                char lowbits = theHex[i * 2];
                char highbits;

                if ((i * 2 + 1) < theHex.Length)
                    highbits = theHex[i * 2 + 1];
                else
                    highbits = '0';

                int a = (int)GetHexBitsValue((byte)lowbits);
                int b = (int)GetHexBitsValue((byte)highbits);
                bytes[i] = (byte)((a << 4) + b);
            }

            return bytes;
        }

        /**/
        public Mifare_1K()
        {
            InitializeComponent();
        }

        private void Mifare_1K_Load(object sender, EventArgs e)
        {
            bConnectedDevice = false;
            //
            cbxSubmass1.Items.Clear();
            cbxSubmass1.Items.Add("1");
            cbxSubmass1.Items.Add("2");
            
            cbxMass1.SelectedIndex = 0;
            cbxSubmass1.SelectedIndex = 0;
            cbxMass2.SelectedIndex = 0;
            cbxSubmass2.SelectedIndex = 0;
            cbxMass3.SelectedIndex = 0;
            cbxSubmass3.SelectedIndex = 0;
            cbxMass4.SelectedIndex = 0;
            cbxSubmass4.SelectedIndex = 0;

            tscbxPort.SelectedIndex = 0;
            tscbxBaud.SelectedIndex = 2;
            //

            txtSearchPurse.MaxLength = 12;
            textBoxPurseKey.MaxLength = 12;

            txtBoxDataOne2.MaxLength = 32;
            txtBoxDataTwo2.MaxLength = 32;
            txtDataThree2.MaxLength = 32;
            txtKeyA2.MaxLength = 12;
            txtKey2.MaxLength = 8;
            txtKeyB2.MaxLength = 12;
            txtInputKey2.MaxLength = 12;

            txtDataOne3.MaxLength = 32;
            txtDataTwo3.MaxLength = 32;
            txtDataThree3.MaxLength = 32;
            txtKeyA3.MaxLength = 12;
            txtKey3.MaxLength = 8;
            txtKeyB3.MaxLength = 12;
            txtInputKey3.MaxLength = 12;

            txtDataOne4.MaxLength = 32;
            txtDataTwo4.MaxLength = 32;
            txtDataThree4.MaxLength = 32;
            txtKeyA4.MaxLength = 12;
            txtKey4.MaxLength = 8;
            txtKeyB4.MaxLength = 12;
            txtInputKey4.MaxLength = 12;
        }

        

        private void btnRequest_Click(object sender, EventArgs e)
        {            
            short icdev = 0x0000;
            int status;
            byte type = (byte)'A';//mifare one 卡询卡方式为A
            byte mode = 0x52;
            ushort TagType = 0;
            byte bcnt = 0x04;//mifare 卡都用4
            IntPtr pSnr;
            byte len = 255;
            sbyte size = 0;


            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            pSnr = Marshal.AllocHGlobal(1024);

            for (int i = 0; i < 2 ;i++ )
            {
                status = rf_antenna_sta(icdev, 0);//关闭天线
                if (status != 0)                
                    continue;
                
                Sleep(20);
                status = rf_init_type(icdev, type);
                if (status != 0)
                    continue;

                Sleep(20);
                status = rf_antenna_sta(icdev, 1);//启动天线
                if (status != 0)
                    continue;

                Sleep(50);
                status = rf_request(icdev, mode, ref TagType);//搜寻所有的卡
                if (status != 0)
                    continue;

                status = rf_anticoll(icdev, bcnt, pSnr, ref len);//返回卡的序列号
                if (status != 0)
                    continue;

                status = rf_select(icdev, pSnr, len, ref size);//锁定一张ISO14443-3 TYPE_A 卡
                if (status != 0)
                    continue;

                byte[] szBytes = new byte[len];
               
                for (int j = 0; j < len; j++)
                {
                    szBytes[j] = Marshal.ReadByte(pSnr, j);
                }

                String m_cardNo = String.Empty;

                for (int q = 0; q < len; q++)
                {
                    m_cardNo += byteHEX(szBytes[q]);
                }
                txtSearchPurse.Text = m_cardNo;                

                break;
            }

            Marshal.FreeHGlobal(pSnr);
        }

        private void btnReqIDL_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            byte mode = 0x26;
            ushort TagType = 0;
            int status;
            byte bcnt = 0x04;//mifare 卡都用4
            IntPtr pSnr;
            byte len = 255;
            sbyte size = 0;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            status = rf_request(icdev, mode, ref TagType);//搜寻所有的卡
            if (status != 0)
            {
                MessageBox.Show("rf_request failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            pSnr = Marshal.AllocHGlobal(1024);
            status = rf_anticoll(icdev, bcnt, pSnr, ref len);//返回卡的序列号
            if (status != 0)
            {
                Marshal.FreeHGlobal(pSnr);
                MessageBox.Show("rf_anticoll failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            status = rf_select(icdev, pSnr, len, ref size);//锁定一张ISO14443-3 TYPE_A 卡
            if (status != 0)
            {
                Marshal.FreeHGlobal(pSnr);
                MessageBox.Show("rf_select failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            byte[] szBytes = new byte[len];          
          
            for (int j = 0; j < len; j++)
            {
                szBytes[j] = Marshal.ReadByte(pSnr, j);
            }
            
            txtSearchPurse.Text = ToHexString(szBytes);
            Marshal.FreeHGlobal(pSnr);
        }

        private void btnHalt_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            status = rf_halt(icdev);
            if (status != 0)
            {
                MessageBox.Show("rf_halt failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);                
            }
        }

        private void btnPurseInit_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr;
	        byte adr;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtPurseKeyB.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass1.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass1.Text) + secnr * 4);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);           

            byte[] bytesKey = ToDigitsBytes(textBoxPurseKey.Text);
            for (int i = 0; i < bytesKey.Length;i++ )
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);

            if(status != 0)
            {                
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (((string)txtPurseDec.Text).Length <= 0)
            {
                MessageBox.Show("not value in purse edit!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error); 
                return;
            }

            Int32 nDecValue = Convert.ToInt32(txtPurseDec.Text);
            status = rf_M1_initval(icdev, adr, nDecValue);

            if (status != 0)
            {                
                MessageBox.Show("rf_M1_initval failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);              
            }            
        }

        private void btnCreditCardIncrement_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr;
            byte adr;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtPurseKeyB.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass1.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass1.Text) + secnr * 4);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(textBoxPurseKey.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (((string)txtPurseDec.Text).Length <= 0)
            {
                MessageBox.Show("not value in purse edit!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Int32 nDecValue = Convert.ToInt32(txtPurseDec.Text);

            status = rf_M1_increment(icdev, adr, nDecValue);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_increment failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);                
            }
        }

        private void btnCreditCardDecrement_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr;
            byte adr;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtPurseKeyB.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass1.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass1.Text) + secnr * 4);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(textBoxPurseKey.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (((string)txtPurseDec.Text).Length <= 0)
            {
                MessageBox.Show("not value in purse edit!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Int32 nDecValue = Convert.ToInt32(txtPurseDec.Text);

            status = rf_M1_decrement(icdev, adr, nDecValue);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_decrement failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnCreditCardBalance_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr;
            byte adr;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtPurseKeyB.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass1.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass1.Text) + secnr * 4);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(textBoxPurseKey.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            Int32 nDecValue = 0;
            status = rf_M1_readval(icdev, adr, ref nDecValue);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_readval failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            txtPurseDec.Text = nDecValue.ToString();
            byte[] byteHex = new byte[4];
            short lowWordbits = (short)((short)nDecValue & 0xFFFF);
            short highWordbits = (short)((nDecValue >> 16) & 0xFFFF);
            byteHex[0] = (byte)(lowWordbits & 0xFF);
            byteHex[1] = (byte)((lowWordbits >> 8) & 0xFF);
            byteHex[2] = (byte)(highWordbits & 0xFF);
            byteHex[3] = (byte)((highWordbits >> 8) & 0xFF);
            txtBoxPurseHex.Text = ToHexString(byteHex);
        }

        private void btnReadSector2_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            txtBoxDataOne2.Text = "";
            txtBoxDataTwo2.Text = "";
            txtDataThree2.Text = "";
            txtKeyA2.Text = "";
            txtKey2.Text = "";
            txtKeyB2.Text = "";

            if (rbtKeyB2.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass2.Text);

            IntPtr keyBuffer = Marshal.AllocHGlobal(256);

            byte[] bytesKey = ToDigitsBytes(txtInputKey2.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i * Marshal.SizeOf(typeof(Byte)), bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            IntPtr dataBuffer = Marshal.AllocHGlobal(256);
            for (int i = 0; i < 4; i++)
            {
                int j;
                byte cLen = 0;
                status = rf_M1_read(icdev, (byte)((secnr * 4) + i), dataBuffer, ref cLen);

                if (status != 0 || cLen != 16)
                {
                    MessageBox.Show("rf_M1_read failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Marshal.FreeHGlobal(dataBuffer);
                    return;
                }

                byte[] bytesData = new byte[16];
                for (j = 0; j < bytesData.Length; j++)
                    bytesData[j] = Marshal.ReadByte(dataBuffer, j);
              
                if (i == 0)
                    txtBoxDataOne2.Text = ToHexString(bytesData);
                else if (i == 1)
                    txtBoxDataTwo2.Text = ToHexString(bytesData);
                else if (i == 2)
                    txtDataThree2.Text = ToHexString(bytesData);
                else if (i == 3)
                {
                    byte[] byteskeyA = new byte[6];
                    byte[] byteskey = new byte[4];
                    byte[] byteskeyB = new byte[6];

                    for (j = 0; j < 16; j++)
                    {
                        if(j < 6)
                            byteskeyA[j] = bytesData[j];
                        else if(j >= 6 && j < 10)
                            byteskey[j - 6] = bytesData[j];
                        else
                            byteskeyB[j - 10] = bytesData[j];
                    }

                    txtKeyA2.Text = ToHexString(byteskeyA);
                    txtKey2.Text = ToHexString(byteskey);
                    txtKeyB2.Text = ToHexString(byteskeyB);
                }
            }
            Marshal.FreeHGlobal(dataBuffer);            
        }

        private void btnWriteBlock2_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;
            byte adr;
            int i;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtKeyB2.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass2.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass2.Text) + secnr * 4);

            if(cbxSubmass2.SelectedIndex == 3)
            {
                if (DialogResult.Cancel == MessageBox.Show("Be sure to write block3!", "Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning))
                    return;
            }

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(txtInputKey2.Text);
            for (i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            byte[] bytesBlock;
            if(cbxSubmass2.SelectedIndex == 0)
            {
                bytesBlock = ToDigitsBytes(txtBoxDataOne2.Text);
            }
            else if(cbxSubmass2.SelectedIndex == 1)
            {
                bytesBlock = ToDigitsBytes(txtBoxDataTwo2.Text);
            }
            else if(cbxSubmass2.SelectedIndex == 2)
            {
                bytesBlock = ToDigitsBytes(txtDataThree2.Text);
            }
            else{                
                String strCompont = txtKeyA2.Text;
                strCompont += txtKey2.Text;
                strCompont += txtKeyB2.Text;
                bytesBlock = ToDigitsBytes(strCompont);
            }

            IntPtr dataBuffer = Marshal.AllocHGlobal(1024);

            for (i = 0; i < bytesBlock.Length; i++)
                Marshal.WriteByte(dataBuffer, i, bytesBlock[i]);
            status = rf_M1_write(icdev, adr, dataBuffer);
            Marshal.FreeHGlobal(dataBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_write failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

        }

        private void btnReadSector3_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            txtDataOne3.Text = "";
            txtDataTwo3.Text = "";
            txtDataThree3.Text = "";
            txtKeyA3.Text = "";
            txtKey3.Text = "";
            txtKeyB3.Text = "";

            if (rbtKeyB3.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass3.Text);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(txtInputKey3.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            IntPtr dataBuffer = Marshal.AllocHGlobal(1024);
            for (int i = 0; i < 4; i++)
            {
                int j;
                byte cLen = 0;
                status = rf_M1_read(icdev, (byte)((secnr * 4) + i), dataBuffer, ref cLen);

                if (status != 0 || cLen != 16)
                {
                    MessageBox.Show("rf_M1_read failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Marshal.FreeHGlobal(dataBuffer);
                    return;
                }

                byte[] bytesData = new byte[16];
                for (j = 0; j < bytesData.Length; j++)
                    bytesData[j] = Marshal.ReadByte(dataBuffer, j);

                if (i == 0)
                    txtDataOne3.Text = ToHexString(bytesData);
                else if (i == 1)
                    txtDataTwo3.Text = ToHexString(bytesData);
                else if (i == 2)
                    txtDataThree3.Text = ToHexString(bytesData);
                else if (i == 3)
                {
                    byte[] byteskeyA = new byte[6];
                    byte[] byteskey = new byte[4];
                    byte[] byteskeyB = new byte[6];

                    for (j = 0; j < 16; j++)
                    {
                        if (j < 6)
                            byteskeyA[j] = bytesData[j];
                        else if (j >= 6 && j < 10)
                            byteskey[j - 6] = bytesData[j];
                        else
                            byteskeyB[j - 10] = bytesData[j];
                    }

                    txtKeyA3.Text = ToHexString(byteskeyA);
                    txtKey3.Text = ToHexString(byteskey);
                    txtKeyB3.Text = ToHexString(byteskeyB);
                }
            }
            Marshal.FreeHGlobal(dataBuffer);            
        }

        private void btnWriteBlock3_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;
            byte adr;
            int i;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtKeyB3.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass3.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass3.Text) + secnr * 4);

            if (cbxSubmass3.SelectedIndex == 3)
            {
                if (DialogResult.Cancel == MessageBox.Show("Be sure to write block3!", "Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning))
                    return;
            }

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(txtInputKey3.Text);
            for (i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            byte[] bytesBlock;
            if (cbxSubmass3.SelectedIndex == 0)
            {
                bytesBlock = ToDigitsBytes(txtDataOne3.Text);
            }
            else if (cbxSubmass3.SelectedIndex == 1)
            {
                bytesBlock = ToDigitsBytes(txtDataTwo3.Text);
            }
            else if (cbxSubmass3.SelectedIndex == 2)
            {
                bytesBlock = ToDigitsBytes(txtDataThree3.Text);
            }
            else
            {
                String strCompont = txtKeyA3.Text;
                strCompont += txtKey3.Text;
                strCompont += txtKeyB3.Text;
                bytesBlock = ToDigitsBytes(strCompont);
            }

            IntPtr dataBuffer = Marshal.AllocHGlobal(1024);

            for (i = 0; i < bytesBlock.Length; i++)
                Marshal.WriteByte(dataBuffer, i, bytesBlock[i]);
            status = rf_M1_write(icdev, adr, dataBuffer);
            Marshal.FreeHGlobal(dataBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_write failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

        }

        private void btnReadSector4_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            txtDataOne4.Text = "";
            txtDataTwo4.Text = "";
            txtDataThree4.Text = "";
            txtKeyA4.Text = "";
            txtKey4.Text = "";
            txtKeyB4.Text = "";

            if (rbtKeyB4.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass4.Text);

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(txtInputKey4.Text);
            for (int i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            IntPtr dataBuffer = Marshal.AllocHGlobal(1024);
            for (int i = 0; i < 4; i++)
            {
                int j;
                byte cLen = 0;
                status = rf_M1_read(icdev, (byte)((secnr * 4) + i), dataBuffer, ref cLen);

                if (status != 0 || cLen != 16)
                {
                    MessageBox.Show("rf_M1_read failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    Marshal.FreeHGlobal(dataBuffer);
                    return;
                }

                byte[] bytesData = new byte[16];
                for (j = 0; j < bytesData.Length; j++)
                    bytesData[j] = Marshal.ReadByte(dataBuffer, j);

                if (i == 0)
                    txtDataOne4.Text = ToHexString(bytesData);
                else if (i == 1)
                    txtDataTwo4.Text = ToHexString(bytesData);
                else if (i == 2)
                    txtDataThree4.Text = ToHexString(bytesData);
                else if (i == 3)
                {
                    byte[] byteskeyA = new byte[6];
                    byte[] byteskey = new byte[4];
                    byte[] byteskeyB = new byte[6];

                    for (j = 0; j < 16; j++)
                    {
                        if (j < 6)
                            byteskeyA[j] = bytesData[j];
                        else if (j >= 6 && j < 10)
                            byteskey[j - 6] = bytesData[j];
                        else
                            byteskeyB[j - 10] = bytesData[j];
                    }

                    txtKeyA4.Text = ToHexString(byteskeyA);
                    txtKey4.Text = ToHexString(byteskey);
                    txtKeyB4.Text = ToHexString(byteskeyB);
                }
            }
            Marshal.FreeHGlobal(dataBuffer);           
        }

        private void btnWriteBlock4_Click(object sender, EventArgs e)
        {
            short icdev = 0x0000;
            int status;
            byte mode = 0x60;
            byte secnr = 0x00;
            byte adr;
            int i;

            if (!bConnectedDevice)
            {
                MessageBox.Show("Not connect to device!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (rbtKeyB4.Checked)
                mode = 0x61; //密钥

            secnr = Convert.ToByte(cbxMass4.Text);
            adr = (byte)(Convert.ToByte(cbxSubmass4.Text) + secnr * 4);

            if (cbxSubmass4.SelectedIndex == 3)
            {
                if (DialogResult.Cancel == MessageBox.Show("Be sure to write block3!", "Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning))
                    return;
            }

            IntPtr keyBuffer = Marshal.AllocHGlobal(1024);

            byte[] bytesKey = ToDigitsBytes(txtInputKey4.Text);
            for (i = 0; i < bytesKey.Length; i++)
                Marshal.WriteByte(keyBuffer, i, bytesKey[i]);
            status = rf_M1_authentication2(icdev, mode, (byte)(secnr * 4), keyBuffer);
            Marshal.FreeHGlobal(keyBuffer);
            if (status != 0)
            {
                MessageBox.Show("rf_M1_authentication2 failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            //
            byte[] bytesBlock;
            if (cbxSubmass4.SelectedIndex == 0)
            {
                bytesBlock = ToDigitsBytes(txtDataOne4.Text);
            }
            else if (cbxSubmass4.SelectedIndex == 1)
            {
                bytesBlock = ToDigitsBytes(txtDataTwo4.Text);
            }
            else if (cbxSubmass4.SelectedIndex == 2)
            {
                bytesBlock = ToDigitsBytes(txtDataThree4.Text);
            }
            else
            {
                String strCompont = txtKeyA4.Text;
                strCompont += txtKey4.Text;
                strCompont += txtKeyB4.Text;
                bytesBlock = ToDigitsBytes(strCompont);
            }

            IntPtr dataBuffer = Marshal.AllocHGlobal(1024);

            for (i = 0; i < bytesBlock.Length; i++)
                Marshal.WriteByte(dataBuffer, i, bytesBlock[i]);
            status = rf_M1_write(icdev, adr, dataBuffer);
            Marshal.FreeHGlobal(dataBuffer);

            if (status != 0)
            {
                MessageBox.Show("rf_M1_write failed!!", "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void tsbtnConnect_Click(object sender, EventArgs e)
        {/*toolbar button[connect] clicked*/
            if(!bConnectedDevice)
            {
                int port = 0;
                int baud = 0;
                int status;

                port = Convert.ToInt32(tscbxPort.Text);
                baud = Convert.ToInt32(tscbxBaud.Text);

                status = rf_init_com(port, baud);
                if (0 == status)
                {
                    tsbtnConnect.Text = "Disconnect";
                    bConnectedDevice = true;
                    MessageBox.Show("Connect device success!");
                }
                else
                {
                    string strError;
                    strError = "Connect device failed";
                    bConnectedDevice = false;
                    MessageBox.Show(strError, "error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else{
                rf_ClosePort();
                bConnectedDevice = false;
                tsbtnConnect.Text = "Connect";
            }
            
        }

        private void cbxMass1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string cbxtext = cbxSubmass1.Text;
            cbxSubmass1.Items.Clear();
           
            if(0 == cbxMass1.SelectedIndex)
            {
                cbxSubmass1.Items.Add("1");
                cbxSubmass1.Items.Add("2");
                if (cbxtext == "2")
                    cbxSubmass1.SelectedIndex = 1;
                else
                    cbxSubmass1.SelectedIndex = 0;
            }
            else
            {
                cbxSubmass1.Items.Add("0");
                cbxSubmass1.Items.Add("1");
                cbxSubmass1.Items.Add("2");   
             
                if(cbxtext == "1")
                    cbxSubmass1.SelectedIndex = 1;
                else if(cbxtext == "2")
                    cbxSubmass1.SelectedIndex = 2;
                else
                    cbxSubmass1.SelectedIndex = 0;
            }
           
        }
    }
}