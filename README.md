# 🏧 ATM Simulation System (C++)

A console-based ATM simulation program written in C++. This project demonstrates core banking functionalities such as balance checking, cash withdrawal, deposit, PIN change, and mini statements — all within a secure and interactive terminal interface.

---

## 📌 Features

- ✅ **PIN Verification** (with 3 attempts limit)
- 💰 **Check Balance** for Savings or Current account
- 💸 **Withdraw Cash** (with denomination breakdown & limit validation)
- 💵 **Deposit Cash** (with deposit limit validation)
- 🔐 **Change PIN** (via OTP simulation)
- 🧾 **Mini Statement** (last 5 transactions shown)
- 💳 **Account Selection** (Savings / Current)
- 🧠 **Input Validation** to prevent invalid entries
- 🧼 Cross-platform **Clear Screen** functionality

---

## 🛠 Technologies Used

- **Language**: C++
- **Standard Libraries**: 
  - `<iostream>`, `<vector>`, `<ctime>`, `<thread>`, `<chrono>`, `<iomanip>`, `<limits>`, `<cstdlib>`, `<cstring>`

---
## 📂 File Structure
```
atm-system/ 
│ 
├── atm.cpp # Main source code 
├── README.md # Project documentation 
```
---

## 🚀 How to Run

1. **Clone the Repository**
   ```bash
   git clone https://github.com/your-username/atm-system.git
   cd atm-system
   g++ -o atm atm.cpp
```
