#include <xc.h>

void CONFIG_I2C2(unsigned int BRG);
void Idle_I2C2();
void START_I2C2();
void CONF_PINES ();
int WRITE_I2C2(unsigned char DAT);
void STOP_I2C2();
void __attribute__((__interrupt__,no_auto_psv)) _MI2C2Interrupt(void);
void __attribute__((__interrupt__,no_auto_psv)) _SI2C2Interrupt(void);
void MASTER_INTERRUPTS_ENABLE();
void SLAVE_INTERRUPTS_ENABLE();