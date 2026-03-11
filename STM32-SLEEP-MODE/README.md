# STM32 Sleep Mode Demo

This project demonstrates **low power operation using Sleep Mode** on an STM32 microcontroller.

The MCU enters sleep mode and wakes up using an **external interrupt from the user button**.

---

## Features

- STM32 Sleep Mode using `HAL_PWR_EnterSLEEPMode()`
- Wakeup using external interrupt
- UART debug messages
- LED indication for active state
- Power consumption measurement

---

## Working Principle

1. STM32 boots and initializes UART and GPIO.
2. A message is sent through UART indicating the system is active.
3. The MCU enters **Sleep Mode** using the `WFI` instruction.
4. The **user button interrupt** wakes the MCU.
5. After wake-up, the system resumes execution and sends a debug message.

---

## Power Consumption Measurement

Power consumption was measured using a **multimeter across the board supply line**.

| Mode | Current Consumption |
|-----|---------------------|
| Active Mode | ~0.31 A |
| Sleep Mode | ~0.17 A |

This confirms that **Sleep Mode reduces power consumption significantly** compared to active operation.

---

## Hardware Used

- STM32 Nucleo H7 board
- On-board LED
- On-board User Button
- USB connection via ST-Link
- Multimeter for current measurement

---

## Software Tools

- STM32CubeIDE
- STM32 HAL drivers
- Embedded C
