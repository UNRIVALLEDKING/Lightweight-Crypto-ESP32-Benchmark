# Evaluating Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices

This repository contains the bare-metal hardware benchmarking implementations used in the research paper: *"Evaluating Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices: A Security and Performance Evaluation."*

**Department:** Information Technology  
**Institution:** University of Mumbai  
**Degree:** M.S. Cybersecurity

## Overview

A comprehensive performance and security evaluation of lightweight cryptographic algorithms specifically designed for resource-constrained IoT devices. This research benchmarks three leading lightweight ciphers on actual hardware to provide empirical evidence for algorithm selection in embedded systems.

## Hardware Target

All benchmarks were designed for and executed on the **ESP32 (Xtensa Dual-Core 32-bit LX6 microprocessor)** operating at 240 MHz.

- **Dual-Core:** Runs on a single core to avoid interference
- **Memory:** 520 KB SRAM, 4 MB Flash
- **Precision:** Cycle-accurate measurements using `esp_cpu_get_cycle_count()` via ESP-IDF
- **No OS Overhead:** Bare-metal implementation for pure CPU cycle measurement

## Evaluated Algorithms

The `main/` directory contains standalone C implementations for:

| Algorithm | Type | Key Size | Block Size | Reference |
|-----------|------|----------|------------|-----------|
| **SIMON 64/128** | Block Cipher | 128-bit | 64-bit | NIST Lightweight Competition |
| **PRESENT-80** | Block Cipher | 80-bit | 64-bit | ISO/IEC 29129 |
| **ASCON-128** | AEAD Cipher | 128-bit | 128-bit | NIST AEAD Selection 2023 |

### Implementation Details

- **ASCON-128:** Core permutation logic from official NIST reference implementation, optimized for Xtensa architecture
- **SIMON & PRESENT:** Bare-metal implementations with cycle-level precision
- **No External Libraries:** All benchmarks self-contained for maximum accuracy

## Prerequisites

### System Requirements
- **OS:** Linux, macOS, or Windows (with WSL2 recommended)
- **Python:** 3.7 or higher
- **Git:** Latest version
- **USB-to-Serial Driver:** CH340 or CP210x (depending on your ESP32 board)

### Hardware
- **ESP32 Development Board:** ESP32-DEVKIT-V1 or equivalent
- **USB Cable:** Micro-USB for flashing and serial monitoring
- **Optional:** Wokwi account for cloud-based simulation

## Installation

### Step 1: Install ESP-IDF

Two methods available:

#### Method A: Using VS Code Extension (Recommended for Beginners)

The easiest way to set up ESP-IDF on any OS:

1. Install Visual Studio Code: https://code.visualstudio.com/
2. Install the **ESP-IDF Extension** from VS Code marketplace:
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "ESP-IDF"
   - Install official extension by Espressif
3. Click the ESP-IDF icon in the sidebar and select **Install ESP-IDF**
4. Follow the interactive setup wizard (ESP-IDF will download and configure automatically)

#### Method B: Manual Installation

**On Windows (Recommended):**
- Download the **ESP-IDF Windows Installer** (.exe): https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html
- Run the installer and follow on-screen instructions
- Restart your system after installation

**On Linux/macOS:**
```bash
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
./install.sh
source ./export.sh
```

**Or use the IDF-Tool Web Installer:**
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html

### Step 2: Clone This Repository

```bash
git clone https://github.com/yourusername/Lightweight-Crypto-ESP32-Benchmark.git
cd Lightweight-Crypto-ESP32-Benchmark
```

### Step 3: Open in VS Code

If using the ESP-IDF Extension:
1. Open the project folder in VS Code
2. The extension auto-detects ESP-IDF configuration
3. Use the ESP-IDF sidebar for all commands

If using manual installation, set up environment variables:

```bash
# Linux/macOS
source $IDF_PATH/export.sh

# Windows (Git Bash)
source $IDF_PATH/export.sh

# Windows (CMD)
%IDF_PATH%\export.bat
```

### Step 4: Configure and Build

**Using VS Code Extension:**
1. Click ESP-IDF icon in sidebar
2. Select "Device Configuration" to configure target
3. Select "Build Project" to compile

**Using Command Line:**
```bash
# Set target and configure
idf.py set-target esp32
idf.py menuconfig

# Build the project
idf.py build
```

## Running the Benchmarks

### Option 1: Hardware Simulation Using Wokwi (Recommended for Quick Testing)

#### Method A: Wokwi VS Code Extension (Easiest)

1. Install the **Wokwi for VS Code** extension from marketplace
2. Open this project in VS Code
3. Right-click `diagram.json` → Select **"Open in Wokwi Simulator"**
4. The simulator will load and begin execution automatically
5. View real-time results in the serial monitor

**Benefits:**
- No need to leave VS Code
- Live serial output during simulation
- Perfect for testing without physical hardware
- Works on any OS (Linux, macOS, Windows)

#### Method B: Wokwi CLI

**Prerequisites:**
- Free Wokwi account: https://wokwi.com
- Node.js installed: https://nodejs.org/
- Install Wokwi CLI: `npm install -g wokwi-cli`

**Steps:**
```bash
# Build the project first
idf.py build

# Start Wokwi simulation
wokwi-cli --elf build/crypto_benchmark.elf
```

The project includes `diagram.json` configuration with ESP32 and serial monitor pre-configured.

**Output:** Real-time simulation results in the Wokwi serial monitor showing cycle counts and execution times.

### Option 2: Flash to Physical Hardware

#### Using VS Code Extension (Recommended)

1. Connect ESP32 board via USB cable
2. Click ESP-IDF icon in sidebar
3. Select "Select Port" and choose your device
4. Click "Build and Flash" to compile and upload
5. Click "Start Monitoring the Device" to see output

#### Using Command Line

```bash
# Build, flash, and monitor all at once
idf.py build flash monitor
```

The `monitor` command:
- Displays serial output in real-time
- Shows benchmark results (cycles, microseconds, memory usage)
- Auto-restarts on upload

To exit the monitor: Press `Ctrl+]` (or `Ctrl+Shift+]` on Windows)

**Windows Users:** The ESP-IDF installer automatically handles USB drivers (.exe installer recommended)

### Option 3: Build Without Flashing

```bash
# Build only (outputs to build/crypto_benchmark.elf and .bin)
idf.py build

# Files generated:
# - build/crypto_benchmark.elf (for Wokwi or JTAG debugging)
# - build/crypto_benchmark.bin (for manual flashing)
```

## Running the Benchmarks

By default, the project is configured to run all three benchmarks (SIMON, PRESENT, and ASCON) sequentially to provide a full performance comparison in a single execution.

### Customizing Execution
If you wish to run only a specific benchmark, you can modify `main/main.c` by commenting out the function calls in `app_main()`:

```c
void app_main(void) {
    // ...
    run_simon_benchmark();    // Comment out to skip
    run_present_benchmark();  // Comment out to skip
    run_ascon_benchmark();    // Comment out to skip
    // ...
}
```

This approach allows you to isolate a single algorithm for more detailed analysis without changing the build configuration.

## Interpreting Benchmark Results

Actual output from all three algorithms running sequentially:

```
====================================================
   LWC PERFORMANCE EVALUATION - ESP32 (XTENSA)      
====================================================

>>> STARTING SIMON 64/128 BENCHMARK
--- SIMON 64/128 Results ---
Avg Time: 82.9120 us
Avg Cycles: 13265.19
Verification: a9291196

>>> STARTING PRESENT-80 BENCHMARK
--- PRESENT-80 Results ---
Avg Time: 9829.1797 us
Avg Cycles: 1572661.88
Verification: 9e05ff74eb26c0b3

>>> STARTING ASCON-128 (AEAD) BENCHMARK
--- ASCON-128 Results ---
Avg Time: 613.8250 us
Avg Cycles: 98211.25
Verification: 08

====================================================
            ALL BENCHMARKS COMPLETED                
====================================================
```

### Key Metrics

| Metric | Description | Unit |
|--------|-------------|------|
| **Avg Time** | Average execution time per encryption operation | Microseconds (µs) |
| **Avg Cycles** | Average CPU cycles required (normalized to 240 MHz) | Clock cycles |
| **Verification** | Checksum of output (validates correctness) | Hexadecimal |

### Performance Summary Table

| Algorithm | Time (µs) | Cycles | Speed Advantage | Use Case |
|-----------|-----------|--------|-----------------|----------|
| **SIMON 64/128** | 82.91 | 13,265 | ⚡ Fastest | High-speed encryption, minimal latency |
| **ASCON-128** | 613.83 | 98,211 | ⚡⚡ Balanced | Authenticated encryption (AEAD) |
| **PRESENT-80** | 9829.18 | 1,572,662 | 🔒 Most Secure | Maximum security margin (slowest) |

### Binary Size & Memory Footprint

```
Memory Type Usage Summary
┏━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓
┃ Memory Type/Section   ┃ Used [bytes] ┃ Used [%] ┃ Remain [bytes] ┃ Total [bytes] ┃
┡━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━╇━━━━━━━━━━╇━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━┩
│ Flash Code            │        48,788 │     3.7% │                │      1,310 KB │
│ Flash Data            │        34,112 │     2.6% │                │      1,310 KB │
│ IRAM                  │        40,759 │    31.1% │         90,313 │        131 KB │
│ DRAM                  │        12,848 │     7.1% │        167,888 │        180 KB │
│ RTC SLOW              │            64 │     0.8% │          8,128 │          8 KB │
├───────────────────────┼──────────────┼──────────┼────────────────┼───────────────┤
│ **Total Image Size**  │    **134 KB** │ ✓ Compact                                  │
└───────────────────────┴──────────────┴──────────┴────────────────┴───────────────┘
```

**Interpretation:**
- **Fits in ESP32:** Binary size well within 4 MB flash limit
- **Efficient RAM usage:** Only 7.1% of DRAM used (ideal for IoT devices)
- **Execution in IRAM:** Critical code cached in fast instruction RAM for optimal performance

## Project Structure

```
.
├── CMakeLists.txt                 # ESP-IDF project configuration
├── main/
│   ├── main.c                     # Entry point and benchmark orchestrator
│   ├── ascon_benchmark.c          # ASCON-128 benchmark
│   ├── simon_benchmark.c          # SIMON 64/128 benchmark
│   ├── present_benchmark.c        # PRESENT-80 benchmark
│   └── CMakeLists.txt             # Component configuration
├── components/
│   └── ascon/                     # ASCON-128 implementation
│       ├── core.c / core.h
│       ├── encrypt.c / decrypt.c
│       ├── permutations.c / permutations.h
│       └── constants.h
├── build/                         # Build artifacts (auto-generated)
├── diagram.json                   # Wokwi simulation configuration
├── wokwi.toml                     # Wokwi project metadata
└── README.md                      # This file
```

## VS Code Integration (Recommended Workflow)

### Essential VS Code Extensions

1. **ESP-IDF Extension** (by Espressif)
   - One-click build, flash, and monitor
   - Device selection and configuration UI
   - Integrated terminal with proper environment

2. **Wokwi Simulator** (by Wokwi)
   - Right-click `diagram.json` to simulate
   - Real-time serial output
   - No external tools required

3. **Optional but Recommended:**
   - C/C++ IntelliSense (Microsoft)
   - Cortex-Debug (Cortex Debug)
   - Git Graph (for version tracking)

### Typical Workflow

```
1. Edit code in VS Code
   ↓
2. ESP-IDF Extension: "Build Project"
   ↓
3. Choose your method:
   ├─ "Wokwi: Open in Simulator" (for simulation)
   └─ "Build and Flash" (for hardware)
   ↓
4. View results in integrated terminal
```

## Troubleshooting

### Build Errors

**Problem:** `Command 'idf.py' not found`  
**Solution:** Using VS Code extension? Ensure extension is active. Manual setup? Source the environment: `source $IDF_PATH/export.sh`

**Problem:** `CMake Error: Could not find ESP-IDF`  
**Solution:** Set the IDF_PATH: `export IDF_PATH=/path/to/esp-idf`

### Flash Errors

**Problem:** `Failed to open port /dev/ttyUSB0`  
**Solution:**
```bash
# Linux: Add user to dialout group
sudo usermod -a -G dialout $USER
# Restart your session
```

**Problem:** `Timed out waiting for packet header` on Windows  
**Solution:** 
- Use ESP-IDF .exe installer (auto-installs drivers)
- Or manually install USB driver from: https://www.wch-ic.com/downloads/CH341SER_EXE.html

### Simulation Issues

**Problem:** Wokwi simulation won't start  
**Solution:**
1. Verify build succeeded: `ls -la build/crypto_benchmark.elf`
2. Using CLI? Ensure installed: `wokwi-cli --version`
3. Check internet connection (Wokwi cloud requires connectivity)
4. Using extension? Reload VS Code

**Problem:** VS Code extension not detecting ESP-IDF  
**Solution:**
1. Click ESP-IDF icon in sidebar
2. Select "Configure ESP-IDF Extension"
3. Follow the "Install ESP-IDF" wizard
4. Reload VS Code when complete

## Data Analysis and Reporting

To extract and analyze benchmark results:

```bash
# Capture serial output to file (while running)
idf.py build flash monitor | tee benchmark_results.log

# Alternative: Use miniterm directly
miniterm.py /dev/ttyUSB0 115200 > results.log
```

**Analysis Recommendations:**
- Run each benchmark 5-10 times for statistical significance
- Include execution environment details (temperature, supply voltage)
- Compare cycle counts across algorithms for normalized performance
- Document RAM/ROM tradeoffs for embedded system selection

## Citation

If you use this research in your work, please cite:

```bibtex
@thesis{lightweight-crypto-iot-2024,
  author = {Aditya Kumar},
  title = {Evaluating Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices: 
           A Security and Performance Evaluation},
  school = {Department of Information Technology, University of Mumbai},
  year = {2026},
  degree = {Master of Science in Cybersecurity}
}
```

## Documentation

- **ESP-IDF Official Docs:** https://docs.espressif.com/projects/esp-idf/
- **Wokwi Documentation:** https://docs.wokwi.com/
- **NIST Lightweight Crypto:** https://csrc.nist.gov/Projects/Lightweight-Cryptography/
- **ASCON Specification:** https://ascon.iaik.tugraz.at/

## License

This project is provided for academic and research purposes. Ensure compliance with your institution's guidelines and applicable licensing agreements.

## Support

For issues or questions:
1. Check existing GitHub issues
2. Review ESP-IDF documentation
3. Consult the research paper for algorithm-specific details
4. Contact your supervisor or research advisor

---

**Last Updated:** April 2026  
**ESP-IDF Version:** 6.0.0  
**Target Device:** ESP32 @ 240 MHz