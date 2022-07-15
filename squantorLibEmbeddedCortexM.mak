# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# squantorLibEmbeddedCortexM library settings
#
# Version: 20220715

# library settings
NAME := squantorLibEmbeddedCortexM

# current makefile base dir relative to Makefile
LIB_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# library files and includes
$(NAME)_LIB_FILES := $(LIB_DIR)/src/cortexM/delay_cycles.c

$(NAME)_LIB_INCLUDES := -I$(LIB_DIR)/inc/cortexM

# --- nothing user definable below ---
LIBRARIES += $(NAME)
