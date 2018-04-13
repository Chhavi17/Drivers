/*
 * LabGPIO.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: chhav
 */

#include "LPC17xx.h"
#include "LabGPIO.hpp"

LabGPIO::LabGPIO(uint8_t port, uint8_t pin)
{
    port_num = port;
    pin_num = pin;
}

void LabGPIO::setAsInput()
{
    if(port_num == 0)
        LPC_GPIO0->FIODIR &= ~(1 << pin_num);
    else if(port_num == 1)
        LPC_GPIO1->FIODIR &= ~(1 << pin_num);
    else if(port_num == 2)
        LPC_GPIO2->FIODIR &= ~(1 << pin_num);
}

void LabGPIO::setAsOutput()
{
    if(port_num == 0)
        LPC_GPIO0->FIODIR |= (1 << pin_num);
    else if(port_num == 1)
        LPC_GPIO1->FIODIR |= (1 << pin_num);
    else if(port_num == 2)
        LPC_GPIO2->FIODIR |= (1 << pin_num);
}

void LabGPIO::setDirection(bool output)
{
    if(output == true)
       setAsOutput();
    else
       setAsInput();
}

void LabGPIO::setHigh()
{
    if(port_num == 0)
        LPC_GPIO0->FIOSET = (1 << pin_num);
    else if(port_num == 1)
        LPC_GPIO1->FIOSET = (1 << pin_num);
    else if(port_num == 2)
        LPC_GPIO2->FIOSET = (1 << pin_num);
}


void LabGPIO::setLow()
{
    if(port_num == 0)
        LPC_GPIO0->FIOCLR = (1 << pin_num);
    else if(port_num == 1)
        LPC_GPIO1->FIOCLR = (1 << pin_num);
    else if(port_num == 2)
        LPC_GPIO2->FIOCLR = (1 << pin_num);
}

void LabGPIO::set(bool high)
{
    if(high == true)
       setHigh();
    else
       setLow();

}

bool LabGPIO::getLevel()
{
    if(port_num == 0)
    {
        if(LPC_GPIO0->FIOPIN & (1 << pin_num))
            return true;
        else
            return false;
    }
    if(port_num == 1)
    {
         if(LPC_GPIO1->FIOPIN & (1 << pin_num))
             return true;
         else
             return false;
     }
    if(port_num == 2)
    {
         if(LPC_GPIO2->FIOPIN & (1 << pin_num))
              return true;
         else
              return false;
     }

}


LabGPIO::~LabGPIO(){

}
