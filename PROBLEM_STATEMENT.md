# 🧠 Axis-Aligned Enclosure Optimization

## 📌 Given by: **Coding Club, IIT Guwahati**  
This is a geometric optimization problem involving zoning policies in a futuristic city.

---

## 🔒 Problem Statement:

Your nation has begun urban redevelopment in the futuristic mega-city of **Axion Prime**, a vast, grid-structured metropolis built on top of ancient technology. The city is populated with various buildings scattered across the land, each associated with a **cost** — a monetary burden for including that building within a regulated zone.

As the chief architect of Axion Prime’s zoning council, your task is to design a **containment boundary** — a simple, closed polygon — to enclose **at least K buildings**.

---

## 🎯 Goals:

The **Total Cost** to minimize is:

Total Cost = Perimeter of the polygon + Sum of weights of enclosed buildings


The polygon must:
- Be **axis-aligned** (its edges should be parallel to X and Y axes).
- Have **floating point** vertices.
- Enclose a building if it lies **strictly inside or on the boundary**.
- Be **simple** — non-self-intersecting and closed.

---

## 📥 Input Format:

- First line: Two integers **N** and **K** — total number of buildings and the minimum number to enclose.
- Next N lines: Each line contains three integers **xᵢ yᵢ wᵢ** — coordinates and cost weight of the *i-th* building.

---

## 📤 Output Format:

- First line: A floating-point number **C** — the **minimum total cost**, printed with at least **6 digits after the decimal point**.
- Next lines: Describe the polygon, **one edge per line**.
    - Each edge is defined as: `x1 y1 x2 y2` — represents a directed edge from `(x1, y1)` to `(x2, y2)`.
    - Edges must be listed in **order**, such that the path is connected and closed.
    - Each edge must be either **horizontal or vertical**.

---

## ⚙️ Constraints:

- 1 ≤ K ≤ N ≤ 10000  
- 0 ≤ xᵢ, yᵢ ≤ 10000  
- wᵢ can be negative  
- Polygon must be **simple, closed, and axis-aligned**
