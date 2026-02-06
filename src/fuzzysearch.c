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

#include <config.h>
#include "fuzzysearch.h"
#include "system.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "xalloc.h"
#include <stdio.h>    // Optional: for debug printing
         

// Optional: define MIN if not already defined
#ifndef MIN
# define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

int damerau_levenshtein(const char *s1, const char *s2) {
    size_t len1 = strlen(s1), len2 = strlen(s2);
    int **d = malloc((len1 + 1) * sizeof(int*));
    for (size_t i = 0; i <= len1; ++i) {
        d[i] = malloc((len2 + 1) * sizeof(int));
        d[i][0] = i;
    }
    for (size_t j = 0; j <= len2; ++j) d[0][j] = j;

    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            int cost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            d[i][j] = MIN(MIN(d[i - 1][j] + 1, d[i][j - 1] + 1),
                          d[i - 1][j - 1] + cost);
            if (i > 1 && j > 1 &&
                s1[i - 1] == s2[j - 2] &&
                s1[i - 2] == s2[j - 1]) {
                d[i][j] = MIN(d[i][j], d[i - 2][j - 2] + cost);
            }
        }
    }

    int result = d[len1][len2];
    for (size_t i = 0; i <= len1; ++i) free(d[i]);
    free(d);
    return result;
}

void *FuzzyCompile(char *pattern, idx_t size, reg_syntax_t ignored, bool exact) {
  struct fuzzysearch *fs = xmalloc(sizeof(*fs));
  fs->pattern = xmalloc(size + 1);
  memcpy(fs->pattern, pattern, size);
  fs->pattern[size] = '\0';
  fs->size = size;
  return fs;
}

ptrdiff_t FuzzyExecute(void *vfs, const char *buf, idx_t size,
                       idx_t *match_size, const char *start_ptr) {
  struct fuzzysearch *fs = vfs;
  const char *pattern = fs->pattern;

  const char *cursor = start_ptr ? start_ptr : buf;
  const char *end = buf + size;

  while (cursor < end) {
    const char *line_end = memchr(cursor, '\n', end - cursor);
    if (!line_end)
      line_end = end;

    size_t line_len = line_end - cursor;
    if (line_len >= 1024)
      line_len = 1023;

    char line[1024];
    memcpy(line, cursor, line_len);
    line[line_len] = '\0';

    for (size_t i = 0; i < line_len;) {
    // Skip non-word chars
    while (i < line_len && !isalnum((unsigned char)line[i]))
        i++;

    size_t start = i;

    // Scan word
    while (i < line_len && isalnum((unsigned char)line[i]))
        i++;

    if (start < i) {
        size_t word_len = i - start;
        if (word_len >= 256) word_len = 255;

        char word[256];
        memcpy(word, &line[start], word_len);
        word[word_len] = '\0';

        int dist = damerau_levenshtein(word, pattern);

        if (dist <= approx_threshold) {
            *match_size = (line_end < end && *line_end == '\n')
                            ? (line_end - cursor + 1)
                            : (line_end - cursor);
            return cursor - buf;
        }
    }
}

    cursor = (line_end < end) ? line_end + 1 : end;
  }
  *match_size = 0;
  return -1;
}





