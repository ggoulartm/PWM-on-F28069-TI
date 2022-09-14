//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
void InitPieCtrl(void);
extern void interrupt ISR(void);
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void INTERRUPT(void)
{
//---------------------------------------------------------------------------
// Configura��es gerais:
//---------------------------------------------------------------------------
    DINT; // Desabilita a chave geral de interrup��es
    InitPieCtrl(); // Desabilita interrup��es (PIE.IERx)/(PIE.IFRx)
    IER = 0x0000; // Desabilita todas as interrup��es da CPU
    asm(" MOV *SP++,IER");
    asm(" POP DBGIER");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    IFR = 0x0000; // Limpa todos os flags de interrup��o da CPU
//---------------------------------------------------------------------------
// Configura��es individuais: (Pheripheral interrupts):
//---------------------------------------------------------------------------
EPwm1Regs.ETSEL.bit.INTEN =0; // Desabilita EPWMxINT evento (gatilho)
EPwm1Regs.ETCLR.bit.INT=1; // Limpa flag do evento (gatilho)
EPwm1Regs.ETSEL.bit.INTSEL=1; // habilita evento quando timer = 0
EPwm1Regs.ETPS.bit.INTPRD =1; // Gera INT no primeiro evento
EPwm1Regs.ETSEL.bit.INTEN =1; // Habilita EPWMxINT evento (gatilho
//---------------------------------------------------------------------------
// Considera endere�o &ISR no PIE (Perif�rico de interrup��es externas):
//---------------------------------------------------------------------------
 EALLOW; // Necessario para escrever em registradores protegidos
 PieVectTable.EPWM1_INT = &ISR;
 EDIS; // Necessario para proteger novamente o registrador
//---------------------------------------------------------------------------
// Habilita as interrup��es externa selecionadas (PIE): (ver a Tabela PIE)
//---------------------------------------------------------------------------
PieCtrlRegs.PIEACK.all = 0x0004; // Habilita a linha INT3
PieCtrlRegs.PIEIER3.bit.INTx1 = 1; // Habilita o EPWM1 na primeira coluna
//---------------------------------------------------------------------------
// Habilita interrup��o selecionada e demais interrup��es:
//---------------------------------------------------------------------------
 IER |= 0x0004; // Habilita interrup�oes = Grupo INT3
 PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // habilita a tabela PIE
EINT; // habilita interrup��o no nivel do CPU
 ERTM; // Coloca 0 no FLAG DBGM, permitindo Debug em Tempo Real
//---------------------------------------------------------------------------
}
void InitPieCtrl(void)
{
//---------------------------------------------------------------------------
//Desabilita interrup��es no nivel da CPU:
//---------------------------------------------------------------------------
 DINT;
//---------------------------------------------------------------------------
 //Desabilita o PIECTRL
 //---------------------------------------------------------------------------
  PieCtrlRegs.PIECTRL.bit.ENPIE = 0;
 //---------------------------------------------------------------------------
 //Limpa todos os registradores PIEIER:
 //---------------------------------------------------------------------------
 PieCtrlRegs.PIEIER1.all = 0;
 PieCtrlRegs.PIEIER2.all = 0;
 PieCtrlRegs.PIEIER3.all = 0;
 PieCtrlRegs.PIEIER4.all = 0;
 PieCtrlRegs.PIEIER5.all = 0;
 PieCtrlRegs.PIEIER6.all = 0;
 PieCtrlRegs.PIEIER7.all = 0;
 PieCtrlRegs.PIEIER8.all = 0;
 PieCtrlRegs.PIEIER9.all = 0;
 PieCtrlRegs.PIEIER10.all = 0;
 PieCtrlRegs.PIEIER11.all = 0;
 PieCtrlRegs.PIEIER12.all = 0;
 //---------------------------------------------------------------------------
 //Limpa todos os registradores PIEIFR:
 //---------------------------------------------------------------------------
 PieCtrlRegs.PIEIFR1.all = 0;
 PieCtrlRegs.PIEIFR2.all = 0;
 PieCtrlRegs.PIEIFR3.all = 0;
 PieCtrlRegs.PIEIFR4.all = 0;
 PieCtrlRegs.PIEIFR5.all = 0;
 PieCtrlRegs.PIEIFR6.all = 0;
 PieCtrlRegs.PIEIFR7.all = 0;
 PieCtrlRegs.PIEIFR8.all = 0;
 PieCtrlRegs.PIEIFR9.all = 0;
 PieCtrlRegs.PIEIFR10.all = 0;
 PieCtrlRegs.PIEIFR11.all = 0;
 PieCtrlRegs.PIEIFR12.all = 0;
 }
