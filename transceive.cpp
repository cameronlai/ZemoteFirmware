/*
 * Zemote
 * (C) Copyright 2014 Cameron Lai
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 3.0 which accompanies this distribution, and is available at
 * https://www.gnu.org/licenses/lgpl-3.0.txt
 *
 * Zemote is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

#include <IRremote.h>

#include "pins.h"
#include "transceive.h"

// External variables
zemote_decode user_cmd[NUM_SOFT_BUTTONS][NUM_COMMANDS_PER_BUTTON] = {
  0};
char user_cmd_len[9] = {
  0};
boolean programModeFlag = false;

// Local variables
int RECV_PIN = IR_RECV_PIN;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;
int user_cmd_index=0;

// Local functions
void printResultsInfo(int index, zemote_decode localResults);
void printDecodeTypeString(int decode_type);

/**
 * \fn void sndIRStream(unsigned char button)
 * \brief Sends the IR command using the IRremote library
 */
void sndIRStream(unsigned char button)
{
  unsigned long tmpValue;
  int tmpBits;
  int protocol;
  if (user_cmd_len[button] > 0)
  {
    for(int i=0;i<user_cmd_len[button];i++)
    {
      protocol = user_cmd[button][i].decode_type;
      tmpValue = user_cmd[button][i].value;
      tmpBits = user_cmd[button][i].bits;
      switch(protocol)
      {
      case NEC:
        irsend.sendNEC(tmpValue, tmpBits);
        break;
      case SONY:
        irsend.sendSony(tmpValue, tmpBits); 
        break;
      case RC5:
        irsend.sendRC5(tmpValue, tmpBits); 
        break;
      case RC6:
        irsend.sendRC6(tmpValue, tmpBits); 
        break;
      case DISH:
        irsend.sendDISH(tmpValue, tmpBits); 
        break;
      case SHARP:
        irsend.sendSharp(tmpValue, tmpBits); 
        break;
      case PANASONIC:
        irsend.sendPanasonic(tmpValue, tmpBits); 
        break; 
      case JVC:
        irsend.sendJVC(tmpValue, tmpBits, 1); // With JVC repeat signal
        break;
      case SAMSUNG:
        irsend.sendSAMSUNG(tmpValue, tmpBits);
        break;      
      }
      delay(200);
    }
  }
}

void enableIRReceive()
{
  irrecv.enableIRIn(); // Start the receiver
  programModeFlag = true;
  user_cmd_index = 0;
  user_cmd_len[activeBtnNum] = 0;
}

void disableIRReceive()
{
  programModeFlag = false;
}

/**
 * \fn void rcvIRStream(unsigned char button)
 * \brief Receives the IR command and saves them to the user_cmd array
 */
boolean rcvIRStream()
{
  if (irrecv.decode(&results))
  {
    if (results.bits)
    {
      // Only extract useful information from decode_results data type
      zemote_decode tmpCmd;
      tmpCmd.decode_type = (unsigned char)results.decode_type;
      tmpCmd.value = (unsigned long)results.value;
      tmpCmd.bits = (unsigned char)results.bits;

      user_cmd[activeBtnNum][user_cmd_index++] = tmpCmd;
      user_cmd_len[activeBtnNum]++;
      
      printResultsInfo(user_cmd_index, tmpCmd);
    }
    irrecv.resume(); // Receive the next value
  }    
  if (user_cmd_len[activeBtnNum] >= NUM_COMMANDS_PER_BUTTON) 
  {
    return false;
  }
  return true;
}

void serial_ack(char cmd)
{
  Serial.print("ok - ");
  Serial.println(cmd); 
}

void serial_error(char cmd)
{
  Serial.print("error - ");
  Serial.println(cmd);  
}

void printButtonInfo(unsigned char button)
{
  if (user_cmd_len[button] > 0)
  {
    for(int i=0;i<user_cmd_len[button];i++)
    {
      printResultsInfo(i+1, user_cmd[button][i]);
    }
  }  
}

void printResultsInfo(int index, zemote_decode localResults)
{
  Serial.print(index);
  Serial.print(", ");
  printDecodeTypeString(localResults.decode_type);
  Serial.print(", 0x");
  Serial.println(localResults.value, HEX);
}

void printDecodeTypeString(int decode_type)
{
  switch (decode_type)
  {
  case NEC:
    Serial.print("NEC");
    break;
  case SONY:
    Serial.print("SONY");
    break;
  case RC5:
    Serial.print("RC5");
    break;
  case RC6:
    Serial.print("RC6");
    break;
  case DISH:
    Serial.print("DISH");
    break;
  case SHARP:
    Serial.print("SHARP");
    break;
  case PANASONIC:
    Serial.print("PANASONIC");
    break; 
  case JVC:
    Serial.print("JVC");
    break;
  case SAMSUNG:
    Serial.print("SAMSUNG");
    break;      
  } 
}

void printAllButtonLength()
{
  for(int i=0;i<NUM_SOFT_BUTTONS;i++)
  {
    Serial.println((int)user_cmd_len[i]);
  }  
}









