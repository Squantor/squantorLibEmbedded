/*
SPDX-License-Identifier: MIT
Copyright (c) 2020 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdbool.h>
#include <print.h>
#include <datastream.h>
#include <results.h>

result printDecNzU32(const datastreamChar_t *__restrict__ stream, uint32_t data)
{
    uint32_t num = 1000000000;
    uint8_t idx;
    bool hitDigits = false;
    if(data == 0)
        return printDigit(stream, 0);
    while(num > 0)
    {
        idx = data / num;
        if((idx != 0) || (hitDigits == true))
        {
            // we have a non zero digit, now print everything
            hitDigits = true;
            result printResult = printDigit(stream, idx);
            if(printResult != noError)
                return printResult;
        }
        data -= idx * num;
        num = num / 10;
    }
    return noError;
}
