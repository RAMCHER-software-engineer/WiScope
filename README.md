WiScope: IEEE 802.11 Security Analyzer

WiScope is a high-performance wireless security auditing tool combining C++20, low-level ARM64 (Apple Silicon) assembly, and system traffic-analysis utilities.

Key features
- Hybrid core: Core logic in C++ with critical checks (e.g., privilege verification) implemented in ARM64 assembly to minimize overhead.
- Modular engine: Clear separation into Executor (system interactions), Sniffer (packet capture), and Terminal UI.
- Intelligent setup: Automated dependency installation scripts for macOS (Homebrew) and Linux (APT/Pacman/DNF).
- Safety first: Built-in privilege checks before accessing network interfaces.

Architecture
The project is modular:

- Hardware layer (ASM): Direct interaction with processor registers.
- Core layer (C++): Data processing, parsing tshark output, and process management.
- UI layer: Interactive terminal UI with color-coded RSSI (signal strength) indicators.

Installation and build
1. Clone the repository
```bash
git clone https://github.com/RAMCHER-software-engineer/WiScope
cd WiScope
```

2. Install dependencies
The installer scripts will attempt to install cmake, tshark, and nmap.

For macOS (Homebrew):
```bash
chmod +x scripts/install_mac.sh
./scripts/install_mac.sh
```

For Linux (APT/Pacman/DNF):
```bash
chmod +x scripts/install_linux.sh
./scripts/install_linux.sh
```

3. Build
```bash
mkdir -p build && cd build
cmake ..
make
```

Usage
Working with a network interface in monitor mode requires root privileges:
```bash
sudo ./WiScope
```

Tech stack
- Languages: C++20, ARM64 Assembly
- Build system: CMake
- Tools: TShark (Wireshark engine), Nmap
- Platforms: macOS (Apple Silicon), Linux

Notes
- Use this tool responsibly and only on networks you are authorized to test.
- Scripts and ASM components are optimized for Apple Silicon; on other platforms some functionality may be limited.
