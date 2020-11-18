const fs = require('fs');
const Path = require('path');

const bin_dir = Path.join(__dirname, "bin");
const build_dir = Path.join(__dirname, "build");
const binary_file = "cpuinfo-js.node";

// Source: https://stackoverflow.com/a/32197381
const deleteFolderRecursive = function (path) {
    if (fs.existsSync(path)) {
        fs.readdirSync(path).forEach((file, index) => {
            const curPath = Path.join(path, file);
            if (fs.lstatSync(curPath).isDirectory()) { // recurse
                deleteFolderRecursive(curPath);
            } else { // delete file
                fs.unlinkSync(curPath);
            }
        });
        fs.rmdirSync(path);
    }
};


function copyBinary() {
    if (fs.existsSync(bin_dir)) {
        console.log(`${bin_dir} exists, deleting it`);
        deleteFolderRecursive(bin_dir);
    }

    console.log(`Creating ${bin_dir}`);
    fs.mkdirSync(bin_dir);

    let dest = Path.join(bin_dir, binary_file);
    console.log(`Copying ${binary_file} to ${dest}`);
    fs.copyFileSync(Path.join(build_dir, "Release", binary_file), dest);
}

function clean() {
    console.log("Cleaning up");
    if (fs.existsSync(build_dir)) {
        console.log(`Deleting directory ${build_dir}`);
        deleteFolderRecursive(build_dir);
    }
}

function invalidArgs() {
    throw new Error("Invalid arguments provided");
}

if (process.argv.length == 3) {
    switch (process.argv[2]) {
        case "--postinstall":
            clean();
            break;
        case "--postbuild":
            copyBinary();
            break;
        default:
            invalidArgs();
    }
} else {
    invalidArgs();
}