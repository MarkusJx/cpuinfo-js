const cpuinfo_js_lib = require("./bin/cpuinfo-js.node");

module.exports = {
    /**
     * The cpu info
     * @typedef {{
     * vendor: String
     * mmx: Boolean
     * x64: Boolean
     * abm: Boolean
     * rdrand: Boolean
     * bmi1: Boolean
     * bmi2: Boolean
     * adx: Boolean
     * prefetchwt1: Boolean
     * sse: Boolean
     * sse2: Boolean
     * sse3: Boolean
     * ssse3: Boolean
     * sse41: Boolean
     * sse42: Boolean
     * sse4a: Boolean
     * aes: Boolean
     * sha: Boolean
     * avx: Boolean
     * xop: Boolean
     * fma3: Boolean
     * fma4: Boolean
     * avx2: Boolean
     * avx512f: Boolean
     * avx512cd: Boolean
     * avx512pf: Boolean
     * avx512er: Boolean
     * avx512vl: Boolean
     * avx512bw: Boolean
     * avx512dq: Boolean
     * avx512ifma: Boolean
     * avx512vbmi: Boolean
     * }} cpuInfo
     */

    /**
     * Get information about the cpu used by this system. Sync call.
     * Based on the work of Mystical: https://stackoverflow.com/a/7495023
     * See also: https://github.com/Mysticial/FeatureDetector
     * 
     * @returns {cpuInfo} the cpu information
     */
    getCpuInfoSync: function () {
        return cpuinfo_js_lib.lib_getCpuInfoSync();
    },

    /**
     * Get information about the cpu used by this system. Async call.
     * Based on the work of Mystical: https://stackoverflow.com/a/7495023
     * See also: https://github.com/Mysticial/FeatureDetector
     * 
     * @returns {cpuInfo} the cpu information
     */
    getCpuInfo: async function () {
        return await cpuinfo_js_lib.lib_getCpuInfo();
    }
};