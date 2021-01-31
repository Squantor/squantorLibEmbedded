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
#include <stdbool.h>
#include <print.h>
#include <datastream.h>
#include <results.h>

result printDecNzU16(const datastreamChar_t *__restrict__ stream, uint16_t data)
{
    uint16_t num = 10000;
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
