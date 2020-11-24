#include "cpuinfo.h"
#include <string.h>
#include <stdint.h>

#ifdef _WIN32

//  Windows
#define cpuid(info, x) __cpuidex(info, x, 0)

#else

//  GCC Intrinsics
#include <cpuid.h>
void cpuid(int32_t info[4], int InfoType) {
    __cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

cpuInfo generateCpuInfo() {
    cpuInfo cInfo;
    memset(&cInfo, 0, sizeof(cpuInfo));

    int32_t info[4];
    cpuid(info, 0);
    int32_t nIds = info[0];

    // Fill in the vendor field
    memcpy(cInfo.VENDOR, &info[1], 4);
    memcpy(cInfo.VENDOR + 4, &info[3], 4);
    memcpy(cInfo.VENDOR + 8, &info[2], 4);

    cpuid(info, 0x80000000);
    unsigned nExIds = info[0];

    //  Detect Features
    if (nIds >= 0x00000001) {
        cpuid(info, 0x00000001);
        cInfo.HW_MMX = (info[3] & ((int)1 << 23)) != 0;
        cInfo.HW_SSE = (info[3] & ((int)1 << 25)) != 0;
        cInfo.HW_SSE2 = (info[3] & ((int)1 << 26)) != 0;
        cInfo.HW_SSE3 = (info[2] & ((int)1 << 0)) != 0;

        cInfo.HW_SSSE3 = (info[2] & ((int)1 << 9)) != 0;
        cInfo.HW_SSE41 = (info[2] & ((int)1 << 19)) != 0;
        cInfo.HW_SSE42 = (info[2] & ((int)1 << 20)) != 0;
        cInfo.HW_AES = (info[2] & ((int)1 << 25)) != 0;

        cInfo.HW_AVX = (info[2] & ((int)1 << 28)) != 0;
        cInfo.HW_FMA3 = (info[2] & ((int)1 << 12)) != 0;

        cInfo.HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
    }

    if (nIds >= 0x00000007) {
        cpuid(info, 0x00000007);
        cInfo.HW_AVX2 = (info[1] & ((int)1 << 5)) != 0;

        cInfo.HW_BMI1 = (info[1] & ((int)1 << 3)) != 0;
        cInfo.HW_BMI2 = (info[1] & ((int)1 << 8)) != 0;
        cInfo.HW_ADX = (info[1] & ((int)1 << 19)) != 0;
        cInfo.HW_SHA = (info[1] & ((int)1 << 29)) != 0;
        cInfo.HW_PREFETCHWT1 = (info[2] & ((int)1 << 0)) != 0;

        cInfo.HW_AVX512F = (info[1] & ((int)1 << 16)) != 0;
        cInfo.HW_AVX512CD = (info[1] & ((int)1 << 28)) != 0;
        cInfo.HW_AVX512PF = (info[1] & ((int)1 << 26)) != 0;
        cInfo.HW_AVX512ER = (info[1] & ((int)1 << 27)) != 0;
        cInfo.HW_AVX512VL = (info[1] & ((int)1 << 31)) != 0;
        cInfo.HW_AVX512BW = (info[1] & ((int)1 << 30)) != 0;
        cInfo.HW_AVX512DQ = (info[1] & ((int)1 << 17)) != 0;
        cInfo.HW_AVX512IFMA = (info[1] & ((int)1 << 21)) != 0;
        cInfo.HW_AVX512VBMI = (info[2] & ((int)1 << 1)) != 0;
    }

    if (nExIds >= 0x80000001) {
        cpuid(info, 0x80000001);
        cInfo.HW_x64 = (info[3] & ((int)1 << 29)) != 0;
        cInfo.HW_ABM = (info[2] & ((int)1 << 5)) != 0;
        cInfo.HW_SSE4a = (info[2] & ((int)1 << 6)) != 0;
        cInfo.HW_FMA4 = (info[2] & ((int)1 << 16)) != 0;
        cInfo.HW_XOP = (info[2] & ((int)1 << 11)) != 0;
    }

    // Get the cpu brand string.
    // Source: https://stackoverflow.com/a/850812
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        cpuid(info, i);
        // Interpret CPU brand string
        if  (i == 0x80000002) {
            memcpy(cInfo.CPU_BRAND_STRING, info, sizeof(info));
        } else if  (i == 0x80000003) {
            memcpy(cInfo.CPU_BRAND_STRING + 16, info, sizeof(info));
        } else if  (i == 0x80000004) {
            memcpy(cInfo.CPU_BRAND_STRING + 32, info, sizeof(info));
        }
    }

    return cInfo;
}