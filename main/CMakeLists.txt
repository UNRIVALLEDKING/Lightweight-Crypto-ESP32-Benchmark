idf_component_register(SRCS "main.c" "ascon_benchmark.c" "simon_benchmark.c" "present_benchmark.c"
                       INCLUDE_DIRS "."
                       REQUIRES ascon esp_timer)