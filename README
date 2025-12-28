# Limit Order Book

A C++/Python hybrid project implementing a **Limit Order Book (LOB)** for tracking and executing buy and sell orders, including AVL-tree-backed limit management, order matching, and JSON serialization for visualization.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

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
│   └── main.cpp
├── include/               # Header files
│   ├── Book.h
│   └── Order.h
├── tests/                 # Unit tests
├── scripts/               # Python utilities (optional)
├── CMakeLists.txt         # Build configuration
├── .gitignore
└── README.md
```

---

## Installation

1. **Clone the repository**:

```bash
git clone https://github.com/USERNAME/limit-order-book.git
cd limit-order-book
```

2. **Install dependencies**:

- Requires **C++17 compiler** (GCC/Clang/MSVC)
- [nlohmann/json](https://github.com/nlohmann/json) (header-only JSON library)

3. **Build the project** using CMake:

```bash
mkdir build
cd build
cmake ..
make
```

---

## Usage

1. **Run the compiled program**:

```bash
./lob
```

2. **Example operations**:

- Add order:
  ```cpp
  book->addOrder(orderId, price, shares, isBuy);
  ```
- Cancel order:
  ```cpp
  book->cancelOrder(orderId, price, isBuy);
  ```
- Execute market order:
  ```cpp
  book->executeOrder(shares, isBuy);
  ```
- Serialize book to JSON:
  ```cpp
  book->returnTreeLimitsInOrder(book->buyTree, buyTreeJson);
  ```

---

## Testing

Unit tests are provided in `tests/`. Run them using:

```bash
cd build
ctest
```

Test scenarios cover:

- Single and multi-limit orders
- Partial and full fills
- Edge cases (empty book, large market orders)

---

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a branch (`git checkout -b feature/my-feature`)
3. Commit your changes (`git commit -am "Add feature"`)
4. Push to the branch (`git push origin feature/my-feature`)
5. Open a pull request

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
