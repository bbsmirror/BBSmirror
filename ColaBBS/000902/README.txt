
  ColaBBS 000902

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請將 bin 目錄下所有的檔案複製到 BBS 的 bin 目錄中.

  三、MailBoxLimiter
    請在 ActivePlasmid.INI 中加入一行:
    MailBoxLimiter
    在 MENU.INI 中的 [SetupAdmin] 加入一行:
    BMailBoxLimiterManager	= "B)使用者信箱限制設定" "@RunPlasmid@MailBoxLimiter@MANAGER" "EditINI"
    
    這個程式會在第一個使用者登入的時候載入設定,
    如果希望在 BBS 啟動後就載入設定,
    請在 Plasmid.INI 中也加入一行:
    MailBoxLimiter
    
    然後到 "登入執行管理員" 中新增項目:
 > 代號:              使用者信箱限制
   啟動狀態:          開啟
   命令:              RunPlasmid
   參數:              MailBoxLimiter
   權限模式:          4 全部皆無則啟動
   權限設定:          O.......O.......................
   簡介:              檢查使用者的信箱容量並設限
   說明:              在使用者登入的時候, 檢查使用者的信箱容量以及信件數量,
                      如果超過設定的上限時, 會要求使用者將信件刪除到符合限制標準.
   使用者關閉:        2 管理者可關閉

  四、ViewAnnounce
    請在 ActivePlasmid.INI 中加入一行:
    ViewAnnounce
    在 MENU.INI 中的 [SetupAdmin] 加入一行:
    ViewAnnounceManager	= "V)閱\讀公告討論區設定" "@RunPlasmid@ViewAnnounce@MANAGER" "EditINI"
    
    這個程式會在第一個使用者登入的時候載入設定,
    如果希望在 BBS 啟動後就載入設定,
    請在 Plasmid.INI 中也加入一行:
    ViewAnnounce
    
    然後到 "登入執行管理員" 中新增項目:
 > 代號:              閱讀公告討論區
   啟動狀態:          開啟
   命令:              RunPlasmid
   參數:              ViewAnnounce
   權限模式:          4 全部皆無則啟動
   權限設定:          O.......O.......................
   簡介:              強制使用者閱讀某些特定討論區內的新文章
   說明:              在使用者登入的時候, 要求使用者必須看過所設定的幾個討論區的新文章,
                      才能夠進入 BBS 站中.
   使用者關閉:        2 管理者可關閉    

  五、TitleFilter
    請在 NewsFilter.INI 中加入一行:
    TitleFilter
    
    設定檔的名稱為 TitleFilter.INI, 內容格式為:
    #                          表示此行為註解.
    A 大家來賺錢               表示擋掉標題為 "大家來賺錢" 的文章.
    L 大家來                   表示擋掉標題開頭為 "大家來" 的文章.
    R 來賺錢                   表示擋掉標題結尾為 "來賺錢" 的文章.
    M 來賺                     表示擋掉標題中含有 "來賺" 的文章.
    
  六、PosterFilter
    請在 NewsFilter.INI 中加入一行:
    PosterFilter
      
    設定檔的名稱為 PosterFilter.INI, 內容格式為:
    #                                    表示此行為註解.
    A shit.bbs@bbs.cis.nctu.edu.tw       表示擋掉發文者為 "shit.bbs@bbs" 的文章.
    L shit.bbs                           表示擋掉發文者開頭為 "shit.bbs" 的文章.
    R nctu.edu.tw                        表示擋掉發文者結尾為 "nctu.edu.tw" 的文章.
    M bbs@bbs                            表示擋掉發文者中含有 "bbs@bbs" 的文章.
    
                                                                    WilliamWey 2000/09/02
                                                                  is85012@cis.nctu.edu.tw
