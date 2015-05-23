file.open("config","r+")
local ssid=string.match(file.read("/"),"SSID=(.+)/")
local pwd=string.match(file.read("/"),"PWD=(.+)/")
wifi.setmode(wifi.STATIONAP)
wifi.sta.config(ssid,pwd)
wifi.sta.connect()
file.close()
collectgarbage()
if wifi.sta.getip()==nil then 
dofile("setup.lua")
end
dofile("run.lua")
