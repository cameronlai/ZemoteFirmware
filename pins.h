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
