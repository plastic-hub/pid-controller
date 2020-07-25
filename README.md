# Multichannel PID controller

Purpose of this PID controller is to lower overall amperage by cycling periodically through SSRs.

This is based on [osPID](http://ospid.com/blog/download/)

### Hardware

- [Controllino - Mega (Arduino compatible)](https://www.controllino.biz/product/controllino-mega/). [See PIN layout](./vendor/controllino/CONTROLLINO-MEGA-Pinout-1.jpg)

![](./vendor/controllino/mega.jpg)

- Optional: OLED & keypad control
- 8 channels
- Optional: Modbus
- TC sensor module, MAX6675 | MAX31855

## Features

### PID

- Autotune per PID
- Support for multiple TCs (see Marlin firmware)

### Configuration

- Set max Amp
- Set max/min heat time per cell/partition

## Milestones / Todos

- [ ] Check/Simulate performance bottle necks for Mega
- [ ] Integrate PID/Auto-tune
   - [ ] EEprom storage ?
- [ ] Debug interface via RS485
- [ ] Data - reader via RS232 (Matlab)
- [ ] Configuration (remote / local) -> Control-Freak - HMI
- [ ] Model testing/verification

