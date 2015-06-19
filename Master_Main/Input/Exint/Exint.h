/*
 * Exint.h
 *
 * Created: 2014/06/19 18:12:03
 *  Author: tatsuro
 */ 


#ifndef EXINT_H_
#define EXINT_H_

#include "../../globalDef.h"

#if defined(INT0_BIT)
static void ExintInitialize0(void);
#endif
#if defined(INT1_BIT)
static void ExintInitialize1(void);
#endif
#if defined(INT2_BIT)
static void ExintInitialize2(void);
#endif
#if defined(INT3_BIT)
static void ExintInitialize3(void);
#endif
#if defined(INT4_BIT)
static void ExintInitialize4(void);
#endif
#if defined(INT5_BIT)
static void ExintInitialize5(void);
#endif
#if defined(INT6_BIT)
static void ExintInitialize6(void);
#endif
#if defined(INT7_BIT)
static void ExintInitialize7(void);
#endif

#endif /* EXINT_H_ */