#!/bin/bash

echo "[*] Checking your system..."
if ! xcode-select -p &> /dev/null; then
    echo "[*] Xcode Command Line Tools not found. Installing..."
    xcode-select --install
    echo "[*] Please run the script again after the installation is complete."
    exit 1
else
    echo "[*] Xcode Command Line Tools are already installed."
fi

if ! command -v brew &> /dev/null; then
    echo "[*] Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    echo "[*] Homebrew is already installed."
fi

ehco "[*] Updating Homebrew..."
brew update

echo "[*] Installing required packages..."
brew install cmake tshark nmap

echo "[*] Configuring access rights to network interfaces..."
if [ ! -e /dev/bpf0 ]; then
    echo "[!] Note: ChmodBPF may need to be manually configured to work without sudo."
fi

echo "[+] Installation and configuration complete."