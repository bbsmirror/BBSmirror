
  ColaBBS 990705

  一、新增與修正功能:
    請參考 Version.txt
    請注意本版除了活動看板外, 並沒有加入或是修改任何功能.

  二、安裝:
    把 ColaBBS.exe 複製到 bin 目錄中. 重新啟動 ColaBBS.

  三、動態看板外掛設定程式
    把 ACBoardManager 目錄複製到 bin 目錄下面.

    在 Plasmid.INI 中加入
    ACBoardManager.Load

    在 ActivePlasmid.INI 中加入兩行
    ACBoardManager.Reload
    ACBoardManager.Setup

    在 MENU.INI 加入下面這些設定, 第一行可以加在 [SetupAdmin] 裡面, 
    後面的幾行則直接放到 MENU.INI 後面就可以了.

ACBoard ="A)活動看板管理員相關設定"     "!ACBoard"    "EditINI"

[ACBoard]
Attrib = "活動看板管理員相關設定" "20" "12" "-1"
RACBM = "R)重新載入活動看板"	"@RunPlasmid@ACBoardManager.Reload"	"EditINI"
SACBM = "S)設定活動看板管理員"	"@RunPlasmid@ACBoardManager.Setup"	"EditINI"
Exit =        "E)回系統設定功\能表"           "!SetupAdmin"          "EditINI"

    然後使用系統管理員權限的 ID 登入,
    執行 S)設定活動看板管理員 的功能, 
    其中 Enabled 代表要不要打開, 要的話輸入 1
    Style 如果是 FromBoard 則是從站上某個版面引入活動看板
          而 BoardName 則是該版面的名稱
    Style 如果是 FromDirectory 則是從某個目錄下面引入活動看板
          而 DirectoryPath 則是該目錄的名稱
          (這個目錄是相對於 BBSHOME 的)

    上面這段看不太懂嗎? (嗚, 實在寫得很爛..)
    嗯, 懶惰的話, 第一次設定的時候 Enabled 選 1, 其他都用預設值就好了.
    (然後去開一個叫做 ACBoard 的討論區, 在裡面貼文章就會被引入活動看板)
    (要注意的是, 只有被 m 起來的文章才會被弄到活動看板中喔..)
    (可以到 CISNT 的 ACBoard 來看看..)	

    此外, 每次開站時候會自動將活動看板引入,
    如果新加了活動看板, 可以用 R)重新載入活動看板 來重新載入.

                                                          WilliamWey 1999/07/05
                                                        is85012@cis.nctu.edu.tw
                                                        

