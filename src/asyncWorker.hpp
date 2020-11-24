#include <napi.h>
#include <string>
#include <thread>
#include <functional>

#include "cpuinfo/cpuinfo.h"

template<class T>
inline void ObjSet(const Napi::Env &env, Napi::Object &obj, const char *key, const T &data) {
    static_assert(std::is_same_v<T, bool> || std::is_same_v<T, std::string>);

    if constexpr(std::is_same_v<T, std::string>) {
        obj.Set(key, Napi::String::New(env, data));
    } else if constexpr (std::is_same_v<T, bool>) {
        obj.Set(key, Napi::Boolean::New(env, data));
    }
}

/**
 * Convert cpuInfo to a Napi::Object
 * 
 * @param env the env to run inj
 * @param info the info to convert
 */
Napi::Object cpuInfoToVal(const Napi::Env &env, const cpuInfo &info);

/**
 * A class for creating js promises. This class must exist since the original n-api is so bad and cannot provide
 * such a simple behaviour by default. Also, the docs on Promises are worth shit, just as a side note.
 * You will need to look at the examples to find this, why not?
 *
 * Source: https://github.com/nodejs/node-addon-examples/issues/85#issuecomment-583887294
 * Also exists here: https://github.com/nodejs/node-addon-examples/blob/master/async_pi_estimate/node-addon-api/async.cc
 */
class AsyncWorker : public Napi::AsyncWorker {
protected:
    /**
     * Construct a Promise
     *
     * @param env the environment to work in
     * @param _fn the function to call
     */
    explicit AsyncWorker(const Napi::Env &env);

    /**
     * A default destructor
     */
    ~AsyncWorker() override;

    virtual void Run() = 0;

    /**
     * The execution thread
     */
    void Execute() override;

    /**
     * Default on ok
     */
    virtual void OnOK() override;

    /**
     * On error
     *
     * @param error the error to throw
     */
    void OnError(const Napi::Error &error) override;

    /**
     * Get the promise
     *
     * @return a Napi::Promise
     */
    Napi::Promise GetPromise();

    Napi::Promise::Deferred deferred;
};

/**
 * A class for creating Promises with return types
 */
class CpuInfoPromise : public AsyncWorker {
public:
    /**
     * Create a javascript promise
     *
     * @param env the environment of the promise
     * @param fn the function to call. Must return T.
     * @return a Napi::Promise
     */
    static Napi::Promise create(const Napi::Env &env, const std::function<cpuInfo()> &fn);

protected:
    /**
     * Construct a Promise
     *
     * @param env the environment to work in
     * @param _fn the function to call
     */
    CpuInfoPromise(const Napi::Env &env, std::function<cpuInfo()> _fn);

    /**
     * A default destructor
     */
    ~CpuInfoPromise() override;

    /**
     * The execution thread
     */
    void Run() override;

    /**
     * On ok
     */
    void OnOK() override;

private:
    std::function<cpuInfo()> fn;
    cpuInfo val;
};