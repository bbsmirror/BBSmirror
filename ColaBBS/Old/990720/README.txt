
  ColaBBS 990720

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的 .exe 及 .class 檔複製到 bin 目錄中.
    
    Messages.INI 新增一行, 請補足.
    
    然後在 ActivePlasmid.INI 中加入下面這行
    ListAllUsers
    
    然後在 MENU.INI 中的適當地方加入下面這行
	UListAllUsers = "U)列出全部使用者"   "@RunPlasmid@ListAllUsers"    "Page"
    
                                                          WilliamWey 1999/07/20
                                                        is85012@cis.nctu.edu.tw
                                                        

