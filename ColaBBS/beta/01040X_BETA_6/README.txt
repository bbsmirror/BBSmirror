
  ColaBBS 01040X BETA 6

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請將 bin 目錄下所有的檔案複製到 BBS 的 bin 目錄中.
    請將 etc 目錄下所有的檔案複製到 BBS 的 etc 目錄中.
    
    Messages.INI 更動了第 84 行, 請與舊版的相互比較.
  
  三、設定:
    ColaBBS.INI 中新增下面兩個設定:
    
    留言版自訂更新時間: 設定留言版於幾點時啟動. (預設為半夜十二點)
    NoteRefresher.runHour=2
    
    離站顯示訊息自訂預設選項: (預設為 R, 保留訊息)
    ExitBBSShowMsgs.default=M
    
    支援 listen 多個 port,
    直接在 TelnetPort 設定後面以空白隔開即可.
    如 TelnetPort = 23 9000
    這樣使用者就可以從 port 23, 或是 port 9000 連上 BBS.
    
    
                                                WilliamWey 2001/06/18
                                              is85012@cis.nctu.edu.tw
