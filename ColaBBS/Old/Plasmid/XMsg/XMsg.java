
import java.io.*;

import colabbs.*;
	
public class XMsg
{
  public static void startup() throws IOException
  {
    String tmp;
	RandomAccessFile XMsgFile=null;
	Long iMsg = new Long(0);
	String sMsg;
	int seeks, index = -2;

    XMsgFile = new RandomAccessFile("XMsg.INI","r");
	while((tmp = XMsgFile.readLine()) != null)
	{
	  if (tmp.charAt(tmp.length()-1) == 13)
		tmp = tmp.substring(0, tmp.length() - 1);
	  while((index = tmp.indexOf("\\n", index + 2)) != -1)
		tmp = tmp.substring(0, index) + (char)13 + (char)10 + tmp.substring(index + 2);
	  tmp.trim();
	  if (tmp.substring(0, 0) == "#")
	    continue;
	  seeks = tmp.indexOf(" ");
	  if (seeks == -1) 
	    continue;
	  iMsg = iMsg.valueOf(tmp.substring(0, seeks), 10);
	  sMsg = new String(tmp.substring(seeks + 1));
	  sMsg.trim();
	  Prompt.Msgs[iMsg.intValue()] = sMsg;
	}
	XMsgFile.close();		
  }
}
