/* 
* This file is part of ZemoteFirmware.
* 
* ZemoteFirmware is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* ZemoteFirmware is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with ZemoteFirmware.  If not, see <http://www.gnu.org/licenses/>.
*/

#define VERSION_NUM 0.1

#include <IRremote.h>
#include <EEPROM.h>
#include "pins.h"
#include "button.h"
#include "transceive.h"

// Variables
char cmdBuffer[128];
unsigned char cmdIdx=0;
unsigned char activeBtnNum=0;

// Local functions
void getAddr();
void saveToEEPROM();
void readFromEEPROM();

/**
 * \fn void setup()
 * \brief Set up buttons and USB and read from EEPROM
 */
void setup(){
  for (int i=0; i<NUM_PHY_BUTTONS; i++)
  {
    pinMode(buttons[i], INPUT); // Input pins
    digitalWrite(buttons[i], HIGH); // Internal pull-up resistor
  }

  readFromEEPROM();

  Serial.begin(9600);
  Serial.print("Zemote\n");  
}

/**
 * \fn void loop()
 * \brief Main loop that handles button checking and USB communication
 */
void loop()
{ 
  while(Serial.available() > 0)
  { 
    cmdBuffer[cmdIdx] = Serial.read();
    if(cmdBuffer[cmdIdx] == '\n')
    {
      if(processCmd())
      {
        serial_ack(cmdBuffer[0]); 
      }
      else
      {
        serial_error(cmdBuffer[0]);
      }
      cmdIdx=0;      
    }
    else
    {
      cmdIdx++;
    }
  }
  if (programModeFlag)
  {
    if(!rcvIRStream())
    {
      serial_ack('F'); 
      disableIRReceive();
    }
  }
  check_buttons();
}

boolean processCmd()
{
  unsigned char retVal=0;
  switch(cmdBuffer[0])
  {
  case 'T':
    if (!checkInputButtonCmd())
    {
      return false;
    }
    Serial.println(activeBtnNum);
    sndIRStream(activeBtnNum);  
    break;
  case 'S':
    saveToEEPROM();
    break;
  case 'R':
    readFromEEPROM();
    break;
  case 'V':
    Serial.print("Firmware Version: ");
    Serial.println(VERSION_NUM);
    break;
  case 'P':
    if (!checkInputButtonCmd())
    {
      return false; 
    }
    enableIRReceive();
    // Action while loop to be done in main loop
    break;
  case 'F':
    disableIRReceive();
    break;
  case 'L':
    printAllButtonLength();
    break;
  case 'G':
    if (!checkInputButtonCmd())
    {
      return false;
    }
    printButtonInfo(activeBtnNum);  
    break;
  default:
    return false;
    break;
  }
  return true;
}

boolean checkInputButtonCmd()
{
  activeBtnNum = cmdBuffer[1] - '0';
  if (activeBtnNum  < 0 || activeBtnNum  > NUM_SOFT_BUTTONS)
  {
    return false; 
  } 
  return true;
}

/**
 * \fn int getAddr(int buttonLen, int cmdLen)
 * \brief Get address for EEPROM read and save
 */
int getAddr(int buttonLen, int cmdLen)
{
  return (buttonLen * NUM_COMMANDS_PER_BUTTON + cmdLen) * NUM_BYTES_PER_COMMAND;
}

/**
 * \fn void saveToEEPROM()
 * \brief Save IR data to EEPROM and 441 bytes are used in EEPROM.
 */
void saveToEEPROM()
{  
  unsigned char tmpValue;
  int k;

  for (int i=0; i<NUM_SOFT_BUTTONS; i++)
  {
    for (int j=0; j<NUM_COMMANDS_PER_BUTTON; j++)
    {
      EEPROM.write(getAddr(i,j), user_cmd[i][j].bits);
#if DEBUG==1
      Serial.println(getAddr(i,j));
      Serial.print("Bits:");
      Serial.println(user_cmd[i][j].bits);
#endif
      for (k=0; k<4; k++)
      {
        tmpValue = (unsigned char)(user_cmd[i][j].value >> (k * 8));
        EEPROM.write(getAddr(i,j)+k+1, tmpValue);
#if DEBUG==1
        Serial.println(getAddr(i,j)+k+1);
        Serial.print("Value:");
        Serial.println(tmpValue, HEX);
#endif
      }
      EEPROM.write(getAddr(i,j)+k+1, user_cmd[i][j].decode_type);
#if DEBUG==1
      Serial.println(getAddr(i,j)+k+1);
      Serial.print("Decode:");
      Serial.println(user_cmd[i][j].decode_type, DEC);
#endif
    } 
  }
  for (int i=0; i<NUM_SOFT_BUTTONS; i++)
  {
    EEPROM.write(getAddr(NUM_SOFT_BUTTONS, 0)+i, user_cmd_len[i]);
#if DEBUG==1
    Serial.println(getAddr(NUM_SOFT_BUTTONS, 0)+i);
    Serial.print("Len:");
    Serial.println(user_cmd_len[i], DEC);
#endif
  }
}

/**
 * \fn void readFromEEPROM()
 * \brief Read IR data from EEPROM and 441 bytes are used in EEPROM.
 */
void readFromEEPROM()
{
  unsigned char tmpValue;
  unsigned long tmpValue2, tmpSum;
  int k;

  for (int i=0; i<NUM_SOFT_BUTTONS; i++)
  {
    for (int j=0; j<NUM_COMMANDS_PER_BUTTON; j++)
    {
      user_cmd[i][j].bits = EEPROM.read(getAddr(i,j));
#if DEBUG==1
      Serial.println(getAddr(i,j));
      Serial.print("Bits:");
      Serial.println(user_cmd[i][j].bits);
#endif
      tmpSum = 0;
      for (k=0; k<4; k++)
      {
        tmpValue = EEPROM.read(getAddr(i,j)+k+1);  
#if DEBUG==1
        Serial.println(getAddr(i,j)+k+1);
        Serial.print("Value:");
        Serial.println(tmpValue, HEX);
#endif       
        tmpSum += ((unsigned long)tmpValue) << (k*8);
      }
      user_cmd[i][j].value = tmpSum;
#if DEBUG==1
      Serial.print("Cmd:");
      Serial.println(tmpSum, HEX);
#endif

      user_cmd[i][j].decode_type = EEPROM.read(getAddr(i,j)+k+1);
#if DEBUG==1
      Serial.println(getAddr(i,j)+k+1);
      Serial.print("Decode:");
      Serial.println(user_cmd[i][j].decode_type, DEC);
#endif
    } 
  }
  for (int i=0; i<NUM_SOFT_BUTTONS; i++)
  {
    user_cmd_len[i] = EEPROM.read(getAddr(NUM_SOFT_BUTTONS, 0)+i);
#if DEBUG==1
    Serial.println(getAddr(NUM_SOFT_BUTTONS, 0)+i);
    Serial.print("Len:");
    Serial.println(user_cmd_len[i], DEC);
#endif
  }
}













