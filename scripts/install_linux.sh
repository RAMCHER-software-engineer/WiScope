#!/bin/bash

echo "[*] Checking package manager..."

if command -v apt-get &> /dev/null; then
    PKG_MANAGER="sudo apt-get install -y"
    UPDATE_CMD="sudo apt-get update"
    DEP_GPP="g++"
    DEP_TSHARK="tshark"
    echo "[+] APT detected"

elif command -v pacman &> /dev/null; then
    PKG_MANAGER="sudo pacman -S --noconfirm"
    UPDATE_CMD="sudo pacman -Sy"
    DEP_GPP="gcc"
    DEP_TSHARK="wireshark-cli"
    echo "[+] Pacman detected"

elif command -v dnf &> /dev/null; then
    PKG_MANAGER="sudo dnf install -y"
    UPDATE_CMD="sudo dnf check-update" 
    DEP_GPP="gcc-c++"
    DEP_TSHARK="wireshark-cli"
    echo "[+] DNF detected"
else
    echo "[!] Error: Package manager not supported."
    exit 1
fi

DEPENDENCIES="cmake nmap $DEP_GPP $DEP_TSHARK"

echo "[*] Updating repositories..."
$UPDATE_CMD

echo "[*] Installing dependencies: $DEPENDENCIES"
$PKG_MANAGER $DEPENDENCIES

if command -v tshark &> /dev/null; then
    echo "[*] Post-install: Adding $USER to 'wireshark' group..."
    sudo usermod -aG wireshark $USER 2>/dev/null || sudo usermod -aG pcap $USER 2>/dev/null
    echo "[!] Note: You may need to relogin for tshark permissions to take effect."
fi

echo "[+] Done."