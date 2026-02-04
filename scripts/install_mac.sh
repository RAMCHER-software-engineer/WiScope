#!/bin/bash

echo "[*] Checking your system..."

if ! xcode-select -p &> /dev/null; then
    echo "[*] Xcode Command Line Tools not found. Installing..."
    xcode-select --install
    echo "[!] A popup window has appeared. Please finish the installation and RERUN this script."
    exit 1
else
    echo "[*] Xcode Command Line Tools are already installed."
fi

if ! command -v brew &> /dev/null; then
    echo "[*] Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    
    if [[ -f /opt/homebrew/bin/brew ]]; then
        eval "$(/opt/homebrew/bin/brew shellenv)"
    fi
else
    echo "[*] Homebrew is already installed."
fi

echo "[*] Updating Homebrew..."
brew update

echo "[*] Installing required packages..."
brew install cmake termshark nmap

echo "[*] Configuring access rights to network interfaces..."
if [ -r /dev/bpf0 ]; then
    echo "[*] You have read access to network interfaces."
else
    echo "[!] Warning: You might need sudo or ChmodBPF to capture traffic with tshark."
fi

echo "[+] Installation and configuration complete."