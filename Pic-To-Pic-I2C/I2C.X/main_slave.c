#include "xc.h"
#include "p24FJ64GA002.h"
#include "I2C2.h"

#define FCY 16000000

int main(void) {
    
    TRISA = 0x00;
    I2C2CONbits.I2CEN = 1;
    I2C2BRG = 0x9D;
    I2C2MSK = 0;
    I2C2ADD = 0xC0>>1;
    
    while(1){
        
        while(!IFS3bits.SI2C2IF);
        
    }
    
    return 0;
}
