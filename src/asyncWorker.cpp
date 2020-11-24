#include "asyncWorker.hpp"

Napi::Object cpuInfoToVal(const Napi::Env &env, const cpuInfo &info) {
#define OSet(key, data) ObjSet(env, res, key, data);
    Napi::Object res = Napi::Object::New(env);

    OSet("vendor", std::string(info.VENDOR));
    OSet("cpuBrandString", std::string(info.CPU_BRAND_STRING));

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

AsyncWorker::AsyncWorker(const Napi::Env &env) : Napi::AsyncWorker(env), deferred(Napi::Promise::Deferred::New(env)) {}

AsyncWorker::~AsyncWorker() = default;

void AsyncWorker::Execute() {
    try {
        Run();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } catch (std::exception &e) {
        Napi::AsyncWorker::SetError(e.what());
    } catch (...) {
        Napi::AsyncWorker::SetError("An unknown error occurred");
    }
}

void AsyncWorker::OnOK() {
    deferred.Resolve(Env().Undefined());
}

void AsyncWorker::OnError(const Napi::Error &error) {
    deferred.Reject(error.Value());
}

Napi::Promise AsyncWorker::GetPromise() {
    return deferred.Promise();
}

Napi::Promise CpuInfoPromise::create(const Napi::Env &env, const std::function<cpuInfo()> &fn) {
    auto *promise = new CpuInfoPromise(env, fn);
    promise->Queue();

    return promise->GetPromise();
}

CpuInfoPromise::CpuInfoPromise(const Napi::Env &env, std::function<cpuInfo()> _fn) : AsyncWorker(env), fn(std::move(_fn)) {}

CpuInfoPromise::~CpuInfoPromise() = default;

void CpuInfoPromise::Run() {
    val = fn();
}

void CpuInfoPromise::OnOK() {
    deferred.Resolve(cpuInfoToVal(Env(), val));
};