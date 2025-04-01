object FormLanguage: TFormLanguage
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'Language'
  ClientHeight = 145
  ClientWidth = 350
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 5
    Width = 320
    Height = 18
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1103#1079#1099#1082' '#1080#1085#1090#1077#1088#1092#1077#1081#1089#1072' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' TShop'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 40
    Top = 29
    Width = 265
    Height = 18
    Caption = 'TShop Program interfeys '#252#231'un dilini se'#231'in'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object ComboBoxLang: TComboBox
    Left = 80
    Top = 66
    Width = 161
    Height = 24
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Items.Strings = (
      #1056#1091#1089#1089#1082#1080#1081' '#1103#1079#1099#1082
      'Az'#601'rbaycan dili')
  end
  object ButtonOk: TButton
    Left = 40
    Top = 110
    Width = 89
    Height = 25
    Caption = 'Ok'
    TabOrder = 1
    OnClick = ButtonOkClick
  end
  object ButtonCancel: TButton
    Left = 206
    Top = 110
    Width = 89
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = ButtonCancelClick
  end
end
