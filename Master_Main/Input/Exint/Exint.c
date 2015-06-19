/*
 * Exint.c
 *
 * Created: 2014/06/19 18:12:14
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_EXINT)

#include "./Exint.h"
#include "./ExintDef.h"

void (*ExintInitialize[8])(void);

void ExintSetup(void) {
	#if defined(INT0_BIT)
		ExintInitialize[0] = ExintInitialize0;
	#endif
	#if defined(INT1_BIT)
		ExintInitialize[1] = ExintInitialize1;
	#endif
	#if defined(INT2_BIT)
		ExintInitialize[2] = ExintInitialize2;
	#endif
	#if defined(INT3_BIT)
		ExintInitialize[3] = ExintInitialize3;
	#endif
	#if defined(INT4_BIT)
		ExintInitialize[4] = ExintInitialize4;
	#endif
	#if defined(INT5_BIT)
		ExintInitialize[5] = ExintInitialize5;
	#endif
	#if defined(INT6_BIT)
		ExintInitialize[6] = ExintInitialize6;
	#endif
	#if defined(INT7_BIT)
		ExintInitialize[7] = ExintInitialize7;
	#endif
}

#if defined(INT0_BIT)
static void ExintInitialize0(void) {
	sbi(*EXINT.EXIMSK, INT0_BIT);
	sbi(*EXINT.EXICRA, ISC01_BIT);
	sbi(*EXINT.EXICRA, ISC00_BIT);
}
#endif

#if defined(INT1_BIT)
static void ExintInitialize1(void) {
	sbi(*EXINT.EXIMSK, INT1_BIT);
	sbi(*EXINT.EXICRA, ISC11_BIT);
	sbi(*EXINT.EXICRA, ISC10_BIT);
}
#endif

#if defined(INT2_BIT)
static void ExintInitialize2(void) {
	sbi(*EXINT.EXIMSK, INT2_BIT);
	sbi(*EXINT.EXICRA, ISC21_BIT);
	sbi(*EXINT.EXICRA, ISC20_BIT);
}
#endif

#if defined(INT3_BIT)
static void ExintInitialize3(void) {
	sbi(*EXINT.EXIMSK, INT3_BIT);
	sbi(*EXINT.EXICRA, ISC31_BIT);
	sbi(*EXINT.EXICRA, ISC30_BIT);
}
#endif

#if defined(INT4_BIT)
static void ExintInitialize4(void) {
	sbi(*EXINT.EXIMSK, INT4_BIT);
	sbi(*EXINT.EXICRB, ISC41_BIT);
	sbi(*EXINT.EXICRB, ISC40_BIT);
}
#endif

#if defined(INT5_BIT)
static void ExintInitialize5(void) {
	sbi(*EXINT.EXIMSK, INT5_BIT);
	sbi(*EXINT.EXICRB, ISC51_BIT);
	sbi(*EXINT.EXICRB, ISC50_BIT);
}
#endif

#if defined(INT6_BIT)
static void ExintInitialize6(void) {
	sbi(*EXINT.EXIMSK, INT6_BIT);
	sbi(*EXINT.EXICRB, ISC61_BIT);
	sbi(*EXINT.EXICRB, ISC60_BIT);
}
#endif

#if defined(INT7_BIT)
static void ExintInitialize7(void) {
	sbi(*EXINT.EXIMSK, INT7_BIT);
	sbi(*EXINT.EXICRB, ISC71_BIT);
	sbi(*EXINT.EXICRB, ISC70_BIT);
}
#endif

#endif
