## Install

https://xgrammar.mlc.ai/docs/start/install.html#option-2-build-from-source

## Quick build whl

```bash
export IMAGE=mlcaidev/package-cpu:254d630
# be sure to have a correct version tag
# sync package (maybe needed)
# python scripts/sync_package.py --package . --package-name xgrammar --version 0.1.0-beta-1
scripts/docker/bash.sh --no-gpu $IMAGE ./scripts/build_xgrammar_wheel_manylinux.sh
# the resulting whl will be in python/repaired_wheels
```
