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

  void init(const uint8_t *initCommands, uint16_t initCommandLength) {
    sendCommands(initCommands, initCommandLength);
  }

  void writeWindow(uint8_t xBegin, uint8_t xEnd, uint8_t yBegin, uint8_t yEnd, const uint8_t *data, uint16_t length) {
    uint8_t setPointer[] = {
      SSD1306::setPageAddress, (uint8_t)(yBegin >> 3), (uint8_t)(yEnd >> 3), SSD1306::setColumnAddress, xBegin, xEnd};
    sendCommands(setPointer, sizeof(setPointer));
    sendData(data, length);
  }

  void update() {}
};

}  // namespace SSD1306
}  // namespace util

#endif