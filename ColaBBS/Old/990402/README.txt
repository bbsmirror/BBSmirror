
  ColaBBS 990402

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請將 CharsetMap.INI 複製到 bin 目錄.
    補足 Messages.INI 的行數, 這次新增 10 行.
    最後把 ColaBBS.exe 複製到 bin 目錄中. 重新啟動 ColaBBS.

  三、Charset Table
    CharsetMap.INI 格式為:
    字元集名稱 字元集公定名稱
    例如 Big5 這個字元集, 在網路上傳遞可能為 big5, 所以我們要設定 big5 Big5,
    這樣系統才知道要使用相對應的解碼函式.

  四、NewsFilter
    MailHeader:
    安裝: 安裝前請注意是否有做完 CharsetTab 的設定工作.
          然後將 MailHeader.class 複製到 bin 目錄中, 並且把 MailHeader 加到 NewsFilter.INI 中.
    使用: 當信轉進來時, 會自動使用 MailHeader 這個 Filter 將被編過碼的文章標題或是發文者名稱解回來.
    注意: 使用 NewsFilter 將會增加系統在轉信時候的負擔, 如果覺得不適合, 不使用並不會影響系統運作.

  五、MENU.INI 新增功能
    @SendMsgToAll       送訊息給全部使用者
    @SendMsgToFriends   送訊息給好友

  六、ActivePlasmid
    什麼是 ActivePlasmid : ActivePlasmid 就是可以從 Menu 上啟動的外掛程式.
    安裝: 請將 ActivePladmid 複製到 bin 目錄中, 並且把他的名字新增到 ActivePlasmid.INI 中.
    使用 ActivePlasmid 的方法:
          在 MENU.INI 中, 原來指令那一欄, 現在多了新的指令: RunPlasmid
          所以要從 MENU.INI 啟動 ActivePlasmid 請使用 @RunPlasmid@plasmid_name
          例如要啟動 Othello 這個 ActivePlasmid, 指令的欄位應該是 @RunPlasmid@Othello
    目前還沒有完成的 ActivePlasmid, 請等待之後的消息.
    
                                                                        WilliamWey 1999/04/02 in NCTU