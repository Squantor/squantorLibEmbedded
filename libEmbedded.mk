# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020-2020 Bart Bilos
# For conditions of distribution and use, see LICENSE file


# libEmbedded library settings
#
# Version: 20200814

# library files and includes
INCLUDES += -IlibEmbedded/inc

FILES += libEmbedded/src/ansi/parse_ansi.c \
libEmbedded/src/queue/queue_string.c \
libEmbedded/src/queue/queue_char.c \
libEmbedded/src/queue/queue_uint8.c \
libEmbedded/src/cmdline/cmdline_prompt.c \
libEmbedded/src/prompt/prompt_mini.c \
libEmbedded/src/command/command_mini.c \
libEmbedded/src/datastream/dswritechar.c \
libEmbedded/src/datastream/dsreadchar.c \
libEmbedded/src/datastream/dsputs.c \
libEmbedded/src/print/print_digit.c \
libEmbedded/src/print/print_hex_u8.c \
libEmbedded/src/print/print_hex_u16.c \
libEmbedded/src/print/print_hex_u32.c \
libEmbedded/src/print/print_dec_u16.c \
libEmbedded/src/print/print_decnz_u16.c \
libEmbedded/src/print/print_decnz_u32.c \
libEmbedded/src/print/print_dec_u32.c \
libEmbedded/src/print/print_bin_u32.c \
libEmbedded/src/parse/parsedigit.c

