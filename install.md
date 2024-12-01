## Install

https://xgrammar.mlc.ai/docs/start/install.html#option-2-build-from-source

## Quick build whl

```bash
export IMAGE=mlcaidev/package-cpu:254d630
# be sure to have a correct version tag in setup.py
# sync package (maybe needed)
# python scripts/sync_package.py --package . --package-name xgrammar --version 0.1.0-beta-1
scripts/docker/bash.sh --no-gpu $IMAGE ./scripts/build_xgrammar_wheel_manylinux.sh
# the resulting whl will be in python/repaired_wheels
```

## Install the whl

```bash
# download it and upload it to file hosting
wget https://db.cluster.44ai.ch/api/files/4w1vvtmayswbiwc/j36g9xmvs4blf05/xgrammar_0_1_JpiskF81Vo.0-py312-none-any.whl
mv xgrammar_0_1_JpiskF81Vo.0-py312-none-any.whl xgrammar-0.1.0-py3-none-any.whl
# we need to have a conformin wheel name
pip install xgrammar-0.1.0-py3-none-any.whl
```
