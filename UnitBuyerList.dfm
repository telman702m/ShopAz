object FormBuyerList: TFormBuyerList
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = #1057#1087#1080#1089#1086#1082' '#1087#1086#1082#1091#1087#1072#1090#1077#1083#1077#1081
  ClientHeight = 626
  ClientWidth = 1164
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
  TextHeight = 13
  object LabelSearchByName: TLabel
    Left = 16
    Top = 57
    Width = 95
    Height = 16
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1080#1084#1077#1085#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object LabelSearchByattribute: TLabel
    Left = 368
    Top = 57
    Width = 124
    Height = 16
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1072#1090#1090#1088#1080#1073#1091#1090#1072#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object EditFindName: TEdit
    Left = 150
    Top = 54
    Width = 162
    Height = 21
    TabOrder = 0
    OnChange = EditFindNameChange
  end
  object EditFindAttributs: TEdit
    Left = 502
    Top = 54
    Width = 162
    Height = 21
    TabOrder = 1
    OnChange = EditFindNameChange
  end
end
