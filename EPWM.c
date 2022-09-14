//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
//------------------------------------------------------------------------
// Variáveis Globais
//------------------------------------------------------------------------
extern int D; // Definido em main.c
extern int TM; // Definido em main.c
extern int TP; // Definido em main.c
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void EPWM(void)
{
EALLOW;
SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC=0; //Para sincronismo da portadora
EDIS;
//------------------------------------------------------------------------
// EPWM1 - GERADOR DO VETOR PARA VISUALIZAÇÃO NO CODE COMPOSER
//------------------------------------------------------------------------
// Configuração gerais PWM1
//----------------------------------------------------
EPwm1Regs.TBCTL.bit.HSPCLKDIV=0; // (high Speed) Tempo-Base do clock (0 = clock/1)
EPwm1Regs.TBCTL.bit.CLKDIV=0; // Pré escala Tempo-Base do clock (0 = clock/1)
// Definição do periodo do PWM(T_PWM) sendo Frequência F_PWM = 1/T_PWM
// Para portadora triangular T_PWM = 2*TBPRD*CLOCK
// Para portadora dente de serra = (TBPRD+1)*CLOCK
EPwm1Regs.TBPRD = 90;//Amostragem// Periodo do Tempo-Base para F_PWM = 500kHz
EPwm1Regs.TBPHS.half.TBPHS = 0; // Configura Ângulo de Fase
EPwm1Regs.CMPA.half.CMPA = 90/2; // Tempo de contagem do comparador A
EPwm1Regs.TBCTL.bit.CTRMODE = 2; // Portador triangular (up-and-down)
EPwm1Regs.TBCTL.bit.PHSEN = 0; // Desabilitado o regulador de Fase
EPwm1Regs.TBCTL.bit.PRDLD = 0; // Definido o carregamento do (Buffer) em 0
EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;// Sincronismo em 0
EPwm1Regs.TBCTL.bit.SWFSYNC = 1; // Sincronismo Forçado por pulso
EPwm1Regs.TBCTL.bit.FREE_SOFT = 2; // Nunca interromper na contagem
EPwm1Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadow mode atualização não imediata (Buffer)
EPwm1Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadow mode atualização não imediata (Buffer)
EPwm1Regs.CMPCTL.bit.LOADAMODE = 2; // Definido carregamento do Buffer em 0 ou PRD
EPwm1Regs.CMPCTL.bit.LOADBMODE = 2; // Definido carregamento do Buffer em 0 ou PRD
//----------------------------------------------------
// Configuração PWMA1
//----------------------------------------------------
EPwm1Regs.AQCTLA.bit.CAU = 2; // Seta nivel alto na subida quando CTR=CMPA (Para PWMA)
EPwm1Regs.AQCTLA.bit.CAD = 1; // Seta nivel baixo na descida quando CTR=CMPA (Para PWMA)
EPwm1Regs.AQCTLA.bit.CBU = 0; // Não faz nada - Comparador B de subida (Para PWMA)
EPwm1Regs.AQCTLA.bit.CBD = 0; // Não faz nada - Comparador B de descida (Para PWMA)
EPwm1Regs.AQCTLA.bit.PRD = 0; // Não faz nada quando o contador CTR = PRD (Para PWMA)
EPwm1Regs.AQCTLA.bit.ZRO = 0; // Não faz nada quando o contador CTR = 0 (Para PWMA)
//----------------------------------------------------
// Configuração PWMB1 (Não utilizada)
//----------------------------------------------------
/* EPwm1Regs.AQCTLB.bit.CAU = 0; // Não faz nada - Comparador A de subida
(Para PWMB)
EPwm1Regs.AQCTLB.bit.CAD = 0; // Não faz nada - Comparador A de descida
(Para PWMB)
EPwm1Regs.AQCTLB.bit.CBU = 2; // Seta nivel alto na subida quando
CTR=CMPB (Para PWMB)
EPwm1Regs.AQCTLB.bit.CBD = 1; // Seta nivel baixo na descida quando
CTR=CMPB (Para PWMB)
EPwm1Regs.AQCTLB.bit.PRD = 0; // Não faz nada quando o contador CTR =
PRD (Para PWMB)
EPwm1Regs.AQCTLB.bit.ZRO = 0; // Não faz nada quando o contador CTR = 0
(Para PWMB)*/
//----------------------------------------------------
// Definição Tempo Morto PWM1 (Ver diagrama ePWM Dead-Band)
//----------------------------------------------------
EPwm1Regs.DBCTL.bit.IN_MODE = 0;// Chave S4 e S5 em nivel baixo
EPwm1Regs.DBCTL.bit.POLSEL = 2; // Chave S3 em nivel alto complementar
EPwm1Regs.DBCTL.bit.OUT_MODE= 0;// Desabilitado Tempo morto
EPwm1Regs.DBRED=0; //Tempo morto de subida = TBCLK*DBRED
EPwm1Regs.DBFED=0; //Tempo morto de descida DBFED = TBCLK*DBFED
//----------------------------------------------------
// Definição do chopper PWM1
//----------------------------------------------------
EPwm1Regs.PCCTL.bit.CHPEN=0; //Chopper debabilitado (Para habilitar =1)
EPwm1Regs.PCCTL.bit.CHPFREQ=111;//Frequência do chopper = (clock/8)/8
EPwm1Regs.PCCTL.bit.CHPDUTY=011;//Razão ciclica do chopper = 50%
//----------------------------------------------------
// Definição Trip Zone (Interrupção de Segurança) PWM1
//----------------------------------------------------
EALLOW;
EPwm1Regs.TZSEL.bit.OSHT1=1; // Habilita disparo da Trip-Zone: 1
EPwm1Regs.TZCTL.bit.TZA =2; // Força o nivel baixo no PWMA
EPwm1Regs.TZCTL.bit.TZB =2; // Força o nivel baixo no PWMB
EPwm1Regs.TZFRC.bit.OST =0; // Força o disparo via programa (0 é ignorado)
EDIS;
//------------------------------------------------------------------------
// EPWM3 - PWM GERADO PARA ANALISE
//------------------------------------------------------------------------
// Configuração gerais PWM3
//----------------------------------------------------
EPwm3Regs.TBCTL.bit.HSPCLKDIV=0; //(high Speed) Tempo-Base do clock (0 = clock/1)
EPwm3Regs.TBCTL.bit.CLKDIV=0; // Pré escala Tempo-Base do clock (0 = clock/1)
// Definição do periodo do PWM(T_PWM) sendo Frequência F_PWM = 1/T_PWM
// Para portadora triangular T_PWM = 2*TBPRD*CLOCK
// Para portadora dente de serra = (TBPRD+1)*CLOCK
 EPwm3Regs.TBPRD = 90*100; // Periodo do Tempo-Base para F_PWM = 5kHz
 EPwm3Regs.TBPHS.half.TBPHS = 0; // Configura Ângulo de Fase
 EPwm3Regs.CMPA.half.CMPA = 90*D; // Tempo de contagem do comparador A
 EPwm3Regs.TBCTL.bit.CTRMODE = 2; // Portador triangular (up-and-down)
 EPwm3Regs.TBCTL.bit.PHSEN = 0; // Desabilitado o regulador de Fase
 EPwm3Regs.TBCTL.bit.PRDLD = 0; // Definido o carregamento do (Buffer) em 0
 EPwm3Regs.TBCTL.bit.SYNCOSEL = 1;// Sincronismo em 0
 EPwm3Regs.TBCTL.bit.SWFSYNC =1; // Sincronismo Forçado por pulso
 EPwm3Regs.TBCTL.bit.FREE_SOFT=2; // Nunca interromper na contagem
 EPwm3Regs.CMPCTL.bit.SHDWAMODE = 0; // Shadow mode atualização não imediata(BufferA)
 EPwm3Regs.CMPCTL.bit.SHDWBMODE = 0; // Shadow mode atualização não imediata(BufferB)
 EPwm3Regs.CMPCTL.bit.LOADAMODE = 2; // Definido carregamento do BufferA em 0 ou PRD
 EPwm3Regs.CMPCTL.bit.LOADBMODE = 2; // Definido carregamento do BufferB em 0 ou PRD
//----------------------------------------------------
// Configuração PWMA3
//----------------------------------------------------
 EPwm3Regs.AQCTLA.bit.CAU = 2; // Seta nivel alto na subida quandoCTR=CMPA (Para PWMA)
 EPwm3Regs.AQCTLA.bit.CAD = 1; // Seta nivel baixo na descida quandoCTR=CMPA (Para PWMA)
 EPwm3Regs.AQCTLA.bit.CBU = 0; // Não faz nada - Comparador B de subida(Para PWMA)
 EPwm3Regs.AQCTLA.bit.CBD = 0; // Não faz nada - Comparador B de descida(Para PWMA)
 EPwm3Regs.AQCTLA.bit.PRD = 0; // Não faz nada quando o contador CTR =PRD (Para PWMA)
 EPwm3Regs.AQCTLA.bit.ZRO = 0; // Não faz nada quando o contador CTR = 0(Para PWMA)
//----------------------------------------------------
// Configuração PWMB3 - (Elaborada pelo Tempo morto para inverter a saida -paragrafo comentado)
/*/----------------------------------------------------
 EPwm3Regs.AQCTLB.bit.CAU = 1; // Seta nivel baixo na subida quando
CTR=CMPA (Para PWMB)
 EPwm3Regs.AQCTLB.bit.CAD = 2; // Seta nivel alto na descida quando
CTR=CMPA (Para PWMB)
 EPwm3Regs.AQCTLB.bit.CBU = 0; // Não faz nada - Comparador B de subida
(Para PWMB)
 EPwm3Regs.AQCTLB.bit.CBD = 0; // Não faz nada - Comparador B de subida
(Para PWMB)
 EPwm3Regs.AQCTLB.bit.PRD = 0; // Não faz nada quando o contador CTR =
PRD (Para PWMB)
 EPwm3Regs.AQCTLB.bit.ZRO = 0; // Não faz nada quando o contador CTR = 0
(Para PWMB)
*///----------------------------------------------------
// Definição Tempo Morto PWM e saida PMWB3 (Ver diagrama ePWM Dead-Band)
//----------------------------------------------------
 EPwm3Regs.DBCTL.bit.HALFCYCLE = 0; // Habilitado para ciclo interiro
 EPwm3Regs.DBCTL.bit.IN_MODE = 0; // Chave S4 e S5 em nivel baixo
 EPwm3Regs.DBCTL.bit.POLSEL = 2; // Chave S2=0 e S3=1 em nivel baixo
// A linha seguinte que define o PWMB como sendo o inverso de PWMA
 EPwm3Regs.DBCTL.bit.OUT_MODE = 3; // Habilita o tempo morto para ambos osPWMs
 EPwm3Regs.DBRED=90*TM; // Tempo morto na subida
 EPwm3Regs.DBFED=90*TM; // Tempo morto na descida
//----------------------------------------------------
// Definição do chopper PWM3
//----------------------------------------------------
 EPwm3Regs.PCCTL.bit.CHPEN = TP;//Chopper debabilitado (Para habilitar =1)
 EPwm3Regs.PCCTL.bit.CHPFREQ = 1;//Frequência do chopper = (clock/8)/1
 EPwm3Regs.PCCTL.bit.CHPDUTY = 3;//Razão ciclica do chopper = 50%
//----------------------------------------------------
// Definição Trip Zone (Interrupção de Segurança) PWM1
//----------------------------------------------------
 EALLOW;
 EPwm3Regs.TZSEL.bit.OSHT1=1; // Habilita disparo da Trip-Zone: 1
 EPwm3Regs.TZCTL.bit.TZA =1; // Força o nivel baixo no PWMA
 EPwm3Regs.TZCTL.bit.TZB =1; // Força o nivel baixo no PWMB
 EPwm3Regs.TZFRC.bit.OST =0; // Força o disparo via programa (0 é ignorado)
 EDIS;
//-------------------------------------
// SINCRONIZANDO PWM3 COM PWM1 PARA GERAÇÃO DOS GRAFICOS
//-------------------------------------
 EALLOW;
 SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC=1; // Para sincronismo das portadoras
 EDIS;
 }
