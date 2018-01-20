
  ColaBBS 000525

  一、新增與修正功能:
    請參考 Version.txt

  二、安裝:
    請複製所有的檔案複製到 bin 目錄中.
    
    在 ActivePlasmid.INI 增加下列五行:
    UserManager.UserManager
    UserManager.ChangeUserPassword
    UserManager.ChangeUserPerm
    UserManager.DelUser
    UserManager.ModifyUser
 
    在 MENU.INI 中的 [UserAdmin] 修改:
    UserManager = "U)使用者管理員" "@RunPlasmid@UserManager.UserManager" "Account"
    Info = "I)修改使用者資料" "@RunPlasmid@UserManager.ModifyUser" "Account"
    ModifyLevel = "M)更改使用者的權限" "@RunPlasmid@UserManager.ChangeUserPerm" "Account"
    DelUser = "D)砍掉使用者帳號" "@RunPlasmid@UserManager.DelUser" "Account"
    Password = "P)更改使用者密碼" "@RunPlasmid@UserManager.ChangeUserPassword" "Account"
        
                                                                     WilliamWey 2000/05/25
                                                                   is85012@cis.nctu.edu.tw
