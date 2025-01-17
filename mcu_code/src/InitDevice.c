//=========================================================
// src/InitDevice.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================

// USER INCLUDES
#include <SI_EFM8BB1_Register_Enums.h>
#include "InitDevice.h"

//==============================================================================
// enter_DefaultMode_from_RESET
//==============================================================================
extern void enter_DefaultMode_from_RESET(void) {
	// $[Config Calls]
	WDT_0_enter_DefaultMode_from_RESET();
	PORTS_0_enter_DefaultMode_from_RESET();
	PORTS_1_enter_DefaultMode_from_RESET();
	PBCFG_0_enter_DefaultMode_from_RESET();
	CLOCK_0_enter_DefaultMode_from_RESET();
	PCA_0_enter_DefaultMode_from_RESET();
	PCACH_0_enter_DefaultMode_from_RESET();
	PCACH_1_enter_DefaultMode_from_RESET();
	PCACH_2_enter_DefaultMode_from_RESET();
	TIMER01_0_enter_DefaultMode_from_RESET();
	TIMER16_3_enter_DefaultMode_from_RESET();
	TIMER_SETUP_0_enter_DefaultMode_from_RESET();
	SMBUS_0_enter_DefaultMode_from_RESET();
	INTERRUPT_0_enter_DefaultMode_from_RESET();
	// [Config Calls]$


}


//================================================================================
// WDT_0_enter_DefaultMode_from_RESET
//================================================================================
extern void WDT_0_enter_DefaultMode_from_RESET(void) {
	// $[WDTCN - Watchdog Timer Control]
	//Disable Watchdog with key sequence
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key
}

//================================================================================
// CLOCK_0_enter_DefaultMode_from_RESET
//================================================================================
extern void CLOCK_0_enter_DefaultMode_from_RESET(void) {
	// $[CLKSEL - Clock Select]
	// CLKSL (Clock Source Select) = HFOSC (Clock derived from the Internal
	//     High-Frequency Oscillator.)
	// CLKDIV (Clock Source Divider) = SYSCLK_DIV_1 (SYSCLK is equal to
	//     selected clock source divided by 1.)
	CLKSEL = CLKSEL_CLKSL__HFOSC | CLKSEL_CLKDIV__SYSCLK_DIV_1;
}

//================================================================================
// PORTS_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTS_0_enter_DefaultMode_from_RESET(void) {


	P0SKIP = P0SKIP_B0__NOT_SKIPPED | P0SKIP_B1__NOT_SKIPPED | P0SKIP_B2__NOT_SKIPPED
		 | P0SKIP_B3__NOT_SKIPPED | P0SKIP_B4__SKIPPED | P0SKIP_B5__SKIPPED
		 | P0SKIP_B6__SKIPPED | P0SKIP_B7__SKIPPED;

	P0MDIN = P0MDIN_B0__DIGITAL | P0MDIN_B1__DIGITAL | P0MDIN_B2__DIGITAL | P0MDIN_B3__DIGITAL
			| P0MDIN_B4__DIGITAL | P0MDIN_B5__DIGITAL | P0MDIN_B6__ANALOG;

	P0 |= P0_B6__HIGH; //For ADC, P0 must be set to high

	P0MDOUT = P0MDOUT_B0__OPEN_DRAIN | P0MDOUT_B1__OPEN_DRAIN | P0MDOUT_B2__PUSH_PULL
		 | P0MDOUT_B3__PUSH_PULL | P0MDOUT_B4__PUSH_PULL | P0MDOUT_B5__PUSH_PULL
		 | P0MDOUT_B6__OPEN_DRAIN | P0MDOUT_B7__OPEN_DRAIN;
}

//================================================================================
// PORTS_1_enter_DefaultMode_from_RESET
//================================================================================
extern void PORTS_1_enter_DefaultMode_from_RESET(void) {

	P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__OPEN_DRAIN | P1MDOUT_B2__OPEN_DRAIN
		 | P1MDOUT_B3__OPEN_DRAIN | P1MDOUT_B4__OPEN_DRAIN | P1MDOUT_B5__OPEN_DRAIN
		 | P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;

	P1SKIP = P1SKIP_B0__SKIPPED | P1SKIP_B1__SKIPPED | P1SKIP_B2__SKIPPED
		 | P1SKIP_B3__SKIPPED | P1SKIP_B4__SKIPPED | P1SKIP_B5__SKIPPED
		 | P1SKIP_B6__SKIPPED | P1SKIP_B7__SKIPPED;
}

//================================================================================
// PBCFG_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PBCFG_0_enter_DefaultMode_from_RESET(void) {
	// $[XBR0 - Port I/O Crossbar 0]

	XBR0 = XBR0_URT0E__DISABLED | XBR0_SPI0E__DISABLED | XBR0_SMB0E__ENABLED
		 | XBR0_CP0E__DISABLED | XBR0_CP0AE__DISABLED | XBR0_CP1E__DISABLED
		 | XBR0_CP1AE__DISABLED | XBR0_SYSCKE__DISABLED;

	XBR1 = XBR1_PCA0ME__CEX0_CEX1 | XBR1_ECIE__DISABLED | XBR1_T0E__DISABLED
		 | XBR1_T1E__DISABLED | XBR1_T2E__DISABLED; //CEX0 and CEX1 are connected to I0 pints (P0.2, P0.3)

	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED; //Disable pull-ups if problem (Since I have some on board)
}

//================================================================================
// SMBUS_0_enter_DefaultMode_from_RESET
//================================================================================
extern void SMBUS_0_enter_DefaultMode_from_RESET(void) {
	// $[SMB0CF - SMBus 0 Configuration]
	/*
	// SMBCS (SMBus Clock Source Selection) = TIMER1 (Timer 1 Overflow.)
	// ENSMB (SMBus Enable) = ENABLED (Enable the SMBus module.)
	// SMBFTE (SMBus Free Timeout Detection Enable) = FREE_TO_ENABLED (Enable
	//     bus free timeouts. The bus the bus will be considered free if SCL and
	//     SDA remain high for more than 10 SMBus clock source periods.)
	// SMBTOE (SMBus SCL Timeout Detection Enable) = SCL_TO_ENABLED (Enable
	//     SCL low timeouts.)
	// EXTHOLD (SMBus Setup and Hold Time Extension Enable) = ENABLED (Enable
	//     SDA extended setup and hold times.)
	*/
	SMB0CF &= ~SMB0CF_SMBCS__FMASK;
	SMB0CF |= SMB0CF_SMBCS__TIMER1
		 | SMB0CF_ENSMB__ENABLED | SMB0CF_SMBFTE__FREE_TO_ENABLED | SMB0CF_SMBTOE__SCL_TO_ENABLED
		 | SMB0CF_EXTHOLD__ENABLED;
	// [SMB0CF - SMBus 0 Configuration]$

	// $[SMB0ADR - SMBus 0 Slave Address]
	/*
	// GC (General Call Address Enable) = IGNORED (General Call Address is
	//     ignored.)
	// SLV (SMBus Hardware Slave Address) = 0x6B
	*/
	SMB0ADR = SMB0ADR_GC__IGNORED | (0x6B << SMB0ADR_SLV__SHIFT);
	// [SMB0ADR - SMBus 0 Slave Address]$

	// $[SMB0ADM - SMBus 0 Slave Address Mask]
	/*
	// EHACK (Hardware Acknowledge Enable) = ADR_ACK_AUTOMATIC (Automatic
	//     slave address recognition and hardware acknowledge is enabled.)
	// SLVM (SMBus Slave Address Mask) = 0x7F
	*/
	SMB0ADM = SMB0ADM_EHACK__ADR_ACK_AUTOMATIC | (0x7F << SMB0ADM_SLVM__SHIFT);
	// [SMB0ADM - SMBus 0 Slave Address Mask]$

	// $[SMB0TC - SMBus 0 Timing and Pin Control]
	// [SMB0TC - SMBus 0 Timing and Pin Control]$


}

//================================================================================
// PCA_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCA_0_enter_DefaultMode_from_RESET(void) {
	// $[PCA Off]
	PCA0CN0_CR = PCA0CN0_CR__STOP;
	// [PCA Off]$

	// $[PCA0MD - PCA Mode]
	/*
	// CIDL (PCA Counter/Timer Idle Control) = NORMAL (PCA continues to
	//     function normally while the system controller is in Idle Mode.)
	// ECF (PCA Counter/Timer Overflow Interrupt Enable) = OVF_INT_DISABLED
	//     (Disable the CF interrupt.)
	// CPS (PCA Counter/Timer Pulse Select) = SYSCLK (System clock.)
	*/
	PCA0MD = PCA0MD_CIDL__NORMAL | PCA0MD_ECF__OVF_INT_DISABLED | PCA0MD_CPS__SYSCLK;
	// [PCA0MD - PCA Mode]$

	// $[PCA0CENT - PCA Center Alignment Enable]
	/*
	// CEX0CEN (CEX0 Center Alignment Enable) = CENTER (Center-aligned.)
	// CEX1CEN (CEX1 Center Alignment Enable) = CENTER (Center-aligned.)
	// CEX2CEN (CEX2 Center Alignment Enable) = EDGE (Edge-aligned.)
	*/
	PCA0CENT = PCA0CENT_CEX0CEN__CENTER | PCA0CENT_CEX1CEN__CENTER | PCA0CENT_CEX2CEN__EDGE;
	// [PCA0CENT - PCA Center Alignment Enable]$

	// $[PCA0CLR - PCA Comparator Clear Control]
	// [PCA0CLR - PCA Comparator Clear Control]$

	// $[PCA0L - PCA Counter/Timer Low Byte]
	// [PCA0L - PCA Counter/Timer Low Byte]$

	// $[PCA0H - PCA Counter/Timer High Byte]
	/*
	// PCA0H (PCA Counter/Timer High Byte) = 0x04
	*/
	PCA0H = (0x04 << PCA0H_PCA0H__SHIFT);
	// [PCA0H - PCA Counter/Timer High Byte]$

	// $[PCA0POL - PCA Output Polarity]
	// [PCA0POL - PCA Output Polarity]$

	// $[PCA0PWM - PCA PWM Configuration]
	/*
	// CLSEL (Cycle Length Select) = 11_BITS (11 bits.)
	// ECOV (Cycle Overflow Interrupt Enable) = COVF_MASK_ENABLED (A PCA
	//     interrupt will be generated when COVF is set.)
	*/
	PCA0PWM &= ~PCA0PWM_CLSEL__FMASK;
	PCA0PWM |= PCA0PWM_CLSEL__11_BITS
		 | PCA0PWM_ECOV__COVF_MASK_ENABLED;
	// [PCA0PWM - PCA PWM Configuration]$

	// $[PCA On]
	PCA0CN0_CR = PCA0CN0_CR__RUN;
	// [PCA On]$

}

//================================================================================
// PCACH_0_enter_DefaultMode_from_RESET
//================================================================================
extern void PCACH_0_enter_DefaultMode_from_RESET(void) {
	// $[PCA0 Settings Save]
	uint8_t PCA0CN0_CR_save = PCA0CN0 & PCA0CN0_CR__BMASK;
	uint8_t PCA0PWM_ARSEL_save = PCA0PWM & PCA0PWM_ARSEL__BMASK;

	// Turn PCA0 off while updating PCACH0
	PCA0CN0 &= ~PCA0CN0_CR__BMASK;
	// Select Capture/Compare register)
	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// [PCA0 Settings Save]$

	// $[PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]
	/*
	// CAPN (Channel 0 Capture Negative Function Enable) = DISABLED (Disable
	//     negative edge capture.)
	// ECCF (Channel 0 Capture/Compare Flag Interrupt Enable) = ENABLED
	//     (Enable a Capture/Compare Flag interrupt request when CCF0 is set.)
	// MAT (Channel 0 Match Function Enable) = DISABLED (Disable match
	//     function.)
	// PWM16 (Channel 0 16-bit Pulse Width Modulation Enable) = 8_BIT (8 to
	//     11-bit PWM selected.)
	// CAPP (Channel 0 Capture Positive Function Enable) = DISABLED (Disable
	//     positive edge capture.)
	// ECOM (Channel 0 Comparator Function Enable) = ENABLED (Enable
	//     comparator function.)
	// PWM (Channel 0 Pulse Width Modulation Mode Enable) = ENABLED (Enable
	//     PWM function.)
	// TOG (Channel 0 Toggle Function Enable) = DISABLED (Disable toggle
	//     function.)
	*/
	PCA0CPM0 = PCA0CPM0_CAPN__DISABLED | PCA0CPM0_ECCF__ENABLED | PCA0CPM0_MAT__DISABLED
		 | PCA0CPM0_PWM16__8_BIT | PCA0CPM0_CAPP__DISABLED | PCA0CPM0_ECOM__ENABLED
		 | PCA0CPM0_PWM__ENABLED | PCA0CPM0_TOG__DISABLED;
	// [PCA0CPM0 - PCA Channel 0 Capture/Compare Mode]$

	// $[PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]
	// [PCA0CPL0 - PCA Channel 0 Capture Module Low Byte]$

	// $[PCA0CPH0 - PCA Channel 0 Capture Module High Byte]
	/*
	// PCA0CPH0 (PCA Channel 0 Capture Module High Byte) = 0x04
	*/
	PCA0CPH0 = (0x04 << PCA0CPH0_PCA0CPH0__SHIFT);
	// [PCA0CPH0 - PCA Channel 0 Capture Module High Byte]$

	// $[Auto-reload]
	PCA0PWM |= PCA0PWM_ARSEL__AUTORELOAD;

	/*
	// PCA0CPH0 (PCA Channel 0 Capture Module High Byte) = 0x04
	*/
	PCA0CPH0 = (0x04 << PCA0CPH0_PCA0CPH0__SHIFT);

	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// [Auto-reload]$

	// $[PCA0 Settings Restore]
	PCA0CN0 |= PCA0CN0_CR_save;
	PCA0PWM |= PCA0PWM_ARSEL_save;
	// [PCA0 Settings Restore]$

}

//================================================================================
// PCACH_1_enter_DefaultMode_from_RESET
//================================================================================
extern void PCACH_1_enter_DefaultMode_from_RESET(void) {
	// $[PCA0 Settings Save]
	uint8_t PCA0CN0_CR_save = PCA0CN0 & PCA0CN0_CR__BMASK;
	uint8_t PCA0PWM_ARSEL_save = PCA0PWM & PCA0PWM_ARSEL__BMASK;

	// Turn PCA0 off while updating PCACH1
	PCA0CN0 &= ~PCA0CN0_CR__BMASK;
	// Select Capture/Compare register)
	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// [PCA0 Settings Save]$

	PCA0CPM1 = PCA0CPM1_CAPN__DISABLED | PCA0CPM1_ECCF__ENABLED | PCA0CPM1_MAT__DISABLED
		 | PCA0CPM1_PWM16__8_BIT | PCA0CPM1_CAPP__DISABLED | PCA0CPM1_ECOM__ENABLED
		 | PCA0CPM1_PWM__ENABLED | PCA0CPM1_TOG__DISABLED;

	// $[PCA0CPM1 - PCA Channel 1 Capture/Compare Mode]
	// [PCA0CPM1 - PCA Channel 1 Capture/Compare Mode]$

	// $[PCA0CPL1 - PCA Channel 1 Capture Module Low Byte]
	// [PCA0CPL1 - PCA Channel 1 Capture Module Low Byte]$

	// $[PCA0CPH1 - PCA Channel 1 Capture Module High Byte]
	// [PCA0CPH1 - PCA Channel 1 Capture Module High Byte]$

	PCA0CPH1 = (0x04 << PCA0CPH1_PCA0CPH1__SHIFT);
	PCA0PWM |= PCA0PWM_ARSEL__AUTORELOAD;
	PCA0CPH1 = (0x04 << PCA0CPH1_PCA0CPH1__SHIFT);
	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// $[Auto-reload]
	// [Auto-reload]$

	// $[PCA0 Settings Restore]
	PCA0CN0 |= PCA0CN0_CR_save;
	PCA0PWM |= PCA0PWM_ARSEL_save;
	// [PCA0 Settings Restore]$


}

//================================================================================
// PCACH_2_enter_DefaultMode_from_RESET
//================================================================================
extern void PCACH_2_enter_DefaultMode_from_RESET(void) {
	// $[PCA0 Settings Save]
	uint8_t PCA0CN0_CR_save = PCA0CN0 & PCA0CN0_CR__BMASK;
	uint8_t PCA0PWM_ARSEL_save = PCA0PWM & PCA0PWM_ARSEL__BMASK;

	// Turn PCA0 off while updating PCACH2
	PCA0CN0 &= ~PCA0CN0_CR__BMASK;
	// Select Capture/Compare register)
	PCA0PWM &= ~PCA0PWM_ARSEL__BMASK;
	// [PCA0 Settings Save]$

	// $[PCA0CPM2 - PCA Channel 2 Capture/Compare Mode]
	// [PCA0CPM2 - PCA Channel 2 Capture/Compare Mode]$

	// $[PCA0CPL2 - PCA Channel 2 Capture Module Low Byte]
	// [PCA0CPL2 - PCA Channel 2 Capture Module Low Byte]$

	// $[PCA0CPH2 - PCA Channel 2 Capture Module High Byte]
	// [PCA0CPH2 - PCA Channel 2 Capture Module High Byte]$

	// $[Auto-reload]
	// [Auto-reload]$

	// $[PCA0 Settings Restore]
	PCA0CN0 |= PCA0CN0_CR_save;
	PCA0PWM |= PCA0PWM_ARSEL_save;
	// [PCA0 Settings Restore]$


}

//================================================================================
// TIMER01_0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER01_0_enter_DefaultMode_from_RESET(void) {
	// $[Timer Initialization]
	//Save Timer Configuration
	uint8_t TCON_save = TCON;
	//Stop Timers
	TCON &= TCON_TR0__BMASK & TCON_TR1__BMASK;

	// [Timer Initialization]$

	// $[TH0 - Timer 0 High Byte]
	/*
	// TH0 (Timer 0 High Byte) = 0x38
	*/
	TH0 = (0x38 << TH0_TH0__SHIFT);
	// [TH0 - Timer 0 High Byte]$

	// $[TL0 - Timer 0 Low Byte]
	/*
	// TL0 (Timer 0 Low Byte) = 0x13
	*/
	TL0 = (0x13 << TL0_TL0__SHIFT);
	// [TL0 - Timer 0 Low Byte]$

	// $[TH1 - Timer 1 High Byte]
	/*
	// TH1 (Timer 1 High Byte) = 0x34
	*/
	TH1 = (0x34 << TH1_TH1__SHIFT);
	// [TH1 - Timer 1 High Byte]$

	// $[TL1 - Timer 1 Low Byte]
	/*
	// TL1 (Timer 1 Low Byte) = 0x34
	*/
	TL1 = (0x34 << TL1_TL1__SHIFT);
	// [TL1 - Timer 1 Low Byte]$

	// $[Timer Restoration]
	//Restore Timer Configuration
	TCON = TCON_save;

	// [Timer Restoration]$


}

//================================================================================
// TIMER16_3_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER16_3_enter_DefaultMode_from_RESET(void) {
	// $[Timer Initialization]
	// Save Timer Configuration
	uint8_t TMR3CN0_TR3_save = TMR3CN0 & TMR3CN0_TR3__BMASK;
	// Stop Timer
	TMR3CN0 &= ~(TMR3CN0_TR3__BMASK);
	// [Timer Initialization]$

	// $[TMR3CN0 - Timer 3 Control]
	// [TMR3CN0 - Timer 3 Control]$

	// $[TMR3H - Timer 3 High Byte]
	// [TMR3H - Timer 3 High Byte]$

	// $[TMR3L - Timer 3 Low Byte]
	// [TMR3L - Timer 3 Low Byte]$

	// $[TMR3RLH - Timer 3 Reload High Byte]
	/*
	// TMR3RLH (Timer 3 Reload High Byte) = 0x38
	*/
	TMR3RLH = (0x38 << TMR3RLH_TMR3RLH__SHIFT);
	// [TMR3RLH - Timer 3 Reload High Byte]$

	// $[TMR3RLL - Timer 3 Reload Low Byte]
	/*
	// TMR3RLL (Timer 3 Reload Low Byte) = 0x9E
	*/
	TMR3RLL = (0x9E << TMR3RLL_TMR3RLL__SHIFT);
	// [TMR3RLL - Timer 3 Reload Low Byte]$

	// $[TMR3CN0]
	/*
	// TR3 (Timer 3 Run Control) = RUN (Start Timer 3 running.)
	*/
	TMR3CN0 |= TMR3CN0_TR3__RUN;
	// [TMR3CN0]$

	// $[Timer Restoration]
	// Restore Timer Configuration
	TMR3CN0 |= TMR3CN0_TR3_save;
	// [Timer Restoration]$


}

//================================================================================
// TIMER_SETUP_0_enter_DefaultMode_from_RESET
//================================================================================
extern void TIMER_SETUP_0_enter_DefaultMode_from_RESET(void) {
	// $[CKCON0 - Clock Control]
	/*
	// SCA (Timer 0/1 Prescale) = SYSCLK_DIV_4 (System clock divided by 4.)
	// T0M (Timer 0 Clock Select) = PRESCALE (Counter/Timer 0 uses the clock
	//     defined by the prescale field, SCA.)
	// T2MH (Timer 2 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 2 high
	//     byte uses the clock defined by the T2XCLK bit in TMR2CN.)
	// T2ML (Timer 2 Low Byte Clock Select) = EXTERNAL_CLOCK (Timer 2 low
	//     byte uses the clock defined by the T2XCLK bit in TMR2CN.)
	// T3MH (Timer 3 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 high
	//     byte uses the clock defined by the T3XCLK bit in TMR3CN0.)
	// T3ML (Timer 3 Low Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 low
	//     byte uses the clock defined by the T3XCLK bit in TMR3CN0.)
	// T1M (Timer 1 Clock Select) = PRESCALE (Timer 1 uses the clock defined
	//     by the prescale field, SCA.)
	*/
	CKCON0 = CKCON0_SCA__SYSCLK_DIV_4 | CKCON0_T0M__PRESCALE | CKCON0_T2MH__EXTERNAL_CLOCK
		 | CKCON0_T2ML__EXTERNAL_CLOCK | CKCON0_T3MH__EXTERNAL_CLOCK | CKCON0_T3ML__EXTERNAL_CLOCK
		 | CKCON0_T1M__PRESCALE;
	// [CKCON0 - Clock Control]$

	// $[TMOD - Timer 0/1 Mode]
	/*
	// T0M (Timer 0 Mode Select) = MODE0 (Mode 0, 13-bit Counter/Timer)
	// T1M (Timer 1 Mode Select) = MODE2 (Mode 2, 8-bit Counter/Timer with
	//     Auto-Reload)
	// CT0 (Counter/Timer 0 Select) = TIMER (Timer Mode. Timer 0 increments
	//     on the clock defined by T0M in the CKCON0 register.)
	// GATE0 (Timer 0 Gate Control) = DISABLED (Timer 0 enabled when TR0 = 1
	//     irrespective of INT0 logic level.)
	// CT1 (Counter/Timer 1 Select) = TIMER (Timer Mode. Timer 1 increments
	//     on the clock defined by T1M in the CKCON0 register.)
	// GATE1 (Timer 1 Gate Control) = DISABLED (Timer 1 enabled when TR1 = 1
	//     irrespective of INT1 logic level.)
	*/
	TMOD = TMOD_T0M__MODE0 | TMOD_T1M__MODE2 | TMOD_CT0__TIMER | TMOD_GATE0__DISABLED
		 | TMOD_CT1__TIMER | TMOD_GATE1__DISABLED;
	// [TMOD - Timer 0/1 Mode]$

	// $[TCON - Timer 0/1 Control]
	/*
	// TR1 (Timer 1 Run Control) = RUN (Start Timer 1 running.)
	*/
	TCON |= TCON_TR1__RUN;
	// [TCON - Timer 0/1 Control]$


	// $[CKCON0 - Clock Control 0]
	/*
	// SCA (Timer 0/1 Prescale) = SYSCLK_DIV_4 (System clock divided by 4.)
	// T0M (Timer 0 Clock Select) = PRESCALE (Counter/Timer 0 uses the clock
	//     defined by the prescale field, SCA.)
	// T2MH (Timer 2 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 2 high
	//     byte uses the clock defined by T2XCLK in TMR2CN0.)
	// T2ML (Timer 2 Low Byte Clock Select) = EXTERNAL_CLOCK (Timer 2 low
	//     byte uses the clock defined by T2XCLK in TMR2CN0.)
	// T3MH (Timer 3 High Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 high
	//     byte uses the clock defined by T3XCLK in TMR3CN0.)
	// T3ML (Timer 3 Low Byte Clock Select) = EXTERNAL_CLOCK (Timer 3 low
	//     byte uses the clock defined by T3XCLK in TMR3CN0.)
	// T1M (Timer 1 Clock Select) = PRESCALE (Timer 1 uses the clock defined
	//     by the prescale field, SCA.)
	*/
	CKCON0 = CKCON0_SCA__SYSCLK_DIV_4 | CKCON0_T0M__PRESCALE | CKCON0_T2MH__EXTERNAL_CLOCK
		 | CKCON0_T2ML__EXTERNAL_CLOCK | CKCON0_T3MH__EXTERNAL_CLOCK | CKCON0_T3ML__EXTERNAL_CLOCK
		 | CKCON0_T1M__PRESCALE;
	// [CKCON0 - Clock Control 0]$

}

//================================================================================
// INTERRUPT_0_enter_DefaultMode_from_RESET
//================================================================================
extern void INTERRUPT_0_enter_DefaultMode_from_RESET(void) {
	// $[EIE1 - Extended Interrupt Enable 1]
	/*
	// EADC0 (ADC0 Conversion Complete Interrupt Enable) = DISABLED (Disable
	//     ADC0 Conversion Complete interrupt.)
	// EWADC0 (ADC0 Window Comparison Interrupt Enable) = DISABLED (Disable
	//     ADC0 Window Comparison interrupt.)
	// ECP0 (Comparator0 (CP0) Interrupt Enable) = DISABLED (Disable CP0
	//     interrupts.)
	// ECP1 (Comparator1 (CP1) Interrupt Enable) = DISABLED (Disable CP1
	//     interrupts.)
	// EMAT (Port Match Interrupts Enable) = DISABLED (Disable all Port Match
	//     interrupts.)
	// EPCA0 (Programmable Counter Array (PCA0) Interrupt Enable) = DISABLED
	//     (Disable all PCA0 interrupts.)
	// ESMB0 (SMBus (SMB0) Interrupt Enable) = ENABLED (Enable interrupt
	//     requests generated by SMB0.)
	// ET3 (Timer 3 Interrupt Enable) = ENABLED (Enable interrupt requests
	//     generated by the TF3L or TF3H flags.)
	*/
	EIE1 = EIE1_EADC0__DISABLED | EIE1_EWADC0__DISABLED | EIE1_ECP0__DISABLED
		 | EIE1_ECP1__DISABLED | EIE1_EMAT__DISABLED | EIE1_EPCA0__ENABLED
		 | EIE1_ESMB0__ENABLED | EIE1_ET3__ENABLED;
	// [EIE1 - Extended Interrupt Enable 1]$

	// $[EIP1 - Extended Interrupt Priority 1]
	// [EIP1 - Extended Interrupt Priority 1]$

	// $[IE - Interrupt Enable]
	/*
	// EA (All Interrupts Enable) = ENABLED (Enable each interrupt according
	//     to its individual mask setting.)
	// EX0 (External Interrupt 0 Enable) = DISABLED (Disable external
	//     interrupt 0.)
	// EX1 (External Interrupt 1 Enable) = DISABLED (Disable external
	//     interrupt 1.)
	// ESPI0 (SPI0 Interrupt Enable) = DISABLED (Disable all SPI0
	//     interrupts.)
	// ET0 (Timer 0 Interrupt Enable) = DISABLED (Disable all Timer 0
	//     interrupt.)
	// ET1 (Timer 1 Interrupt Enable) = DISABLED (Disable all Timer 1
	//     interrupt.)
	// ET2 (Timer 2 Interrupt Enable) = DISABLED (Disable Timer 2 interrupt.)
	// ES0 (UART0 Interrupt Enable) = DISABLED (Disable UART0 interrupt.)
	*/
	IE = IE_EA__ENABLED | IE_EX0__DISABLED | IE_EX1__DISABLED | IE_ESPI0__DISABLED
		 | IE_ET0__DISABLED | IE_ET1__DISABLED | IE_ET2__DISABLED | IE_ES0__DISABLED;
	// [IE - Interrupt Enable]$

	// $[IP - Interrupt Priority]
	// [IP - Interrupt Priority]$


}



// $[Library Includes]
// [Library Includes]$

