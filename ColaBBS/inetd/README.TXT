
  inetd 使用說明
  
  1. 安裝方法(獨立使用):
     建立一個目錄, 將壓縮檔案中的各檔案放置在該目錄裡面.

  2. 安裝方法(配合 ColaBBS ):
     將壓縮檔案中的檔案放置到 BBS 的 bin 目錄中, 並且在 Plasmid.INI 中加入一行

     inetd

  3. 使用方法:
     如果是獨立使用, 請直接執行 inetd.exe 或是 inetd.class
     如果配合 ColaBBS 使用, 設定好後, 當 BBS 啟動時就會啟動 inetd

  4. 設定方法: 
     在同目錄中建立一個 inetd.INI 檔案, 裡面的格式為:
    
     port class

     port 是指該服務要 listen 的 TCP port 號碼, class 則是負責的 class

     例如 2007 ECHOd 就是說, 當有程式連進來 2007 這個 port, 會呼叫 ECHOd 這個 class

     至於 ECHOd.class 要放在系統的 classpath 下, 例如與 inetd.class 或 inetd.exe 同目錄即可.

  5. 服務 class 寫法:
     參考 Service.zip 中的原始碼檔案.

 
                                                                      WilliamWey 1999/05/30
                                                                    is85012@cis.nctu.edu.tw