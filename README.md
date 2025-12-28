# Limit Order Book

A C++/Python hybrid project implementing a **Limit Order Book (LOB)** for tracking and executing buy and sell orders, including AVL-tree-backed limit management, order matching, and JSON serialization for visualization.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)

---

## Overview

A **Limit Order Book** stores buy and sell orders for a market, matching orders based on **price-time priority**.  
This project implements:

- **Buy and sell trees** for fast price lookup (AVL trees)
- **Order insertion, cancellation, and execution**
- JSON output for tree visualization
- Market orders and limit orders support

---

## Features

- **Efficient order storage** using AVL trees for buy/sell limits
- **Order matching engine** supporting partial and full fills
- JSON serialization of the order book
- **Automatic updating** of best bid/ask prices
- **FIFO execution** for orders at the same price level

---

## Project Structure

```
.
├── src/                   # C++ source files
│   ├── Book.cpp
│   ├── Order.cpp
│   └── Limit.cpp
├── header_files/               # Header files
│   ├── Book.h
│   └── Order.h
│   ├── httplib.h
│   └── Limit.h
├── api_tester/                 # tests (python)
├── Makefile         # Build configuration
├── .gitignore
└── README.md
```

---

## Installation

1. **Clone the repository**:

```bash
git clone https://github.com/talK951/LimitOrderBookAPI.git
```

2. **Install dependencies**:

- Requires **C++17 compiler** (GCC/Clang/MSVC)
- Requires installed python 3+ version

3. **Build the project** using CMake:

```bash
make
```

---

## Usage

1. **Run the compiled program**:

```bash
./lob
```
