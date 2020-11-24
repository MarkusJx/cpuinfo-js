#include <iostream>
#include <type_traits>
#include "asyncWorker.hpp"

Napi::Object getCpuInfoSync(const Napi::CallbackInfo &cb_info) {
    Napi::Env env = cb_info.Env();
    cpuInfo info = generateCpuInfo();
    return cpuInfoToVal(env, info);
}

Napi::Promise getCpuInfo(const Napi::CallbackInfo &cb_info) {
    return CpuInfoPromise::create(cb_info.Env(), [] {
        return generateCpuInfo();
    });
}

#define export(func) exports.Set(std::string("lib_") + #func, Napi::Function::New(env, func))

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    export(getCpuInfoSync);
    export(getCpuInfo);

    return exports;
}

NODE_API_MODULE(cpuinfo_js, InitAll)