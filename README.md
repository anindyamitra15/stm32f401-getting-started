# Getting started with STM32F401

## Introduction
This is a repository where various features of STM32f401 are demonstrated with the help of simple projects. All the projects are developed for [Black Pill](https://stm32-base.org/boards/STM32F401CCU6-WeAct-Black-Pill-V1.2.html), based on STM32F401CCU6.
## Contents
```
|_ blink-timer-interrupt
|_ pwm_dma
``` 
1. [Blink using Timer Interrupt](./blink-timer-interrupt/): It is an LED blink program which is implemented using hardware timer interrupt.
<br/>![Demo-Blink](./blink-timer-interrupt/Results/demo.gif)<br/>

2. [DMA PWM](./pwm_dma/): It is an LED fade program that keeps the CPU free and uses DMA to copy the PWM duty cycle values from a lookup table in the memory, in a cyclic mode.
<br/>![Demo-DMA-PWM](./pwm_dma/Results/demo.gif)<br/>

3. [sPWM Continuous Mode](./sPWM-1/): 50Hz sPWM (sinusoidal PWM) generation using DMA transferred PWM. Useful for building a basic sPWM inverter circuit which can generate 50Hz sine wave signal.
<br/>![Demo-sPWM-1](./sPWM-1/Results/logic_analyser.gif)<br/>

4. [sPWM Push Pull Mode](./sPWM-2/): Push pull mode 50Hz sPWM (sinusoidal PWM) generation using DMA transferred PWM. Useful for building a basic sPWM inverter circuit which can work in a push-pull (saving on the number of FETs, double-ended push-pull vs h-bridge switching, which are the main types of switching used in UPSs) mode and can generate a sine wave of 50Hz
<br/>![Demo-sPWM-2](./sPWM-2/Results/Demo.gif)<br/>

<hr>

## Other experiments:

Also checkout my work with STM32F1: [STM32F103 RTOS](https://github.com/anindyamitra15/stm32-rtos), [STM32F103 UART](https://github.com/anindyamitra15/stm32-uart) and, [STM32 GPIO Alternate Functions](https://github.com/anindyamitra15/stm32-gpio-modes)
