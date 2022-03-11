/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file pulse_density.h
 *
 */
#ifndef PULSE_DENSITY_H
#define PULSE_DENSITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint32_t sum;
  uint32_t threshold;
  uint32_t step;
} pulseDensityModulator;

/** \brief Initializes the pulse density modulator
 * \param modulator Pointer to the pulse density modulator
 * \param threshold threshold where the pulse density modulator triggers
 * \param step step value of the pulse density modulator
 */
void pulseDensityInit(pulseDensityModulator *modulator, uint32_t threshold, uint32_t step);

/** \brief executes one pulse density modulator step
 * \param modulator Pointer to the pulse density modulator
 * \return if the pulse density modulator is triggered
 */
bool pulseDensityOutput(pulseDensityModulator *modulator);

/** \brief sets the pulse density modulator step size
 * \param modulator Pointer to the pulse density modulator
 * \param step step value of the pulse density modulator
 */
void pulseDensitySetStep(pulseDensityModulator *modulator, uint32_t step);

#ifdef __cplusplus
}
#endif

#endif