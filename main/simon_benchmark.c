#include <stdio.h>
#include <stdint.h>
#include "esp_timer.h"
#include "esp_cpu.h"

#define ROTL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

void simon_encrypt_64_128(volatile uint32_t *ct, const uint32_t *pt, const uint32_t *rk) {
    uint32_t y = pt[0], x = pt[1];
    for (int i = 0; i < 44; i++) {
        uint32_t tmp = x;
        x = y ^ (ROTL32(x, 1) & ROTL32(x, 8)) ^ ROTL32(x, 2) ^ rk[i];
        y = tmp;
    }
    ct[0] = y; ct[1] = x;
}

void run_simon_benchmark(void) {
    uint32_t rk[44] = {0};
    uint32_t pt[2] = {0x6c6c6548, 0x206f776f};
    volatile uint32_t ct[2]; // VOLATILE FIX
    const int iterations = 1000;

    int64_t start_time = esp_timer_get_time();
    uint32_t start_cycles = esp_cpu_get_cycle_count();

    for (int i = 0; i < iterations; i++) {
        simon_encrypt_64_128(ct, pt, rk);
    }

    uint32_t end_cycles = esp_cpu_get_cycle_count();
    int64_t end_time = esp_timer_get_time();

    printf("--- SIMON 64/128 Results ---\n");
    printf("Avg Time: %.4f us\n", (float)(end_time - start_time) / iterations);
    printf("Avg Cycles: %.2f\n", (float)(end_cycles - start_cycles) / iterations);
    printf("Verification: %08lx\n", ct[0]);
}