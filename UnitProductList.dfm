object FormProductList: TFormProductList
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1057#1087#1080#1089#1086#1082' '#1085#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1081' '#1090#1086#1074#1072#1088#1086#1074
  ClientHeight = 670
  ClientWidth = 1157
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
  OnResize = FormResize
  OnShow = FormShow
  TextHeight = 13
  object LabelGroup: TLabel
    Left = 16
    Top = 54
    Width = 41
    Height = 16
    Caption = #1043#1088#1091#1087#1087#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object LabelSearchByName: TLabel
    Left = 344
    Top = 54
    Width = 116
    Height = 16
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1072#1079#1074#1072#1085#1080#1102
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object ComboBoxFilter: TComboBox
    Left = 88
    Top = 51
    Width = 217
    Height = 24
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnChange = ComboBoxFilterChange
  end
  object EditFind: TEdit
    Left = 471
    Top = 51
    Width = 162
    Height = 21
    TabOrder = 1
    OnChange = EditFindChange
  end
  object CheckBoxShowEmpty: TCheckBox
    Left = 923
    Top = 55
    Width = 185
    Height = 17
    Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1086#1090#1089#1091#1090#1089#1090#1074#1091#1102#1097#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = CheckBoxShowEmptyClick
  end
  object CheckBoxHidePrice: TCheckBox
    Left = 715
    Top = 55
    Width = 185
    Height = 17
    Caption = #1057#1082#1088#1099#1090#1100' '#1089#1090#1086#1080#1084#1086#1089#1090#1100
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 3
    OnClick = CheckBoxHidePriceClick
  end
  object FileSaveDialog1: TFileSaveDialog
    FavoriteLinks = <>
    FileTypes = <
      item
        DisplayName = 'Excel 2010'
        FileMask = 'xlsx'
      end
      item
        DisplayName = 'Excel 2003'
        FileMask = 'xls'
      end>
    Options = []
    Left = 1056
    Top = 608
  end
end
