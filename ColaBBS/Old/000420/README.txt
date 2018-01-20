
  ColaBBS 000420

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 ActivePlasmid.INI 增加下列四行:
    LoginExecTools.MenuLoginExecManager
	LoginExecTools.MenuLoginExecUserDefine
	ShowLoginFailed
	ShowNotePad
    
    在 MENU.INI 中的適當位置增加:
    LoginExecDefine	= "L)設定個人登入畫面" "@RunPlasmid@LoginExecTools.MenuLoginExecUserDefine" "Post"
    LoginExecManager = "L)登入畫面設定" "@RunPlasmid@LoginExecTools.MenuLoginExecManager" "EditINI"
    
  三、ColaBBS.INI
    新增 DefaultExitBBS 設定, 設定離站選單的預設選項, 例如:
    DefaultExitBBS=2
    預設值為 4.
  
  四、LoginExec
    原來的 LoginView.INI 已經被新的 LoginExec 取代, 所以請將原來的 LoginView.INI 設定到 LoginExec 中.
    在 "登入執行管理員" 中, 按 a 可以新增一項設定, 設定選單各項的意思如下:
    
    代號:              設定的名稱. 例如 "錯誤登入列表".
    啟動狀態:          是否啟動這項設定.
    命令:              執行的命令, 目前只有 ViewFile 以及 RunPlasmid 兩種.
    參數:              給命令的參數, 如果是 ViewFile, 放的是要顯示的檔案. 如果是 RunPlasmid, 則是 ActivePlasmid 的名字.
    權限模式:          使用者的權限符合規定的權限模式及權限才會執行. 模式是代表使用者權限和規定權限的關係.
    權限設定:          
    簡介:              使用者設定選單時列出來的名稱.
    說明:              使用者設定選單時下方列出的說明部分, 可以有三行.
    使用者關閉:        設定使用者是否可以關閉.
    儲存               設定完成後請按此項才會有效.
    
    在做完設定後, 回設定列表選單時, 請按 "寫入[w]" 才會將設定存會檔案中.
    
    如果希望讓某一選項只能讓未註冊的使用者看到, 但又不希望讓 guest 看到,
    可以先將 guest 的 "I.帳號永久保留" 權限打開, 再將權限模式設定為 "4 全部皆無則啟動", 
    並選擇 "E.使用者資料正確", "I.帳號永久保留", 就可以了.
    
																									WilliamWey 2000/04/20
																								  is85012@cis.nctu.edu.tw
