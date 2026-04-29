#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Declare the benchmark functions from your other files
extern void run_ascon_benchmark(void);
extern void run_simon_benchmark(void);
extern void run_present_benchmark(void);

void app_main(void) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    printf("\n====================================================\n");
    printf("   LWC PERFORMANCE EVALUATION - ESP32 (XTENSA)      \n");
    printf("====================================================\n\n");

    // 1. Run SIMON
    printf(">>> STARTING SIMON 64/128 BENCHMARK\n");
    run_simon_benchmark();
    vTaskDelay(pdMS_TO_TICKS(500));

    // 2. Run PRESENT
    printf("\n>>> STARTING PRESENT-80 BENCHMARK\n");
    run_present_benchmark();
    vTaskDelay(pdMS_TO_TICKS(500));

    // 3. Run ASCON
    printf("\n>>> STARTING ASCON-128 (AEAD) BENCHMARK\n");
    run_ascon_benchmark();

    printf("\n====================================================\n");
    printf("            ALL BENCHMARKS COMPLETED                \n");
    printf("====================================================\n");

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}