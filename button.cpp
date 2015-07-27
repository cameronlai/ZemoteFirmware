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

#include "pins.h"
#include "button.h"
#include "transceive.h"

// Local variables
char lastButtonStates[NUM_PHY_BUTTONS] = {
  LOW};
char buttonStates[NUM_PHY_BUTTONS]={
  LOW};
long lastDebounceTime[NUM_PHY_BUTTONS] = {
  0};
char current_channel = HOME_CHANNEL;

// Local functions
void findAvailableChannel(int change);

/**
 * \fn check_buttons()
 * \brief button checking loop
 */
void check_buttons()
{
  for (char i=0;i<NUM_PHY_BUTTONS;i++)
  {
    int reading = digitalRead(buttons[i]);
    //Serial.print("R:");
    //Serial.println(reading);
    if (reading != lastButtonStates[i]) 
    {
      lastDebounceTime[i]=millis();
    }
    if ((millis()-lastDebounceTime[i]) > DEBOUNCE_DELAY)
    {    
      // if the button state has changed:
      if (reading != buttonStates[i]) 
      {
        buttonStates[i] = reading;
        if (buttonStates[i] == HIGH)
        {
          button_send_handler(i);
        }      
      }
    }
    lastButtonStates[i]=reading;
  }
}

/**
 * \fn void button_send_handler(unsigned char button)
 * \brief maps the physical button to the software buttons and channels
 */
void button_send_handler(unsigned char button){
  switch(button)
  {
  case 3: // Home Button
    sndIRStream(HOME_CHANNEL);
    current_channel = HOME_CHANNEL;
    break;
  case 4: // Channel Plus Button
    if (simpleModeEnabled)
    {
      current_channel = SIMPLE_MODE_UP_CHANNEL;
    }
    else
    {
      findAvailableChannel(1);
    }
#if DEBUG==1
    Serial.println(current_channel, DEC);
#endif
    sndIRStream(current_channel);
    break;
  case 5: // Channel Minus Button
    if (simpleModeEnabled)
    {
      current_channel = SIMPLE_MODE_DOWN_CHANNEL;
    }
    else
    {
      findAvailableChannel(-1);
    }
#if DEBUG==1
    Serial.println(current_channel, DEC);
#endif
    sndIRStream(current_channel);
    break;
  default:
    sndIRStream(button);
    break;
  }
}

/**
 * \fn void findAvailableChannel(int change)
 * \brief Bounds the channels by home channel and max. no. of channels
 */
void findAvailableChannel(int change)
{
  for (int i = 1; i <= NUM_PHY_BUTTONS; i+=change)
  {
    current_channel += change;
    if (current_channel < HOME_CHANNEL) 
    {
      current_channel = MAX_SOFT_BUTTONS_IDX;
    } 
    if (current_channel > MAX_SOFT_BUTTONS_IDX) 
    {
      current_channel = HOME_CHANNEL;
    }
    if(user_cmd_len[current_channel] != 0)
    {
      break; 
    }
  }    
}











