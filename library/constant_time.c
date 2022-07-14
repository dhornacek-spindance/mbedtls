/**
 *  Constant-time functions
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

 /*
 * The following functions are implemented without using comparison operators, as those
 * might be translated to branches by some compilers on some platforms.
 */

// #include "common.h"
// #include "constant_time_internal.h"
// #include "mbedtls/constant_time.h"
// #include "mbedtls/error.h"
// #include "mbedtls/platform_util.h"

// #if defined(MBEDTLS_BIGNUM_C)
// #include "mbedtls/bignum.h"
// #endif

// #if defined(MBEDTLS_SSL_TLS_C)
// #include "mbedtls/ssl_internal.h"
// #endif

// #if defined(MBEDTLS_RSA_C)
// #include "mbedtls/rsa.h"
// #endif

// #if defined(MBEDTLS_BASE64_C)
// #include "constant_time_invasive.h"
// #endif

#include <string.h>

int mbedtls_ct_memcmp( const void *a,
                       const void *b,
                       size_t n )
{
    size_t i;
    volatile const unsigned char *A = (volatile const unsigned char *) a;
    volatile const unsigned char *B = (volatile const unsigned char *) b;
    volatile unsigned char diff = 0;

    for( i = 0; i < n; i++ )
    {
        /* Read volatile data in order before computing diff.
         * This avoids IAR compiler warning:
         * 'the order of volatile accesses is undefined ..' */
        unsigned char x = A[i], y = B[i];
        diff |= x ^ y;
    }

    return( (int)diff );
}
