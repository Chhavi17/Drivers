/*
 * LabUART.cpp

 *
 *  Created on: Mar 11, 2018
 *      Author: chhav
 */

#include "LabUART.hpp"

QueueHandle_t LabUART::rxq;

void rx_interrupt0(void);
void rx_interrupt2(void);
void rx_interrupt3(void);

LabUART::LabUART()
{

}

bool LabUART::init(Peripheral peripheral, int baudrate)
{
    //calculating value for setting baudrate
    int dl = (sys_get_cpu_clock()) / (16 * baudrate);

    rxq = xQueueCreate(10, sizeof(int));

    if (peripheral == 0) {
        LPC_SC->PCONP |= (1 << 3); //powering UART0

        //Setting PCLK = CCLK for UART0
        LPC_SC->PCLKSEL0 &= ~((1 << 6) | (1 << 7));
        LPC_SC->PCLKSEL0 |= (1 << 6);

        //Setting pins for UART0
        LPC_PINCON->PINSEL0 &= ~((1 << 6) | (1 << 7) | (1 << 4) | (1 << 5));
        LPC_PINCON->PINSEL0 |= ((1 << 4) | (1 << 6));

        //setting DLL and DLM
        LPC_UART0->LCR |= (1 << 7);
        LPC_UART0->DLL = (dl);
        LPC_UART0->DLM = (dl >> 8);
        LPC_UART0->LCR &= ~(1 << 7);

        //setting  data size
        LPC_UART0->LCR = 3;

        //enabling interrupts
        LPC_UART0->IER |= (1 << 0) | (1 << 2);

        //setup register "UART0IRQHandler" as the UART0 ISR and configure NVIC to notice UART0 IRQs.
        isr_register(UART0_IRQn, rx_interrupt0);
        NVIC_EnableIRQ(UART0_IRQn);
    }

    else if (peripheral == 1) {
        LPC_SC->PCONP |= (1 << 24); //powering UART2

        //Setting PCLK = CCLK for UART2
        LPC_SC->PCLKSEL1 &= ~((1 << 16) | (1 << 17));
        LPC_SC->PCLKSEL1 |= (1 << 16);

        //Setting pins for UART2
        LPC_PINCON->PINSEL4 &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19));
        LPC_PINCON->PINSEL4 |= ((1 << 17) | (1 << 19));

        //setting DLL and DLM
        LPC_UART2->LCR |= (1 << 7);
        LPC_UART2->DLL = (dl);
        LPC_UART2->DLM = (dl >> 8);
        LPC_UART2->LCR &= ~(1 << 7);

        //setting  data size
        LPC_UART2->LCR = 3;

        //enabling interrupts
        LPC_UART2->IER |= (1 << 0) | (1 << 2);

        //setup register "UART2IRQHandler" as the UART2 ISR and configure NVIC to notice UART2 IRQs.
        isr_register(UART2_IRQn, rx_interrupt2);
        NVIC_EnableIRQ(UART2_IRQn);
    }

    else if (peripheral == 2) {
        LPC_SC->PCONP |= (1 << 25); //powering UART3

        //Setting PCLK = CCLK for UART3
        LPC_SC->PCLKSEL1 &= ~((1 << 18) | (1 << 19));
        LPC_SC->PCLKSEL1 |= (1 << 18);

        //Setting pins
        LPC_PINCON->PINSEL9 |= (3 << 24);
        LPC_PINCON->PINSEL9 |= (3 << 26); //UART3

        //setting DLL and DLM
        LPC_UART3->LCR |= (1 << 7);
        LPC_UART3->DLL = (dl);
        LPC_UART3->DLM = (dl >> 8);
        LPC_UART3->LCR &= ~(1 << 7);

        //setting  data size
        LPC_UART3->LCR = 3;

        //enabling interrupts
        LPC_UART3->IER |= (1 << 0) | (1 << 2);

        //setup register "UART3IRQHandler" as the UART3 ISR and configure NVIC to notice UART3 IRQs.
        isr_register(UART3_IRQn, rx_interrupt3);
        NVIC_EnableIRQ(UART3_IRQn);
    }
    else
        return false;

    return true;
}

void rx_interrupt0(void)
{
    uint8_t data;
    if ( LPC_UART0->LSR & (1 << 0)) {
        data = LPC_UART0->RBR;
        xQueueSend(LabUART::rxq, &data, 1000);
    }

}

void rx_interrupt2(void)
{
    uint8_t data;
    if ( LPC_UART2->LSR & (1 << 0)) {
        data = LPC_UART2->RBR;
        xQueueSend(LabUART::rxq, &data, 1000);
    }
}

void rx_interrupt3(void)
{
    uint8_t data;
    if ( LPC_UART3->LSR & (1 << 0)) {
        data = LPC_UART3->RBR;
        xQueueSend(LabUART::rxq, &data, 1000);
    }

}

bool LabUART::send_data(Peripheral peripheral, uint8_t data)
{
    if (peripheral == 0) {
        if (LPC_UART0->LSR & (1 << 6)) {
            LPC_UART0->THR = data;
            return 1;
        }
        else {
            u0_dbg_printf("\nnot Transmitted");
            return 0;
        }

    }
    else if (peripheral == 1) {
        if (LPC_UART2->LSR & (1 << 6)) {
            LPC_UART2->THR = data;
            return 1;
        }
        else {
            u0_dbg_printf("\nnot Transmitted");
            return 0;
        }
    }
    else if (peripheral == 2) {
        if (LPC_UART3->LSR & (1 << 6)) {
            LPC_UART3->THR = data;
            return 1;
        }
        else {
            u0_dbg_printf("\nnot Transmitted");
            return 0;
        }

    }
    else
        return 0;

}

uint8_t LabUART::receive_data(Peripheral peripheral)
{
    uint8_t c;
    if (peripheral == 0) {
        if (xQueueReceive(rxq, &c, 1000)) {
            return c;
        }

    }
    else if (peripheral == 1) {
        if (xQueueReceive(rxq, &c, 1000)) {
            return c;
        }

    }
    else if (peripheral == 2) {
        if (xQueueReceive(rxq, &c, 1000)) {
            return c;
        }

    }

}

LabUART::~LabUART()
{

}
