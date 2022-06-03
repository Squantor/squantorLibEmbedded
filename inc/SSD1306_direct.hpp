/*
SPDX-License-Identifier: MIT

Copyright (c) 2022 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef SSD1306_DIRECT_HPP
#define SSD1306_DIRECT_HPP

#include <cstdint>
#include <cstddef>

namespace util {
namespace SSD1306 {

constexpr uint8_t setVcomDeselectLevel = 0xDB;
consteval uint8_t vcomDeselectLevel(uint8_t level) {
  return (level & 0x07) << 4;
}
constexpr uint8_t setComPinsHardware = 0xDA;
enum comPinMapping : uint8_t {
  sequentialNormal = 0x00,
  sequentialRemapped = 0x20,
  alternatingNormal = 0x10,
  alternatingRemapped = 0x30,
};
consteval uint8_t ComPinsHardware(comPinMapping setting) {
  return 0x02 | setting;
}

constexpr uint8_t setDisplayClockDivide = 0xD5;
consteval uint8_t displayClockDivisor(uint8_t ratio) {
  return ratio;
}

constexpr uint8_t setPrechargeLevel = 0xD9;
consteval uint8_t prechargeLevel(uint8_t level) {
  return level;
}

constexpr uint8_t setDisplayOffset = 0xD3;
consteval uint8_t displayOffset(uint8_t offset) {
  return offset;
}

enum scanDirection : uint8_t {
  normalDirection = 0x00,
  remappedDirection = 0x08,
};

consteval uint8_t comOutputScanDirection(scanDirection mode) {
  return mode | 0xC0;
}

consteval uint8_t setPageStart(uint8_t address) {
  return (address & 0x07) | 0xB0;
}
constexpr uint8_t displayActive = 0xAF;     /*!< turn display on */
constexpr uint8_t displaySleep = 0xAE;      /*!< turn display off */
constexpr uint8_t setMultiplexRatio = 0xA8; /*!< multiplex ratio */
consteval uint8_t multiplexRatio(uint8_t ratio) {
  return ratio;
}
constexpr uint8_t displayInvert = 0xA7; /*!< invert display */
constexpr uint8_t displayNormal = 0xA6; /*!< normal display */
constexpr uint8_t displayRam = 0xA5;    /*!< display RAM content */
constexpr uint8_t displayOn = 0xA4;     /*!< turn all pixels on */

enum segmentMapping : uint8_t {
  column0 = 0,  /*!< Segment 0 mapped to column address 0 */
  column127 = 1 /*!< Segment 0 mapped to column address 127 */
};
/*!< @brief set segment remapping */
consteval uint8_t setSegmentRemap(segmentMapping mapping) {
  return mapping | 0xA0;
}
constexpr uint8_t setChargePump = 0x8D; /*!< set charge pump state */
consteval uint8_t chargePumpOn(bool pumpOn) {
  if (pumpOn)
    return 0x14;
  else
    return 0x10;
}
constexpr uint8_t setContrast = 0x81; /*!< set contrast level */
consteval uint8_t ConstrastLevel(uint8_t level) {
  return level;
}
consteval uint8_t setDisplayStartLine(uint8_t address) {
  return (address & 0x3F) | 0x40;
}
constexpr uint8_t scrollOn = 0x2F;
constexpr uint8_t scrollOff = 0x2E;
constexpr uint8_t setPageAddress = 0x22;
constexpr uint8_t setColumnAddress = 0x21;
constexpr uint8_t setMemoryAddressingMode = 0x20;

enum addressingModes : uint8_t {
  horizontalMode = 0, /*!< Horizontal addressing mode */
  verticalMode = 1,   /*!< vertical addressing mode */
  pageMode = 2,       /*!< page addressing mode */
  invalidMode = 3,    /*!< INVALID! DO NOT USE! */
};

consteval uint8_t AddressingMode(addressingModes mode) {
  return mode;
}

consteval uint8_t higherColumnAddress(uint8_t address) {
  return (address & 0x0F) | 0x10;
}

consteval uint8_t lowerColumnAddress(uint8_t address) {
  return (address & 0x0F) | 0x00;
}

const uint8_t init128x64[] = {SSD1306::displaySleep,
                              SSD1306::setDisplayClockDivide,
                              SSD1306::displayClockDivisor(0x80),
                              SSD1306::setMultiplexRatio,
                              SSD1306::multiplexRatio(63),
                              SSD1306::setDisplayOffset,
                              SSD1306::displayOffset(0),
                              SSD1306::setDisplayStartLine(0),
                              SSD1306::setChargePump,
                              SSD1306::chargePumpOn(true),
                              SSD1306::setMemoryAddressingMode,
                              SSD1306::AddressingMode(SSD1306::horizontalMode),
                              SSD1306::setSegmentRemap(SSD1306::column127),
                              SSD1306::comOutputScanDirection(SSD1306::remappedDirection),
                              SSD1306::setComPinsHardware,
                              SSD1306::ComPinsHardware(SSD1306::alternatingNormal),
                              SSD1306::setContrast,
                              SSD1306::ConstrastLevel(0x01),
                              SSD1306::setPrechargeLevel,
                              SSD1306::prechargeLevel(0xF1),
                              SSD1306::setVcomDeselectLevel,
                              SSD1306::vcomDeselectLevel(4),
                              SSD1306::displayOn,
                              SSD1306::displayNormal,
                              SSD1306::scrollOff,
                              SSD1306::displayActive};
const uint8_t init128x32[] = {SSD1306::displaySleep,
                              SSD1306::setDisplayClockDivide,
                              SSD1306::displayClockDivisor(0x80),
                              SSD1306::setMultiplexRatio,
                              SSD1306::multiplexRatio(31),
                              SSD1306::setDisplayOffset,
                              SSD1306::displayOffset(0),
                              SSD1306::setDisplayStartLine(0),
                              SSD1306::setChargePump,
                              SSD1306::chargePumpOn(true),
                              SSD1306::setMemoryAddressingMode,
                              SSD1306::AddressingMode(SSD1306::horizontalMode),
                              SSD1306::setSegmentRemap(SSD1306::column127),
                              SSD1306::comOutputScanDirection(SSD1306::remappedDirection),
                              SSD1306::setComPinsHardware,
                              SSD1306::ComPinsHardware(SSD1306::sequentialNormal),
                              SSD1306::setContrast,
                              SSD1306::ConstrastLevel(0x01),
                              SSD1306::setPrechargeLevel,
                              SSD1306::prechargeLevel(0xF1),
                              SSD1306::setVcomDeselectLevel,
                              SSD1306::vcomDeselectLevel(4),
                              SSD1306::displayOn,
                              SSD1306::displayNormal,
                              SSD1306::scrollOff,
                              SSD1306::displayActive};

template <uint8_t i2cAddress>
struct display {
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
};

}  // namespace SSD1306
}  // namespace util

#endif