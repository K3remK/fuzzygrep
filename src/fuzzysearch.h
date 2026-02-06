/*
 * Copyright (C) 2025 Kerem Karamanlioglu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FUZZYSEARCH_H
#define FUZZYSEARCH_H

#include <stdbool.h>
#include <regex.h>    // For reg_syntax_t
#include "grep.h"  // // For idx_t and other project-specific types

struct fuzzysearch {
  char *pattern;       // original pattern
  idx_t size;          // size of the pattern
};

extern int approx_threshold;

void *FuzzyCompile(char *pattern, idx_t size, reg_syntax_t unused, bool exact);
ptrdiff_t FuzzyExecute (void *compiled_pattern, const char *buf, idx_t size, idx_t *match_size, const char *start_ptr);
int damerau_levenshtein(const char *s1, const char *s2);

#endif
