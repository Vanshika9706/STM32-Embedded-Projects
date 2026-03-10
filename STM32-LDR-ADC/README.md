# STM32 LDR Sensor Interfacing using ADC

## Overview

This project demonstrates how to interface a Light Dependent Resistor (LDR) with an STM32 microcontroller using the ADC peripheral.

The analog voltage from the LDR voltage divider is converted into a digital value by the STM32 ADC. The measured light intensity values are transmitted via UART for monitoring.

## Hardware Components

* STM32 Nucleo Board
* LDR (Light Dependent Resistor) module
* Breadboard
* Jumper wires

## Circuit Principle

The LDR forms a voltage divider with a fixed resistor. As light intensity changes, the resistance of the LDR changes, which alters the voltage at the ADC input pin.

The STM32 ADC converts this voltage into a digital value representing light intensity.

## Features

* ADC peripheral configuration
* Analog sensor interfacing
* Light intensity monitoring
* UART debugging output

## Concepts Demonstrated

* STM32 peripheral configuration
* Analog-to-Digital Conversion
* Sensor interfacing
* Embedded firmware development
