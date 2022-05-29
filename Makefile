
TOOLCHAIN=riscv64-unknown-elf-

CC=$(TOOLCHAIN)gcc
CFLAGS=-march=rv64g -mabi=lp64d -mcmodel=medany -I. -O3
LDFLAGS=-nostdlib -nostartfiles -Tlink.ld -static
CDEFS=-DPRINTF_DISABLE_SUPPORT_FLOAT

LIBC=$(wildcard lib/*.c)
SRCS?=$(wildcard src/*.S)
BENCHC=$(wildcard bench/*.c)
LIBO=$(addprefix build/, $(LIBC:c=o))
SRCO=$(addprefix build/, $(SRCS:S=o))

SIM=/home/liuhao/boom_perf_origin/build/simulator-MediumBoomConfig

.PHONY: build clean spike_test csr_test print_test test

all: build | build/main

build:
	mkdir -p build build/src build/lib

build/lib/%.o: lib/%.c
	$(CC) $(CFLAGS) $(CDEFS) -c -o $@ $<

build/src/%.S: src/%.S
	./unimacro -o $@ $<

build/src/%.o: build/src/%.S
	$(CC) $(CFLAGS) -DCASENAME=$(subst /,_,$(subst .,_,$(<:build/%=%))) -c -o $@ $<

build/%.o: build/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.c:
	./instantiate $(SRCS) -o build/main.c

build/main: build/main.o $(LIBO) $(SRCO) lib/crt.S
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf build

%.dump: %
	$(TOOLCHAIN)objdump -D $< > $@

%.elf: %
	$(TOOLCHAIN)readelf -e $< > $@

read_csr:$(LIBC) $(BENCHC) readcsr_bm.c
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS \
    -o readcsr_bm readcsr_bm.c bench/*.c lib/crt.S lib/*.c "

qsort:$(LIBC) $(BENCHC)  readcsr_bm.c
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && mkdir -p build && riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS \
    -o build/qsort readcsr_bm.c bench/*.c lib/crt.S lib/*.c "

qsort_csr:$(LIBC) $(BENCHC) readcsr_bm.c
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && mkdir -p build && riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS -D CSR\
    -o build/qsort_csr readcsr_bm.c bench/*.c lib/crt.S lib/*.c "

spike_test: qsort
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear &&spike -l build/qsort 2>&1 | wc -l"
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear &&spike -l build/qsort 2>&1 | grep jal| wc -l"

print_test: qsort
	$(SIM) -V build/qsort 2>output.txt 
	python3 /home/liuhao/boom_perf_origin/util/branch-processor.py output.txt

csr_test: qsort_csr
	$(SIM) -V build/qsort_csr 2>output_csr.txt 

test:spike_test print_test csr_test

run_csr:runcsr.c
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-linux-gnu-gcc -O3 -o runcsr runcsr.c"
