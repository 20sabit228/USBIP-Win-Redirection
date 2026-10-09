# Remote USB Redirection & Device Virtualization Engine

An end-to-end, modular system built in C and C++17 to transparently forward physical USB devices over local and wide-area networks (NAT/Internet) and mount them as native peripherals on a target machine.

Rather than diving straight into low-level Windows Kernel filter drivers, this project builds the entire stack layer-by-layer in user space using `libusb`, `usbip-win`, custom binary protocols, WebRTC NAT traversal, and modern C++ desktop interfaces.

---

## 🏗 System Architecture & Roadmap Overview

```text
[ Physical USB Device ]
         │
         ▼
 ┌─────────────────────────────────────────────────────────┐
 |  PC A (Host / Exposer Daemon)                            |
 |  ├── Sub-Project 1: libusb Enumeration & Interception    |
 |  ├── Sub-Project 4: RPC Control Plane & Status Daemon    |
 |  └── Sub-Project 3: NAT Traversal / WebRTC DataChannel   |
 └──────────────────────────┬──────────────────────────────┘
                            │ Network Tunnel (TCP / P2P)
                            ▼
 ┌─────────────────────────────────────────────────────────┐
 |  PC B (Client / Receiver & Mount Engine)                |
 |  ├── Sub-Project 2: Binary Network Tunnel               |
 |  ├── Sub-Project 5: Virtual Device Mounting (usbip-win) |
 |  └── Sub-Project 6: Native Desktop GUI (Qt6 / ImGui)    |
 └──────────────────────────┬──────────────────────────────┘
                            │ IOCTL Calls
                            ▼
      [ OS Device Manager / Windows PNP Stack ]

```

---

## 📅 Execution Plan (6 Modular Sub-Projects)

### Month 1: Local Hardware Interception & Core Networking

* **Sub-Project 1: USB Interception (`libusb`)**
* Target: CLI app to enumerate local USB hardware, claim device interfaces (mice, gamepads, storage), and capture raw URB packet buffers in real-time.
* *Branch:* `feature/01-local-usb-interception`


* **Sub-Project 2: Local Binary Tunnel (`C++ Networking`)**
* Target: Ultra-low latency (< 5ms) TCP binary socket streamer transporting raw USB payloads between local host (`usb_sender`) and client (`usb_receiver`).
* *Branch:* `feature/02-binary-network-tunnel`



### Month 2: Internet Connectivity & Control Protocol

* **Sub-Project 3: NAT Traversal & Hole Punching (`libdatachannel`)**
* Target: P2P encrypted networking layer using WebRTC DataChannels and STUN/TURN traversal to connect machines across home Wi-Fi/NATs via short session codes.
* *Branch:* `feature/03-nat-traversal-webrtc`


* **Sub-Project 4: Control Plane & RPC Daemon (`nlohmann/json`)**
* Target: Asynchronous background daemon managing state, device discovery, ping/heartbeat checks, and attach/detach commands using structured JSON messaging.
* *Branch:* `feature/04-rpc-control-daemon`



### Month 3: Virtualization & Native Desktop GUI

* **Sub-Project 5: Virtual Device Mounting (`usbip-win`)**
* Target: Feed incoming USB packets directly into the Windows Plug and Play stack via Win32 IOCTL calls to the `usbip-win` VHCI driver, making remote devices show up in Device Manager.
* *Branch:* `feature/05-usbip-virtual-mounting`


* **Sub-Project 6: Desktop GUI Application (`Qt6` / `Dear ImGui`)**
* Target: Modern C++ desktop GUI displaying local/remote peripheral lists, signal diagnostics, and dynamic attach/detach toggle switches.
* *Branch:* `feature/06-desktop-gui`



---

## 🛠 Tech Stack & Dependencies

| Category | Component / Library | Purpose |
| --- | --- | --- |
| **Language & Toolchain** | C11, C++17, MSVC (Visual Studio 2022) | System-level programming and Windows APIs |
| **USB Interception** | `libusb-1.0` | User-space USB device access & asynchronous URB transfer |
| **Networking & Protocols** | Winsock2, `asio`, `libdatachannel` | TCP socket streaming and WebRTC P2P NAT traversal |
| **Control Plane** | `nlohmann/json` | Modern C++ JSON RPC protocol formatting |
| **Virtualization** | `usbip-win` (VHCI Driver API) | Windows kernel driver integration for peripheral mounting |
| **GUI Framework** | Qt 6 / Dear ImGui | Asynchronous multi-threaded desktop control panel |
| **Inspection & Debug** | Wireshark & USBPcap | Lower-level packet analysis and buffer validation |

---

## 📌 Repository Branch Index

Each milestone is implemented on its own dedicated branch for modular development and clean commit histories:

* `main` — Project overview, architecture docs, and integration status tracking.
* `feature/01-local-usb-interception` — Sub-Project 1 implementation
* `feature/02-binary-network-tunnel` — Sub-Project 2 implementation
* `feature/03-nat-traversal-webrtc` — Sub-Project 3 implementation
* `feature/04-rpc-control-daemon` — Sub-Project 4 implementation
* `feature/05-usbip-virtual-mounting` — Sub-Project 5 implementation
* `feature/06-desktop-gui` — Sub-Project 6 implementation

---

## 📊 Progress Tracker

* [ ] **Sub-Project 1**: Local USB Interception (`libusb`)
* [ ] **Sub-Project 2**: Local Network Binary Tunnel
* [ ] **Sub-Project 3**: NAT Traversal & WebRTC Relay
* [ ] **Sub-Project 4**: Control Plane & RPC Daemon
* [ ] **Sub-Project 5**: Virtual Device Mounting (`usbip-win`)
* [ ] **Sub-Project 6**: C++ Desktop GUI

---

## 🚀 Getting Started (Build Prerequisite Setup)

1. Clone the repository and submodules:
```bash
git clone --recursive https://github.com/YOUR_USERNAME/USBIP-Win-Redirection.git
cd USBIP-Win-Redirection

```


2. Open the project solution in **Visual Studio 2022** (Ensure the *Desktop Development with C++* workload is installed).
3. Switch to the specific feature branch you are building or reviewing:
```bash
git checkout feature/01-local-usb-interception

```
