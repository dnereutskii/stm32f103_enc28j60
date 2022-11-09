/**
  ******************************************************************************
  * @file    stm32f1xx.h
  * @author  MCD Application Team
  * @brief   CMSIS STM32F1xx Device Peripheral Access Layer Header File. 
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *            - Configuration section that allows to select:
  *              - The STM32F1xx device used in the target application
  *              - To use or not the peripheral�s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral�s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_HAL_DRIVER"
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f1xx
  * @{
  */
    
#ifndef __STM32F1XX_H
#define __STM32F1XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */

/**
  * @brief STM32 Family
  */
#if !defined (STM32F1)
#define STM32F1
#endif /* STM32F1 */

/* Uncomment the line below according to the target STM32L device used in your 
   application 
  */

#if !defined (STM32F100xB) && !defined (STM32F100xE) && !defined (STM32F101x6) && \
    !defined (STM32F101xB) && !defined (STM32F101xE) && !defined (STM32F101xG) && !defined (STM32F102x6) && !defined (STM32F102xB) && !defined (STM32F103x6) && \
    !defined (STM32F103xB) && !defined (STM32F103xE) && !defined (STM32F103xG) && !defined (STM32F105xC) && !defined (STM32F107xC)
  /* #define STM32F100xB  */   /*!< STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6, STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB, STM32F100RB and STM32F100VB */
  /* #define STM32F100xE */    /*!< STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD, STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE and STM32F100ZE */
  /* #define STM32F101x6  */   /*!< STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6, STM32F101R6 and STM32F101T6 Devices */
  /* #define STM32F101xB  */   /*!< STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8, STM32F101CB, STM32F101RB, STM32F101TB and STM32F101VB */
  /* #define STM32F101xE */    /*!< STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD, STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE and STM32F101ZE */ 
  /* #define STM32F101xG  */   /*!< STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG, STM32F101VG and STM32F101ZG */
  /* #define STM32F102x6 */    /*!< STM32F102C4, STM32F102R4, STM32F102C6 and STM32F102R6 */
  /* #define STM32F102xB  */   /*!< STM32F102C8, STM32F102R8, STM32F102CB and STM32F102RB */
  /* #define STM32F103x6  */   /*!< STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6, STM32F103R6 and STM32F103T6 */
  #define STM32F103xB  /*!< STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8, STM32F103CB, STM32F103RB, STM32F103TB and STM32F103VB */
  /* #define STM32F103xE */    /*!< STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD, STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE and STM32F103ZE */
  /* #define STM32F103xG  */   /*!< STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG, STM32F103VG and STM32F103ZG */
  /* #define STM32F105xC */    /*!< STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB, STM32F105RC and STM32F105VC */
  /* #define STM32F107xC  */   /*!< STM32F107RB, STM32F107VB, STM32F107RC and STM32F107VC */  
#endif

/*  Tip: To avoid modifying this file each time you need to switch between these
        devices, you can define the device in your toolchain compiler preprocessor.
  */
  
#if !defined  (USE_HAL_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will 
   be based on direct access to peripherals registers 
   */
  /*#define USE_HAL_DRIVER */
#endif /* USE_HAL_DRIVER */

/**
  * @brief CMSIS Device version number V4.3.1
  */
#define __STM32F1_CMSIS_VERSION_MAIN   (0x04) /*!< [31:24] main version */
#define __STM32F1_CMSIS_VERSION_SUB1   (0x03) /*!< [23:16] sub1 version */
#define __STM32F1_CMSIS_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32F1_CMSIS_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32F1_CMSIS_VERSION        ((__STM32F1_CMSIS_VERSION_MAIN << 24)\
                                       |(__STM32F1_CMSIS_VERSION_SUB1 << 16)\
                                       |(__STM32F1_CMSIS_VERSION_SUB2 << 8 )\
                                       |(__STM32F1_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32F100xB)
  #include "stm32f100xb.h"
#elif defined(STM32F100xE)
  #include "stm32f100xe.h"
#elif defined(STM32F101x6)
  #include "stm32f101x6.h"
#elif defined(STM32F101xB)
  #include "stm32f101xb.h"
#elif defined(STM32F101xE)
  #include "stm32f101xe.h"
#elif defined(STM32F101xG)
  #include "stm32f101xg.h"
#elif defined(STM32F102x6)
  #include "stm32f102x6.h"
#elif defined(STM32F102xB)
  #include "stm32f102xb.h"
#elif defined(STM32F103x6)
  #include "stm32f103x6.h"
#elif defined(STM32F103xB)
  #include "stm32f103xb.h"
#elif defined(STM32F103xE)
  #include "stm32f103xe.h"
#elif defined(STM32F103xG)
  #include "stm32f103xg.h"
#elif defined(STM32F105xC)
  #include "stm32f105xc.h"
#elif defined(STM32F107xC)
  #include "stm32f107xc.h"
#else
 #error "Please select first the target STM32F1xx device used in your application (in stm32f1xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */  
typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 

#define MASK_TO_BIT31(A)        (A==0x80000000)? 31 : 0
#define MASK_TO_BIT30(A)        (A==0x40000000)? 30 : MASK_TO_BIT31(A)
#define MASK_TO_BIT29(A)        (A==0x20000000)? 29 : MASK_TO_BIT30(A)
#define MASK_TO_BIT28(A)        (A==0x10000000)? 28 : MASK_TO_BIT29(A)
#define MASK_TO_BIT27(A)        (A==0x08000000)? 27 : MASK_TO_BIT28(A)
#define MASK_TO_BIT26(A)        (A==0x04000000)? 26 : MASK_TO_BIT27(A)
#define MASK_TO_BIT25(A)        (A==0x02000000)? 25 : MASK_TO_BIT26(A)
#define MASK_TO_BIT24(A)        (A==0x01000000)? 24 : MASK_TO_BIT25(A)
#define MASK_TO_BIT23(A)        (A==0x00800000)? 23 : MASK_TO_BIT24(A)
#define MASK_TO_BIT22(A)        (A==0x00400000)? 22 : MASK_TO_BIT23(A)
#define MASK_TO_BIT21(A)        (A==0x00200000)? 21 : MASK_TO_BIT22(A)
#define MASK_TO_BIT20(A)        (A==0x00100000)? 20 : MASK_TO_BIT21(A)
#define MASK_TO_BIT19(A)        (A==0x00080000)? 19 : MASK_TO_BIT20(A)
#define MASK_TO_BIT18(A)        (A==0x00040000)? 18 : MASK_TO_BIT19(A)
#define MASK_TO_BIT17(A)        (A==0x00020000)? 17 : MASK_TO_BIT18(A)
#define MASK_TO_BIT16(A)        (A==0x00010000)? 16 : MASK_TO_BIT17(A)
#define MASK_TO_BIT15(A)        (A==0x00008000)? 15 : MASK_TO_BIT16(A)
#define MASK_TO_BIT14(A)        (A==0x00004000)? 14 : MASK_TO_BIT15(A)
#define MASK_TO_BIT13(A)        (A==0x00002000)? 13 : MASK_TO_BIT14(A)
#define MASK_TO_BIT12(A)        (A==0x00001000)? 12 : MASK_TO_BIT13(A)
#define MASK_TO_BIT11(A)        (A==0x00000800)? 11 : MASK_TO_BIT12(A)
#define MASK_TO_BIT10(A)        (A==0x00000400)? 10 : MASK_TO_BIT11(A)
#define MASK_TO_BIT09(A)        (A==0x00000200)? 9  : MASK_TO_BIT10(A)
#define MASK_TO_BIT08(A)        (A==0x00000100)? 8  : MASK_TO_BIT09(A)
#define MASK_TO_BIT07(A)        (A==0x00000080)? 7  : MASK_TO_BIT08(A)
#define MASK_TO_BIT06(A)        (A==0x00000040)? 6  : MASK_TO_BIT07(A)
#define MASK_TO_BIT05(A)        (A==0x00000020)? 5  : MASK_TO_BIT06(A)
#define MASK_TO_BIT04(A)        (A==0x00000010)? 4  : MASK_TO_BIT05(A)
#define MASK_TO_BIT03(A)        (A==0x00000008)? 3  : MASK_TO_BIT04(A)
#define MASK_TO_BIT02(A)        (A==0x00000004)? 2  : MASK_TO_BIT03(A)
#define MASK_TO_BIT01(A)        (A==0x00000002)? 1  : MASK_TO_BIT02(A)
#define MASK_TO_BIT(A)          (A==0x00000001)? 0  : MASK_TO_BIT01(A)

#define	BIT_BAND_PER(reg, reg_val)	(*(volatile uint32_t*)(PERIPH_BB_BASE + \
                                    32 * ((uint32_t)(&(reg))-PERIPH_BASE) + \
                                    4 * ((uint32_t)(MASK_TO_BIT(reg_val)))))
/**
  * @}
  */

#if defined (USE_HAL_DRIVER)
 #include "stm32f1xx_hal.h"
#endif /* USE_HAL_DRIVER */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32F1xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
