#define ONTIME 20000
#define INTERVAL1 5000
#define RELAYNO 2
#define SENSNO 2
#define INSTART 14
#define RELAYSTART 8
#include "EEPROM.h"
#define LIGHT 0
#define FAN 1
#define DEBUG 0
byte changestatus=0;
byte wifihist[RELAYNO]={};
byte status[RELAYNO]={};
int sensor[SENSNO]={};
unsigned long int time=millis();

void setup(){
  for(byte i=0;i<RELAYNO+SENSNO;i++){
  pinMode(RELAYSTART+i,OUTPUT);
  status[i]=readstatus(i);
}
for(byte i=0;i<RELAYNO+SENSNO;i++){
  pinMode(INSTART+i,INPUT);
}
if(DEBUG){  Serial.begin(9600);}
}

byte getwifi(){
byte wifirecvd=0;
for(byte i=0;i<RELAYNO;i++){
     if(wifihist[i]!=digitalRead(INSTART+i)){
     wifihist[i]=digitalRead(INSTART+i);
     wifirecvd=1;
   }
}

return wifirecvd;
}
void getsens(){
for(byte i=0;i<SENSNO;i++){
  sensor[i]=analogRead(INSTART+RELAYNO+i);
  }
}
byte readstatus(byte i){
return EEPROM.read(i);
}
void writestatus(){
if(DEBUG){  Serial.println("  writing to EEPROM ");}
  for(byte i=0;i<RELAYNO;i++){
EEPROM.write(i,status[i]);// disabled to prevent eeprom degradation
digitalWrite(i+RELAYSTART,status[i]);
  }
  time=millis();
}
void wifiact(byte wifirecvd){
if(wifirecvd==1){
  for(byte i=0;i<RELAYNO;i++){
        status[i]=wifihist[i];
        changestatus=1;
  }
}
}

void sensact(){
  for(byte i=0;i<SENSNO;i++){
      if(sensor[i]>500){
          //still present turn on lights and fans
            if(status[LIGHT]==1&&millis()>=time+INTERVAL1&&status[FAN]==0){status[FAN]=1;changestatus=1;time=millis();}  
            if(status[LIGHT]==0){status[LIGHT]=1;changestatus=1;time=millis();}
            if(status[FAN]==1&&status[LIGHT]==1){time=millis();}  
    }
    else{
    //no one present simply wait for ONTIME and then turn OFF everything
      if(millis()>=time+ONTIME&&(status[LIGHT]!=0||status[LIGHT]!=0)){status[LIGHT]=0;status[FAN]=0;changestatus=1;       time=millis();}   
 }  
    }
}




void loop(){
getsens();sensact();
  byte getwi=getwifi();
wifiact(getwi);
  if(getwi==1){
 if(DEBUG){ Serial.print(" recvd stat ");
  Serial.print(getwi);
  Serial.print("  ");
 }
  }
  
if(changestatus==1){writestatus();changestatus=0;}
  if(DEBUG){  Serial.print(status[0]);
  Serial.print(" , ");
  Serial.print(status[1]);
/*  Serial.print("  wifi ");  Serial.print(wifi);
  Serial.print("  sens ");  Serial.print(sens);*/
  Serial.print("    ");
  Serial.print(wifihist[0]);
  Serial.print(" , ");
  Serial.println(wifihist[1]);
  }
delay(1000);//friendly delay to prevent frequent changes
}
