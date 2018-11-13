#include "xc.h"
#include "p24FJ64GA002.h"
#include "I2C2.h"
#define FCY 16000000

unsigned int BRG;
unsigned char DAT;



int main(void) {
    
    AD1PCFG = 0xFFFF;
    TRISA = 0xFFFF;
    PORTA = 0x0000;
    
    //SDA2 y SCL2 Colector Abierto
    CONF_PINES();
 
    BRG = 0x9D;
    
    //Habilitar Interfaz I2C2
    CONFIG_I2C2(BRG);
    /*
     * BRG = 0x9D 400Khz para FCY = 16 Mhz
     * Formato de 7 bits
     */
      
    MASTER_INTERRUPTS_ENABLE();  
    //Interrupciones como maestro habilitadas
    //Condici�n de Inicio (S)
    //Condici�n de Stop (P)
    //Dato Transferido/Recibido
    //ACK Transmitido
    //Detecci�n de colisi�n del bus
    
    while(1){
       
        while(PORTAbits.RA0);
        while(!PORTAbits.RA0);
     
        //Espera que el bus est� inactivo
        Idle_I2C2();

        //Condici�n de START (S)
        START_I2C2();

        //Enviar direcci�n del dispositivo esclavo + R/W
        //<7:1>Direcci�n <0>R/W
        //0: Write
        //1: Read

        DAT = 0xC0;
        WRITE_I2C2(DAT);

        //Enviar dato como maestro
        DAT = 0x77;
        WRITE_I2C2(DAT);

        //Enviar bit de Parada (P))
        STOP_I2C2();
    
    }
    
    return 0;
}
