# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# squantorLibEmbedded library settings
#
# Version: 20220715

# library settings
NAME := squantorLibEmbedded

# current makefile base dir relative to Makefile
LIB_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# library files and includes
$(NAME)_LIB_FILES := $(LIB_DIR)/src/ansi/parse_ansi.c \
$(LIB_DIR)/src/queue/queue_string.c \
$(LIB_DIR)/src/queue/queue_char.c \
$(LIB_DIR)/src/queue/queue_uint8.c \
$(LIB_DIR)/src/cmdline/cmdline_prompt.c \
$(LIB_DIR)/src/prompt/prompt_mini.c \
$(LIB_DIR)/src/command/command_mini.c \
$(LIB_DIR)/src/datastream/dswritechar.c \
$(LIB_DIR)/src/datastream/dsreadchar.c \
$(LIB_DIR)/src/datastream/dsputs.c \
$(LIB_DIR)/src/print/print_digit.c \
$(LIB_DIR)/src/print/print_hex_u8.c \
$(LIB_DIR)/src/print/print_hex_u16.c \
$(LIB_DIR)/src/print/print_hex_u32.c \
$(LIB_DIR)/src/print/print_dec_u16.c \
$(LIB_DIR)/src/print/print_decnz_u16.c \
$(LIB_DIR)/src/print/print_decnz_u32.c \
$(LIB_DIR)/src/print/print_dec_u32.c \
$(LIB_DIR)/src/print/print_bin_u32.c \
$(LIB_DIR)/src/parse/parsedigit.c \
$(LIB_DIR)/src/parse/parsedigit.cpp \
$(LIB_DIR)/src/font/font_8x8.cpp \
$(LIB_DIR)/src/bit/bitzoom.c \
$(LIB_DIR)/src/pulse_density/pulse_density.c \
$(LIB_DIR)/src/pulse_density/pulse_density.cpp \
$(LIB_DIR)/src/bit/bitblit1d.cpp \
$(LIB_DIR)/src/bit/readmodifywrite.cpp \
$(LIB_DIR)/src/bit/bitblit2d.cpp

$(NAME)_LIB_INCLUDES := -I$(LIB_DIR)/inc

# --- nothing user definable below ---
LIBRARIES += $(NAME)
