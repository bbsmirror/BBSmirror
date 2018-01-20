
  ColaBBS 991110

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    然後在 Plasmid.INI 中加入兩行:
    LoginCounterBar
    ExpireAccount
    
    請在 ActivePlasmid.INI 中加入四行:
	ReloadINIIPAccess
	ReloadINILoginCounterBar
	LoginCounterBar
	SendInternetMail
	
    在 MENU.INI 中適當位置加一行
    ISendInternetMail = "I)寄 Internet 信件" "@RunPlasmid@SendInternetMail"    "Post"
  
    還有
	ReloadINILoginCounterBar = "R)重新載入 LoginCounterBar 設定"	"@RunPlasmid@ReloadINILoginCounterBar"	"EditINI"
	LoginCounterBarToFile = "L)製作某天 LoginCounterBar 檔案" "@RunPlasmid@LoginCounterBar"	"EditINI"
    
	開個新討論區, 取名為 BBSRecord
      21◇BBSRecord          [系統]     CISNT BBS 的昨日與今天     SYSOP	

    設定 LoginCounterBar.INI
	Enabled=1					是否啟動統計人次功能
	Block=5						統計人次每格區塊代表單位
	FileEnabled=1				是否啟動將人次記載到討論區的功能
	FileBlock=5					寫到討論區時每格區塊代表單位
	FileBoard=BBSRecord			寫到哪個討論區
	FileAuthor=SYSOP			用哪個帳號發表
	FileTitle=每日上站人次統計	標題為?
 
  三、ColaSMTPd 的 ColaSMTPd_MBOX_BOARD
    請參考 SMTP_INI 中的 board.ini 作設定
    在 SMTP_VirtualHost.INI 中加入下列設定
    board@cisnt.cis.nctu.edu.tw = SMTP_INI\board.ini
    然後設定完 board.ini 後,
    寄給 SYSOP.board@cisnt.cis.nctu.edu.tw 的信件就會直接 post 到討論區內.
    可以配合訂閱 maillist 使用.
  
 
                                                               WilliamWey 1999/11/10
                                                             is85012@cis.nctu.edu.tw
