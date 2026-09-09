/** @file
 * Copyright (c) 2019-2023, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#ifndef _PAL_CONFIG_H_
#define _PAL_CONFIG_H_

#include "pal_crypto_config.h"
#include "pal_attestation_config.h"
#include "pal_storage_config.h"

/* Define PSA test suite dependent macros for non-cmake build */
#if !defined(PSA_CMAKE_BUILD)

/* Print verbosity = TEST */
#define VERBOSE 3

/* NSPE or SPE VAL build? */
#define VAL_NSPE_BUILD

/* NSPE or SPE TEST build? */
#define NONSECURE_TEST_BUILD

/* If not defined, skip watchdog programming */
#define WATCHDOG_AVAILABLE

/* Are Dynamic memory APIs available to secure partition? */
#define SP_HEAP_MEM_SUPP

/* PSA Isolation level supported by platform.
 *
 * Only reached by a non-CMake build - this whole block is skipped when PSA_CMAKE_BUILD is
 * defined, and the tests_psa_arch CMake passes -DPLATFORM_PSA_ISOLATION_LEVEL=
 * ${TFM_ISOLATION_LEVEL} instead, so the tests always see the level the SPE was actually
 * built at. The value here only matters if this target is ever driven by the standalone
 * makefile flow.
 *
 * The RA ports default to level 1 in their config.cmake and declare
 * PLATFORM_HAS_ISOLATION_L3_SUPPORT, so levels 1, 2 and 3 all build; profile_large, which
 * the crypto suite requires, asks for 3.
 */
#define PLATFORM_PSA_ISOLATION_LEVEL 3
#endif /* PSA_CMAKE_BUILD */

/* Version of crypto spec used in attestation */
#define CRYPTO_VERSION_BETA3

#ifndef PLATFORM_HAS_ATTEST_PK
/* Use hardcoded public key */
#define PLATFORM_OVERRIDE_ATTEST_PK
#endif

/*
 * Include of PSA defined Header files
 */
#ifdef IPC
/* psa/client.h: Contains the PSA Client API elements */
#include "psa/client.h"

/*
 * psa_manifest/sid.h:  Macro definitions derived from manifest files that map from RoT Service
 * names to Service IDs (SIDs). Partition manifest parse build tool must provide the implementation
 * of this file.
*/
#include "psa_manifest/sid.h"

/*
 * psa_manifest/pid.h: Secure Partition IDs
 * Macro definitions that map from Secure Partition names to Secure Partition IDs.
 * Partition manifest parse build tool must provide the implementation of this file.
*/
#include "psa_manifest/pid.h"
#endif

#ifdef CRYPTO
/* psa/crypto.h: Contains the PSA Crypto API elements */
#include "psa/crypto.h"
#endif

#if defined(INTERNAL_TRUSTED_STORAGE) || defined(STORAGE)
/* psa/internal_trusted_storage.h: Contains the PSA ITS API elements */
#include "psa/internal_trusted_storage.h"
#endif

#if defined(PROTECTED_STORAGE) || defined(STORAGE)
/* psa/protected_storage.h: Contains the PSA PS API elements */
#include "psa/protected_storage.h"
#endif

#ifdef INITIAL_ATTESTATION
/* psa/initial_attestation.h: Contains the PSA Initial Attestation API elements */
#include "psa/initial_attestation.h"
#endif

/* Provided by the TF-M non-secure side rather than by a driver in this repo:
 * tfm_log_printf() is the tf-m-tests NS log backend, which this port routes to SEGGER RTT
 * through syscalls_ns.c's _write(); tfm_platform_system_reset() is the PSA platform
 * service. pal_nvmem_get_addr() is defined in nspe/pal_driver_intf.c.
 */
extern int tfm_log_printf(const char *, ...);
extern int32_t tfm_platform_system_reset(void);
extern uint32_t pal_nvmem_get_addr(void);

#endif /* _PAL_CONFIG_H_ */
