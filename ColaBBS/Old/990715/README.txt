
  ColaBBS 990715

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的 .exe 及 .class 檔複製到 bin 目錄中.
    然後在 ActivePlasmid.INI 中加入下面兩行
    LockScreen
    UserTeaTime
    
    然後在 MENU.INI 中的適當地方加入下面兩行
	ATeaTime = "A)休息一下" "@RunPlasmid@UserTeaTime"    "Page"    
	OLockScreen = "O)鎖定畫面" "@RunPlasmid@LockScreen"    "Page"
    
  三、ACBoardManager
    安裝後請重新進行設定, 這個版本可以從多個討論區及目錄中載入活動看板.
    設定取消選擇哪種形式, 當在輸入版名時, 直接用空白隔開版名
    例如要載入 ACBoard_SYS, ACBoard 兩個版, 輸入
    ACBoard_SYS ACBoard

                                                          WilliamWey 1999/07/15
                                                        is85012@cis.nctu.edu.tw
                                                        

