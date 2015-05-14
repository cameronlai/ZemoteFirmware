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

#ifndef button_h
#define button_h

#define NUM_PHY_BUTTONS 6
#define NUM_CHANNELS 6
#define HOME_CHANNEL 3
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

void check_buttons();
void button_send_handler(unsigned char button);

#endif


