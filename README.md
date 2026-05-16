# ESP32 UART Shell

A simple modular UART-based shell for ESP32 built with ESP-IDF and PlatformIO.

This project provides a lightweight serial terminal interface with support for custom commands, input handling, command history, validation, and modular driver architecture.

---

## Features

- UART-based interactive shell
- Modular command system
- Dynamic HELP command generation
- Command history support
- ANSI colored terminal output
- Integer argument validation
- Negative number support
- Ring buffer implementation
- Clean modular architecture
- Easy to extend with custom commands
- ESP-IDF + PlatformIO support

---

## Current Commands

| Command | Description |
|---|---|
| `HELP` | Show all available commands |
| `GREET` | Display greeting message |
| `VERSION` | Show firmware version info |
| `HISTORY` | Print command history |

---

## Project Structure

```text
include/        Header files
src/            Source files
test/           Test files
lib/            External libraries
.vscode/        VSCode configuration
```

---

## Technologies Used

- ESP32
- ESP-IDF
- PlatformIO
- C Programming

---

## Future Improvements

- Command auto-completion
- VT100 cursor navigation
- Built-in logging system
- File system support
- Telnet/WiFi shell access
- Command permissions
- Better shell editing
- Task monitoring commands
- Configurable command registration
- FreeRTOS integration improvements

---

## Build & Flash

```bash
pio run
pio run --target upload
pio device monitor
```

---

## Goal

This project is mainly focused on learning:

- Embedded software architecture
- UART communication
- Shell design
- Modular C programming
- ESP32 firmware development

---

## License

MIT License
