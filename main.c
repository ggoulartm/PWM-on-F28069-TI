//------------------------------------------------------------------------
// Arquivos Header
//------------------------------------------------------------------------
#include "DSP28x_Project.h"
//------------------------------------------------------------------------
// Prot�tipos das fun��es
//------------------------------------------------------------------------
void SYSTEM(void);
void GPIO28069(void);
void EPWM(void);
void INTERRUPT(void);
extern void interrupt ISR();
//------------------------------------------------------------------------
// Vari�veis Globais
//------------------------------------------------------------------------
int PWM3A[100]; // Vetor de aquisi��o de dados para plotar
int PWM3B[100]; // Vetor de aquisi��o de dados para plotar
int g = 0; // Ponto inicial
int D = 50; // Raz�o ciclica em %
int TM = 5; // Tempo morto em % utilizado o mesmo para subida e descida
int TP = 0; // Trem de pulso (1=Habilita <-> 0=desabilita)
//------------------------------------------------------------------------
// Rotina Principal
//------------------------------------------------------------------------
void main(void)
{
//-------------------------------------
// Configura��o do sistema
//-------------------------------------
 SYSTEM();
 GPIO28069();
 EPWM();
 INTERRUPT();
//-------------------------------------
// C�digo para aquisi��o de daodos
//-------------------------------------
 while(1){
 //Loop infinito
 }
}
//------------------------------------------------------------------------
// Fim da Rotina Principal
//------------------------------------------------------------------------
