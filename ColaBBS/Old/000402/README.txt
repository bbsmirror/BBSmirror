
  ColaBBS 000402

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 ActivePlasmid.INI 新增兩行:
    Games.WinLinez.WinLinez
    BoardManager.BoardManager
    BoardManager.NewBoard
    BoardManager.EditBoard
    BoardManager.DelBoard
    
    在 MENU.INI 中適當位置加入:
    Games = "G)線上遊樂場" "!Games" "Page"

    [Games]
    Attrib = "線上遊樂場" "32" "13" "2"
    WinLinez = "1)排球球" "@RunPlasmid@Games.WinLinez.WinLinez" "Page"
    Exit =     "E)回上一層選單"     "!.."       "Basic"
    
    請修改 MENU.INI 中的 BoardAdmin 區段:
    [BoardAdmin]
    Attrib = "版務管理功\能表" "20" "12" "-1"
    NewBoard = "M)討論區管理員" "@RunPlasmid@BoardManager.BoardManager" "OBoards"
    NewBoard = "N)開啟新討論區" "@RunPlasmid@BoardManager.NewBoard" "OBoards"
    ChangeBoard = "C)修改討論區設定" "@RunPlasmid@BoardManager.EditBoard" "OBoards"
    BoardDelete = "B)刪除討論區" "@RunPlasmid@BoardManager.DelBoard" "OBoards"
    Exit = "E)回主選單" "!.." "OBoards"
    
  三、BoardManager
    管理討論區的工具, 其中提供的 NewBoard, EditBoard, DelBoard,
    只為了提供跟之前提供的功能相同的使用方法,
    如果不需要使用, 可以不加到 ActivePlasmid.INI 中,
    就不會吃掉額外的記憶體了!
  
  四、哈哈
    已經被我荼毒了一年了..
    
                                                             WilliamWey 2000/04/02
                                                           is85012@cis.nctu.edu.tw
