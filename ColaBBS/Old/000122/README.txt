
  ColaBBS 000122

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    請在 ActivePlasmid.INI 中加入三行:
    ReloadINISMTPAccess
	ReloadINISMTPRelay
	ReloadINISMTPVirtualHost
	並且把 SysInfo
	改成 SysInfo.SysInfo
	
    在 MENU.INI 中適當位置加一個區塊:
	
	[ColaSMTPdAdmin]
	Attrib = "使用者管理功\能表" "20" "12" "-1"
	"1EditAccess" = "1)編輯 Access.INI 檔案"     "@EditFile@bin\\SMTP_Access.INI"    "EditINI"
	"2EditRelay" = "2)編輯 Relay.INI 檔案"     "@EditFile@bin\\SMTP_Relay.INI"    "EditINI"
	"3EditVirtualHost" = "3)編輯 VirtualHost.INI 檔案"     "@EditFile@bin\\SMTP_VirtualHost.INI"    "EditINI"
	"1LoadAccess" = "1)重新載入 Access.INI 檔案"     "@RunPlasmid@ReloadINISMTPAccess"    "EditINI"
	"2LoadRelay" = "2)重新載入 Relay.INI 檔案"     "@RunPlasmid@ReloadINISMTPRelay"    "EditINI"
	"3LoadVirtualHost" = "3)重新載入 VirtualHost.INI 檔案"     "@RunPlasmid@ReloadINISMTPVirtualHost"    "EditINI"
	Exit =        "E)回主選單"           "!.."          "SYSOP"
	
	並且在適當的位置加上一行, 例如在 [Admin] 區塊中:
	MColaSMTPdAdmin = "M)ColaSMTPd 設定功\能表"    "!ColaSMTPdAdmin"  "EditINI"
	
	此外, 還需要更動一個位置:
	ISysInfo = "I)系統資訊"   "@RunPlasmid@SysInfo"    "Basic"
	請改成
	ISysInfo = "I)系統資訊"   "@RunPlasmid@SysInfo.SysInfo"    "Basic"
	
  三、SysInfo
    安裝時請注意要將 PDH.dll 複製到與 ColaBBS.EXE 同目錄下.
    有部分的資訊只在 Windows NT 下面有作用, 例如系統負荷度.
    此外, 在 Windows 9x 下, 因為系統限制, 所以最常開機時間為 49 天多一點.
 
                                                               WilliamWey 2000/01/22
                                                             is85012@cis.nctu.edu.tw
