/** @file
 * Copyright (c) 2018-2020, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "pal_uart.h"

#ifndef ARG_UNUSED
#define ARG_UNUSED(arg)  (void)arg
#endif

static volatile uint8_t tx_data_empty_test = 1;
static volatile uint8_t tx_irq_triggered_test = 0;


extern const uart_instance_t g_uart0;



/**
    @brief    - This function initializes the UART
**/

void pal_uart_ra8d1_init(uint32_t uart_base_addr)
{
	ARG_UNUSED(uart_base_addr);

    g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg);

}

/**
    @brief    - This function checks for empty TX FIFO
**/
static int pal_uart_ra8d1_is_tx_empty(void)
{
    /* Note: Check for empty TX FIFO */
    return ((tx_data_empty_test));
}

/**
    @brief    - This function checks for empty TX FIFO and writes to FIFO register
**/
void pal_uart_ra8d1_putc(uint8_t c)
{
    uint32_t bytes = 1U;
    
    /* ensure TX buffer to be empty */
    /* write the data (upper 24 bits are reserved) */
    while (!pal_uart_ra8d1_is_tx_empty());
    tx_data_empty_test = 0U;

    g_uart0.p_api->write(g_uart0.p_ctrl, &c, bytes);
	
}

/**
    @brief    - This function parses the input string and writes bytes into UART TX FIFO
    @param    - str      : Input String
              - data     : Value for format specifier
**/
void __attribute__((weak)) pal_ra8d1_print(const char *str, int32_t data)
{
    uint8_t j, buffer[16];
    int8_t  i = 0, is_neg = 0, k = 2 * sizeof(data);

    for (; *str != '\0'; ++str)
    {
        if (*str == '%')
        {
            ++str;
            if (*str == 'd')
            {
                if (data < 0)
                {
                    data = -(data);
                    is_neg = 1;
                }

                while (data != 0)
                {
                    j         = data % 10;
                    data      = data /10;
                    buffer[i] = j + 48;
                    i        += 1;
                }

                if (is_neg)
                    buffer[i++] = '-';
            }
            else if (*str == 'x' || *str == 'X')
            {
                while (k--)
                {
                    j         = data & 0xf;
                    data    >>= 4;
                    buffer[i] = j + ((j > 9) ? 55 : 48);
                    i        += 1;
                }
            }
            if (i > 0)
            {
                while (i > 0) 
				{
                    pal_uart_ra8d1_putc(buffer[--i]);
                }
            }
            else
            {
                pal_uart_ra8d1_putc(48);
            }
        }
        else
        {
            pal_uart_ra8d1_putc(*str);
            if (*str == '\n')
            {
                pal_uart_ra8d1_putc('\r');
            }
        }
    }
}

/**
    @brief    - This function checks for TX interrupt triggered or not
**/
static int pal_uart_ra8d1_is_tx_irq_triggerd(void)
{
    return tx_irq_triggered_test;
}

/**
    @brief    - This function triggers the UART TX interrupt
**/
void pal_uart_ra8d1_generate_irq(void)
{
    /* Fill the TX buffer to generate TX IRQ */
    pal_uart_ra8d1_putc(' ');
    pal_uart_ra8d1_putc(' ');

    /* Loop until TX interrupt trigger */
    while (!pal_uart_ra8d1_is_tx_irq_triggerd());
}

/**
    @brief    - This function disable the UART TX interrupt
**/
void pal_uart_ra8d1_disable_irq(void)
{
    tx_irq_triggered_test = 0;
}

void user_uart_callback(uart_callback_args_t *p_args)
{
    if(p_args->event == UART_EVENT_TX_DATA_EMPTY)
    {
       tx_data_empty_test = 1U;
    }
    if(p_args->event == UART_EVENT_TX_COMPLETE)
    {
       tx_data_empty_test = 1U;
       tx_irq_triggered_test = 1U;
    }
}
