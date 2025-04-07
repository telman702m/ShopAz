object FormShopUnit: TFormShopUnit
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1044#1072#1085#1085#1099#1077' '#1086#1073' '#1086#1073#1098#1077#1082#1090#1077' '#1089#1077#1090#1080' '#1084#1072#1075#1072#1079#1080#1085#1086#1074
  ClientHeight = 367
  ClientWidth = 457
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 443
    Height = 318
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object LabelName: TLabel
      Left = 16
      Top = 54
      Width = 65
      Height = 17
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelType: TLabel
      Left = 17
      Top = 13
      Width = 84
      Height = 17
      Caption = #1058#1080#1087' '#1086#1073#1098#1077#1082#1090#1072
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelAddress: TLabel
      Left = 17
      Top = 95
      Width = 42
      Height = 17
      Caption = #1040#1076#1088#1077#1089
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPhone1: TLabel
      Left = 16
      Top = 126
      Width = 67
      Height = 17
      Caption = #1058#1077#1083#1077#1092#1086#1085'1'
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelPhone2: TLabel
      Left = 16
      Top = 157
      Width = 67
      Height = 17
      Caption = #1058#1077#1083#1077#1092#1086#1085'2'
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
    object LabelDescript: TLabel
      Left = 16
      Top = 193
      Width = 68
      Height = 17
      Caption = #1054#1087#1080#1089#1072#1085#1080#1077
      DragMode = dmAutomatic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = [fsItalic, fsUnderline]
      ParentFont = False
    end
    object EditName: TEdit
      Left = 120
      Top = 52
      Width = 225
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      MaxLength = 40
      ParentFont = False
      TabOrder = 0
    end
    object EditAddress: TEdit
      Left = 120
      Top = 93
      Width = 314
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      MaxLength = 40
      ParentFont = False
      TabOrder = 1
    end
    object EditPhone1: TEdit
      Left = 120
      Top = 124
      Width = 145
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      MaxLength = 40
      ParentFont = False
      TabOrder = 2
    end
    object EditPhone2: TEdit
      Left = 120
      Top = 154
      Width = 145
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = []
      MaxLength = 40
      ParentFont = False
      TabOrder = 3
    end
    object MemoDescription: TMemo
      Left = 16
      Top = 212
      Width = 418
      Height = 75
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Arial'
      Font.Style = []
      Lines.Strings = (
        'MemoDescription')
      ParentFont = False
      TabOrder = 5
    end
    object CheckBoxEnable: TCheckBox
      Left = 17
      Top = 293
      Width = 82
      Height = 17
      Caption = #1040#1082#1090#1080#1074#1085#1099#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
    object ComboBoxType: TComboBox
      Left = 120
      Top = 10
      Width = 177
      Height = 25
      Style = csDropDownList
      TabOrder = 6
      Items.Strings = (
        #1057#1082#1083#1072#1076
        #1052#1072#1075#1072#1079#1080#1085)
    end
  end
  object ButtonSave: TButton
    Left = 64
    Top = 333
    Width = 105
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 1
    OnClick = ButtonSaveClick
  end
  object ButtonClose: TButton
    Left = 279
    Top = 332
    Width = 105
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 2
    OnClick = ButtonCloseClick
  end
end
