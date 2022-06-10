/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef SSD1306_DIRECT_HPP
#define SSD1306_DIRECT_HPP

#include <cstdint>
#include <cstddef>
#include "drivers/SSD1306/SSD1306.hpp"
#include "array.hpp"

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
    int normYBegin = yBegin >> 3;
    int normYEnd = yEnd >> 3;
    for (int i = normYBegin; i <= normYEnd; i++) {
      for (int j = xBegin; j <= xEnd; j++) {
        int index = i * (maxX) + j;
        frameBuffer[index] = *data;
        ++data;
        --length;
        if (length == 0) {
          return;
        }
      }
    }
  }

  void update() {
    uint8_t setPointer[] = {SSD1306::setPageAddress, 0, (maxY - 1) >> 3, SSD1306::setColumnAddress, 0, maxX - 1};
    sendCommands(setPointer, sizeof(setPointer));
    sendData(frameBuffer.data(), frameBuffer.size());
  }

  void clear(uint8_t clearColor) {
    for (uint8_t &data : frameBuffer) data = clearColor;
  }

  array<uint8_t, ((config::maxY) / 8) * (config::maxX)> frameBuffer;
  static const uint8_t maxX = config::maxX;
  static const uint8_t maxY = config::maxY;
};

}  // namespace SSD1306
}  // namespace util

#endif