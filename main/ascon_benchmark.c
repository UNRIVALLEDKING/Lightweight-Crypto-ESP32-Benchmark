#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "esp_timer.h"
#include "esp_cpu.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "api.h"
#include "ascon.h"

extern int crypto_aead_encrypt(
    unsigned char *c, unsigned long long *clen,
    const unsigned char *m, unsigned long long mlen,
    const unsigned char *ad, unsigned long long adlen,
    const unsigned char *nsec,
    const unsigned char *npub,
    const unsigned char *k
);

void run_ascon_benchmark() {
    unsigned char key[16] = {0};
    unsigned char nonce[16] = {0};
    unsigned char plaintext[16] = {0};
    
    // VOLATILE prevents the compiler from deleting the loop
    volatile unsigned char ciphertext[32]; 
    unsigned long long clen;
    const int iterations = 1000; 

    vTaskDelay(pdMS_TO_TICKS(100));
    int64_t start_time = esp_timer_get_time();
    uint32_t start_cycles = esp_cpu_get_cycle_count();

    for (int i = 0; i < iterations; i++) {
        // cast to (unsigned char*) because volatile changes the pointer type
        crypto_aead_encrypt((unsigned char*)ciphertext, &clen, plaintext, 16, NULL, 0, NULL, nonce, key);
    }

    uint32_t end_cycles = esp_cpu_get_cycle_count();
    int64_t end_time = esp_timer_get_time();

    printf("--- ASCON-128 Results ---\n");
    printf("Avg Time: %.4f us\n", (float)(end_time - start_time) / iterations);
    printf("Avg Cycles: %.2f\n", (float)(end_cycles - start_cycles) / iterations);
    // Side effect to ensure ciphertext was actually written
    printf("Verification: %02x\n", ciphertext[0]);
}