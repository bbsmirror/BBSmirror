
  ColaBBS 990914

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    並在 ColaBBS.INI 中新增兩行:
    SMTPAddress=localhost
	SMTPPort=25
 
  三、IssueManager
    Plasmid.INI:
    新增一行
    IssueManager.Load
  
	ActivePlasmid.INI:
	新增兩行
    IssueManager.Reload
    IssueManager.Setup
	
	MENU.INI 新增:
    [SetupAdmin]
    Issue = "I)進站畫面管理員相關設定" "!Issue" "EditINI"
    
    [Issue]
    Attrib = "進站畫面管理員相關設定" "20" "12" "-1"
    RIM = "R)重新載入進站畫面" "@RunPlasmid@IssueManager.Reload" "EditINI"
    SIM = "S)設定進站畫面管理員" "@RunPlasmid@IssueManager.Setup" "EditINI"
    Exit = "E)回系統設定功\能表" "!SetupAdmin" "EditINI"
  
    設定方法請看 cisnt.cis.nctu.edu.tw 的 ColaBBSFAQ 討論區的
    "[疑問] 多重進站畫面要怎麼設定呢?"
  
  四、PackageMail
	ActivePlasmid.INI:
	新增一行
	PackageMail
	
	MENU.INI 新增:
	PackageMail = "P)打包信件" "@RunPlasmid@PackageMail" "Post"
	
  五、ColaSMTPd
    Plasmid.INI:
    新增一行
    ColaSMTPd.ColaSMTPd
    
    並且把 ColaBBS.INI 中的 UserColaMail 設定為 false
	UseColaMail=false
	然後看看 InternetMail 是不是 true
    InternetMail=true
    
    ColaSMTPd 有多個設定檔, 請看該設定檔內的說明.
    ColaSMTPd.INI
    SMTP_Access.INI
    SMTP_Relay.INI
    SMTP_VirtualHost.INI    
    
    對設定有問題, 請到 cisnt.cis.nctu.edu.tw 的 ColaBBS 討論區.
    	
                                                          WilliamWey 1999/09/14
                                                        is85012@cis.nctu.edu.tw
