# rfid-attendance-system
An RFID-based attendance system using ESP32 for automated attendance recording and digital record management.
# RFID Attendance System

An ESP32-based RFID attendance system designed to automate attendance recording, reduce manual workload, and minimize errors in attendance records.

---

# Project Overview

Manual attendance recording can be repetitive, time-consuming, and prone to human error.

This project was developed to automate attendance recording using RFID identification, digital data storage, and Python-based data processing.

Each student is assigned an RFID card with a unique UID. When the card is scanned, the system records the UID together with the reporting time and stores the information in a CSV file on an SD card.

The attendance CSV is later processed using Python and compared against a student database containing student names and their RFID UIDs. The system then generates a final attendance report containing each student's name, RFID ID, reporting time, and attendance status.

---

# System Workflow

             Student RFID Card
                     │
                     ▼
             MFRC522 RFID Reader
                     │
                     ▼
                  ESP32
                ┌───┴────┐
                │        │
                ▼        ▼
             DS1302    SD Card
               RTC
                │
                ▼
        UID + Time Stored
          as Attendance CSV
                │
                ▼
        Python Data Processing
                │
                ▼
        Student Database
     (Name + RFID UID List)
                │
                ▼
      Student Information Matching
                │
                ▼
      Final Attendance Report
                │
                ▼
Name | UID | Reporting Time | Status
```

---

# Main Features

- Automatic attendance recording
- RFID-based student identification
- Automatic reporting time recording
- Duplicate attendance detection
- Duplicate scans automatically ignored
- Attendance stored as CSV files
- SD card data storage
- Python-based attendance processing
- Automatic student name matching
- Automatic Present/Absent generation
- LED status indication

---

# Hardware Components

- ESP32
- MFRC522 RFID Reader
- RFID Cards
- SD Card
- DS1302 Real-Time Clock (RTC)
- Breadboard
- LEDs
- Resistors
- Jumper Wires

---

# Software and Libraries

## Embedded System

- Arduino IDE
- SPI Library
- MFRC522 Library
- RtcDS1302 Library
- FS Library
- SD_MMC Library

## Desktop Application

- Python
- CSV Module
- Tkinter

## Development Tool

- Sublime Text

---

# LED Status Indicators

| LED | Meaning |
|------|---------|
| 🔵 Blue | System operational |
| 🔴 Red | SD card unavailable |
| 🟢 Green Flash | Attendance recorded successfully |
| 🔴 Red Flash | Duplicate attendance ignored |

Currently, no buzzer or sound feedback has been implemented.

---

# Attendance Collection Process

1. Student scans an RFID card.
2. MFRC522 reads the card UID.
3. ESP32 checks whether the UID has already been recorded.
4. If the UID has not been recorded:
   - Current date and time are obtained from the RTC.
   - UID and timestamp are stored in a CSV file on the SD card.
5. If the UID has already been recorded:
   - The duplicate scan is ignored.
   - The red LED flashes.

---

# Attendance Processing

After attendance collection:

- The attendance CSV is copied from the SD card.
- Python loads the attendance file.
- Python loads the student database.
- RFID UIDs are matched with student names.
- Students not found in the attendance file are marked **Absent**.
- Students found in the attendance file are marked **Present**.
- A final attendance report is generated.

The final report contains:

- Student Name
- RFID UID
- Reporting Time
- Attendance Status

---

# Hardware Prototype

![Hardware Prototype](images/hardware.jpg)

---

# Generated Attendance Report

![Attendance Report](images/attendance-report.jpg)

---

# Student Database Selection

![Database Selection](images/database-interface.jpg)

---

# Challenges Encountered

During development, several challenges were encountered:

- SD card mounting failures
- ESP32 and RFID communication problems
- Wiring issues
- Software bugs
- Duplicate attendance detection
- Python CSV processing
- Communication interference between the RTC and RFID reader

---

# Troubleshooting Approach

Instead of attempting to solve every problem at once, each subsystem was isolated and tested independently.

The development process followed these steps:

1. Build one subsystem.
2. Test it independently.
3. Debug hardware and software issues.
4. Integrate one additional subsystem.
5. Test again.
6. Repeat until the complete system operated successfully.

This systematic approach made it easier to identify the source of problems and ensured reliable integration of all hardware and software components.

---

# Project Status

✅ Completed

The system successfully:

- Reads RFID cards
- Records attendance
- Stores attendance data on an SD card
- Prevents duplicate attendance
- Processes attendance using Python
- Matches RFID IDs with student names
- Generates a complete attendance report
- Automatically identifies absent students

---

# Future Improvements

Planned improvements include:

- Buzzer for sound feedback
- LCD or OLED display
- Wireless attendance synchronization
- Cloud database integration
- Automatic report emailing
- Web dashboard
- Improved enclosure design
- Attendance analytics and statistics

---

# Skills Demonstrated

This project demonstrates experience in:

- Embedded Systems
- ESP32 Programming
- RFID Technology
- Hardware Troubleshooting
- Circuit Prototyping
- SPI Communication
- SD Card File Management
- Real-Time Clock Integration
- CSV Data Processing
- Python Programming
- Tkinter GUI Development
- Debugging
- Problem Solving
- System Integration
- Data Management

---

# Author

**Hakim Iddrisu**

📍 Western North, Ghana

📧 hakimiddrisu22@gmail.com

GitHub: https://github.com/hakimiddrisu
