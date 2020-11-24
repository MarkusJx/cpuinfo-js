const cpuinfo = require(".");

console.time("cpuInfoSync");
const info = cpuinfo.getCpuInfoSync();
console.timeEnd("cpuInfoSync");

console.log("CpuInfo (sync):\n", info);

console.time("cpuInfoAsync");
cpuinfo.getCpuInfo().then((res) => {
    console.log("CpuInfo (async):\n", res);
});
console.timeEnd("cpuInfoAsync");
