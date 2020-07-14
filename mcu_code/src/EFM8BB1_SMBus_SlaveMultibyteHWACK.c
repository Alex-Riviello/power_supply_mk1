//-----------------------------------------------------------------------------
// EFM8BB1_SMBus_SlaveMultibyteHWACK.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// Example software to demonstrate the SMBus interface in Slave mode
// with Hardware Ack enabled:
// - Interrupt-driven SMBus implementation
// - Only slave states defined
// - Multi-byte SMBus data holders used for both transmit and receive
// - SMB0CN_ARBLOST support included
// - supports multiple-byte writes and multiple-byte reads
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC / 1
//   SMBus  - SMBus master, SCL = 10 kHz
//   Timer1 - SMBus clock rate (used only for free timeout detection)
//   Timer3 - SMBus SCL low timeout detection
//   P0.0   - Display enable
//   P1.2   - SMBus SDA
//   P1.3   - SMBus SCL
//   P1.4   - LED green
//
//-----------------------------------------------------------------------------
// How To Test: EFM8BB1 STK (SMBus Slave) + EFM8BB1 STK (SMBus Master)
//-----------------------------------------------------------------------------
// 1) Connect the device first EFM8BB1 STK to second EFM8BB1 STK running the
//    corresponding SMBus_Master_Multibyte code.
// 2) Place the switch in "AEM" mode.
// 3) Connect the EFM8BB1 STK board to a PC using a mini USB cable.
// 4) Compile and download code to the first EFM8BB1 STK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 5) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 6) The slave code will write data and read data from the
//    same data byte, so a successive write and read will effectively echo the
//    data written. To verify that the code is working properly, verify on the
//    master that the data written is the same as the data received.
//
// Target:         EFM8BB1
// Tool chain:     Generic
//
// Release 0.1 (ST)
//    - Initial Revision
//    - 10 OCT 2014
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>
#include "InitDevice.h"
#include "EFM8BB1_SMBus_SlaveMultibyteHWACK.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
// Global holder for SMBus data.
// All receive data is written here
// NUM_BYTES_WR used because an SMBus write is Master->Slave
uint8_t SMB_DATA_IN[NUM_BYTES_WR];
extern uint16_t CEX0_Compare_Value;    // Holds current PCA compare value
extern uint16_t CEX1_Compare_Value;    // Holds current PCA compare value
// Global holder for SMBus data.
// All transmit data is read from here
// NUM_BYTES_RD used because an SMBus read is Slave->Master
uint8_t SMB_DATA_OUT[NUM_BYTES_RD];

bool DATA_READY = 0;                    // Set to '1' by the SMBus ISR
uint8_t p_voltage_val_msb = 0;
uint8_t p_voltage_val_lsb = 0;
uint8_t n_voltage_val_msb = 0;
uint8_t n_voltage_val_lsb = 0;

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
//
// Main routine performs all configuration tasks, then waits for SMBus
// communication.
//
//-----------------------------------------------------------------------------
void main (void)
{
   uint8_t i;
   uint16_t delay_count;               // Used to implement a delay
   uint16_t positive_voltage = 0;
   uint16_t negative_voltage = 0;
   uint16_t old_positive_voltage = 0;
   uint16_t old_negative_voltage = 0;

   enter_DefaultMode_from_RESET();

   // Initialize the outgoing data array in case a read is done before a
   // write
   for(i = 0; i < NUM_BYTES_RD; i++)
   {
      SMB_DATA_OUT[i] = 0xFD;
   }

   //Added this to test
  // P0 = 0x00;

   // Configure initial PWM duty cycle = 10%
   //CEX0_Compare_Value = 2048 - (2048 * 0.1);
   //CEX1_Compare_Value = 2048 - (2048 * 0.1);
   CEX0_Compare_Value = 2048 - positive_voltage; //Bug 2048 or 2047 (gives 3.3V at boot)
   CEX1_Compare_Value = 2048 - negative_voltage;

   while(1)
   {
	   // Wait a little while
	   for (delay_count = 1200; delay_count > 0; delay_count--);

	   positive_voltage = p_voltage_val_msb*256 + p_voltage_val_lsb;
	   negative_voltage = n_voltage_val_msb*256 + n_voltage_val_lsb;

	   if((old_positive_voltage != positive_voltage) || (old_negative_voltage != negative_voltage)){

		   if(positive_voltage > 0x7FF){
			   positive_voltage = 0x7FF;
		   }
		   if(negative_voltage > 0x7FF){
			   negative_voltage = 0x7FF;
		   }

		   CEX0_Compare_Value = 2048 - positive_voltage; //Bug 2048 or 2047 (gives 3.3V at boot)
		   CEX1_Compare_Value = 2048 - negative_voltage;

		   old_positive_voltage = positive_voltage;
		   old_negative_voltage = negative_voltage;

		   // Wait a little while
		   for (delay_count = 1200; delay_count > 0; delay_count--);
	   }

   }
}

