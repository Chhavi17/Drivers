///*
// * LabGPIOInterrupts.cpp
// *
// *  Created on: Feb 19, 2018
// *      Author: chhav
// */
//
//#include "LPC17xx.h"
//#include "L0_LowLevel/source/startup.cpp"
//#include "LabGPIOInterrupts.hpp"
//
//
//
//LabGPIOInterrupts::LabGPIOInterrupts(){
//
//}
//
//void LabGPIOInterrupts::init()
//{
//    isr_register(EINT3_IRQn, handle_interrupt);
//    NVIC_EnableIRQ(EINT3_IRQn);
//}
//
//bool LabGPIOInterrupts::attachInterruptHandler(uint8_t port, uint32_t pin, void (*pin_isr)(void), InterruptCondition_E condition)
//{
//    if(port>=0 && port<4 && pin>=0 && pin<32){
//        if(condition == condition_rising_edge)
//        {
//
//            int_array[port][pin];
//            pin_isr();
//            return true;
//        }
//        else if(condition == condition_falling_edge)
//        {
//
//        }
//        else if(condition == condition_both)
//        {
//
//        }
//        else
//            return false;
//
//    }
//    else
//        return false;
//}
//
//void LabGPIOInterrupts::handle_interrupt(void)
//{
//
//}
