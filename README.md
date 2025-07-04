# ComputerOrg_final

## gem5-NVmain

```bash
scons EXTRAS=../NVmain build/X86/gem5.opt
```

## benchmark

```bash
gcc -static benchmark/quicksort.c -o benchmark/quicksort
```

```bash
gcc -static benchmark/multiply.c -o benchmark/multiply
```

## Q2

### enable L3 cache

```bash
./build/X86/gem5.opt configs/example/se.py -c tests/test-progs/hello/bin/x86/linux/hello --cpu-type=TimingSimpleCPU --caches --l2cache --l3cache --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

## Q3

### 2-way

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --l3_assoc=2 --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

### full-way

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --l3_assoc=16384 --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

## Q4

### LRU

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

### LFU

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

### FBRP

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```


## Q5

### write-back

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/multiply --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --l3_assoc=4 --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

### write-through

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/multiply --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --l3_assoc=4 --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```

## bonus

### ENERGYRP

```bash
./build/X86/gem5.opt configs/example/se.py -c ./benchmark/quicksort --cpu-type=TimingSimpleCPU --caches --l1i_size=32kB --l1d_size=32kB --l2cache --l2_size=128kB --l3cache --l3_size=1MB --mem-type=NVMainMemory --nvmain-config=../NVmain/Config/PCM_ISSCC_2012_4GB.config
```