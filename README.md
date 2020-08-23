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

- [x] Check/Simulate performance bottle necks for Mega
- [ ] Temperature logger, serial & MaxC based
- [ ] Integrate PID/Auto-tune
  - [ ] EEprom storage ?
- [ ] Debug interface via RS485
- [ ] Data - reader via RS232 (Matlab)
- [ ] Configuration (remote / local) -> Control-Freak - HMI
- [ ] Model testing/verification

## Edge cases / Errors

- [ ] PID-Partition Timeout : PID didn't reach target with limits
- [ ] PID/Partition Overshooting : PID or operator malfunction
- [ ] PID Auto-tuning timeout : autotuning too long
- [ ] PID/Partition interference : partition overlap noise ?

## Modes

- [ ] Groups (partition groups)
- [ ] Serial (single linked partition group)
- [ ] Remote (HMI & control)

## PP/PH

### New parameters

- [ ] Ramp-time
- [ ] Amp Budget

### New beahviours

- [ ] Currently there are multiple issues surfacing regarding the sheetpress. A profile should allow to have multiple target temperature points (eg: 1 hour to hold softening point, 30 mins for holding melting point rage, 10 mins for slightly over melting point : pressing phase) with a holding & ramp time each.
- [ ] The user should be able to adjust these profiles per flake size. For that we should also study the effects of various flake sizes regarding stresses created in the sheets.

### References

- [PID research](https://github.com/plastic-hub/research#pid-control)
