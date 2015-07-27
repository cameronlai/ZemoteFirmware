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

#ifndef button_h
#define button_h

#define NUM_PHY_BUTTONS 6
#define NUM_CHANNELS 6
#define HOME_CHANNEL 3
#define SIMPLE_MODE_UP_CHANNEL 4
#define SIMPLE_MODE_DOWN_CHANNEL 5
#define DEBOUNCE_DELAY 50 // ms

/*
  Physical buttons relationship with user_cmd
 ----------------------------------------------------
 Button | Name      | Link with user_cmd
 ----------------------------------------------------
 0      | POWER     | user_cmd[0]
 1      | V_PLUS    | user_cmd[1]
 2      | V_MINUS   | user_cmd[2]
 3      | HOME      | user_cmd[3]
 4      | CH_PLUS   | Increase current_channel index
 5      | CH_MINUS  | Decrease current_channel index
 ----------------------------------------------------
 */
const char buttons[6] = {
  PWR_PIN, V_PLUS_PIN, V_MINUS_PIN, HOME_PIN, CH_PLUS_PIN, CH_MINUS_PIN};

extern boolean simpleModeEnabled;

void check_buttons();
void button_send_handler(unsigned char button);

#endif



