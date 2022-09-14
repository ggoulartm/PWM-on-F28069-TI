//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
//------------------------------------------------------------------------
// Variáveis Globais
//------------------------------------------------------------------------
volatile Uint16 iVol;
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void SYSTEM(void)
{
//-------------------------------------
// Oscilador interno (Oscilador 1)
//-------------------------------------
 EALLOW;
 SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 0;// Habilita oscilador interno 1
 SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL=0;// Fonte do Clock interna
 SysCtrlRegs.CLKCTL.bit.XCLKINOFF=1; // Desabilita XCLKIN
 SysCtrlRegs.CLKCTL.bit.XTALOSCOFF=1; // Desabilita Cristal XTALOSC
 SysCtrlRegs.CLKCTL.bit.INTOSC2OFF=1; // Desabilita oscilador interno2
 EDIS;
//-------------------------------------
// Desabilita Watchdog timer e configura a logica de Bits
//-------------------------------------
 EALLOW;
 SysCtrlRegs.WDCR= 0x0068;
 EDIS;
//-------------------------------------
// PLL (freq.max: 90 MHz)
//-------------------------------------
 if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
 {
 EALLOW;
 // Rotina para falha no OSCCLKSRC1 operando em (limp mode).
 // Limpa o Bit tirando do (limp mode)
 SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
 EDIS; //Possivel Re-Habilitar a logica do clock.
 asm(" ESTOP0"); // Para compilação
 }
 // Configuração da celula de divisão DIVSEL (0 = 1/4)
  // Deve ser 0 antes da mudança do PLLCR
  if (SysCtrlRegs.PLLSTS.bit.DIVSEL != 0)
  {
  EALLOW;
  SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
  EDIS;
  }
  // Mudança do PLLCR para frequência mais alta
  if (SysCtrlRegs.PLLCR.bit.DIV != 18)
  {
  EALLOW;
  // Antes de mudar o PLLCR desabilitar a detecção lógica do clock
  SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
  SysCtrlRegs.PLLCR.bit.DIV = 18;
  EDIS;
  // Continue para esperar o bloqueio do PLL.
  // Isto é importante para o tempo critico do programa.
  while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) { }
  EALLOW;
  SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
  EDIS;
  }
  // Configurada a divisão por 2 para obter 90MHz (18/2)
  EALLOW;
  SysCtrlRegs.PLLSTS.bit.DIVSEL = 2;
  EDIS;
 //-------------------------------------
 // Clocks periféricos
 //-------------------------------------
  EALLOW;
  GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3; // Configura GPIO18 como Clock Output
  SysCtrlRegs.LOSPCP.all = 0x0002; // Configura a frequencia p/(Clock/4)
  SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2; // Configura XCLKOUT = SYSCLKOUT
 // Modulo habilitação o Bit do Clock / 0 = Desabilita <-> 1 = habilita
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1; // ADC
  SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1; // COMP1
  SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 1; // COMP2
  SysCtrlRegs.PCLKCR3.bit.COMP3ENCLK = 1;
  SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer-0
  SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1; // CPU Timer-1
  SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1; // CPU Timer-2
  SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1; // eCAP1
  SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1; // eCAP2
  SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1; // EPWM1
  SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1; // EPWM2
  SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1; // EPWM3
  SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1; // EPWM4
  SysCtrlRegs.PCLKCR0.bit.HRPWMENCLK = 1; // HRPWM (Alta definição)
  SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1; // I2C
  SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1; // SCI-A
  SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1; // SPI-A
  SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; // Tempo base do clock p/ EPWM
  EDIS;
 }
