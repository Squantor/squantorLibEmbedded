/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file pulse_density.h
 * \brief contains code for a Pulse Density Modulator
 */
#include <pulse_density.h>

void pulseDensityInit(pulseDensityModulator *modulator, uint32_t threshold, uint32_t step) {
  modulator->sum = 0;
  modulator->threshold = threshold;
  modulator->step = step;
}

bool pulseDensityOutput(pulseDensityModulator *modulator) {}

void pulseDensitySetStep(pulseDensityModulator *modulator, uint32_t step) {}