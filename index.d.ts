/**
 * An object storing CPU information.
 * @see https://en.wikipedia.org/wiki/CPUID
 */
export type cpuInfo = {
    /**
     * The vendor string.
     * May be 'GenuineIntel' for Intel cpus or 'AuthenticAMD' for amd cpus.
     * @see https://en.wikipedia.org/wiki/CPUID#EAX=0:_Highest_Function_Parameter_and_Manufacturer_ID
     */
    vendor: string,

    /**
     * The CPU brand string.
     * E.g. 'Intel(R) Core(TM) ${MODEL} CPU @ ${FREQ}GHz'
     */
    cpuBrandString: string,

    /**
     * Whether the cpu has MMX support.
     * @see https://en.wikipedia.org/wiki/MMX_(instruction_set)
     */
    mmx: boolean,

    /**
     * Whether the cpu supports the x64 instruction set.
     * @see https://en.wikipedia.org/wiki/X86-64
     */
    x64: boolean,

    /**
     * Whether the cpu supports Advanced Bit Manipulation.
     * @see https://en.wikipedia.org/wiki/Bit_manipulation_instruction_set#ABM
     */
    abm: boolean,

    /**
     * Whether the 'read random' instruction.
     * @see https://en.wikipedia.org/wiki/RDRAND
     */
    rdrand: boolean,

    /**
     * Whether the cpu supports the Bit Manipulation Instruction Set 1.
     * @see https://en.wikipedia.org/wiki/Bit_manipulation_instruction_set#BMI1_(Bit_Manipulation_Instruction_Set_1)
     */
    bmi1: boolean,

    /**
     * Whether the cpu supports the Bit Manipulation Instruction Set 2.
     * @see https://en.wikipedia.org/wiki/Bit_manipulation_instruction_set#BMI2_(Bit_Manipulation_Instruction_Set_2)
     */
    bmi2: boolean,

    /**
     * Whether the cpu supports Intel ADX.
     * @see https://en.wikipedia.org/wiki/Intel_ADX
     */
    adx: boolean,

    /**
     * Whether the cpu supports the prefetchwt1 instruction.
     */
    prefetchwt1: boolean,

    /**
     * Whether the cpu supports Streaming SMID Extensions.
     * @see https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions
     */
    sse: boolean,

    /**
     * Whether the cpu supports Streaming SIMD Extensions 2.
     * @see https://en.wikipedia.org/wiki/SSE2
     */
    sse2: boolean,

    /**
     * Whether the cpu supports Streaming SIMD Extensions 3.
     * @see https://en.wikipedia.org/wiki/SSE3
     */
    sse3: boolean,

    /**
     * Whether the cpu supports Supplemental Streaming SIMD Extensions 3.
     * @see https://en.wikipedia.org/wiki/SSSE3
     */
    ssse3: boolean,

    /**
     * Whether the cpu supports Streaming SMID Extensions 4.1.
     * @see https://en.wikipedia.org/wiki/SSE4#SSE4.1
     */
    sse41: boolean,

    /**
     * Whether the cpu supports Streaming SMID Extensions 4.2.
     * @see https://en.wikipedia.org/wiki/SSE4#SSE4.2
     */
    sse42: boolean,

    /**
     * Whether the cpu supports Streaming SMID Extensions 4a.
     * @see https://en.wikipedia.org/wiki/SSE4#SSE4a
     */
    sse4a: boolean,

    /**
     * Whether the cpu supports the AES instruction set.
     * @see https://en.wikipedia.org/wiki/AES_instruction_set
     */
    aes: boolean,

    /**
     * Whether the cpu supports the Intel SHA extensions.
     * @see https://en.wikipedia.org/wiki/Intel_SHA_extensions
     */
    sha: boolean,

    /**
     * Whether the cpu supports Advanced Vector Extensions.
     * @see https://en.wikipedia.org/wiki/Advanced_Vector_Extensions#Advanced_Vector_Extensions
     */
    avx: boolean,

    /**
     * Whether the cpu supports the eXtended Operations instructions set.
     * @see https://en.wikipedia.org/wiki/XOP_instruction_set
     */
    xop: boolean,

    /**
     * Whether the cpu supports the FMA3 instruction set.
     * @see https://en.wikipedia.org/wiki/FMA_instruction_set#FMA3_instruction_set
     */
    fma3: boolean,

    /**
     * Whether the cpu supports the FMA4 instruction set.
     * @see https://en.wikipedia.org/wiki/FMA_instruction_set#FMA4_instruction_set
     */
    fma4: boolean,

    /**
     * Whether the cpu supports Advanced Vector Extensions 2.
     * @see https://en.wikipedia.org/wiki/Advanced_Vector_Extensions#Advanced_Vector_Extensions_2
     */
    avx2: boolean,

    /**
     * Whether the cpu supports the AVX-512 Foundation instruction set.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512f: boolean,

    /**
     * Whether the cpu supports the AVX-512 Conflict Detection Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512cd: boolean,

    /**
     * Whether the cpu supports the AVX-512 Prefetch Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512pf: boolean,

    /**
     * Whether the cpu supports the AVX-512 Exponential and Reciprocal Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512er: boolean,

    /**
     * Whether the cpu supports the AVX-512 Vector Length Extensions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512vl: boolean,

    /**
     * Whether the cpu supports the AVX-512 Byte and Word Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512bw: boolean,

    /**
     * Whether the cpu supports the AVX-512 Doubleword and Quadword Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512dq: boolean,

    /**
     * Whether the cpu supports the AVX-512 Integer Fused Multiply Add Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512ifma: boolean,

    /**
     * Whether the cpu supports the AVX-512 Vector Byte Manipulation Instructions.
     * @see https://en.wikipedia.org/wiki/AVX-512#Instruction_set
     */
    avx512vbmi: boolean
};

/**
 * Get information about the cpu used by this system. Sync call.
 * Based on the work of Mystical: https://stackoverflow.com/a/7495023
 * See also: https://github.com/Mysticial/FeatureDetector
 * 
 * @returns the cpu information
 */
export function getCpuInfoSync(): cpuInfo;

/**
 * Get information about the cpu used by this system. Async call.
 * Based on the work of Mystical: https://stackoverflow.com/a/7495023
 * See also: https://github.com/Mysticial/FeatureDetector
 * 
 * @returns the cpu information
 */
export async function getCpuInfo(): Promise<cpuInfo>;