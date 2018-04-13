#ifndef LABUART_H
#define LABUART_H

#include "lpc_isr.h"
#include "LPC17xx.h"
#include "sys_config.h"
#include "printf_lib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


class LabUART {

public:

    // static queue variable
    static QueueHandle_t rxq;

    enum Peripheral
    {
        UART0 = 0, UART2 = 1, UART3 = 2
    };

    LabUART();
    ~LabUART();

    /**
     * 1) Powers on UARTn peripheral
     * 2) Set peripheral clock
     * 3) Sets pins for specified peripheral to TXD and RXD
     * 4) Set baudrate using LCR,DLL and DLM registers
     * 5) Enable receive interrupt using IER register
     * 6) Register UART2_IRQ handle function into isr and enable NVIC
     *
     * @param peripheral which peripheral UARTn you want to select.
     * @param baudrate sets baudrate
     *
     * @return true if initialization was successful
     */
    bool init(Peripheral peripheral, int baudrate);

    /**
     * Checks if the THR register is empty for the data to be sent over UART using LSR
     * Transfers a byte via UART using the THR data register.
     *
     * @param peripheral which peripheral UARTn you want to select.
     * @param data is the 8-bit data to be sent over UART
     *
     * @return true if transmission was successful
     */
    bool send_data(Peripheral peripheral, uint8_t data);

    /**
     * Receives a byte via UART when receive interrupt occurs
     *
     * @param peripheral which peripheral UARTn you want to select.
     *
     * @return received byte from the receive queue.
     */
    uint8_t receive_data(Peripheral peripheral);

    /**
     * checks if data is available to read when the receive interrupt occurs via the LSR register
     * reads the RBR register and sends it to the receive queue
     *
     * @return received byte from the receive queue.
     */
    friend void rx_interrupt0(void);
    friend void rx_interrupt2(void);
    friend void rx_interrupt3(void);

};

#endif
