//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void GPIO28069(void)
{
EALLOW;
//--------------------------------------//
// Configura EPWM como periferico //
//--------------------------------------//
//--------------------------------------//
// Configura EPWM1 A como periferico //
//--------------------------------------//
//MUX: 0 = GPIO0, 1 = EPWM1A, 2 = RESERVADO, 3 = RESERVADO
 GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1; //Configura como I/O
 GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; //Configura como saída
 GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1; //Desabilita PULL-UP interno
//--------------------------------------//
// Configura EPWM3 A como periferico //
//--------------------------------------//
//MUX: 0 = GPIO4, 1 = EPWM3A, 2 = RESERVADO, 3 = RESERVADO
 GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1; //Configura como IO
 GpioCtrlRegs.GPADIR.bit.GPIO4 = 1; //Configura como saída
 GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1; //Desabilita PULL-UP interno
//--------------------------------------//
// Configura EPWM3 B como periferico //
//--------------------------------------//
 //MUX: 0 = GPIO5, 1 = EPWM3B, 2 = RESERVADO, 3 = ECAP1
 GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1; //Configura como IO
 GpioCtrlRegs.GPADIR.bit.GPIO5 = 1; //Configura como saida
 GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1; //Desabilita PULL-UP interno*/
//--------------------------------------//
// Configura GPIO12 como entrada TZ1 //
//--------------------------------------//
 GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;//1=TZ1 Habilita Sinal TRIP-ZONE (Pullup)
EDIS;
}

