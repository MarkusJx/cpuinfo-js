# cpuinfo-js

A **client-only** library to get supported instruction sets by the machines CPU.
Based on the work of [Mystical](https://github.com/Mysticial)
(also see [here](https://github.com/Mysticial/FeatureDetector) and [here](https://stackoverflow.com/a/7495023)).

## Usage
### Sync calls
```js
const cpuinfo = require("cpuinfo-js");

// Sync call
const info = cpuinfo.getCpuInfoSync();

// Print the cpu info
console.log(info);

// Or check for specific features, e.g. AVX2
if (info.avx2) {
    // Has avx2 support
} else {
    // No avx2 support :(
}
```

### Async calls
There is no real need for this, but whatever.
```js
const cpuinfo = require("cpuinfo-js");

// Async call
cpuinfo.getCpuInfo().then(info => {
    // Print the cpu info
    console.log(info);

    // Or check for specific features, e.g. AVX2
    if (info.avx2) {
        // Has avx2 support
    } else {
        // No avx2 support :(
    }
});
```