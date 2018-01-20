
  ColaBBS 01040X BETA 5

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請將 bin 目錄下所有的檔案複製到 BBS 的 bin 目錄中.
    請將 etc 目錄下所有的檔案複製到 BBS 的 etc 目錄中.
      更動檔案為 etc\help\MenuUserList.help
    
    Messages.INI 更動了第 71 行, 請與舊版的相互比較.
    MENU.INI 此行更動: E
      BoardExpire = "X)BoardExpire 相關設定" "!BoardExpire" "EditINI"
      換成 XBoardExpire = "X)BoardExpire 相關設定" "!BoardExpire" "EditINI"
    ChatRoom.msg 增加最後三行, 請與舊版的相互比較.

  三、ColaSMTPd_MBOX_BOARD
    各討論區需要額外設定才能使用這個功能, 請於 ColaSMTPd_MBOX_BOARD 所使用之設定檔, 
    如 board.ini 中增加一行設定
    MBOX_BOARD_Enabled = 討論區名稱 討論區名稱 討論區名稱 ......
    
                                                                    WilliamWey 2001/05/27
                                                                  is85012@cis.nctu.edu.tw
