/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 *\file spi.hpp
 *
 * hardware mock SPI class template used for testing drivers but also useful for other things
 *
 */
#ifndef SPI_HPP
#define SPI_HPP

#include <cstdint>
#include <cstddef>
#include <array>

enum class spiChipEnables : uint16_t {
  SPI_DEV_0 = 1,
  SPI_DEV_1 = 2,
  SPI_DEV_2 = 3,
  SPI_DEV_3 = 4,
};

template <size_t N, typename chipEnables>
class spi {
 public:
  spi() : transmitIndex{0}, receiveIndex{0} {}
  /**
   * @brief clears this simulated SPI peripheral
   *
   */
  void initialize(void) {
    for (auto& data : txTransactions) data = 0;
    for (auto& data : rxTransactions) data = 0;
    transmitIndex = 0;
    receiveIndex = 0;
    spiError = 0;
  }

  /**
   * @brief
   *
   * @param device
   * @param transmitBuffer
   * @param bitcount
   * @param lastAction
   */
  void transmit(chipEnables device, const uint16_t* transmitBuffer, uint16_t bitcount, bool lastAction) {
    // TODO: added spi error reporting
    size_t dataElementCount = bitcount / 16 + 1;
    txTransactions[transmitIndex++] = bitcount;
    txTransactions[transmitIndex++] = static_cast<uint16_t>(device);
    txTransactions[transmitIndex++] = static_cast<uint16_t>(lastAction);
    for (size_t i = 0; i < dataElementCount; i++) {
      txTransactions[transmitIndex++] = transmitBuffer[i];
    }
  }

  /**
   * @brief
   *
   * @param device
   * @param receiveBuffer
   * @param bitcount
   * @param lastAction
   */
  void receive(chipEnables device, uint16_t* receiveBuffer, uint16_t bitcount, bool lastAction) {
    // TODO: added spi error reporting
    // Put transaction data into transactionsReceive
    // compute index count
    // copy data in receive buffer
  }

  /**
   * @brief
   *
   * @param device
   * @param transmitBuffer
   * @param receiveBuffer
   * @param bitcount
   * @param lastAction
   */
  void transceive(chipEnables device, const uint16_t* transmitBuffer, uint16_t* receiveBuffer, uint16_t bitcount, bool lastAction) {
    // TODO: added spi error reporting
    // Put transaction data into transactionsReceive
    // compute index count for transmit and receive
    // copy data from transactionsReceive in receive buffer
    // put transmit buffer data in transactionsTransmit
  }

  /**
   * @brief Return amount of transmit transactions
   *
   * @return size_t
   */
  int txTransactionCount(void) {
    size_t index = transactionNext(txTransactions.data(), 0);
    int transactionCount = 0;
    // iterate through transmit transactions
    while (index != 0) {
      transactionCount++;
      index = transactionNext(txTransactions.data(), index);
      if (index == 0) {
        break;
      }
    }
    return transactionCount;
  }

  /**
   * @brief Get bit transfer count from transaction
   *
   * @param transaction transaction number,
   * @return uint16_t   transferred bits in transaction
   */
  uint16_t txTransactionGetBits(int transaction) {
    size_t index = transactionToIndex(txTransactions.data(), transaction);
    return txTransactions[index];
  }

  /**
   * @brief get chip enable from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   chip enable from transaction
   */
  uint16_t txTransactionGetChip(int transaction) {
    size_t index = transactionToIndex(txTransactions.data(), transaction);
    return txTransactions[index + 1];
  }
  /**
   * @brief get last transmission indicator from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   get last transmission indicator, 0 for not, non zero for last
   */
  uint16_t txTransactionGetLast(int transaction) {
    size_t index = transactionToIndex(txTransactions.data(), transaction);
    return txTransactions[index + 2];
  }
  /**
   * @brief get data from transaction
   *
   * @param transaction transaction number
   * @return uint16_t*  pointer to first bits in uint16_t array
   */
  uint16_t* txTransactionGetData(int transaction) {
    size_t index = transactionToIndex(txTransactions.data(), transaction);
    return &txTransactions[index + 3];
  }

  /**
   * @brief Add a transaction to be received
   *
   * @param device
   * @param transmitBuffer
   * @param bitcount
   * @param lastAction
   */
  void rxTransactionAdd(chipEnables device, const uint16_t* transmitBuffer, uint16_t bitcount, bool lastAction) {
    // TODO: added spi error reporting
    size_t dataElementCount = bitcount / 16 + 1;
    rxTransactions[receiveIndex++] = bitcount;
    rxTransactions[receiveIndex++] = static_cast<uint16_t>(device);
    rxTransactions[receiveIndex++] = static_cast<uint16_t>(lastAction);
    for (size_t i = 0; i < dataElementCount; i++) {
      rxTransactions[receiveIndex++] = transmitBuffer[i];
    }
  }

  int spiError; /**< error number if somebthing bad occurs TODO change to error enum */
  ::std::array<uint16_t, N> txTransactions;
  ::std::array<uint16_t, N> rxTransactions;
  size_t transmitIndex, receiveIndex; /**< BIT indices of where we are */

 private:
  /**
   * @brief Change transaction number to array index
   *
   * @param buffer      transaction buffer to inspect
   * @param transaction transaction number
   * @return size_t
   */
  size_t transactionToIndex(const uint16_t* buffer, int transaction) {
    size_t index = 0;
    int transactionCount = 1;
    // iterate through transmit transactions
    while (transactionCount < transaction) {
      index = transactionNext(buffer, index);
      if (index == 0) break;
      transactionCount++;
    }
    return index;
  }

  /**
   * @brief returns next transaction index
   *
   * @param buffer  transaction buffer to walk through
   * @param index   input index
   * @return size_t index of next transaction, 0 for end or invalid
   */
  size_t transactionNext(const uint16_t* buffer, size_t index) {
    if (buffer[index] == 0) return 0;
    size_t newIndex = index + (buffer[index] / 16) + 4;
    if (newIndex > N) return 0;
    return newIndex;
  }
};

#endif