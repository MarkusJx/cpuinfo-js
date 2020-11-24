const cpuinfo = require(".");

for (let i = 0; i < 30; i++) {
    console.time("a");
    const info = cpuinfo.getCpuInfoSync();
    console.timeEnd("a");

    //&console.log("CpuInfo:\n", info);

    console.time("b");
    cpuinfo.getCpuInfo().then((res) => {
        //console.log(res);
    });
    console.timeEnd("b");
}