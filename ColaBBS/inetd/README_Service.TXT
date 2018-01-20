
  以下為這幾個 Service 的說明:

  1. ECHO	RFC 862		Port 7
     對方傳過來什麼, 就傳一樣的回去.

  2. DISCARD	RFC 863		Port 9
     對方傳過來什麼都不做動作.

  3. DAYTIME	RFC 867		Port 13
     將目前的時間傳回去.

  4. QUOTE	RFC 865		Port 17
     傳回一段小俗諺或格言.

     這個會去尋找目前目錄下面的 QUOTES 下面的所有 .TXT 檔案,
     以亂數決定要秀出哪一個檔案.

  5. CHARGEN	RFC 864		Port 19
     依序努力傳會文字. 可用於偵錯以及測網路速度.

  這些服務皆有附執行檔(.class)及原始檔(.java)

                                       WilliamWey 1999/05/30
                                     is85012@cis.nctu.edu.tw