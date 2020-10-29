Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
Friend Class frm_main
	Inherits System.Windows.Forms.Form
	
	Private Sub Command1_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Command1.Click
		Dim port, i, baud As Integer
		Dim j As Short
		Dim buf1(200) As Byte
		Dim b1 As Byte
		Dim s1 As String
		port = cb_ckh.SelectedIndex + 1
		If (port = 0) Then
			lb_info.Text = "Please select COM Port!"
		End If
		baud = CInt(cb_btl.Text)
		If (baud = 0) Then
			lb_info.Text = "Please select Baud rate!"
		End If
		'Open Port
		i = rf_init_com(port, baud)
		If (i <> 0) Then
			lb_info.Text = "Open Port Fail!"
			Exit Sub
		End If
		'Request
		i = rf_request(0, &H52s, j)
		If (i <> 0) Then
			lb_info.Text = "Request Fail!"
			Exit Sub
		End If
		'Anticollision
		i = rf_anticoll(0, 4, buf1(0), b1)
		If (i <> 0) Then
			lb_info.Text = "Anticollision Fail!"
			Exit Sub
		End If
		s1 = ""
		For i = 0 To b1 - 1
			s1 = s1 & VB.Right("00" & Hex(buf1(i)), 2)
		Next i
		tx_kh.Text = s1
		'Select card
		i = rf_select(0, buf1(0), 4, b1)
		If (i <> 0) Then
			lb_info.Text = "Select card fail!"
			Exit Sub
		End If
		lb_info.Text = "Select card succeed!"
	End Sub
	
	Private Sub Command2_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Command2.Click
		Dim i, m As Integer
		Dim buf1(200) As Byte
		Dim buf2(200) As Byte
		Dim s1 As String
		Dim b2, b1, b3 As Byte
		s1 = Trim(tx_key.Text)
		If (Len(s1) <> 12) Then
			lb_info.Text = "Wrong Key Length!"
			tx_key.Focus()
			Exit Sub
		End If
		For i = 0 To 5
			buf1(i) = Val("&H" & Mid(s1, i * 2 + 1, 2))
		Next i
		m = cb_kh.SelectedIndex
		If (m = -1) Then
			lb_info.Text = "Select Block Please!"
			Exit Sub
		End If
		If (op_a.Checked) Then
			b1 = &H60s
		End If
		If (op_b.Checked) Then
			b1 = &H61s
		End If
		b3 = CByte(m)
		'Authentication
		i = rf_M1_authentication2(0, b1, b3, buf1(0))
		If (i <> 0) Then
			lb_info.Text = "Authentication Fail£¡"
			Exit Sub
		End If
		'Read card
		i = rf_M1_read(0, b3, buf2(0), b2)
		If (i <> 0) Then
			lb_info.Text = "Read Card Fail!"
			Exit Sub
		End If
		s1 = ""
		For i = 0 To b2 - 1
			s1 = s1 & VB.Right("00" & Hex(buf2(i)), 2)
		Next i
		tx_sj.Text = s1
		lb_info.Text = "Read Succeed!"
	End Sub
	
	Private Sub Command3_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Command3.Click
		Dim i, m As Integer
		Dim buf1(200) As Byte
		Dim buf2(200) As Byte
		Dim s1 As String
		Dim b2, b1, b3 As Byte
		s1 = Trim(tx_key.Text)
		If (Len(s1) <> 12) Then
			lb_info.Text = "Wrong Key Length!"
			tx_key.Focus()
			Exit Sub
		End If
		For i = 0 To 5
			buf1(i) = Val("&H" & Mid(s1, i * 2 + 1, 2))
		Next i
		m = cb_kh.SelectedIndex
		If (m = -1) Then
			lb_info.Text = "Select Block Please!"
			Exit Sub
		End If
		If (op_a.Checked) Then
			b1 = &H60s
		End If
		If (op_b.Checked) Then
			b1 = &H61s
		End If
		
		s1 = Trim(tx_sj.Text)
		If (Len(s1) <> 32) Then
			lb_info.Text = "Wrong Data length "
			tx_sj.Focus()
			Exit Sub
		End If
		For i = 0 To 15
			buf2(i) = Val("&H" & Mid(s1, i * 2 + 1, 2))
		Next i
		'Authentication
		b3 = CByte(m)
		i = rf_M1_authentication2(0, b1, b3, buf1(0))
		If (i <> 0) Then
			lb_info.Text = "Authentication Fail!"
			Exit Sub
		End If
		'Write card
		i = rf_M1_write(0, b3, buf2(0))
		If (i <> 0) Then
			lb_info.Text = "Write Card Fail£¡"
			Exit Sub
		End If
		
		lb_info.Text = "Write Succeed!"
	End Sub
	
	Private Sub Command4_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles Command4.Click
		Dim i As Integer
		i = rf_halt(0)
		If (i <> 0) Then
			lb_info.Text = "Halt Fail!"
			Exit Sub
		End If
		lb_info.Text = "Halt Succeed"
	End Sub
	
	Private Sub frm_main_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
		Dim i As Integer
		For i = 0 To 63
			cb_kh.Items.Insert(i, CStr(i))
		Next i
		cb_ckh.SelectedIndex = 0 : cb_btl.SelectedIndex = 1 : cb_kh.SelectedIndex = 4
	End Sub
End Class