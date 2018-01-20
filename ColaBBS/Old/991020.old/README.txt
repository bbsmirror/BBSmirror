
  ColaBBS 991020

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    然後在 Plasmid.INI 中加入兩行:
    LoginCounterBar
    ExpireAccount
    在 MENU.INI 中適當位置加一行
    ALoginCounterBar = "A)今日上站人次" "@ViewFile@etc\\LoginCounterBar.txt" "Basic"
  
    在 LoginView.INI 中加入一行:
    etc\LoginCounterBar.txt
 
                                                               WilliamWey 1999/10/20
                                                             is85012@cis.nctu.edu.tw
