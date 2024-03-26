// Change ID value 

#include <SoftwareSerial.h>
#include <Wire.h>



/*
Note: If you forget the present sensor address value, you can check the sensor address by the following 
instruction:
Host sends: FE 03 02 00 00 01 91 BD
If feedback: FE 03 02 00 01 6D 90
It mean the sensor address is 01.
*/

// General command to get the sensor id : 0xFE 0x03 0x02 0x00 0x00 0x01 0x91 0xBD
// change the 5th byte with your new id from "1 -> 255" !! Note "1" is the default value !!
const byte CMD_Change_ID [] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x02, 0xe4, 0x0c};

const byte CMD_Get_ID    [] = {0xFE, 0x03, 0x02, 0x00, 0x00, 0x01, 0x6D, 0x90};


// for NANO
#define RE  8
#define DE  7


// storing reading values 
byte values[13];

// for arduino nano & uno
SoftwareSerial mod(2, 3);

//for arduino mega
// SoftwareSerial mod(10, 11);



// initialize your variables for each reading
uint16_t Value_Response;

void setup() 
{
// initialize serial Comm -> 9600
  Serial.begin(9600);

// initialize mod bus ->9600
  mod.begin(9600);
 
// set pins RE , DE for mod bus as output 
// Define pin modes for RE and DE-
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  delay(500);
}

void loop() {
char i = 0;

if (i==0)
{
  // get the read from the function then display it on the serial monitor 
  Value_Response = HAL_u16Change_ID_sensor(CMD_Change_ID);
  Serial.print("ID change response is : ");
  Serial.print(Value_Response);
  delay(1000);
  i++;
  }

Value_Response = HAL_u16Change_ID_sensor(CMD_Get_ID);
Serial.print("New Sensor ID is : ");
Serial.print(Value_Response);
delay(1000);

}


// function takes pionter to the command array then return the reading value 

uint16_t HAL_u16Change_ID_sensor(const byte * COMMAND)
{
  uint16_t Local_u16Read;

  // trasmit 
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);

  if(mod.write(COMMAND,sizeof(COMMAND))==8)
  {
    // recieve 
  digitalWrite(DE,LOW);
  digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++)
    {
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.println(values[i],HEX);
    }    
    Serial.println();
  }

// Local_u16Read = (uint16_t)((values[3]&0x00ff)<<8 | (values[4]&0xff));
return values[5];

}