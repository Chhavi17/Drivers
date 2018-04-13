/*
 * LabSPI.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: chhav
 */

#include "LabSPI.hpp"

constexpr LPC_SSP_TypeDef * LabSPI::SSP[];

SemaphoreHandle_t LabSPI::xx = 0;

LabSPI::LabSPI()
{

}

bool LabSPI::init(Peripheral peripheral, uint8_t data_size_select, FrameModes format, uint8_t divide)
{

    xx = xSemaphoreCreateMutex(); //initializing the static mutex

    //if peripheral is SSP0
    if (peripheral == Peripheral::SSP0) {

        LPC_SC->PCONP |= (1 << 21); //power up SSP0

        //setting clock
        LPC_SSP0->CR1 |= (1 << 1);

        LPC_SSP0->CPSR = divide;
        if (divide == 1) {
            LPC_SC->PCLKSEL1 &= ~((1 << 10) | (1 << 11));
            LPC_SC->PCLKSEL1 |= (1 << 10);
        }

        else if (divide == 2) {
            LPC_SC->PCLKSEL1 &= ~((1 << 10) | (1 << 11));
            LPC_SC->PCLKSEL1 |= (1 << 11);
        }

        else if (divide == 4) {
            LPC_SC->PCLKSEL1 &= ~((1 << 10) | (1 << 11));
        }
        else if (divide == 8)
        LPC_SC->PCLKSEL1 |= ((1 << 10) | (1 << 11));
        else
            return false;

        //setting pins
        LPC_PINCON->PINSEL1 &= ~((1 << 0) | (1 << 1));
        LPC_PINCON->PINSEL1 |= (1 << 1); //SSEL0
        LPC_PINCON->PINSEL1 &= ~((1 << 2) | (1 << 3));
        LPC_PINCON->PINSEL1 |= (1 << 3); //MISO0
        LPC_PINCON->PINSEL1 &= ~((1 << 4) | (1 << 5));
        LPC_PINCON->PINSEL1 |= (1 << 5); //MOSI0
        LPC_PINCON->PINSEL0 &= ~((1 << 30) | (1 << 31));
        LPC_PINCON->PINSEL0 |= (1 << 31); //SCK0

        //configuring CR0
        LPC_SSP0->CR0 = data_size_select - 1;
        if (format == 0) {
            LPC_SSP0->CR0 &= ~((1 << 5) | (1 << 4));
        }
        else if (format == 1) {
            LPC_SSP0->CR0 &= ~((1 << 5) | (1 << 4));
            LPC_SSP0->CR0 |= (1 << 4);
        }
        else if (format == 2) {
            LPC_SSP0->CR0 &= ~((1 << 5) | (1 << 4));
            LPC_SSP0->CR0 |= (1 << 5);
        }
        else
            return false;

    }

    if (peripheral == Peripheral::SSP1) {

        LPC_SC->PCONP |= (1 << 10); //power up SSP1

        //setting clock
        LPC_SSP1->CR1 |= (1 << 1);
        LPC_SSP1->CPSR = divide;

        LPC_SC->PCLKSEL0 &= ~((1 << 20) | (1 << 21));
        LPC_SC->PCLKSEL0 |= (1 << 20);

        //setting pins
        LPC_PINCON->PINSEL0 &= ~((1 << 15) | (1 << 14));
        LPC_PINCON->PINSEL0 |= (1 << 15); //SCK1
        LPC_PINCON->PINSEL0 &= ~((1 << 16) | (1 << 17));
        LPC_PINCON->PINSEL0 |= (1 << 17); //MISO1
        LPC_PINCON->PINSEL0 &= ~((1 << 18) | (1 << 19));
        LPC_PINCON->PINSEL0 |= (1 << 19); //MOSI1

        //configuring CR0
        LPC_SSP1->CR0 = data_size_select - 1;
        if (format == 0) {
            LPC_SSP1->CR0 &= ~((1 << 5) | (1 << 4));
        }
        else if (format == 1) {
            LPC_SSP1->CR0 &= ~((1 << 5) | (1 << 4));
            LPC_SSP1->CR0 |= (1 << 4);
        }
        else if (format == 2) {
            LPC_SSP1->CR0 &= ~((1 << 5) | (1 << 4));
            LPC_SSP1->CR0 |= (1 << 5);
        }
        else
            return false;

    }
    else
        return false;

    return true;
}

uint8_t LabSPI::transfer(uint8_t send, Peripheral ph)
{

    SSP[ph]->DR = send;
    while (SSP[ph]->SR & (1 << 4))
        ;

    return SSP[ph]->DR;

}

LabSPI::~LabSPI()
{

}
