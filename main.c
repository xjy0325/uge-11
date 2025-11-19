#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  // YOUR CODE HERE

  // NULL has no '\0'
  if (line == NULL) {
    return line;
  }

  // avoid 'line-1' when length = 0
  if (strlen(line) > 0 && line[strlen(line) - 1] == '\n') {

    line[strlen(line) - 1] = '\0';
  }

  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  // YOUR CODE HERE
  FILE *f = fopen(filename, "r");
  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];
  while (
      // Read one line from the stream
      // YOUR CODE HERE
      fgets(line, TRACK_TITLE_SIZE, f)) {
    remove_newline_if_exists(line);

    auto new_node = (Node *)malloc(sizeof(Node));
    new_node->next = nullptr;
    auto data = (Data *)malloc(sizeof(Data));
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    // YOUR CODE HERE
    strcpy(new_node->data, line);
    if (*list == NULL) {
      *list = new_node;
    } else {
      tail(*list)->next = new_node;
    }
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  // YOUR CODE HERE
  FILE *f = fopen(filename, "w");
  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // (char *)current->data
  // Because current->data is a pointer to everything (void*).
  auto current = playlist;
  // YOUR CODE HERE
  while (current) {
    fprintf(f, "%s\n", (char *)current->data);
    current = current->next;
  }
  fclose(f);
  //// END SOLUTION
}

void print_tracks(const Node *const playlist) {
  auto current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2ld: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = nullptr};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}