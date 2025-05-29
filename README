# University Assignment: Matrix Operations & Slot Machine Simulation

**Author**: Theodor Vulpe  
**Course**: PCLP1 (Programming)  
**Assignment Link**: [Tema 1 - CBD (Matrix Operations)](https://ocw.cs.pub.ro/courses/programare/teme_2024/tema1_2024_cbd)

---

## 📖 Overview

This C project implements a **matrix manipulation system** simulating a slot machine, with features like:  
- Circular column rotations (`Task 1`)  
- Winning combination detection (`Task 2`)  
- Dynamic reward calculation (`Tasks 3–5`)  
- Minimum-path cost analysis using **Lee’s algorithm** (`Task 6`)

---

## 🛠️ Implementation Details

### 🔄 Task 1: Circular Column Rotation

- Created a function to rotate matrix columns circularly (simulating slot machine spins)  
- **Key Insight**: Efficiently handles repeated rotations without data loss

### 🎰 Task 2: Winning Combination Detection

- **Modular Design**: Separate functions for each winning pattern (lines, diagonals, "X" shapes)  
- **Edge Cases**:  
  - Avoided double-counting "X" patterns overlapping with diagonals  
  - Used an appearance vector to track distinct symbols for bonus checks

### 💰 Task 3: Reward Calculation

- Leveraged `Task 1` and `Task 2` to compute total rewards after a series of rotations

### 🔍 Task 4: Optimal Symbol Replacement

- Iterated through all possible symbol replacements per cell to maximize rewards

### ♻️ Task 5: Two-Column Rotation Optimization

- Tested all column-pair rotation combinations to find the maximum reward  
- **Critical Step**: Reset columns to their original state after each evaluation

### 🏁 Task 6: Minimum-Path Cost (Lee’s Algorithm)

- **Implementation**:  
  - Used a coordinate queue for BFS traversal  
  - Maintained a cost matrix to track minimum path costs  
  - Dynamic memory allocation for matrices and queues  
- **Optimization**: Revisited cells only if a cheaper path was found

---

## 🚀 How to Build & Run

```bash
# Compile the project
make

# Run the executable
./tema1
