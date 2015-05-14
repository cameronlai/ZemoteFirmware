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

#ifndef transceive_h
#define transceive_h

#define NUM_SOFT_BUTTONS 9
#define MAX_SOFT_BUTTONS_IDX 8
#define NUM_COMMANDS_PER_BUTTON 8
#define NUM_BYTES_PER_COMMAND 6

struct zemote_decode{
  unsigned char decode_type;
  unsigned long value;
  unsigned char bits;
};

/*
  user_cmd mapping
 -----------------------------
 0 => Power
 1 => Volume Up
 2 => Volume Down
 3 => Channel 1 (Home Channel)
 4 => Channel 2
 5 => Channel 3
 6 => Channel 4
 7 => Channel 5
 8 => Channel 6
 -----------------------------
 */
extern zemote_decode user_cmd[NUM_SOFT_BUTTONS][NUM_COMMANDS_PER_BUTTON];
extern char user_cmd_len[9];
extern boolean programModeFlag;
extern unsigned char activeBtnNum;

// Function prototype
void sndIRStream(unsigned char button);
boolean rcvIRStream();
void enableIRReceive();
void disableIRReceive();
void serial_ack(char cmd);
void serial_error(char cmd);
void printButtonInfo(unsigned char button);
void printAllButtonLength();

#endif

