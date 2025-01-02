/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>
#include <cr_section_macros.h>

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_inputmux.h"
#include "fsl_smartdma.h"
#include "fsl_smartdma_mcxn.h"
#include "fsl_smartdma_mdio.h"
#include "peripherals.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MEM0_SIZE 32
#define MEM0_ZONE 0x8000
#define MEM1_SIZE 32
#define MEM1_ZONE 0x9000
#define MEM2_SIZE 32
#define MEM2_ZONE 0xA000
#define MEM3_SIZE 32
#define MEM3_ZONE 0xB000

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
smartdma_mdio_param_t smartdmaParam;                  /*!< SMARTDMA function parameters. */
volatile uint8_t g_samrtdma_stack[32];
MDIO_Type g_mdio_registers;
volatile uint32_t g_mdio_mem0[MEM1_SIZE];
volatile uint32_t g_mdio_mem1[MEM1_SIZE];
volatile uint32_t g_mdio_mem2[MEM1_SIZE];
volatile uint32_t g_mdio_mem3[MEM1_SIZE];
volatile uint32_t g_mdio_debug[1024];


/*******************************************************************************
 * Code
 ******************************************************************************/
void SMARTDMA_Callbck(void)
{
	GPIO_PortToggle(BOARD_INITPINS_ARM_DEBUG_IO1_GPIO, BOARD_INITPINS_ARM_DEBUG_IO1_PIN_MASK);

}
/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    /* attach FRO 12M to FLEXCOMM4 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom4Clk, 1u);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach TRACECLKDIV to TRACE */
    CLOCK_SetClkDiv(kCLOCK_DivTraceClk, 2U);
    CLOCK_AttachClk(kTRACE_DIV_to_TRACE);
    /* Enables the clock for GPIO4: Enables clock */
    CLOCK_EnableClock(kCLOCK_Evtg);
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    BOARD_InitPeripherals();

    /*give smartdma role with secure user and non-privilege*/
 	AHBSC->MASTER_SEC_LEVEL = (AHBSC->MASTER_SEC_LEVEL) | (0x2<<4);
 	AHBSC->MASTER_SEC_ANTI_POL_REG = (AHBSC->MASTER_SEC_ANTI_POL_REG) & (~(0x2<<4));
    /*set GPIO pins user permission with secure user and non-privilege*/
 	GPIO1->PCNP = 0xffffffff;
 	GPIO3->PCNP = 0xffffffff;
    for(uint32_t delay=0;delay<=10000;delay++)
    {
    	__NOP();

    }

    CTIMER4_PERIPHERAL->TCR |= CTIMER_TCR_CRST_MASK;

    for(uint32_t delay=0;delay<=50000;delay++)
    {
    	__NOP();

    }
    INPUTMUX_Init(INPUTMUX0);
    /* CTIMER4_CH3 is selected for SMARTDMA arch B 0 */
    INPUTMUX_AttachSignal(INPUTMUX0, 0U, kINPUTMUX_Ctimer4M3ToSmartDma);
    INPUTMUX_AttachSignal(INPUTMUX0, 1U, kINPUTMUX_Gpio3PinEventTrig0ToSmartDma);

    PRINTF("MCXN947 SmartDMA MDIO Demo.\r\n");
    memset((void *)&g_mdio_registers, 0, sizeof(g_mdio_registers));
    memset((void *)g_mdio_mem0, 0x0, sizeof(g_mdio_mem0));
    memset((void *)g_mdio_mem1, 0x0, sizeof(g_mdio_mem1));
    memset((void *)g_mdio_mem2, 0x0, sizeof(g_mdio_mem2));
    memset((void *)g_mdio_mem3, 0x0, sizeof(g_mdio_mem3));
    g_mdio_registers.SETPHYADD = 0x10;
    g_mdio_registers.SETDEVADD = 0x0;
    g_mdio_registers.TIMERADDR  =(uint32_t)&CTIMER4_PERIPHERAL->TCR;
    g_mdio_registers.MDIODEBUG = (uint32_t)g_mdio_debug;
    g_mdio_registers.MEM0ADDR =(uint32_t)g_mdio_mem0;
    g_mdio_registers.MEM0SIZE = MEM0_SIZE;
    g_mdio_registers.MEM0ZONE = MEM0_ZONE;
    g_mdio_registers.MEM1ADDR =(uint32_t)g_mdio_mem1;
    g_mdio_registers.MEM1SIZE = MEM1_SIZE;
    g_mdio_registers.MEM1ZONE = MEM1_ZONE;
    g_mdio_registers.MEM2ADDR =(uint32_t)g_mdio_mem2;
    g_mdio_registers.MEM2SIZE = MEM2_SIZE;
    g_mdio_registers.MEM2ZONE = MEM2_ZONE;
    g_mdio_registers.MEM3ADDR =(uint32_t)g_mdio_mem3;
    g_mdio_registers.MEM3SIZE = MEM3_SIZE;
    g_mdio_registers.MEM3ZONE = MEM3_ZONE;
    g_mdio_registers.INTEN	  = (1<<0);
	PRINTF("g_mdio_registers.MEM0ADDR:0x%8x\r\n", g_mdio_registers.MEM0ADDR);
	PRINTF("g_mdio_registers.MEM1ADDR:0x%8x\r\n", g_mdio_registers.MEM1ADDR);
	PRINTF("g_mdio_registers.MEM2ADDR:0x%8x\r\n", g_mdio_registers.MEM2ADDR);
	PRINTF("g_mdio_registers.MEM3ADDR:0x%8x\r\n", g_mdio_registers.MEM3ADDR);

    /* Initialize components */

	SMARTDMA_InitWithoutFirmware();
	SMARTDMA_InstallFirmware(SMARTDMA_MDIO_MEM_ADDR,s_smartdmaMDIOFirmware,SMARTDMA_MDIO_FIRMWARE_SIZE);
	SMARTDMA_InstallCallback((smartdma_callback_t)SMARTDMA_Callbck, NULL);
	EnableIRQWithPriority(SMARTDMA_IRQn, 3);
	smartdmaParam.smartdma_stack = (uint32_t*)g_samrtdma_stack;
	smartdmaParam.p_registers_base_address = (uint32_t *)&g_mdio_registers;
	SMARTDMA_Boot(kSmartDMA_MDIO_Slave, &smartdmaParam, 0x2);

    while (1)
    {
        ch = GETCHAR();
        PUTCHAR(ch);
        for(uint32_t i=0; i<=64; i++)
        {
            PRINTF("OP:0x%8x; mem0[%2d]:0x%8x; mem1[%2d]:0x%8x; mem2[%2d]:0x%8x; mem3[%2d]:0x%8x; \r\n",g_mdio_debug[i], i,g_mdio_mem0[i], i,g_mdio_mem1[i],i, g_mdio_mem2[i],i, g_mdio_mem3[i]);
        }
    }
}
