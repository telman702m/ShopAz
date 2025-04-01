object FormMoveOther: TFormMoveOther
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1054#1087#1083#1072#1090#1072' '#1076#1086#1083#1075#1072
  ClientHeight = 413
  ClientWidth = 411
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  TextHeight = 13
  object LabelNote: TLabel
    Left = 10
    Top = 265
    Width = 84
    Height = 17
    Caption = #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  object GroupBoxSource: TGroupBox
    Left = 10
    Top = 39
    Width = 382
    Height = 66
    TabOrder = 0
    object LabelSourceUnit: TLabel
      Left = 7
      Top = 8
      Width = 83
      Height = 17
      Caption = #1055#1083#1072#1090#1077#1083#1100#1097#1080#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelSourcePerson: TLabel
      Left = 7
      Top = 38
      Width = 29
      Height = 17
      Caption = #1048#1084#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditSourceUnit: TEdit
      Left = 105
      Top = 6
      Width = 274
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnClick = EditSourceUnitClick
    end
    object EditSourcePerson: TEdit
      Left = 103
      Top = 36
      Width = 274
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
  end
  object GroupBoxCenter: TGroupBox
    Left = 10
    Top = 6
    Width = 237
    Height = 27
    TabOrder = 1
    object LabeluDate: TLabel
      Left = 11
      Top = 3
      Width = 33
      Height = 17
      Caption = #1044#1072#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelDate: TLabel
      Left = 94
      Top = 3
      Width = 120
      Height = 17
      Caption = '13.03.2015   15:54'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
  end
  object MemoDescription: TMemo
    Left = 10
    Top = 286
    Width = 399
    Height = 81
    TabOrder = 2
  end
  object ButtonSubmit: TButton
    Left = 59
    Top = 380
    Width = 98
    Height = 25
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 3
  end
  object ButtonCancel: TButton
    Left = 253
    Top = 380
    Width = 98
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 4
    OnClick = ButtonCancelClick
  end
  object GroupBoxRight: TGroupBox
    Left = 10
    Top = 209
    Width = 399
    Height = 45
    TabOrder = 5
    object LabelActualPayment: TLabel
      Left = 11
      Top = 10
      Width = 119
      Height = 17
      Caption = #1042#1085#1086#1089#1080#1084#1072#1103' '#1086#1087#1083#1072#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPrice1: TLabel
      Left = 231
      Top = 10
      Width = 41
      Height = 17
      Caption = #1084#1072#1085#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelCent1: TLabel
      Left = 341
      Top = 10
      Width = 46
      Height = 17
      Caption = #1082#1086#1087#1077#1077#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditActualPayment1: TEdit
      Left = 152
      Top = 10
      Width = 73
      Height = 21
      Alignment = taRightJustify
      NumbersOnly = True
      TabOrder = 0
      OnChange = EditActualPayment1Change
    end
    object EditActualPayment2: TEdit
      Left = 286
      Top = 10
      Width = 49
      Height = 21
      Alignment = taRightJustify
      NumbersOnly = True
      TabOrder = 1
      OnChange = EditActualPayment1Change
    end
  end
  object GroupBox1: TGroupBox
    Left = 10
    Top = 117
    Width = 382
    Height = 66
    TabOrder = 6
    object LabelTargetUnit: TLabel
      Left = 7
      Top = 8
      Width = 80
      Height = 17
      Caption = #1055#1086#1083#1091#1095#1072#1090#1077#1083#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelTargetPerson: TLabel
      Left = 7
      Top = 38
      Width = 29
      Height = 17
      Caption = #1048#1084#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditTargetUnit: TEdit
      Left = 105
      Top = 6
      Width = 274
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnClick = EditSourceUnitClick
    end
    object EditTargetPerson: TEdit
      Left = 103
      Top = 36
      Width = 274
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      OnClick = EditSourceUnitClick
    end
  end
  object TimerDate: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TimerDateTimer
    Left = 318
    Top = 65532
  end
end
