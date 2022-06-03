/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef SSD1306_DIRECT_HPP
#define SSD1306_DIRECT_HPP

#include <cstdint>
#include <cstddef>
#include <drivers/SSD1306/SSD1306.hpp>
#include <array.hpp>

namespace util {
namespace SSD1306 {

template <uint8_t i2cAddress, typename config>
struct display {
  void init() {
    sendCommands(config::init, config::initLength);
  }

  uint32_t startI2CTransfer(I2C_Type *peripheral, uint8_t address) {
    uint32_t busStatus;
    i2cSetMasterData(peripheral, address);
    i2cSetMasterControl(peripheral, I2C_MSCTL_MSTSTART);
    do {
      busStatus = i2cGetStatus(peripheral);
    } while (((busStatus & (I2C_STAT_MSTPENDING | I2C_STAT_EVENTTIMEOUT | I2C_STAT_SCLTIMEOUT)) == 0));
    return busStatus;
  }

  uint8_t sendI2CData(I2C_Type *peripheral, uint8_t data) {
    uint32_t busStatus;
    i2cSetMasterData(peripheral, data);
    i2cSetMasterControl(peripheral, I2C_MSCTL_MSTCONTINUE);
    do {
      busStatus = i2cGetStatus(peripheral);
    } while (((busStatus & (I2C_STAT_MSTPENDING | I2C_STAT_EVENTTIMEOUT | I2C_STAT_SCLTIMEOUT)) == 0));
    return busStatus;
  }

  void stopI2CTransfer(I2C_Type *peripheral) {
    i2cSetMasterControl(peripheral, I2C_MSCTL_MSTSTOP);
  }

  uint8_t sendCommands(const uint8_t *data, uint16_t length) {
    uint16_t dataIndex = 0;
    uint32_t busStatus;
    busStatus = startI2CTransfer(I2C0, i2cAddress);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    busStatus = sendI2CData(I2C0, 0x00);  // Command setup
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    do {
      busStatus = sendI2CData(I2C0, data[dataIndex]);
      if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
      dataIndex++;
    } while (dataIndex < length);
  i2cStop:
    stopI2CTransfer(I2C0);
    return busStatus;
  }

  uint8_t sendData(const uint8_t *data, uint16_t length) {
    uint16_t dataIndex = 0;
    uint32_t busStatus;
    busStatus = startI2CTransfer(I2C0, i2cAddress);
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    busStatus = sendI2CData(I2C0, 0x40);  // data write
    if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
    do {
      busStatus = sendI2CData(I2C0, data[dataIndex]);
      if ((I2C_STAT_MSTSTATE(busStatus) != I2C_STAT_MSSTATE_TRANSMIT_READY)) goto i2cStop;
      dataIndex++;
    } while (dataIndex < length);
  i2cStop:
    stopI2CTransfer(I2C0);
    return busStatus;
  }

  void writeWindow(uint8_t xBegin, uint8_t xEnd, uint8_t yBegin, uint8_t yEnd, const uint8_t *data, uint16_t length) {
    for (int i = yBegin; i < yEnd; i++) {
      for (int j = xBegin; j < xEnd; j++) {
        int index = 
      }
    }
  }

  void update() {
    uint8_t setPointer[] = {SSD1306::setPageAddress, 0, maxY >> 3, SSD1306::setColumnAddress, 0, maxX};
    sendCommands(setPointer, sizeof(setPointer));
    sendData(frameBuffer.data(), frameBuffer.size());
  }

  array<uint8_t, ((config::maxX / 8) + 1) * config::maxY> frameBuffer;
  static const uint8_t maxX = config::maxX;
  static const uint8_t maxY = config::maxY;
};

}  // namespace SSD1306
}  // namespace util

#endif