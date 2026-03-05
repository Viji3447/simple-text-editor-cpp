# Text Editor with Undo (C++)

A simple command‑line text editor implemented in C++ that demonstrates:

- Manual memory management with `char*`
- Rule of Three (copy ctor, copy assignment, destructor)
- Deep copy semantics
- Undo via history snapshots
- Basic C‑style string ops (`strcpy`, `strcat`, `strlen`)

> Great for practicing low‑level C++ fundamentals, object ownership, and Git/GitHub workflows.

---

## ✨ Features

- **Append text** — add characters to the end of the buffer
- **Remove text** — delete a range by index (`start`, `count`)
- **Undo** — restore the previous state (supports 10+ levels)
- **Deep copies** — no shared memory between snapshots
- **Clean design** — `TextBuffer` + `TextEditor` classes

---

## 📁 Project Structure
