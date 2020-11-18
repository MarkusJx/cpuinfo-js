#include <iostream>
#include <type_traits>
#include <napi.h>
#include "cpuinfo/cpuinfo.h"

template<class T>
void ObjSet(const Napi::Env &env, Napi::Object &obj, const char *key, const T &data) {
    static_assert(std::is_same_v<T, bool> || std::is_same_v<T, std::string>);

    if constexpr(std::is_same_v<T, std::string>) {
        obj.Set(key, Napi::String::New(env, data));
    } else if constexpr (std::is_same_v<T, bool>) {
        obj.Set(key, Napi::Boolean::New(env, data));
    }
}

Napi::Object getCpuInfo(const Napi::CallbackInfo &cb_info) {
#define OSet(key, data) ObjSet(env, res, key, data);
    Napi::Env env = cb_info.Env();
    Napi::Object res = Napi::Object::New(env);

    cpuInfo info = generateCpuInfo();

    OSet("vendor", std::string(info.VENDOR));

    OSet("mmx", info.HW_MMX);
    OSet("x64", info.HW_x64);
    OSet("abm", info.HW_ABM);
    OSet("rdrand", info.HW_RDRAND);
    OSet("bmi1", info.HW_BMI1);
    OSet("bmi2", info.HW_BMI2);
    OSet("adx", info.HW_ADX);
    OSet("prefetchwt1", info.HW_PREFETCHWT1);

    OSet("sse", info.HW_SSE);
    OSet("sse2", info.HW_SSE2);
    OSet("sse3", info.HW_SSE3);
    OSet("ssse3", info.HW_SSSE3);
    OSet("sse41", info.HW_SSE41);
    OSet("sse42", info.HW_SSE42);
    OSet("sse4a", info.HW_SSE4a);
    OSet("aes", info.HW_AES);
    OSet("sha", info.HW_SHA);

    OSet("avx", info.HW_AVX);
    OSet("xop", info.HW_XOP);
    OSet("fma3", info.HW_FMA3);
    OSet("fma4", info.HW_FMA4);
    OSet("avx2", info.HW_AVX2);

    OSet("avx512f", info.HW_AVX512F);
    OSet("avx512cd", info.HW_AVX512CD);
    OSet("avx512pf", info.HW_AVX512PF);
    OSet("avx512er", info.HW_AVX512ER);
    OSet("avx512vl", info.HW_AVX512VL);
    OSet("avx512bw", info.HW_AVX512BW);
    OSet("avx512dq", info.HW_AVX512DQ);
    OSet("avx512ifma", info.HW_AVX512IFMA);
    OSet("avx512vbmi", info.HW_AVX512VBMI);

    return res;
#undef OSet
}

#define export(func) exports.Set(std::string("lib_") + #func, Napi::Function::New(env, func))

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    export(getCpuInfo);

    return exports;
}

NODE_API_MODULE(cpuinfo_js, InitAll)