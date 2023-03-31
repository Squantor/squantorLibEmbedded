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
#include <span>

enum class spiChipEnables : uint16_t {
  SPI_DEV_0 = 1,
  SPI_DEV_1 = 2,
  SPI_DEV_2 = 3,
  SPI_DEV_3 = 4,
};

enum class spiErrors {
  noError = 0,
  transactionNotFound = -1,
  transactionInvalid = -2,
  mismatch = -3,
};

template <size_t N, typename chipEnables>
class spi {
 public:
  /**
   * @brief Construct a new spi object
   *
   */
  spi() : spiError{spiErrors::noError}, transmitIndex{0}, receiveIndex{0}, currentReceiveIndex{0} {}
  /**
   * @brief clears this simulated SPI peripheral
   *
   */
  void initialize(void) {
    txTransactions.fill(0);
    rxTransactions.fill(0);
    transmitIndex = 0;
    receiveIndex = 0;
    spiError = spiErrors::noError;
    currentReceiveIndex = 0;
  }

  /**
   * @brief Transmit data to SPI
   *
   * @param device SPI device to transmit to
   * @param transmitBuffer data to transmit
   * @param bitcount amount of bits to transmit
   * @param lastAction is this the last action? This will disable the chip select
   */
  void transmit(chipEnables device, const std::span<uint16_t> transmitBuffer, uint16_t bitcount, bool lastAction) {
    transactionAdd(txTransactions, transmitIndex, device, transmitBuffer, bitcount, lastAction);
  }

  /**
   * @brief Receive data from SPI
   *
   * @param device SPI device to receive data from
   * @param receiveBuffer buffer to put data into
   * @param bitcount amount of bits to receive
   * @param lastAction is this the last action? This will disable the chip select
   */
  void receive(chipEnables device, std::span<uint16_t> receiveBuffer, uint16_t bitcount, bool lastAction) {
    int nextTransaction = transactionNext(rxTransactions, currentReceiveIndex);

    if (nextTransaction == 0) {
      spiError = spiErrors::transactionNotFound;
      return;
    }

    chipEnables receiveEnable;
    uint16_t receiveBitcount;
    bool receiveLastAction;

    transactionGet(rxTransactions, currentReceiveIndex, receiveEnable, receiveBuffer, receiveBitcount, receiveLastAction);

    // compare the retrieved transaction with what you expect
    if (device != receiveEnable) {
      spiError = spiErrors::mismatch;
      return;
    }
    if (receiveBitcount != bitcount) {
      spiError = spiErrors::mismatch;
      return;
    }
    if (receiveLastAction != lastAction) {
      spiError = spiErrors::mismatch;
      return;
    }
    currentReceiveIndex = nextTransaction;
  }

  /**
   * @brief Transmit and recieve data via SPI
   *
   * @param device SPI device to use
   * @param transmitBuffer data to transmit
   * @param receiveBuffer buffer to put data into
   * @param bitcount amount of bits
   * @param lastAction is this the last action? This will disable the chip select
   */
  void transceive(chipEnables device, const std::span<uint16_t> transmitBuffer, std::span<uint16_t> receiveBuffer,
                  uint16_t bitcount, bool lastAction) {
    int nextTransaction = transactionNext(rxTransactions, currentReceiveIndex);
    // is there a next transaction? No? error out
    if (nextTransaction == 0) {
      spiError = spiErrors::transactionNotFound;
      return;
    }

    transactionAdd(txTransactions, transmitIndex, device, transmitBuffer, bitcount, lastAction);

    chipEnables receiveEnable;
    uint16_t receiveBitcount;
    bool receiveLastAction;
    transactionGet(rxTransactions, currentReceiveIndex, receiveEnable, receiveBuffer, receiveBitcount, receiveLastAction);
    // compare the retrieved transaction with what you expect
    if (device != receiveEnable) {
      spiError = spiErrors::mismatch;
      return;
    }
    if (receiveBitcount != bitcount) {
      spiError = spiErrors::mismatch;
      return;
    }
    if (receiveLastAction != lastAction) {
      spiError = spiErrors::mismatch;
      return;
    }
    currentReceiveIndex = nextTransaction;
  }

  /**
   * @brief Return amount of transmit transactions
   *
   * @return int count of transmit transactions in mock transmit buffer
   */
  int txTransactionCount(void) {
    size_t index = transactionNext(txTransactions, 0);
    int transactionCount = 0;
    // iterate through transmit transactions
    while (index != 0) {
      transactionCount++;
      index = transactionNext(txTransactions, index);
      if (index == 0) {
        break;
      }
    }
    return transactionCount;
  }

  /**
   * @brief Return amount of receive transactions
   *
   * @return int count of transmit transactions in mock receive buffer
   */
  int rxTransactionCount(void) {
    size_t index = transactionNext(rxTransactions, 0);
    int transactionCount = 0;
    // iterate through transmit transactions
    while (index != 0) {
      transactionCount++;
      index = transactionNext(rxTransactions, index);
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
    size_t index = transactionToIndex(txTransactions, transaction);
    return txTransactions[index];
  }

  /**
   * @brief get chip enable from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   chip enable from transaction
   */
  uint16_t txTransactionGetChip(int transaction) {
    size_t index = transactionToIndex(txTransactions, transaction);
    return txTransactions[index + 1];
  }
  /**
   * @brief get last transmission indicator from transaction
   *
   * @param transaction transaction number
   * @return uint16_t   get last transmission indicator, 0 for not, non zero for last
   */
  uint16_t txTransactionGetLast(int transaction) {
    size_t index = transactionToIndex(txTransactions, transaction);
    return txTransactions[index + 2];
  }
  /**
   * @brief get data from transaction
   *
   * @param transaction transaction number
   * @return uint16_t*  pointer to first bits in uint16_t array
   */
  uint16_t* txTransactionGetData(int transaction) {
    size_t index = transactionToIndex(txTransactions, transaction);
    return &txTransactions[index + 3];
  }

  /**
   * @brief Add a transaction to be received
   *
   * @param device SPI device for the transaction
   * @param transmitBuffer data to be used in mock receive
   * @param bitcount amount of bits used in mock receive
   * @param lastAction if this is the last transaction
   */
  void rxTransactionAdd(chipEnables device, const std::span<uint16_t> receiveBuffer, uint16_t bitcount, bool lastAction) {
    transactionAdd(rxTransactions, receiveIndex, device, receiveBuffer, bitcount, lastAction);
  }

  spiErrors spiError;                     /**< error if something bad occurs */
  std::array<uint16_t, N> txTransactions; /**< Transmit transaction data buffer */
  std::array<uint16_t, N> rxTransactions; /**< Receive transaction data buffer */
  size_t transmitIndex, receiveIndex;     /**< BIT indices of where we are */
  int currentReceiveIndex;                /**< Which receive transaction is now current */

 private:
  /**
   * @brief Add transaction to a buffer and update its current index
   *
   * @param buffer            Transaction buffer
   * @param index             pointer to current transaction buffer index
   * @param device            Device enable in transaction
   * @param transactionBuffer Transaction data
   * @param bitcount          Bits in transaction
   * @param lastAction        Last transaction
   */
  void transactionAdd(std::span<uint16_t> buffer, size_t& index, chipEnables device, const std::span<uint16_t> transactionBuffer,
                      uint16_t bitcount, bool lastAction) {
    size_t dataElementCount = bitcount / 16 + 1;
    buffer[index++] = bitcount;
    buffer[index++] = static_cast<uint16_t>(device);
    buffer[index++] = static_cast<uint16_t>(lastAction);
    for (size_t i = 0; i < dataElementCount; i++) {
      buffer[index++] = transactionBuffer[i];
    }
  }
  /**
   * @brief Get transaction from a buffer at index
   *
   * @param buffer            Transaction buffer
   * @param index             pointer to current transaction buffer index
   * @param device            Device enable in transaction
   * @param transactionBuffer Transaction data
   * @param bitcount          Bits in transaction
   * @param lastAction        Last transaction
   */
  void transactionGet(const std::span<uint16_t> buffer, size_t index, chipEnables& device, std::span<uint16_t> transactionBuffer,
                      uint16_t& bitcount, bool& lastAction) {
    bitcount = buffer[index++];
    device = static_cast<chipEnables>(buffer[index++]);
    lastAction = static_cast<bool>(buffer[index++]);
    size_t dataElementCount = bitcount / 16 + 1;
    for (size_t i = 0; i < dataElementCount; i++) {
      transactionBuffer[i] = buffer[index++];
    }
  }
  /**
   * @brief Change transaction number to array index
   *
   * @param buffer      transaction buffer to inspect
   * @param transaction transaction number
   * @return size_t
   */
  size_t transactionToIndex(const std::span<uint16_t> buffer, int transaction) {
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
  size_t transactionNext(const std::span<uint16_t> buffer, size_t index) {
    if (buffer[index] == 0) return 0;
    size_t newIndex = index + (buffer[index] / 16) + 4;
    if (newIndex > N) return 0;
    return newIndex;
  }
};

#endif