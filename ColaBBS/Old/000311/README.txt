
  ColaBBS 000311

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 ActivePlasmid.INI 新增三行:
    FileExplorer.FileExplorer
    
    在 MENU.INI 中適當位置加入:
    FileExplorer = "X)檔案總管" "@RunPlasmid@FileExplorer.FileExplorer" "EditINI"
    
  三、FileExplorer
    除了畫面中出現的功能鍵之外, 還有以下功能鍵:
    i: 取得檔案或是目錄的資訊.
    !: 取得 FileExplorer 版本訊息.
    CTRL + c: 剪貼檔案, 複製.
    CTRL + u: 剪貼檔案, 剪下.
    CTRL + p: 剪貼檔案, 貼上.
    CTRL + l: 重新整理列表.
    
                                                             WilliamWey 2000/03/11
                                                           is85012@cis.nctu.edu.tw
