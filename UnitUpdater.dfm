object FormUpdate: TFormUpdate
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1099
  ClientHeight = 197
  ClientWidth = 555
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 13
  object LabelInfo: TLabel
    Left = 24
    Top = 13
    Width = 524
    Height = 19
    Alignment = taCenter
    Caption = 
      #1048#1084#1077#1077#1090#1089#1103' '#1085#1086#1074#1072#1103' '#1074#1077#1088#1089#1080#1103' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' TShop_3.1.2.3. '#1057#1082#1072#1095#1072#1090#1100' '#1080' '#1086#1073#1085#1086#1074#1080#1090#1100 +
      '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object ProgressBar1: TProgressBar
    Left = 24
    Top = 81
    Width = 524
    Height = 25
    TabOrder = 0
  end
  object ButtonUpdate: TButton
    Left = 95
    Top = 144
    Width = 129
    Height = 25
    Caption = #1054#1073#1085#1086#1074#1080#1090#1100' '#1089#1077#1081#1095#1072#1089
    TabOrder = 1
    OnClick = ButtonUpdateClick
  end
  object ButtonCancel: TButton
    Left = 360
    Top = 144
    Width = 129
    Height = 25
    Caption = #1053#1077#1090' '#1085#1077' '#1089#1077#1081#1095#1072#1089
    TabOrder = 2
    OnClick = ButtonCancelClick
  end
  object IdAntiFreeze1: TIdAntiFreeze
    Active = False
    Left = 279
    Top = 143
  end
end
