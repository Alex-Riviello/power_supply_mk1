//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

         
// USER INCLUDES			
#include <SI_EFM8BB1_Register_Enums.h>
#include "EFM8BB1_SMBus_SlaveMultibyteHWACK.h"

//Device Address = 0x6B
#define P_VOLTAGE_MSB 0x00
#define P_VOLTAGE_LSB 0x01
#define N_VOLTAGE_MSB 0x02
#define N_VOLTAGE_LSB 0x03

uint16_t CEX0_Compare_Value;       // Holds current PCA compare value
uint16_t CEX1_Compare_Value;

//-----------------------------------------------------------------------------
// SMBUS0_ISR
//-----------------------------------------------------------------------------
//
// SMBUS0 ISR Content goes here. Remember to clear flag bits:
// SMB0CN0::SI (SMBus Interrupt Flag)
//
// SMBus ISR state machine
// - Slave only implementation - no master states defined
// - All incoming data is written to global variable <SMB_DATA_IN>
// - All outgoing data is read from global variable <SMB_DATA_OUT>
//
//-----------------------------------------------------------------------------
SI_INTERRUPT(SMBUS0_ISR, SMBUS0_IRQn)
{
   static uint8_t sent_byte_counter;
   static uint8_t rec_byte_counter;

   if (SMB0CN0_ARBLOST == 0)
   {
      switch (SMB0CN0 & 0xF0)          // Decode the SMBus status vector
      {
         // Slave Receiver: Start+Address received
         case  SMB_SRADD:

            SMB0CN0_STA = 0;           // Clear SMB0CN0_STA bit

            sent_byte_counter = 1;     // Reinitialize the data counters
            rec_byte_counter = 1;

            if ((SMB0DAT & 0x01) == READ) // If the transfer is a master READ,
            {
            	if(SMB_DATA_IN[0] == P_VOLTAGE_MSB){
            		SMB0DAT = p_voltage_val_msb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == P_VOLTAGE_LSB){
            		SMB0DAT = p_voltage_val_lsb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == N_VOLTAGE_MSB){
            		SMB0DAT = n_voltage_val_msb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == N_VOLTAGE_LSB){
            		SMB0DAT = n_voltage_val_lsb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else{
            		SMB0DAT = 0xAA;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            }
            //else{
            //	SMB0DAT = 0x6B;
            //	sent_byte_counter++;
            //
            //}
            break;

         // Slave Receiver: Data received
         case  SMB_SRDB:

            if (rec_byte_counter < NUM_BYTES_WR) //If under 2, received device address
            {                                    //Next byte has to be register address
               // Store incoming data
               SMB_DATA_IN[0] = SMB0DAT; //SMB_DATA_IN[0] stores register address
               rec_byte_counter++;

              // SMB0CN0_ACK = 1;        // SMB0CN0_ACK received data
            }
            else if(SMB_DATA_IN[0] == P_VOLTAGE_MSB){
            	p_voltage_val_msb = SMB0DAT;
            	rec_byte_counter++;
            	SMB_DATA_IN[0] = SMB_DATA_IN[0] + 1;
            }
            else if(SMB_DATA_IN[0] == P_VOLTAGE_LSB){
            	p_voltage_val_lsb = SMB0DAT;
            	rec_byte_counter++;
            	SMB_DATA_IN[0] = SMB_DATA_IN[0] + 1;
            }
            else if(SMB_DATA_IN[0] == N_VOLTAGE_MSB){
            	n_voltage_val_msb = SMB0DAT;
            	rec_byte_counter++;
            	SMB_DATA_IN[0] = SMB_DATA_IN[0] + 1;
            }
            else if(SMB_DATA_IN[0] == N_VOLTAGE_LSB){
            	n_voltage_val_lsb = SMB0DAT;
            	rec_byte_counter++;
            	SMB_DATA_IN[0] = SMB_DATA_IN[0] + 1;
            }
            else{
            	SMB_DATA_IN[1] = SMB0DAT; //Store data somewhere (might not use it)
            	rec_byte_counter++;
            }
          /*  {
               // Store incoming data
               SMB_DATA_IN[rec_byte_counter-1] = SMB0DAT;

               DATA_READY = 1;         // Indicate new data fully received
            }*/
            SMB0CN0_ACK = 1; //This necessary?
            break;

         // Slave Receiver: Stop received while either a Slave Receiver or
         // Slave Transmitter
         case  SMB_SRSTO:

            SMB0CN0_STO = 0;           // SMB0CN0_STO must be cleared by software when
                                       // a STOP is detected as a slave
            break;

         // Slave Transmitter: Data byte transmitted
         case  SMB_STDB:

            if (SMB0CN0_ACK == 1)      // If Master SMB0CN0_ACK's, send the next byte
            {
            	if(SMB_DATA_IN[0] == P_VOLTAGE_MSB){
            		SMB0DAT = p_voltage_val_msb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == P_VOLTAGE_LSB){
            		SMB0DAT = p_voltage_val_lsb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == N_VOLTAGE_MSB){
            		SMB0DAT = n_voltage_val_msb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else if(SMB_DATA_IN[0] == N_VOLTAGE_LSB){
            		SMB0DAT = n_voltage_val_lsb;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	else{
            		SMB0DAT = 0xAA;
            		sent_byte_counter++;
            		SMB_DATA_IN[0] = SMB_DATA_IN[0]+1;
            	}
            	/*
               if (sent_byte_counter <= NUM_BYTES_RD)
               {
                  // Prepare next outgoing byte
                  SMB0DAT = 0x6B;
                  sent_byte_counter++;
               }*/
            }                          // Otherwise, do nothing
            break;

         // Slave Transmitter: Arbitration lost, Stop detected
         //
         // This state will only be entered on a bus error condition.
         // In normal operation, the slave is no longer sending data or has
         // data pending when a STOP is received from the master, so the SMB0CN0_TXMODE
         // bit is cleared and the slave goes to the SRSTO state.
         case  SMB_STSTO:

            SMB0CN0_STO = 0;           // SMB0CN0_STO must be cleared by software when
                                       // a STOP is detected as a slave
            break;

         // Default: all other cases undefined
         default:

            SMB0CF &= ~0x80;           // Reset communication
            SMB0CF |= 0x80;
            SMB0CN0_STA = 0;
            SMB0CN0_STO = 0;
            SMB0CN0_ACK = 1;
            break;
      }
   }
   // SMB0CN0_ARBLOST = 1, Abort failed transfer
   else
   {
      SMB0CN0_STA = 0;
      SMB0CN0_STO = 0;
      SMB0CN0_ACK = 1;
   }

   SMB0CN0_SI = 0;                     // Clear SMBus interrupt flag
}


//-----------------------------------------------------------------------------
// TIMER3_ISR
//-----------------------------------------------------------------------------
//
// TIMER3 ISR Content goes here. Remember to clear flag bits:
// TMR3CN::TF3H (Timer # High Byte Overflow Flag)
// TMR3CN::TF3L (Timer # Low Byte Overflow Flag)
//
// A Timer3 interrupt indicates an SMBus SCL low timeout.
// The SMBus is disabled and re-enabled here
//
//-----------------------------------------------------------------------------
SI_INTERRUPT(TIMER3_ISR, TIMER3_IRQn)
{
   SMB0CF  &= ~0x80;                   // Disable SMBus
   SMB0CF  |=  0x80;                   // Re-enable SMBus
   TMR3CN0 &= ~0x80;                   // Clear Timer3 interrupt-pending flag
}

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
//
// PCA0 ISR Content goes here. Remember to clear flag bits:
// PCA0CN::CCF0 (PCA Module 0 Capture/Compare Flag)
// PCA0CN::CCF1 (PCA Module 1 Capture/Compare Flag)
// PCA0CN::CCF2 (PCA Module 2 Capture/Compare Flag)
// PCA0CN::CF (PCA Counter/Timer Overflow Flag)
// PCA0PWM::COVF (Cycle Overflow Flag)
//
// This is the ISR for the PCA.  It handles the case when a match occurs on
// channel 0, and updates the PCA0CPn compare register with the value held in
// the global variable "CEX0_Compare_Value".
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
{
   PCA0PWM &= ~0x20;                   // Clear cycle overflow flag

   PCA0PWM |= 0x80;                    // Target Auto-reload registers

   PCA0CPL0 = (CEX0_Compare_Value & 0x00FF);
   PCA0CPH0 = (CEX0_Compare_Value & 0xFF00)>>8;

   PCA0CPL1 = (CEX1_Compare_Value & 0x00FF);
   PCA0CPH1 = (CEX1_Compare_Value & 0xFF00)>>8;

   PCA0PWM &= ~0x80;                   // Target PCA0CPH/L registers
}