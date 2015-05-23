function change(socket,data)
 local state = string.match(data, "<(.+)>")
if state~=nil then
print(state)
gpio.mode(3,gpio.OUTPUT)
gpio.mode(4,gpio.OUTPUT)
if state%2==1 then
    gpio.write((state%2)+(state/2)+2,gpio.HIGH)
else
    gpio.write((state%2)+(state/2)+2,gpio.LOW)
end
end
end
function Checkserver()
if wifi.sta.getip()~=nil then
socket = net.createConnection(net.TCP,0)
socket:on("receive",change)
socket:on("connection",function(sck) 
    sck:send("GET /f/6vnzp4xc7jt58ai.txt HTTP/1.1\r\nHost: www.homeautomationserver.com\r\nConnection: close\r\n\r\n")
     end)
socket:connect(80,"www.homeautomationserver.com") 
end
end
tmr.alarm(0,2000,1,Checkserver)
