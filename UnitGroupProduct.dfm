object FormGroupProduct: TFormGroupProduct
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1061#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080' '#1075#1088#1091#1087#1087#1099' '#1090#1086#1074#1072#1088#1086#1074
  ClientHeight = 338
  ClientWidth = 561
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
  object LabelGroupCode: TLabel
    Left = 16
    Top = 24
    Width = 146
    Height = 18
    Caption = #1050#1086#1076' '#1075#1088#1091#1087#1087#1099' '#1090#1086#1074#1072#1088#1086#1074
    DragMode = dmAutomatic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object LabelGroupName: TLabel
    Left = 16
    Top = 64
    Width = 189
    Height = 18
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1075#1088#1091#1087#1087#1099' '#1090#1086#1074#1072#1088#1086#1074
    DragMode = dmAutomatic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object LabelDescription: TLabel
    Left = 112
    Top = 141
    Width = 202
    Height = 19
    Caption = #1054#1087#1080#1089#1072#1085#1080#1077' '#1075#1088#1091#1087#1087#1099' '#1090#1086#1074#1072#1088#1086#1074
    DragMode = dmAutomatic
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object EditCode: TEdit
    Left = 264
    Top = 25
    Width = 273
    Height = 21
    MaxLength = 20
    TabOrder = 0
  end
  object EditName: TEdit
    Left = 264
    Top = 65
    Width = 273
    Height = 21
    MaxLength = 30
    TabOrder = 1
  end
  object CheckBoxEnable: TCheckBox
    Left = 16
    Top = 104
    Width = 82
    Height = 17
    Caption = #1040#1082#1090#1080#1074#1085#1099#1081
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Visible = False
  end
  object MemoDescription: TMemo
    Left = 16
    Top = 166
    Width = 521
    Height = 115
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    Lines.Strings = (
      'MemoDescription')
    MaxLength = 360
    ParentFont = False
    TabOrder = 3
  end
  object ButtonInsert: TButton
    Left = 94
    Top = 294
    Width = 105
    Height = 25
    Caption = #1042#1089#1090#1072#1074#1080#1090#1100
    TabOrder = 4
    OnClick = ButtonInsertClick
  end
  object ButtonClose: TButton
    Left = 336
    Top = 294
    Width = 105
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 5
    OnClick = ButtonCloseClick
  end
end
