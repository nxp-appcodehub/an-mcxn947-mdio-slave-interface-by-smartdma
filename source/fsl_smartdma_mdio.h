/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_SMARTDMA_MDIO_H_
#define FSL_SMARTDMA_MDIO_H_

#include "fsl_common.h"

/*!
 * @addtogroup gpio
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
// Define a structure with bit fields

union mdio_inten
{
   uint32_t inten_register;
   struct 
   {
      bool frame_end_int_enable:  1; // FALSE / TRUE
      bool except_int_enable:  1; // 
      uint32_t reserved:  32; //
  }bit;
};

/** MDIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t RXOPCODE;         /**< MDIO received data Register, offset: 0x0 */
  __IO uint32_t RXPHYADD;         /**< MDIO received data Register, offset: 0x4 */
  __IO uint32_t RXDEVADD;         /**< MDIO received data Register, offset: 0x8 */
  __IO uint32_t RXDAT;         	  /**< MDIO received data Register, offset: 0xC */
  __IO uint32_t RXMEMADD;         /**< MDIO received address Register, offset: 0x10 */
  __IO uint32_t ADDINC;       	  /**< MDIO increase read address offset Register, offset: 0x14 */
  __IO uint32_t SETPHYADD;        /**< MDIO Test Register, offset: 0x18 */
  __IO uint32_t SETDEVADD;        /**< MDIO Test Register, offset: 0x1C */
  __IO uint32_t STA;       	      /**< MDIO Test Register, offset: 0x20 */
  __IO uint32_t INTEN;            /**< MDIO Test Register, offset: 0x24 */
  __IO uint32_t TIMERADDR;        /**< MDIO Memory 4 Zone Register, offset: 0x28 */
  __IO uint32_t MDIODEBUG;        /**< MDIO Memory 4 Zone Register, offset: 0x2C */
  __IO uint32_t RESERVED[4];        /**< MDIO Memory 4 Zone Register, offset: 0x30~0x40 */

  __IO uint32_t MEM0ADDR;         /**< MDIO Memory 0 Address Register, offset: 0x40 */
  __IO uint32_t MEM1ADDR;         /**< MDIO Memory 1 Address Register, offset: 0x44 */
  __IO uint32_t MEM2ADDR;         /**< MDIO Memory 2 Address Register, offset: 0x48 */
  __IO uint32_t MEM3ADDR;      	  /**< MDIO Memory 3 Address Register, offset: 0x4C */
  __IO uint32_t MEM4ADDR;         /**< MDIO Memory 4 Address Register, offset: 0x50 */
  __IO uint32_t MEM0SIZE;         /**< MDIO Memory 0 Size Register, offset: 0x54 */
  __IO uint32_t MEM1SIZE;         /**< MDIO Memory 1 Size Register, offset: 0x58 */
  __IO uint32_t MEM2SIZE;         /**< MDIO Memory 2 Size Register, offset: 0x5C */
  __IO uint32_t MEM3SIZE;         /**< MDIO Memory 3 Size Register, offset: 0x60 */
  __IO uint32_t MEM4SIZE;         /**< MDIO Memory 4 Size Register, offset: 0x64 */
  __IO uint32_t MEM0ZONE;         /**< MDIO Memory 0 Zone Register, offset: 0x68 */
  __IO uint32_t MEM1ZONE;         /**< MDIO Memory 1 Zone Register, offset: 0x6C */
  __IO uint32_t MEM2ZONE;         /**< MDIO Memory 2 Zone Register, offset: 0x70 */
  __IO uint32_t MEM3ZONE;         /**< MDIO Memory 3 Zone Register, offset: 0x74 */
  __IO uint32_t MEM4ZONE;         /**< MDIO Memory 4 Zone Register, offset: 0x78 */
} MDIO_Type;



/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif



#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* FSL_SMARTDMA_MDIO_H_*/
