const read = require('@xblox/fs/read');
const write = require('@xblox/fs/write');
const path = require('path');
const cwd = path.resolve('../../');
const pkgVersion = read.sync('package.json', 'json').version;
const cid = read.sync('package.json', 'json').cid;

async function status(workingDir) {
  const git = require('simple-git/promise');

  let statusSummary = null;
  try {
    statusSummary = await git(workingDir).log();
  }
  catch (e) {
    // handle the error
  }

  return statusSummary;
}


status(cwd).then((status) => {
  const version =
    `#ifndef VERSION_H \n
     #define VERSION_H \n
     #define VERSION "${pkgVersion}|${status.latest.hash}"\n
     #define CID "${cid}"\n
     #endif`;

  write.sync('./Version.h', version);
  console.log(version);
}
);