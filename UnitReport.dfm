object FormReport: TFormReport
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1054#1090#1095#1077#1090
  ClientHeight = 676
  ClientWidth = 1278
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  TextHeight = 13
  object GroupBoxDateRange: TGroupBox
    Left = 24
    Top = 8
    Width = 433
    Height = 73
    Caption = #1044#1080#1072#1087#1072#1079#1086#1085' '#1076#1072#1090' '#1076#1083#1103' '#1092#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1103' '#1086#1090#1095#1077#1090#1072' '
    TabOrder = 0
    object LabelStartDate: TLabel
      Left = 16
      Top = 38
      Width = 44
      Height = 16
      Caption = #1053#1072#1095#1072#1083#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelEndDate: TLabel
      Left = 249
      Top = 38
      Width = 36
      Height = 16
      Caption = #1050#1086#1085#1077#1094
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object DateTimePicker1: TDateTimePicker
      Left = 75
      Top = 35
      Width = 109
      Height = 23
      Date = 41045.000000000000000000
      Time = 0.931088599536451500
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
      OnClick = DateTimePicker1Click
      OnCloseUp = DateTimePicker1CloseUp
      OnChange = DateTimePicker1Change
    end
    object DateTimePicker2: TDateTimePicker
      Left = 306
      Top = 35
      Width = 109
      Height = 23
      Date = 41045.000000000000000000
      Time = 0.931088599536451500
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 1
      OnClick = DateTimePicker1Click
      OnCloseUp = DateTimePicker1CloseUp
      OnChange = DateTimePicker1Change
    end
  end
  object GroupBoxPredefInterval: TGroupBox
    Left = 528
    Top = 8
    Width = 750
    Height = 73
    Caption = #1055#1088#1077#1076#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1099#1077' '#1076#1080#1072#1087#1072#1079#1086#1085#1099' '#1076#1072#1090' '#1076#1083#1103' '#1086#1090#1095#1077#1090#1072
    TabOrder = 1
    object ButtonLastDay: TButton
      Left = 16
      Top = 32
      Width = 140
      Height = 25
      Caption = #1047#1072' '#1087#1086#1089#1083#1077#1076#1085#1080#1081' '#1076#1077#1085#1100
      TabOrder = 0
      OnClick = ButtonsPredefClick
    end
    object ButtonLastWeek: TButton
      Left = 208
      Top = 32
      Width = 140
      Height = 25
      Caption = #1047#1072' '#1087#1086#1089#1083#1077#1076#1085#1102#1102' '#1085#1077#1076#1077#1083#1102
      TabOrder = 1
      OnClick = ButtonsPredefClick
    end
    object ButtonLastMonth: TButton
      Left = 400
      Top = 32
      Width = 140
      Height = 25
      Caption = #1047#1072' '#1087#1086#1089#1083#1077#1076#1085#1080#1081' '#1084#1077#1089#1103#1094
      TabOrder = 2
      OnClick = ButtonsPredefClick
    end
    object ButtonLastYear: TButton
      Left = 592
      Top = 32
      Width = 140
      Height = 25
      Caption = #1047#1072' '#1087#1086#1089#1083#1077#1076#1085#1080#1081' '#1075#1086#1076
      TabOrder = 3
      OnClick = ButtonsPredefClick
    end
  end
  object GroupBoxStatistic: TGroupBox
    Left = 40
    Top = 424
    Width = 1238
    Height = 209
    Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1095#1077#1089#1082#1080#1077' '#1087#1086#1082#1072#1079#1072#1090#1077#1083#1080'  '
    TabOrder = 2
    object Label1: TLabel
      Left = 13
      Top = 40
      Width = 278
      Height = 13
      Caption = #1057#1087#1080#1089#1086#1082' '#1090#1086#1074#1072#1088#1086#1074', '#1087#1088#1080#1085#1086#1089#1103#1097#1080#1093' '#1089#1072#1084#1091#1102' '#1074#1099#1089#1086#1091#1102' '#1087#1088#1080#1073#1099#1083#1100' '
    end
    object Label2: TLabel
      Left = 13
      Top = 80
      Width = 243
      Height = 13
      Caption = #1057#1087#1080#1089#1086#1082' '#1085#1072#1080#1073#1086#1083#1077#1077' '#1095#1072#1089#1090#1086' '#1074#1086#1079#1074#1088#1072#1097#1072#1077#1084#1099#1093' '#1090#1086#1074#1072#1088#1086#1074
    end
    object Label3: TLabel
      Left = 13
      Top = 128
      Width = 142
      Height = 13
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1073#1099#1090#1086#1095#1085#1099#1093' '#1090#1086#1074#1072#1088#1086#1074
    end
    object Label4: TLabel
      Left = 13
      Top = 168
      Width = 31
      Height = 13
      Caption = #1048' '#1090'.'#1076'.'
    end
  end
end
