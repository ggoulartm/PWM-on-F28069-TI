//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
//------------------------------------------------------------------------
// Variáveis Globais
//------------------------------------------------------------------------
extern int g; // Definido em main.c
extern int PWM3A[100];// Definido em main.c
extern int PWM3B[100];// Definido em main.c
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void interrupt ISR()
{
//-----------------------------------------------
// Suporte Gráfico
//-----------------------------------------------
 PWM3A[g] = (int) GpioDataRegs.GPADAT.bit.GPIO4; //GPIO4 = EPWM3A (Pino 36)
 PWM3B[g] = (int) GpioDataRegs.GPADAT.bit.GPIO5; //GPIO5 = EPWM3B (Pino 35)
 if(++g==100)g=0;
//-----------------------------------------------
// Flags de Interrupção
//-----------------------------------------------
PieCtrlRegs.PIEACK.all= 0x0004; //Reseta o bit de reconhecimento
EPwm1Regs.ETCLR.bit.INT=1; //Limpa flag do evento(gatilho)
}
