# MPI Parallel Lab

This project includes several simple C++ programs utilizing **MPI (Message Passing Interface)** for parallel computing. Each program explores number theory concepts and implements parallel distribution strategies such as ring, block, and block-cyclic distributions.

## 📁 Project Files

1. `deniz_sayisi.cpp`
2. `defne_sayisi.cpp`
3. `palandoken_sayisi.cpp`
4. `bora_sayisi.cpp`
5. `palandoken_sayisi_block.cpp`
6. `palandoken_sayisi_blockcyclic.cpp`
7. `leibniz_pi.cpp`

---

## 🐚 Deniz Number

### Definition:
A number is a **Deniz Number** if:
- It is **composite** (not prime),
- It is a **palindrome**,
- The **sum of its proper divisors** is also a **palindrome**.

🔸 Example:  
1001 → Composite, Palindrome, Sum of proper divisors = 343 (Palindrome)

### Code Summary:
- Uses ring distribution with MPI.
- Master receives limits, broadcasts them.
- All processes compute in parallel.

---

## 🌸 Defne Number

### Definition:
A number is a **Defne Number** if:
- It has **unique digits**,
- It has **at least 15 palindromic divisors**.

🔸 Example:  
2904 → 16 palindromic divisors, all digits unique.

---

## 🏔️ Palandöken Number

### Definition:
A number is a **Palandöken Number** if:
- All digits are unique,
- The **number of odd digits** is **greater than** the number of even digits.

🔸 Example:  
751824693 → 5 odd, 4 even → ✅ Palandöken

---

## 🔢 Bora Number

### Definition:
A **Bora Number** must:
- Have **unique digits**,
- Be in **strictly increasing order** from left to right.

🔸 Example:  
12467 → ✅  
76241 → ❌

---

## 🔁 Palandöken Numbers (Block Distribution)

- Numbers are divided into **equal contiguous blocks** across processes.
- Remaining numbers are distributed to the first few processes.

🔸 Example:  
`altLimit = 1`, `ustLimit = 21`, `size = 4`  
→ rank 0: 1–6  
→ rank 1: 7–11  
→ rank 2: 12–16  
→ rank 3: 17–21

---

## 🔁 Palandöken Numbers (Block-Cyclic Distribution)

- Numbers are split into **fixed-size blocks** (e.g., 3),
- These blocks are **distributed cyclically** among processes.

🔸 Example:  
`altLimit = 1`, `blokBoyutu = 3`, `size = 4`

→ rank 0: 1–3, 13–15, 25–27  
→ rank 1: 4–6, 16–18, 28–30  
→ rank 2: 7–9, 19–21  
→ rank 3: 10–12, 22–24

---

## 🧮 Leibniz Series for Pi

### Formula:
π ≈ 4 × (1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)

- Each process computes a portion of the series.
- Results are reduced to the master process to calculate π.

---

## 💻 How to Compile & Run

```bash
mpic++ -o program deniz_sayisi.cpp
mpirun -np 4 ./program
```

Replace the `.cpp` file with any example you want to test.

---

## 🎯 Purpose

This repository provides practical MPI examples for those learning **parallel computing** and **basic number theory applications**.  
All codes are beginner-friendly and showcase fundamental distribution techniques.

