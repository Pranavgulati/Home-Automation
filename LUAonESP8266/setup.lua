function savesettings(ssid,pwd)
file.remove("config")
if file.open("config","w+") then
file.write("SSID="..ssid.."/")
file.write("PWD="..pwd.."/")
file.close()
end
end
----------
function sckrecv(sck,recv)
print(recv)
   local method, path, vars = string.match(recv, "([A-Z]+) (.+)?(.+) HTTP")
if vars~=nil then
ssid,pwd=string.match(vars,"s=(.+)&p=(.+)")
print(ssid)
print(pwd)
wifi.setmode(wifi.STATIONAP)
wifi.sta.config(ssid,pwd)
wifi.sta.connect()
savesettings(ssid,pwd)
sck:send("trying to connect")
sck:close()
else
sck:close()
end
end--done f1
function client(sck)
 sck:on("receive",sckrecv)
a="<html><head></head><body><form method=\"get\">SSID:<input name=\"s\"><br>Password:<input name=\"p\"><br><button type=\"submit\">Submit</button></form></body></html>"
sck:send(a)
 end--done f2
--------------------------------------------
function server()
local apip,_,_=wifi.ap.getip()
local staip,_,_=wifi.sta.getip()
--print(wifi.sta.getip())
if staip~=nil then  
wifi.setmode(wifi.STATION)
sv:close()
tmr.stop(1)
sv=nil
collectgarbage()
end
if apip~=nil and staip==nil then 
sv:listen(80,apip,client)
collectgarbage()
end
if node.heap()<=7000 then
node.restart();dofile("init.lua")
end
end
----------------main code here-----------------------
 tmr.alarm(1,2000,1,server)
 sv=net.createServer(net.TCP,30)
 

