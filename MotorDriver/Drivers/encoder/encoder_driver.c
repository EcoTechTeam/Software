/*
 * encoder_driver.c
 */


#include "encoder_driver.h"


void ENC_Init(void)
{

	/*!
	 * ENCA_PIN = GPIOB_PIN7
	 * ENCB_PIN = GPIOB_PIN6
	 * ENCI_PIN = GPIOB_PIN5
	 *
	 * CNF1		CNF0	MODE1	MODE0	ODR
	 * 1		0		0		0		0
	 *
	 * Input pull-up
	 */
	ENC_GPIO->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_CNF6 | GPIO_CRL_CNF5);
	ENC_GPIO->CRL |= GPIO_CRL_CNF7_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF5_1;
	ENC_GPIO->BSRR = ENCA_PIN | ENCB_PIN | ENCI_PIN;

	//! ENCA and ENCB timer configuration
	ENC_TIM->CCMR1 |= TIM_CCMR1_CC2S_0 | TIM_CCMR1_CC1S_0;
	ENC_TIM->SMCR |= TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0;
	ENC_TIM->CNT = 0;
	ENC_TIM->CR1 |= TIM_CR1_CEN;

	//! ENCI interrupt configuration
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI5_PB;
	EXTI->RTSR |= EXTI_RTSR_TR5;
	EXTI->IMR |= EXTI_IMR_MR5;
	NVIC_EnableIRQ(EXTI9_5_IRQn);
}


int16_t ENC_ReadAndReset(void)
{
	int16_t val = ENC_TIM->CNT;
	ENC_TIM->CNT = 0;
	return val;
}


int16_t ENC_Read(void)
{
	return ENC_TIM->CNT;
}


void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR5)
	{
		if(ENC_GPIO->IDR & ENCI_PIN) ENC_FullRotation();
		EXTI->PR |= EXTI_PR_PR5;
	}
}
