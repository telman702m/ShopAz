object FormMoveProduct: TFormMoveProduct
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1055#1088#1086#1076#1072#1078#1072' '#1090#1086#1074#1072#1088#1086#1074
  ClientHeight = 631
  ClientWidth = 1160
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  OnShow = FormShow
  TextHeight = 13
  object LabelNote: TLabel
    Left = 516
    Top = 510
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
  object ButtonSubmit: TButton
    Left = 285
    Top = 600
    Width = 98
    Height = 25
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 0
  end
  object GroupBoxSource: TGroupBox
    Left = 10
    Top = 46
    Width = 382
    Height = 83
    TabOrder = 1
    object LabelSourceUnit: TLabel
      Left = 7
      Top = 16
      Width = 90
      Height = 17
      Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1077#1083#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelSourcePerson: TLabel
      Left = 7
      Top = 54
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
      Left = 103
      Top = 14
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
      Top = 52
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
  object GroupBoxTarget: TGroupBox
    Left = 752
    Top = 46
    Width = 382
    Height = 83
    TabOrder = 2
    object LabelTargetPerson: TLabel
      Left = 7
      Top = 54
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
    object LabelTargetUnit: TLabel
      Left = 7
      Top = 16
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
    object EditTargetUnit: TEdit
      Left = 100
      Top = 14
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
      OnClick = EditTargetUnitClick
    end
    object EditTargetPerson: TEdit
      Left = 100
      Top = 52
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
      OnClick = EditTargetUnitClick
    end
  end
  object ButtonCancel: TButton
    Left = 711
    Top = 600
    Width = 98
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 3
    OnClick = ButtonCancelClick
  end
  object GroupBoxLeft: TGroupBox
    Left = 10
    Top = 431
    Width = 425
    Height = 78
    TabOrder = 4
    object LabelDiscount: TLabel
      Left = 10
      Top = 47
      Width = 50
      Height = 17
      Caption = #1057#1082#1080#1076#1082#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPercent: TLabel
      Left = 133
      Top = 47
      Width = 13
      Height = 17
      Caption = '%'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPriceL: TLabel
      Left = 242
      Top = 47
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
    object LabelCentL: TLabel
      Left = 357
      Top = 47
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
    object LabelTotalPayment: TLabel
      Left = 10
      Top = 10
      Width = 95
      Height = 17
      Caption = #1054#1073#1097#1072#1103' '#1089#1091#1084#1084#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPrice3: TLabel
      Left = 242
      Top = 10
      Width = 41
      Height = 17
      Caption = #1084#1072#1085#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelCent3: TLabel
      Left = 357
      Top = 10
      Width = 46
      Height = 17
      Caption = #1082#1086#1087#1077#1077#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditDiscountPercent: TEdit
      Left = 78
      Top = 47
      Width = 49
      Height = 21
      Alignment = taRightJustify
      MaxLength = 10
      TabOrder = 0
      OnChange = EditDiscountPercentChange
    end
    object EditDiscountPrice1: TEdit
      Left = 163
      Top = 47
      Width = 73
      Height = 21
      Alignment = taRightJustify
      MaxLength = 8
      NumbersOnly = True
      TabOrder = 1
      OnChange = EditDiscountPrice1Change
    end
    object EditDiscountPrice2: TEdit
      Left = 302
      Top = 47
      Width = 49
      Height = 21
      Alignment = taRightJustify
      MaxLength = 2
      NumbersOnly = True
      TabOrder = 2
      OnChange = EditDiscountPrice1Change
    end
    object EditTotalPrice1: TEdit
      Left = 163
      Top = 10
      Width = 73
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      MaxLength = 8
      NumbersOnly = True
      ReadOnly = True
      TabOrder = 3
    end
    object EditTotalPrice2: TEdit
      Left = 302
      Top = 10
      Width = 49
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      MaxLength = 2
      NumbersOnly = True
      ReadOnly = True
      TabOrder = 4
    end
  end
  object GroupBoxRight: TGroupBox
    Left = 752
    Top = 431
    Width = 422
    Height = 78
    TabOrder = 5
    object LabelActualPayment: TLabel
      Left = 11
      Top = 10
      Width = 139
      Height = 17
      Caption = #1060#1072#1082#1090#1080#1095#1077#1089#1082#1072#1103' '#1086#1087#1083#1072#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPrice1: TLabel
      Left = 243
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
      Left = 358
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
    object LabelDebt: TLabel
      Left = 11
      Top = 47
      Width = 120
      Height = 17
      Caption = #1054#1089#1090#1072#1074#1096#1080#1081#1089#1103' '#1076#1086#1083#1075
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPrice2: TLabel
      Left = 243
      Top = 47
      Width = 41
      Height = 17
      Caption = #1084#1072#1085#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelCent2: TLabel
      Left = 358
      Top = 47
      Width = 46
      Height = 17
      Caption = #1082#1086#1087#1077#1077#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditActualPayment1: TEdit
      Left = 164
      Top = 10
      Width = 73
      Height = 21
      Alignment = taRightJustify
      NumbersOnly = True
      TabOrder = 0
      OnChange = EditActualPayment1Change
    end
    object EditActualPayment2: TEdit
      Left = 303
      Top = 10
      Width = 49
      Height = 21
      Alignment = taRightJustify
      NumbersOnly = True
      TabOrder = 1
      OnChange = EditActualPayment1Change
    end
    object EditDebt1: TEdit
      Left = 164
      Top = 47
      Width = 73
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      ReadOnly = True
      TabOrder = 2
    end
    object EditDebt2: TEdit
      Left = 303
      Top = 47
      Width = 49
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      ReadOnly = True
      TabOrder = 3
    end
  end
  object GroupBoxCenter: TGroupBox
    Left = 463
    Top = 46
    Width = 252
    Height = 83
    TabOrder = 6
    object LabeluDate: TLabel
      Left = 18
      Top = 16
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
      Left = 100
      Top = 16
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
    object LabeluCashNumb: TLabel
      Left = 48
      Top = 54
      Width = 51
      Height = 17
      Caption = #8470' '#1095#1077#1082#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelCashNumb: TLabel
      Left = 130
      Top = 54
      Width = 72
      Height = 17
      Caption = '12 345 567'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
  end
  object MemoDescription: TMemo
    Left = 8
    Top = 533
    Width = 1166
    Height = 57
    TabOrder = 7
  end
  object GroupBoxCenter2: TGroupBox
    Left = 463
    Top = 431
    Width = 262
    Height = 78
    TabOrder = 8
    object LabelSum: TLabel
      Left = 12
      Top = 10
      Width = 108
      Height = 17
      Caption = #1057#1091#1084#1084#1072' '#1082' '#1086#1087#1083#1072#1090#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPriceR: TLabel
      Left = 91
      Top = 43
      Width = 41
      Height = 17
      Caption = #1084#1072#1085#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelCentR: TLabel
      Left = 206
      Top = 43
      Width = 46
      Height = 17
      Caption = #1082#1086#1087#1077#1077#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGrayText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object EditBuyerPayment1: TEdit
      Left = 12
      Top = 43
      Width = 73
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      ReadOnly = True
      TabOrder = 0
      OnChange = EditBuyerPayment1Change
    end
    object EditBuyerPayment2: TEdit
      Left = 151
      Top = 43
      Width = 49
      Height = 21
      Alignment = taRightJustify
      Enabled = False
      ReadOnly = True
      TabOrder = 1
    end
  end
  object TimerDate: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TimerDateTimer
    Left = 552
    Top = 355
  end
end
