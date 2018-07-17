taskkill -im JS_DBAgentd.exe -f
taskkill -im JS_LoginServerd.exe -f
taskkill -im JS_ContentServerd.exe -f

cd D:\Projects\Bin\DBAgent
start JS_DBAgentd.exe

cd D:\Projects\Bin\LoginServer
start JS_LoginServerd.exe

cd D:\Projects\Bin\ContentServer
start JS_ContentServerd.exe

