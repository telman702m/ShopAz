object FormUserStatus: TFormUserStatus
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1057#1090#1072#1090#1091#1089' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
  ClientHeight = 255
  ClientWidth = 248
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 13
  object LabelPassword: TLabel
    Left = 12
    Top = 75
    Width = 55
    Height = 16
    Caption = 'Password'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LabelUnitShop: TLabel
    Left = 12
    Top = 12
    Width = 88
    Height = 16
    Caption = #1042#1099#1073#1086#1088' '#1086#1073#1098#1077#1082#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LabelLogin: TLabel
    Left = 12
    Top = 48
    Width = 35
    Height = 16
    Caption = 'Login:'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LabelLastLoadDate: TLabel
    Left = 12
    Top = 168
    Width = 83
    Height = 16
    Caption = #1044#1072#1090#1072' '#1079#1072#1075#1088#1091#1079#1082#1080
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object ComboBoxShopUnits: TComboBox
    Left = 113
    Top = 9
    Width = 121
    Height = 24
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnChange = ComboBoxShopUnitsChange
  end
  object EditPassword: TEdit
    Left = 113
    Top = 74
    Width = 121
    Height = 21
    Enabled = False
    PasswordChar = '*'
    TabOrder = 2
    OnKeyDown = EditPasswordKeyDown
  end
  object ButtonOk: TButton
    Left = 12
    Top = 211
    Width = 81
    Height = 25
    Caption = 'Ok'
    TabOrder = 4
    OnClick = ButtonOkClick
  end
  object ButtonCancel: TButton
    Left = 153
    Top = 211
    Width = 81
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 5
    OnClick = ButtonCancelClick
  end
  object EditLogin: TEdit
    Left = 113
    Top = 47
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 1
    OnKeyDown = EditPasswordKeyDown
  end
  object DateTimePickerStartData: TDateTimePicker
    Left = 113
    Top = 167
    Width = 121
    Height = 23
    Date = 41045.000000000000000000
    Time = 0.931088599536451500
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 3
    OnChange = DateTimePickerStartDataChange
  end
  object CheckBoxLoadType: TCheckBox
    Left = 12
    Top = 112
    Width = 222
    Height = 33
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1086#1089#1085#1086#1074#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' '#1080#1079' '#1083#1086#1082#1072#1083#1100#1085#1099#1093' '#1092#1072#1081#1083#1086#1074
    Checked = True
    State = cbChecked
    TabOrder = 6
    WordWrap = True
  end
end
