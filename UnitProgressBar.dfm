object FormProgressBar: TFormProgressBar
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1089' '#1041#1072#1079#1099' '#1044#1072#1085#1085#1099#1093
  ClientHeight = 103
  ClientWidth = 410
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  TextHeight = 13
  object Label1: TLabel
    AlignWithMargins = True
    Left = 19
    Top = 19
    Width = 365
    Height = 16
    Alignment = taCenter
    Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1076#1072#1085#1085#1099#1093' '#1086' "'#1054#1087#1077#1088#1072#1094#1080#1103#1093' '#1089' '#1090#1086#1074#1072#1088#1072#1084#1080'" '#1089' '#1089#1077#1088#1074#1077#1088#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    Transparent = True
  end
  object ProgressBar1: TProgressBar
    Left = 19
    Top = 46
    Width = 365
    Height = 33
    TabOrder = 0
  end
end
