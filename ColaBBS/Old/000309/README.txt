
  ColaBBS 000309

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 MENU.INI 中適當位置加一個區塊:
    
    [UserReg]
    Attrib = "註冊升級看這邊" "32" "13" "2"
    FillForm = "F)註冊個人詳細資料" "@FillForm" "Basic"
    MRegMail = "M)寄出身分確認信件" "@RunPlasmid@UserReg.SendRegMail" "Basic"
    NRegNumberMail = "N)寄出身分確認號碼" "@RunPlasmid@UserReg.SendRegNumberMail" "Basic"
    IInputRegNumber = "I)輸入身分確認號碼" "@RunPlasmid@UserReg.InputRegNumber" "Basic"
    Exit =     "E)回上一層選單"     "!.."       "Basic"
    
    然後把原來在 [Info] 中的
    FillForm =   "F)註冊個人詳細資料"   "@FillForm"   "Basic"
    改成
    RUserReg = "R)註冊升級看這邊" "!UserReg" "Basic"
      
    在 Plasmid.INI 新增一行:
    UserReg.UserReg
    
    在 ActivePlasmid.INI 新增三行:
    UserReg.SendRegMail
    UserReg.SendRegNumberMail
    UserReg.InputRegNumber
    
  三、ColaSMTPd, ColaSMTPd_MBOX_REGMAIL
    配合收身分確認信時使用, 必須要新增類似 SYSOP.reg@cisnt.cis.nctu.edu.tw 這種的信件,
    請在 SMTP_VirtualHost.INI 增加一行 reg@cisnt.cis.nctu.edu.tw = SMTP_INI\bbsreg.ini
    然後在 SMTP_INI 目錄中新增一個檔案 bbsreg.ini
    內容為:
    MBOX = ColaSMTPd_MBOX_REGMAIL
    
                                                               WilliamWey 2000/03/09
                                                             is85012@cis.nctu.edu.tw
