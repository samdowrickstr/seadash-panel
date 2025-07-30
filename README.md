# 🧭 seadash-panel

**A lightweight, Qt 6-based taskbar and system panel for the SeaDash marine desktop environment.**

`seadash-panel` is the core system panel for [SeaDash](https://github.com/samdowrickstr/SeaDash), a marine-optimized desktop environment designed for Raspberry Pi OS Lite. Built for motor yachts, sailing boats, and similar embedded marine systems, it offers real-time system status, GPS data, and seamless integration with the SeaDash stack via D-Bus.

---

## 🚀 Features

- 🛰 **Live GPS Display**  
  Real-time display of coordinates, speed, and heading from NMEA 2000 via D-Bus.

- 🕓 **System Clock**  
  Clean 24-hour marine-style time display.

- 🔔 **Notification Tray**  
  Receives and displays notifications using `seadash-notifyd`.

- ⚡ **System Status Icons**  
  Visual indicators for power, network signal, and other key system stats.

- 🪟 **Fullscreen-aware Auto-Hide** *(planned)*  
  Panel hides automatically when a full-screen app is active.

---

## 🛠️ Built With

- **C++17**
- **Qt 6**
- **D-Bus** (via `QtDBus` module)

---

## 🔗 Dependencies

- `qt6-base-dev`
- `qt6-declarative-dev` *(optional, if using QML in future)*
- `libdbus-1-dev`
- CMake (recommended)

---

## 📦 Installation

```bash
git clone https://github.com/samdowrickstr/seadash-panel.git
cd seadash-panel
mkdir build && cd build
cmake ..
make
sudo make install
