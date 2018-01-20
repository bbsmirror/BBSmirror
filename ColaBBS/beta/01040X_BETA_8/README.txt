
  ColaBBS 01040X BETA 8

  一、新增與修正功能:
    請參考 Version.txt

  二、升級:
    請將 bin 目錄下所有的檔案複製到 BBS 的 bin 目錄中.
    請將 etc 目錄下所有的檔案複製到 BBS 的 etc 目錄中.

    在 ActivePlasmid.INI 中新增兩行:
    FromHostChecker
    SendMailToSYSOPs
    
    在 MENU.INI 中新增:
    在 [Mail] 下新增:
    OMailToSYSOPs = "O)寄信給站長們" "@RunPlasmid@SendMailToSYSOPs" "Basic"
    
    在 [Info] 下新增:
    HostChecker = "H)設定來源限制" "@RunPlasmid@FromHostChecker@Setup" "EditINI"
    FLoginFailed = "F)顯示登入錯誤紀錄" "@RunPlasmid@ShowLoginFailed" "Basic"
    
    在 [Admin] 下新增:
    PLoginFailed = "P)顯示 SYSOP 登入錯誤紀錄" "@RunPlasmid@ShowLoginFailed@VIEW@SYSOP" "EditINI"
    
    在 [UserAdmin] 下新增:
    FLoginFailed = "F)顯示使用者登入錯誤紀錄" "@RunPlasmid@ShowLoginFailed@VIEW" "Account"
    
    在 [EditINI] 下新增:
    BadIDList = "B)編輯 BadIDList.INI 檔案" "@EditFile@bin\\BadIDList.INI" "EditINI"
    "4LoadBadIDList" = "4)重新載入 BadIDList.INI 檔案" "@RunPlasmid@BBSTools@ReloadBadIDList" "EditINI"
    
    開啟 [登入執行管理員] 新增一個項目:
    代號:              登入來源檢查
    啟動狀態:          開啟
    命令:              RunPlasmid
    參數:              FromHostChecker
    權限模式:          1 有其中之一則啟動
    權限設定:          ..............O.................
    簡介:              限制自己帳號的連線來源
    說明:              可以設定自己的帳號只能從哪些地方連線
    使用者關閉:        0 可以關閉
    然後將他搬移到最優先啟動.
    
  三、其他
    ColaBBS.INI 中新增下列設定:
    disableSYSOP = true/false        是否關閉 SYSOP 帳號, 預設為 false
    BMTools.defTitleBegin = number   中文版名在該欄位的的起始位置, 請扣除掉最前面的 group 分類字元
                  例如: "0[站內]     活動看板廣告區", "活" 這個字扣除掉 "0" 以後是在第 12 個位置上.
                  預設為 12
    
                                                                                  WilliamWey 2001/08/28
                                                                                is85012@cis.nctu.edu.tw
