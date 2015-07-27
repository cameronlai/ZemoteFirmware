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

#ifndef pins_h
#define pins_h

#include <Arduino.h>

// Input button pins on Arduino UNO
#define PWR_PIN      10
#define HOME_PIN      9
#define V_PLUS_PIN    8
#define V_MINUS_PIN   6
#define CH_PLUS_PIN   7
#define CH_MINUS_PIN  5

// IR receiver pin
#define IR_RECV_PIN A0

// IR transmitter output uses Timer 2A, which is on pin 3
// This is hard coded in the IR Remote library

#define DEBUG 0


#endif

