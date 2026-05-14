# Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices: A Security and Performance Evaluation

[![Paper](https://img.shields.io/badge/Paper-IJERT-blue.svg)](https://www.ijert.org/research/lightweight-cryptographic-algorithms-for-resource-constrained-iot-devices-a-security-and-performance-IJERTV15IS050866.pdf)
[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-6.0.0-orange.svg)](https://docs.espressif.com/projects/esp-idf/)
[![License](https://img.shields.io/badge/License-Academic-green.svg)](#license)

This repository contains the bare-metal hardware benchmarking implementations for the research paper:  
**"Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices: A Security and Performance Evaluation"**

---

## 📄 Research Publication

**Authors:**  
- **Aditya Kumar** — M.S. Cybersecurity, University of Mumbai  
- **Prof. Jayesh Shinde** — Department of IT, University of Mumbai  

**Published In:** *International Journal of Engineering Research & Technology (IJERT)*, Volume 15, Issue 05, May 2026.  
**🔗 Paper Link:** [Read on IJERT](https://www.ijert.org/research/lightweight-cryptographic-algorithms-for-resource-constrained-iot-devices-a-security-and-performance-IJERTV15IS050866.pdf)  
**🔗 DOI:** (Activation Pending)

---

## 🚀 Overview & Key Contributions

A comprehensive performance and security evaluation of leading lightweight ciphers (SIMON, PRESENT, ASCON) on ESP32 hardware. This research provides empirical evidence for algorithm selection in resource-constrained IoT environments.

### Key Contributions:
- **Cycle-Accurate Benchmarking:** Precise measurements using `esp_cpu_get_cycle_count()` on actual hardware.
- **Bare-Metal Implementation:** Minimal OS overhead for pure CPU performance evaluation.
- **Comparative Analysis:** Evaluation of block ciphers (SIMON, PRESENT) vs. AEAD (ASCON-128).
- **Optimization Insights:** Performance behavior on Xtensa LX6 architecture under different compiler optimizations.
- **Reproducible Framework:** A plug-and-play benchmarking suite for cryptographic research.

---

## 🛠️ Hardware Target

Benchmarks are executed on the **ESP32 (Xtensa Dual-Core 32-bit LX6)**:
- **Clock Speed:** 240 MHz
- **Isolation:** Executes on a single core to eliminate multi-core interference.
- **Memory:** 520 KB SRAM, 4 MB Flash.
- **Execution:** Critical code is placed in **IRAM** for zero-wait-state performance.

---

## 🔐 Evaluated Algorithms

| Algorithm | Type | Key / Block Size | Rounds | Reference / Standard | Primary Use Case |
|-----------|------|------------------|--------|----------------------|------------------|
| **SIMON 64/128** | Block Cipher | 128 / 64-bit | 44 | NSA Lightweight Cipher | High-speed software optimization |
| **PRESENT-80** | Block Cipher | 80 / 64-bit | 31 | ISO/IEC 29192-2 | Hardware-efficient encryption |
| **ASCON-128** | AEAD Cipher | 128 / 128-bit | 12 / 6 | NIST AEAD Selection (2023) | Authenticated encryption for IoT |

---

## 📦 Getting Started

### 1. Prerequisites
- **Hardware:** ESP32 DevKit V1 (or equivalent) + Micro-USB cable.
- **Software:** Python 3.7+, Git, and Serial Drivers (CH340/CP210x).

### 2. Setup ESP-IDF
The project requires **ESP-IDF v6.0.0+**.

*   **Option A (VS Code):** Install the [ESP-IDF Extension](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension) and use the "Install ESP-IDF" wizard.
*   **Option B (CLI):** Follow the [Official Installation Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).

### 3. Clone Repository
```bash
git clone https://github.com/yourusername/Lightweight-Crypto-ESP32-Benchmark.git
cd Lightweight-Crypto-ESP32-Benchmark
```

---

## 💻 Usage

### Build & Run (Physical Hardware)
1.  **Configure:** `idf.py set-target esp32`
2.  **Flash & Monitor:** `idf.py build flash monitor`
    *   *To exit monitor: `Ctrl + ]`*

### Simulation (Wokwi)
No hardware? Use the Wokwi simulator:
1.  **VS Code:** Install "Wokwi for VS Code", right-click `diagram.json` → **Open in Wokwi Simulator**.
2.  **CLI:** `wokwi-cli --elf build/crypto_benchmark.elf`

---

## 📊 Benchmark Results

### Performance Metrics (at 240 MHz)

| Algorithm | Time (µs) | CPU Cycles | Relative Speed | Primary Benefit |
|-----------|-----------|------------|----------------|-----------------|
| **SIMON 64/128** | 82.91 | 13,265 | ⚡⚡⚡ | Fastest execution |
| **ASCON-128** | 613.83 | 98,211 | ⚡⚡ | Authenticated Encryption |
| **PRESENT-80** | 9829.18 | 1,572,662 | 🔒 | High security margin |

### Memory Footprint
The implementation is highly optimized for IoT, consuming only **~134 KB** of total image size.

| Memory Section | Usage | % Used | Total Available |
|----------------|-------|--------|-----------------|
| **Flash Code** | 48.8 KB | 3.7% | 1.3 MB |
| **IRAM** | 40.8 KB | 31.1% | 131 KB |
| **DRAM (Static)** | 12.8 KB | 7.1% | 180 KB |

---

## 📁 Project Structure

```text
.
├── main/
│   ├── main.c              # Orchestrator
│   ├── ascon_benchmark.c   # ASCON implementation & tests
│   ├── simon_benchmark.c   # SIMON implementation & tests
│   └── present_benchmark.c # PRESENT implementation & tests
├── components/
│   └── ascon/              # Shared ASCON core logic
├── diagram.json            # Wokwi simulation config
└── README.md               # You are here
```

---

## 📜 Citation

If you use this work in your research, please cite:

```bibtex
@article{kumar_shinde_2026_lightweight,
  author = {Aditya Kumar and Jayesh Shinde},
  title = {Lightweight Cryptographic Algorithms for Resource-Constrained IoT Devices: A Security and Performance Evaluation},
  journal = {International Journal of Engineering Research & Technology (IJERT)},
  volume = {15},
  number = {05},
  year = {2026},
  url = {https://www.ijert.org/research/lightweight-cryptographic-algorithms-for-resource-constrained-iot-devices-a-security-and-performance-IJERTV15IS050866.pdf}
}
```

---

## ⚖️ License & Support

- **License:** This project is provided for academic and research purposes.
- **Support:** For questions, please open a GitHub issue or refer to the [official ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/).

**Last Updated:** May 2026  
**Target:** ESP32 @ 240MHz
