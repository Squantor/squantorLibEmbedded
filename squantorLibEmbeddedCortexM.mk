# SPDX-License-Identifier: MIT
#
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file


# squantorLibEmbedded library settings
# Arm specific files
#
# Version: 20220315

# library files and includes, assuming you also add squantorLibEmbedded

# library files and includes
INCLUDES += -IsquantorLibEmbedded/inc/cortexM

FILES += squantorLibEmbedded/src/cortexM/delay_cycles.c

