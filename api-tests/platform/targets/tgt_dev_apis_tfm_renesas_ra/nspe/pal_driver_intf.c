/** @file
 * Copyright (c) 2026, Renesas Electronics Corporation. All rights reserved.
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

#include "pal_common.h"
#include "pal_nvmem.h"

/* Non-volatile scratch the VAL layer uses to carry state across a reset.
 *
 * NOT actually non-volatile here. The RA6/RA4 parts have 8 KB of data flash and the TF-M port gives
 * ALL of it to the secure side - 2 KB NV counters, 3 KB PS, 3 KB ITS - so there is no
 * non-secure flash to back this with, and the secure side exposes no raw-write service.
 * Backing it with .bss is correct for every suite that does not reboot, which is all of
 * the dev_apis suites as configured here.
 *
 * If a suite that reboots is ever enabled, this is the first thing to fix: give the
 * solution a small non-secure data-flash partition (BSP_PARTITION_DATA_FLASH_CPU0_N_SIZE
 * is 0 today) and point this at it. A silently volatile nvmem does not fail loudly - the
 * test simply behaves as though it had never run before.
 */
static uint32_t g_pal_nvmem[1024 / sizeof(uint32_t)] __attribute__((aligned(4)));

uint32_t pal_nvmem_get_addr(void)
{
    return (uint32_t)g_pal_nvmem;
}

/**
    @brief    - This function initializes the UART
    @param    - uart base addr
    @return   - SUCCESS/FAILURE
**/
int pal_uart_init_ns(uint32_t uart_base_addr)
{
    /* The console is RTT, brought up by the TF-M platform before the test app runs. */
    (void)uart_base_addr;
    return PAL_STATUS_SUCCESS;
}

/**
    @brief    - This function parses the input string and writes bytes into UART TX FIFO
    @param    - str      : Input String
              - data     : Value for format specifier
    @return   - SUCCESS/FAILURE
**/
int pal_print_ns(const char *str, int32_t data)
{
    tfm_log_printf(str, data);
    return PAL_STATUS_SUCCESS;
}

/* Watchdog: not driven on this port.
 *
 * These return SUCCESS rather than PAL_STATUS_UNSUPPORTED_FUNC because the VAL layer
 * treats a failed watchdog program as a test failure, not as "no watchdog". The cost is
 * that a hung test hangs rather than resetting - acceptable for bring-up on a board with
 * a debugger attached, and the reason WATCHDOG_AVAILABLE is worth revisiting if these
 * tests ever run unattended.
 */
int pal_wd_timer_init_ns(addr_t base_addr, uint32_t time_us, uint32_t timer_tick_us)
{
    (void)base_addr;
    (void)time_us;
    (void)timer_tick_us;
    return PAL_STATUS_SUCCESS;
}

int pal_wd_timer_enable_ns(addr_t base_addr)
{
    (void)base_addr;
    return PAL_STATUS_SUCCESS;
}

int pal_wd_timer_disable_ns(addr_t base_addr)
{
    (void)base_addr;
    return PAL_STATUS_SUCCESS;
}

/**
    @brief    - Reads from given non-volatile address.
    @param    - base    : Base address of nvmem
                offset  : Offset
                buffer  : Pointer to source address
                size    : Number of bytes
    @return   - SUCCESS/FAILURE
**/
int pal_nvmem_read_ns(addr_t base, uint32_t offset, void *buffer, int size)
{
    if (base != 0) {
        /* Unexpected base address - target.cfg declares 0 and defers to the accessor */
        return PAL_STATUS_ERROR;
    }
    base = pal_nvmem_get_addr();
    return nvmem_read(base, offset, buffer, size) ? PAL_STATUS_SUCCESS
                                                  : PAL_STATUS_ERROR;
}

/**
    @brief    - Writes into given non-volatile address.
    @param    - base    : Base address of nvmem
                offset  : Offset
                buffer  : Pointer to source address
                size    : Number of bytes
    @return   - SUCCESS/FAILURE
**/
int pal_nvmem_write_ns(addr_t base, uint32_t offset, void *buffer, int size)
{
    if (base != 0) {
        return PAL_STATUS_ERROR;
    }
    base = pal_nvmem_get_addr();
    return nvmem_write(base, offset, buffer, size) ? PAL_STATUS_SUCCESS
                                                   : PAL_STATUS_ERROR;
}

/**
 *   @brief    - Terminates the simulation at the end of all tests completion.
 *   @param    - void
 *   @return   - void
**/
void pal_terminate_simulation(void)
{
    while (1)
    {
        __asm volatile("WFI");
    }
}

/**
 *   @brief    - Resets the system.
 *   @param    - void
 *   @return   - SUCCESS/FAILURE
**/
int pal_system_reset(void)
{
    return tfm_platform_system_reset();
}
