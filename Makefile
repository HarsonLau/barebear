
TOOLCHAIN=riscv64-unknown-elf-

CC=$(TOOLCHAIN)gcc
CFLAGS=-march=rv64g -mabi=lp64d -mcmodel=medany -I. -O3
LDFLAGS=-nostdlib -nostartfiles -Tlink.ld -static
CDEFS=-DPRINTF_DISABLE_SUPPORT_FLOAT -D CSR

LIBC=$(wildcard lib/*.c)
SRCS?=$(wildcard src/*.S)
BENCHC=$(wildcard bench/*.c)
LIBO=$(addprefix build/, $(LIBC:c=o))
SRCO=$(addprefix build/, $(SRCS:S=o))

SIM=/home/liuhao/boom_perf_origin/build/simulator-MediumBoomConfig

PODMAN_CSR_CMD= riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany -I. -O3 -nostdlib -nostartfiles -Tlink.ld -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS 

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

podman_qsort:$(LIBC) $(BENCHC)  readcsr_bm.c
	$(PODMAN_CSR_CMD) -o build/qsort readcsr_bm.c bench/*.c lib/crt.S lib/*.c 
podman_qsort_20:$(LIBC) $(BENCHC)  readcsr_bm_20.c
	$(PODMAN_CSR_CMD) -o build/qsort_20 readcsr_bm_20.c bench/*.c lib/crt.S lib/*.c
podman_qsort_30:$(LIBC) $(BENCHC)  readcsr_bm_30.c
	$(PODMAN_CSR_CMD) -o build/qsort_30 readcsr_bm_30.c bench/*.c lib/crt.S lib/*.c
podman_qsort_40:$(LIBC) $(BENCHC)  readcsr_bm_40.c
	$(PODMAN_CSR_CMD) -o build/qsort_40 readcsr_bm_40.c bench/*.c lib/crt.S lib/*.c
podman_qsort_100:$(LIBC) $(BENCHC)  readcsr_bm_100.c
	$(PODMAN_CSR_CMD) -o build/qsort_100 readcsr_bm_100.c bench/*.c lib/crt.S lib/*.c
podman_all_qsort:podman_qsort podman_qsort_20 podman_qsort_30 podman_qsort_40 podman_qsort_100
	echo "compiling all qsort without reading csr"
qsort:$(LIBC) $(BENCHC)  readcsr_bm.c
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && mkdir -p build && make podman_all_qsort"
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-elf-objdump -D build/qsort >build/qsort.dump"
qsort_twice:$(LIBC) $(BENCHC)  readcsr_bm.c
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && mkdir -p build && riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS -DTWICE\
    -o build/qsort_twice readcsr_bm.c bench/*.c lib/crt.S lib/*.c "
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-elf-objdump -D build/qsort_twice >build/qsort_twice.dump"

qsort_csr:$(LIBC) $(BENCHC) readcsr_bm.c
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && mkdir -p build && riscv64-unknown-elf-gcc -march=rv64g -mabi=lp64 -mcmodel=medany \
    -I. -O3 -nostdlib -nostartfiles -Tlink.ld \
    -DPRINTF_DISABLE_SUPPORT_FLOAT -DBAREBEAR_DISABLE_FS -D CSR\
    -o build/qsort_csr readcsr_bm.c bench/*.c lib/crt.S lib/*.c "
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-elf-objdump -D build/qsort_csr >build/qsort_csr.dump"

spike_test: qsort qsort_twice
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear &&spike -l build/qsort 2>output_spike_1.txt"
	 podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear &&spike -l build/qsort_twice 2>output_spike_2.txt"

print_test: qsort qsort_twice
	$(SIM) -V build/qsort 2>output_print_1.txt
	$(SIM) -V build/qsort_twice 2>output_print_2.txt 

delta_test:spike_test print_test
	python3 delta-processor.py

csr_test: qsort_csr
	$(SIM) -V build/qsort_csr 2>output_csr.txt 

test:spike_test print_test csr_test

run_csr:runcsr.c
	podman run -it --rm -v ./:/root/barebear chipyard-slim bash -c "cd /root/barebear && riscv64-unknown-linux-gnu-gcc -O3 -o runcsr runcsr.c"
