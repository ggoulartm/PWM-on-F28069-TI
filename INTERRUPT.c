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
// Configurações gerais:
//---------------------------------------------------------------------------
    DINT; // Desabilita a chave geral de interrupções
    InitPieCtrl(); // Desabilita interrupções (PIE.IERx)/(PIE.IFRx)
    IER = 0x0000; // Desabilita todas as interrupções da CPU
    asm(" MOV *SP++,IER");
    asm(" POP DBGIER");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    asm(" NOP");
    IFR = 0x0000; // Limpa todos os flags de interrupção da CPU
//---------------------------------------------------------------------------
// Configurações individuais: (Pheripheral interrupts):
//---------------------------------------------------------------------------
EPwm1Regs.ETSEL.bit.INTEN =0; // Desabilita EPWMxINT evento (gatilho)
EPwm1Regs.ETCLR.bit.INT=1; // Limpa flag do evento (gatilho)
EPwm1Regs.ETSEL.bit.INTSEL=1; // habilita evento quando timer = 0
EPwm1Regs.ETPS.bit.INTPRD =1; // Gera INT no primeiro evento
EPwm1Regs.ETSEL.bit.INTEN =1; // Habilita EPWMxINT evento (gatilho
//---------------------------------------------------------------------------
// Considera endereço &ISR no PIE (Periférico de interrupções externas):
//---------------------------------------------------------------------------
 EALLOW; // Necessario para escrever em registradores protegidos
 PieVectTable.EPWM1_INT = &ISR;
 EDIS; // Necessario para proteger novamente o registrador
//---------------------------------------------------------------------------
// Habilita as interrupções externa selecionadas (PIE): (ver a Tabela PIE)
//---------------------------------------------------------------------------
PieCtrlRegs.PIEACK.all = 0x0004; // Habilita a linha INT3
PieCtrlRegs.PIEIER3.bit.INTx1 = 1; // Habilita o EPWM1 na primeira coluna
//---------------------------------------------------------------------------
// Habilita interrupção selecionada e demais interrupções:
//---------------------------------------------------------------------------
 IER |= 0x0004; // Habilita interrupçoes = Grupo INT3
 PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // habilita a tabela PIE
EINT; // habilita interrupção no nivel do CPU
 ERTM; // Coloca 0 no FLAG DBGM, permitindo Debug em Tempo Real
//---------------------------------------------------------------------------
}
void InitPieCtrl(void)
{
//---------------------------------------------------------------------------
//Desabilita interrupções no nivel da CPU:
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
