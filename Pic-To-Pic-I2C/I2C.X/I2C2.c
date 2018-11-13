#include "xc.h"
#include "p24FJ64GA002.h"

//Habilita Interfaz I2C2
void CONFIG_I2C2(unsigned int BRG){
    
    I2C2BRG = BRG;
    I2C2CONbits.I2CEN = 1;
    I2C2CONbits.A10M = 0;
    
}

//Espera a que el bus este inactivo
void Idle_I2C2(void)
{
    while(I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
          I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);	
}

//Condición de START
void START_I2C2(){
    
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
}

// SDA2 y SCL2 configurados como Salidas en colector abierto
void CONF_PINES (void)
{
    ODCBbits.ODB2    =   0;
    ODCBbits.ODB3    =   0;
}

//Enviar dato de 8 bits como maestro
int WRITE_I2C2(unsigned char DAT){
        
    I2C2TRN = DAT;   
    while(I2C2STATbits.TRSTAT);

    if(I2C2STATbits.IWCOL)        /* If write collision occurs,return -1 */   
        return -1;   
    else   
    {   
        return 0;   
    }  
    
}

void STOP_I2C2(){
    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
}

void __attribute__((__interrupt__,no_auto_psv)) _MI2C2Interrupt(void)
{
    if(I2C2STATbits.S){
        
        IFS3bits.MI2C2IF = 0;
        
    }else if(I2C2STATbits.S){
        
        IFS3bits.MI2C2IF = 0;

    }
}

void __attribute__((__interrupt__,no_auto_psv)) _SI2C2Interrupt(void)
{
        if(I2C2STATbits.RBF){
            
            PORTA = I2C2RCV;
            
        }
        IFS3bits.SI2C2IF = 0;
}

void MASTER_INTERRUPTS_ENABLE(){
    
    INTCON1bits.NSTDIS = 1;
    IPC12 = 0b0000011100000000;
    IFS3bits.MI2C2IF = 0;
    IEC3bits.MI2C2IE = 1;
    
}

void SLAVE_INTERRUPTS_ENABLE(){
    
    INTCON1bits.NSTDIS = 1;
    IPC12 = 0b00000000001110000;
    IFS3bits.SI2C2IF = 0;
    IEC3bits.SI2C2IE = 1;
    
}
