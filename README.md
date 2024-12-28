# ML-KEM NATIVE


## Quickstart for Ubuntu

```bash
# Clone mlkem-native
git clone https://github.com/NgKore47/mlkem-native.git
cd mlkem-native

# Install base packages
sudo apt-get update
sudo apt-get install make gcc python3

# Build and run base tests
make quickcheck

# Build and run all tests
./scripts/tests all
```

## Benchmarking

```shell
make bench
```
Binaries are created now perform benchmarking

```shell
./test/build/mlkem512/bin/bench_mlkem512
./test/build/mlkem768/bin/bench_mlkem768
./test/build/mlkem1024/bin/bench_mlkem1024
```
