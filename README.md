# Getting started with STM32F401

## Introduction
This is a repository where features of STM32f401 is demonstrated with the help of simple, easy to implement projects.
## Contents
```
|_ blink-timer-interrupt
|_ pwm_dma
``` 
1. [Blink using Timer Interrupt](./blink-timer-interrupt/): It is an LED blink program which is implemented using hardware timer interrupt.
![Demo-Blink](./blink-timer-interrupt/Results/demo.gif)
2. [DMA PWM](./pwm_dma/): It is an LED fade program that keeps the CPU free and uses DMA to copy the PWM duty cycle values from a lookup table in the memory, in a cyclic mode.
![Demo-DMA-PWM](./pwm_dma/Results/demo.gif)