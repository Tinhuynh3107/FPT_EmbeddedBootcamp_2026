#include "cmd_line.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int8_t cmd_line_parser(cmd_line_t *cmd_tbl, const int8_t *cmd) {
  int8_t cmd_buffer[MAX_CMD_SIZE];
  int8_t *p_cmd = cmd;
  uint8_t cmd_index = 0;
  uint8_t index = 0;

  if (cmd == NULL || cmd_tbl == NULL) {
    return CMD_TBL_NOT_FOUND;
  }

  while (*p_cmd) {
    if (*p_cmd == ' ' || *p_cmd == '\n' || *p_cmd == '\r') {
      cmd_buffer[cmd_index] = '\0';
      break;
    } else {
      cmd_buffer[cmd_index++] = *p_cmd;
      p_cmd++;

      if (cmd_index >= MAX_CMD_SIZE) {
        return CMD_TOO_LONG;
      }
    }
  }

  while (cmd_tbl[index].cmd_buffer != NULL) {
    if (strcmp(cmd_tbl[index].cmd_buffer, cmd_buffer) == 0) {
      cmd_tbl[index].handler(&cmd_index);
      return CMD_SUCCESS;
    }
    index++;
  }
  printf("Command not found: %s\n", cmd);
  return CMD_NOT_FOUND;
}
