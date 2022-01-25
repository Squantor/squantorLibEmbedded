# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file


# squantorLibEmbedded library settings
#
# Version: 20200814

# library files and includes
INCLUDES += -IsquantorLibEmbedded/inc

FILES += squantorLibEmbedded/src/ansi/parse_ansi.c \
squantorLibEmbedded/src/queue/queue_string.c \
squantorLibEmbedded/src/queue/queue_char.c \
squantorLibEmbedded/src/queue/queue_uint8.c \
squantorLibEmbedded/src/cmdline/cmdline_prompt.c \
squantorLibEmbedded/src/prompt/prompt_mini.c \
squantorLibEmbedded/src/command/command_mini.c \
squantorLibEmbedded/src/datastream/dswritechar.c \
squantorLibEmbedded/src/datastream/dsreadchar.c \
squantorLibEmbedded/src/datastream/dsputs.c \
squantorLibEmbedded/src/print/print_digit.c \
squantorLibEmbedded/src/print/print_hex_u8.c \
squantorLibEmbedded/src/print/print_hex_u16.c \
squantorLibEmbedded/src/print/print_hex_u32.c \
squantorLibEmbedded/src/print/print_dec_u16.c \
squantorLibEmbedded/src/print/print_decnz_u16.c \
squantorLibEmbedded/src/print/print_decnz_u32.c \
squantorLibEmbedded/src/print/print_dec_u32.c \
squantorLibEmbedded/src/print/print_bin_u32.c \
squantorLibEmbedded/src/parse/parsedigit.c \
squantorLibEmbedded/src/parse/parsedigit.cpp \
squantorLibEmbedded/src/font/font_8x8.c \
squantorLibEmbedded/src/bit/bitzoom.c

