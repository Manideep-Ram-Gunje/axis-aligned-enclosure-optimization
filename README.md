# 🧠 Axis-Aligned Enclosure Optimization

This repository contains four progressively optimized C++ solutions to the **Axis-Aligned Enclosure Optimization** problem.

> **Problem Statement**  
Given a set of `N` buildings (each with coordinates and a weight), design an axis-aligned, simple, closed polygon that encloses at least `K` buildings and minimizes:

Total Cost = Perimeter of the polygon + Sum of weights of enclosed buildings


A building is considered enclosed if it lies strictly inside or on the boundary of the polygon.

---

## 🧩 Constraints

- Polygon must be axis-aligned (edges parallel to X/Y axes)
- Polygon must be simple and closed (non-self-intersecting)
- Vertices may be floating points
- Weight `wᵢ` of buildings can be negative
- 1 ≤ K ≤ N ≤ 10000

---

## 📁 File Structure

| File                     | Description                                 | Time Complexity                  |
|--------------------------|---------------------------------------------|----------------------------------|
| `naive_rectangle.cpp`    | Brute-force rectangle over all building pairs | O(N² log N)                      |
| `optimized_rectangle.cpp`| Chan & Har-Peled inspired sweeping algorithm | O(N log N + N·K log K)           |
| `randomized_approx.cpp`  | Randomized (1+ε)-approximation of bounding box | ~O(K log N) per sample × 50     |
| `hybrid_model.cpp`       | Hybrid: rectangle + convex-hull-based polygon | ~O(K log N) per sample × 50     |

---

## 🧪 Approach Summaries

### 1. `naive_rectangle.cpp`
- Enumerates all possible X and Y boundaries
- For each rectangle, counts enclosed buildings
- Optimizes based on total cost
- **Slow**, but works fine for small N

### 2. `optimized_rectangle.cpp`
- Based on sweeping strategies in Chan & Har-Peled's 2012 paper
- Uses prefix sums to efficiently calculate weight sums inside vertical slabs
- **Much faster** and scalable to large inputs

### 3. `randomized_approx.cpp`
- Implements a (1 + ε)-approximation
- Randomly samples subsets of buildings, constructs bounding rectangles
- Picks the one with best cost
- **Extremely fast**, especially when K is small

### 4. `hybrid_model.cpp`
- Merges rectangle approximation with polygonal enclosure
- Computes both rectangle and convex-hull-shaped polygon around sampled buildings
- Chooses the tighter one
- **Best balance** between accuracy and performance

---

## 📚 Research Reference

This work is inspired by:

> **Timothy M. Chan and Sariel Har-Peled**  
> *Smallest k-Enclosing Rectangle Revisited*  
> [https://doi.org/10.1137/110851725](https://doi.org/10.1137/110851725)  
> (SIAM Journal on Computing, 2012)

Key contributions from the paper include:
- Efficient `O(n log n + nk log k)` sweeping techniques
- Random sampling for approximate solutions
- Sub-rectangle filtering strategies

---

## 🛠️ How to Compile & Run

### Using g++ on Windows (Git Bash or WSL):

```bash
g++ -std=c++17 algorithms/naive_rectangle.cpp -o naive
./naive < input.txt


---


## 🤝 Contributors

This project was developed as part of a Coding Club challenge at **IIT Guwahati**.

| Name                      | Role                            |
|---------------------------|---------------------------------|
| Manideep Ram Gunje        | Core Developer, Repo Maintainer |
| Annigandla Kameshwara Rao | Algorithm Design                |
| Maddala Bogati Sushanth   | Research & Optimization         |
| Sankiti Aishwarya         | Testing & Validation            |
