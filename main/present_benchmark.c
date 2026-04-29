#include <stdio.h>
#include <stdint.h>
#include "esp_timer.h"
#include "esp_cpu.h"

static const uint8_t sbox[] = {0xc,0x5,0x6,0xb,0x9,0x0,0xa,0xd,0x3,0xe,0xf,0x8,0x4,0x7,0x1,0x2};

void present_encrypt(volatile uint64_t *state, const uint64_t key_high) {
    uint64_t s = *state;
    for (int i = 1; i <= 31; i++) {
        s ^= key_high; 
        uint64_t temp_s = 0;
        for (int j = 0; j < 16; j++) {
            temp_s |= (uint64_t)sbox[(s >> (j * 4)) & 0xF] << (j * 4);
        }
        uint64_t permuted = 0;
        for (int j = 0; j < 64; j++) {
            int p = (j * 16) % 63;
            if (j == 63) p = 63;
            permuted |= ((temp_s >> j) & 1) << p;
        }
        s = permuted;
    }
    *state = s;
}

void run_present_benchmark(void) {
    volatile uint64_t state = 0x0123456789ABCDEF; // VOLATILE FIX
    uint64_t key = 0x0000000000000000;
    const int iterations = 100; // Lower iterations for PRESENT to avoid watchdog

    int64_t start_time = esp_timer_get_time();
    uint32_t start_cycles = esp_cpu_get_cycle_count();

    for (int i = 0; i < iterations; i++) {
        present_encrypt(&state, key);
    }

    uint32_t end_cycles = esp_cpu_get_cycle_count();
    int64_t end_time = esp_timer_get_time();

    printf("--- PRESENT-80 Results ---\n");
    printf("Avg Time: %.4f us\n", (float)(end_time - start_time) / iterations);
    printf("Avg Cycles: %.2f\n", (float)(end_cycles - start_cycles) / iterations);
    printf("Verification: %016llx\n", state);
}