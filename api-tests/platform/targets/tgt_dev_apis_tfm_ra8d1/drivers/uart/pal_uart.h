/** @file
 * Copyright (c) 2018-2019, Arm Limited or its affiliates. All rights reserved.
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

#ifndef _PAL_UART_ra8d1_H_
#define _PAL_UART_ra8d1_H_

#include <stdint.h>
#include "r_sci_b_uart.h"

/* function prototypes */
void pal_uart_ra8d1_init(uint32_t uart_base_addr);
void __attribute__((weak)) pal_ra8d1_print(const char *str, int32_t data);
void pal_uart_ra8d1_generate_irq(void);
void pal_uart_ra8d1_disable_irq(void);

#endif /* _PAL_UART_ra8d1_H_ */
