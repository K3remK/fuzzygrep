# FuzzyGrep - Approximate Pattern Matching

![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)
![C](https://img.shields.io/badge/Language-C-00599C.svg)
![Status](https://img.shields.io/badge/Status-Stable-success.svg)

**FuzzyGrep** is an extended version of GNU Grep that introduces approximate (fuzzy) pattern matching capabilities using the Damerau-Levenshtein distance algorithm. This tool allows users to find matches even when words contain typos or slight variations.

## 🚀 Overview

Standard `grep` is a powerful tool for exact pattern matching, but it fails when data is messy or contains spelling errors. **FuzzyGrep** solves this by adding a new command-line option `--approx=N`, enabling the detection of words that are within `N` edits (insertions, deletions, replacements, or transpositions) from the target search term.

## ✨ Key Features

*   **Approximate Matching**: Matches words within a specified edit distance using the Damerau-Levenshtein algorithm.
*   **Word-Level Granularity**: Instead of comparing entire lines blindly, the text is tokenized into words for more accurate fuzzy matching.
*   **Whole-Line Output**: Preserves the standard `grep` behavior—if any word in a line matches approximately, the entire line is printed.
*   **Customizable Threshold**: Users can define the strictness of the match using `--approx=N`.
    *   `--approx=0`: Exact match (same as standard grep).
    *   `--approx=1`: Allows 1 edit (typo).
    *   `--approx=2`: Allows 2 edits, and so on.

## 🛠️ Installation & Building

To build the project from source, you will need a standard C build environment (GCC/Clang, Make).

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/fuzzygrep.git
    cd fuzzygrep
    ```

2.  **Build the project:**
    Run the following command in the project root:
    ```bash
    make
    ```

    This will compile the modified `grep` executable in the `src` directory.

## 📖 Usage

The usage is identical to standard `grep`, with the addition of the `--approx` flag.

### Syntax
```bash
./src/grep --approx=[N] "pattern" [file]
```

### Examples

**1. Exact Match (Default Behavior)**
```bash
$ ./src/grep --approx=0 "hello" input.txt
> hello world
```

**2. Fuzzy Match (Single Typo)**
Finds "hello" even if it is spelled "helllo" or "hullo".
```bash
$ ./src/grep --approx=1 "hello" input.txt
> hello
> helllo
> hullo
```

**3. Fuzzy Match (More Relaxed)**
Finds "hello" with up to 2 edits, matching "helllloo" or "yelloo".
```bash
$ ./src/grep --approx=2 "hello" input.txt
> hello
> helllo
> helllloo
> yelloo
```

## 🧪 How It Works

1.  **Input Parsing**: Each line of the input file is scanned individually.
2.  **Tokenization**: The line is divided into words using standard character classification (`isalnum`).
3.  **Distance Calculation**: The Damerau-Levenshtein distance is computed between each word and the search pattern.
    *   This algorithm accounts for insertions, deletions, substitutions, and adjacent transpositions.
4.  **Matching**: If the calculated distance is less than or equal to the threshold `N`, the line is considered a match.

## 📄 License

This project is adhering to the GNU General Public License v3 (GPLv3).
Copyright (C) 2025 Kerem Karamanlioglu.
Based on the original GNU Grep source code.
