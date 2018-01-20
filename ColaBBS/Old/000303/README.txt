
  ColaBBS 000303

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 MENU.INI 中適當位置加一個區塊:
    
    [BoardExpire]
    Attrib = "BoardExpire 相關設定" "20" "12" "-1"
    NBoardExpireNow = "N)啟動 Expire" "@RunPlasmid@BoardExpire.BoardExpireNow" "EditINI"
    CBoardExpireControlPanel = "P)BoardExpire 管理員" "@RunPlasmid@BoardExpire.BoardExpireControlPanel" "EditINI"
    Exit = "E)回系統設定功\能表" "!SetupAdmin" "EditINI"
    
    然後把原來在 [SetupAdmin] 中的
    BoardExpireNow = "N)啟動 Expire" "@RunPlasmid@BoardExpire.BoardExpireNow" "EditINI"
    改成
    BoardExpire = "B)BoardExpire 相關設定" "!BoardExpire" "EditINI"
  
    然後在 [SetupAdmin] 中新增一段:
    NReloadNLANTable = "N)重新載入 NLAN 設定" "@RunPlasmid@ReloadNLANTable" "EditINI"
    TEditNLANTable = "T)編輯 NLAN 設定" "@EditFile@bin\\NLAN.INI" "EditINI"
    
    在 [UserAdmin] 中新增一行:
    EMailToAllUsers = "E)寄信給所有的使用者" "@RunPlasmid@MailToAllUsers" "Account"
    
    在 Plasmid.INI 新增一行:
    LoadNLANTable
    
    在 ActivePlasmid.INI 新增三行:
    MailToAllUsers
    ReloadNLANTable
    BoardExpire.BoardExpireControlPanel
     
                                                               WilliamWey 2000/03/03
                                                             is85012@cis.nctu.edu.tw
