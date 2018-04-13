

#include "pwmDriver.hpp"
#include "sys_config.h"
#include "LPC17xx.h"

PWMDriver::PWMDriver(){
    mr_value = 0;
}


void PWMDriver::pwmSelectAllPins(){
    // selecting the PWM pins
    LPC_PINCON->PINSEL4 &=  ~((3 << 0) | (3 << 2) | (3 << 4) | (3 << 6) | (3 << 8) | (3 << 10));
    LPC_PINCON->PINSEL4 |=   ((1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) | (1 << 8) | (1 << 10));

    // setting the PCR (control register)
    LPC_PWM1->PCR   |=  ((1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14));
}


void PWMDriver::pwmSelectPin(PWM_PIN pwm_pin_arg){
    // setting  PWM pins
    LPC_SC->PCONP |= (1 << 6); //power
    LPC_SC->PCLKSEL0    &=  ~(3 << 12);     // setting to '01' to set peripheral clock equal to sys_clock (i.e. 96 MHz)

    switch(pwm_pin_arg)
    {
        case 0:
                LPC_PINCON->PINSEL4 &= ~(3<<0);
                LPC_PINCON->PINSEL4 |= (1<<0);
                LPC_PWM1->PCR |= (1<<9);
                break;
        case 1:
                LPC_PINCON->PINSEL4 &= ~(3<<2);
                LPC_PINCON->PINSEL4 |= (1<<2);
                LPC_PWM1->PCR |= (1<<10);
                break;
        case 2:
                LPC_PINCON->PINSEL4 &= ~(3<<4);
                LPC_PINCON->PINSEL4 |= (1<<4);
                LPC_PWM1->PCR |= (1<<11);
                break;
        case 3:
                LPC_PINCON->PINSEL4 &= ~(3<<6);
                LPC_PINCON->PINSEL4 |= (1<<6);
                LPC_PWM1->PCR |= (1<<12);
                break;
        case 4:
                LPC_PINCON->PINSEL4 &= ~(3<<8);
                LPC_PINCON->PINSEL4 |= (1<<8);
                LPC_PWM1->PCR |= (1<<13);
                break;
        case 5:
                LPC_PINCON->PINSEL4 &= ~(3<<10);
                LPC_PINCON->PINSEL4 |= (1<<10);
                LPC_PWM1->PCR |= (1<<14);
                break;
    }

}


void PWMDriver::pwmInitSingleEdgeMode(uint32_t frequency_Hz){

    mr_value = sys_get_cpu_clock() / frequency_Hz;



    LPC_PWM1->MCR |= (1 << 1);
    LPC_PWM1->MR0 = mr_value;


    LPC_PWM1->LER   |=  (1 << 0);

    LPC_PWM1->TCR   |=    (1 << 0) | (1 << 3);   // enable PWM mode


    // setting the PCR (control register)
    LPC_PWM1->PCR   |=  ((1 << 9) | (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14));

    // set as 0 because the duty cycle is 0%
    LPC_PWM1->MR1   = 0;
    LPC_PWM1->MR2   = 0;
    LPC_PWM1->MR3   = 0;
    LPC_PWM1->MR4   = 0;
    LPC_PWM1->MR5   = 0;
    LPC_PWM1->MR6   = 0;
}


void PWMDriver::setDutyCycle(PWM_PIN pwm_pin_arg, float duty_cycle_percentage){
    uint32_t MR_x = duty_cycle_percentage * mr_value / 100;

    if(pwm_pin_arg == 0){
        LPC_PWM1->MR1  = MR_x;
        LPC_PWM1->LER |= (1 << 1);
    }
    if(pwm_pin_arg == 1){
        LPC_PWM1->MR2  = MR_x;
        LPC_PWM1->LER |= (1 << 2);
    }
    if(pwm_pin_arg == 2){
        LPC_PWM1->MR3  = MR_x;
        LPC_PWM1->LER |= (1 << 3);
    }
    if(pwm_pin_arg == 3){
        LPC_PWM1->MR4  = MR_x;
        LPC_PWM1->LER |= (1 << 4);
    }
    if(pwm_pin_arg == 4){
        LPC_PWM1->MR5  = MR_x;
        LPC_PWM1->LER |= (1 << 5);
    }
    if(pwm_pin_arg == 5){
        LPC_PWM1->MR6  = MR_x;
        LPC_PWM1->LER |= (1 << 6);
    }
}


void PWMDriver::setFrequency(uint32_t frequency_Hz){
    mr_value = sys_get_cpu_clock() / frequency_Hz;
    LPC_PWM1->MR0 = mr_value;
}
