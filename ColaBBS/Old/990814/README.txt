
  ColaBBS 990814

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的 .exe 及 .class 檔複製到 bin 目錄中.
 
  三、ChatRoom
    如果要使用外掛的 ChatRoom, 除了將 ChatRoom 目錄複製到 bin 下外,
    請作下面幾項更動:
    
    MENU.INI:
	EnterChat =   "E)進入聊天室"   "@EnterChat"  "Post"
	換成
	EnterChat =   "E)進入聊天室"   "@RunPlasmid@ChatRoom.CRCT"  "Post"
	
	Plasmid.INI:
	新增一行 ChatRoom.ChatRoom_Server
	
	ActivePlasmid.INI:
	新增一行 ChatRoom.CRCT
	
	這個外掛的 ChatRoom 適用於較舊的 ColaBBS, 不過能多舊我就不清楚了.
	
                                                          WilliamWey 1999/08/14
                                                        is85012@cis.nctu.edu.tw
