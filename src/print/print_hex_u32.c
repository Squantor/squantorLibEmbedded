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
#include <print.h>
#include <datastream.h>
#include <results.h>

// TODO: refactor this!
result printHexU32(const datastreamChar_t *__restrict__ stream, const uint32_t data)
{
    result printResult;
    printResult = printDigit(stream, data>>28);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>24);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>20);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>16);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>12);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>8);
    if(printResult != noError)
        return printResult;
    printResult = printDigit(stream, data>>4);
    if(printResult != noError)
        return printResult;
    return printDigit(stream, data);
}