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

#include <prompt_mini.h>
#include <datastream.h>
#include <string.h>

#define ASCII_NUL   (0)
#define ASCII_CR    ('\r')    // Carriage Return
#define ASCII_LF    ('\n')    // Line Feed

result promptProcess(promptData_t *const promptData, const datastreamChar_t *stream)
{
    char c;
    result r = dsReadChar(stream, &c);
    if(r != noError)
    {
        return r;
    }
    switch(c)
    {
        case ASCII_CR:
            dsWriteChar(stream, ASCII_CR);
            // terminate prompt string
            promptData->buffer[promptData->bufferIndex] = ASCII_NUL;
            // check length
            if(strlen(promptData->buffer) == 0)
                // zero length string, do nothing
                return promptError;
            // clear prompt
            promptData->bufferIndex = 0;
            // execute
            return promptData->commandHandler(promptData->buffer);
            break;
        case ASCII_LF:
            // just ignore line feeds
        break;
        default:
            // always leave one space for zero terminator
            if(promptData->bufferIndex < (promptData->bufSize - 1))
            {
                dsWriteChar(stream, c);
                promptData->buffer[promptData->bufferIndex] = c;
                promptData->bufferIndex++;
            }
            break;
    }
    return noError;
}