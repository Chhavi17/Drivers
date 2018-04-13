/*
 * adcDriver.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: chhav
 */

#include "adcDriver.hpp"
#include "printf_lib.h"

ADCDriver::ADCDriver()
{

}

void ADCDriver::adcInitBurstMode()
{
    LPC_SC->PCONP |= (1 << 12); //powering up ADC pin
    LPC_ADC->ADCR |= (1 << 21); //enabling ADC

    //selecting PCLK_ADC = CCLK
    LPC_SC->PCLKSEL0 &= ~(3 << 24);
    LPC_SC->PCLKSEL0 |= (1 << 24);

    //setting clkdiv
    LPC_ADC->ADCR |= ((96000000/(13000000-1)) << 8);

    //setting pins
    LPC_PINCON->PINSEL1 &= ~(3 << 18); // clear AD0.2
    LPC_PINCON->PINSEL1 |= (1 << 18); // setting AD0.2

    LPC_PINCON->PINSEL1 &= ~(3 << 20); // clear AD0.3
    LPC_PINCON->PINSEL1 |= (1 << 20); // setting AD0.3

    LPC_PINCON->PINSEL3 &= ~(3 << 28); // clear AD0.4
    LPC_PINCON->PINSEL3 |= (1 << 28); // setting AD0.4

    LPC_PINCON->PINSEL3 &= ~(3 << 30); // clear AD0.5
    LPC_PINCON->PINSEL3 |= (1 << 30); // setting AD0.5

    LPC_PINCON->PINMODE1 &= ~(3 << 18); // clear AD0.2
    LPC_PINCON->PINMODE1 |= (2 << 18); // setting AD0.2

    LPC_PINCON->PINMODE1 &= ~(3 << 20); // clear AD0.3
    LPC_PINCON->PINMODE1 |= (2 << 20); // setting AD0.3

    LPC_PINCON->PINMODE3 &= ~(3 << 28); // clear AD0.4
    LPC_PINCON->PINMODE3 |= (1 << 28); // setting AD0.4

    LPC_PINCON->PINMODE3 &= ~(3 << 30); // clear AD0.5
    LPC_PINCON->PINMODE3 |= (1 << 30); // setting AD0.5


    LPC_ADC->ADCR &= ~((1 << 24)|(1 << 25)|(1 << 26));
    LPC_ADC->ADCR |= (1 << 16); // burst mode

}

void ADCDriver::adcSelectPin(ADC_PIN adc_pin_arg)
{
    if (adc_pin_arg == ADC_PIN_0_25)
    LPC_ADC->ADCR |= (1 << 2);
    if (adc_pin_arg == ADC_PIN_0_26)
    LPC_ADC->ADCR |= (1 << 3);
    if (adc_pin_arg == ADC_PIN_1_30)
    LPC_ADC->ADCR |= (1 << 4);
    if (adc_pin_arg == ADC_PIN_1_31)
    LPC_ADC->ADCR |= (1 << 5);
}

float ADCDriver::readADCVoltageByChannel(uint8_t adc_channel_arg)
{
    float result;
    if (adc_channel_arg == 0) {
        while(! (LPC_ADC->ADDR0 & (1 << 31))) ;
        result = ((LPC_ADC->ADDR0 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR0 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 1) {
        while (!(LPC_ADC->ADDR1 & (1 << 31)));
        result = ((LPC_ADC->ADDR1 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR1 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 2) {
        while (!(LPC_ADC->ADDR2 & (1 << 31)))   ;
        result = ((LPC_ADC->ADDR2 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR2 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 3) {
        while (!(LPC_ADC->ADDR3 & (1 << 31)))  ;
        result = ((LPC_ADC->ADDR3 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR3 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 4) {
        while (!(LPC_ADC->ADDR4 & (1 << 31)))  ;
        result = ((LPC_ADC->ADDR4 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR4 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 5) {
        while (!(LPC_ADC->ADDR5 & (1 << 31)))   ;
        result = ((LPC_ADC->ADDR5 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR5 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 6) {
        while (!(LPC_ADC->ADDR6 & (1 << 31)))  ;
        result = ((LPC_ADC->ADDR6 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR6 &= ~(1 << 31);
    }
    else if (adc_channel_arg == 7) {
        while (!(LPC_ADC->ADDR7 & (1 << 31)));
        result = ((LPC_ADC->ADDR7 & 0x0000FFF0) >> 4);
        LPC_ADC->ADDR7 &= ~(1 << 31);
    }
    return result;

}
