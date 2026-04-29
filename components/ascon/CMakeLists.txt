# This finds every .c and .S file in your ascon folder
file(GLOB_RECURSE srcs "*.c" "*.S")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS "."
                       PRIV_INCLUDE_DIRS ".")