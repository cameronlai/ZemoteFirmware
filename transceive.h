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

