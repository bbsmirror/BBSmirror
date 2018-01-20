
  ColaBBS 990819

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
	
	此外請注意 ChatRoom.txt (設定動作畫面) 還有 ChatRoom.msg (所有的顯示訊息)
	都必須要放在 bin 目錄下面.
	
	這版的外掛 ChatRoom 只能用在 990819 以後的 ColaBBS.
	
                                                          WilliamWey 1999/08/19
                                                        is85012@cis.nctu.edu.tw
