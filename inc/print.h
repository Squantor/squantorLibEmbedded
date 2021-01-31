/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef PRINT_H
#define PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <datastream.h>
#include <stdint.h>
#include <results.h>

// print single digit, decimal or hex
result printDigit(const datastreamChar_t *__restrict__ stream, const uint8_t data);
// print hex number
result printHexU8(const datastreamChar_t *__restrict__ stream, const uint8_t data);
result printHexU16(const datastreamChar_t *__restrict__ stream, const uint16_t data);
result printHexU32(const datastreamChar_t *__restrict__ stream, const uint32_t data);
// print decimal number with leading zeroes
result printDecU16(const datastreamChar_t *__restrict__ stream, uint16_t data);
result printDecU32(const datastreamChar_t *__restrict__ stream, uint32_t data);
// print decimal number without leading zeroes
result printDecNzU16(const datastreamChar_t *__restrict__ stream, uint16_t data);
result printDecNzU32(const datastreamChar_t *__restrict__ stream, uint32_t data);
// print binary number
result printBinU32(const datastreamChar_t *__restrict__ stream, const uint32_t data);

#define printHex(stream, e) _Generic( e , \
    uint8_t : printHexU8, \
    uint16_t : printHexU16, \
    uint32_t : printHexU32 \
    )(stream, e)

#define printDec(stream, e) _Generic( e , \
    uint16_t : printDecU16, \
    uint32_t : printDecU32 \
    )(stream, e)

#define printDecNz(stream, e) _Generic( e , \
    uint16_t : printDecNzU16, \
    uint32_t : printDecNzU32 \
    )(stream, e)

#define printBin(stream, e) _Generic( e , \
    uint32_t : printBinU32 \
    )(stream, e)

#ifdef __cplusplus
}
#endif

#endif
