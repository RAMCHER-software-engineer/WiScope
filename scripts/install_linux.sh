#!/bin/bash

echo "[*] Checking package manager..."

if command -v apt-get &> /dev/null; then
    # Debian, Ubuntu, Kali Linux, Parrot OS
    PKG_MANAGER="sudo apt-get install -y"
    echo "[+] APT detected (Debian/Ubuntu/Kali)"
    sudo apt-get update
elif command -v pacman &> /dev/null; then
    # Arch Linux, Manjaro
    PKG_MANAGER="sudo pacman -S --noconfirm"
    echo "[+] Pacman detected (Arch/Manjaro)"
elif command -v dnf &> /dev/null; then
    # Fedora, RedHat, CentOS
    PKG_MANAGER="sudo dnf install -y"
    echo "[+] DNF detected (Fedora/RHEL)"
else
    echo "[!] Error: Could not determine package manager. Please install dependencies manually."
    exit 1
fi

# List of dependencies for WiScope
DEPENDENCIES="tshark nmap cmake g++"

echo "[*] Installing dependencies: $DEPENDENCIES"
$PKG_MANAGER $DEPENDENCIES