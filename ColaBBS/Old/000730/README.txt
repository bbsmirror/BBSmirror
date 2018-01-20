
  ColaBBS 000730

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請將 bin 目錄下所有的檔案複製到 BBS 的 bin 目錄中.
    請將 etc 目錄下所有的檔案複製到 BBS 的 etc 目錄中.
    請注意新的討論區分組方式, 如果沒有作更改, 分類討論區將會不正常.
    
  三、新的討論區分群組方式
    請注意新的討論區分組方式, 如果沒有作更改, 分類討論區將會不正常.
    原來在 ColaBBS.INI 中的 BoardGroup, Group? 的設定都取消了.
    現在改為在 @EGroups 指令之後加上 @ 參數, 參數代表要顯示的分類.
    (分類依然為中文版名的第一個字)
    例如有個選項想要將分類 123 都列在裡面, 就設定 @EGroups@123,
    而分類選項也不限制在 0 ~ 9, 可以用 a-z, A-Z 等字元.
    如果希望 EGroup 進入後預設為顯示新文章,
    可以在 ColaBBS.INI 中新增一行 DefaultReadNew = true 設定.

  四、MultiLoginsChecker
    請在 ActivePlasmid 中加入一行:
    MultiLoginsChecker
    
    這個程式會參考到 ColaBBS.INI 中的兩個選項:
    MultiLogins=true        //是否允許多重登入, 預設為 true
    MaxMultiLogins=3        //最多多重登入各數, 預設為 3
    
    然後到 "登入執行管理員" 中新增項目:
  > 代號:              多重登入檢查
    啟動狀態:          開啟
    命令:              RunPlasmid
    參數:              MultiLoginsChecker
    權限模式:          0 永遠啟動
    權限設定:          ................................
    簡介:              檢查使用者多重登入狀況
    說明:              檢查使用者是否多重登入,                       如果有太多連線則要求離開或是切離其它在站上的連線.                       相關的設定在 ColaBBS.INI 中的 MultiLogins 以及 MaxMultiLogins.
    使用者關閉:        1 不能關閉
      
                                                                    WilliamWey 2000/07/30
                                                                  is85012@cis.nctu.edu.tw
