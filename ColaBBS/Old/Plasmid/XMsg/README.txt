
  Plasmid: XMsg
  Classname: XMsg
  File: XMsg.java, XMsg.class, XMsg.INI
  Document: README.txt
  Compatible: ColaBBS 990321 ->
  Announce: WilliamWey.bbs@cisnt.cis.nctu.edu.tw
  Date: 1999/03/21
  
  XMsg 讀取 XMsg.INI 的內容, 替換掉原來從 Messages.INI 中讀取的訊息.
  這樣如果你懶得每次去補足 Messages.INI 的行數, 你就可以只編寫 XMsg.INI,
  然後每次有新的 Messages.INI 出來時, 直接蓋掉舊的就行了.

  安裝時把 XMsg.class 以及 XMsg.INI 放置在 bin 目錄下面, 並且在 Plasmid.INI 中,
  新增一行
  XMsg
  然後再編寫 XMsg.INI 這樣就可以了.
  
  XMsg.INI 的結構:
  xxxx yyyyyyyyyyyyy

  xxxx 是在 Messages.INI 中的行數
  yyyyyyyyyyyyy 是要設定的訊息.
