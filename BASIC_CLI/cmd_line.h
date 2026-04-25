#ifndef CMD_LINE_H
#define CMD_LINE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_CMD_SIZE 20
#define MAX_ARGS 10

typedef void (*pf_cmd_handler)(uint8_t *argc);

typedef struct {
  const int8_t *cmd_buffer;
  pf_cmd_handler handler;
  const int8_t *description;
} cmd_line_t;

enum {
  CMD_SUCCESS = 0,
  CMD_NOT_FOUND,
  CMD_TBL_NOT_FOUND,
  CMD_TOO_LONG,
};

extern int8_t cmd_line_parser(cmd_line_t *cmd_tbl, const int8_t *cmd);

#ifdef __cplusplus
}
#endif

#endif
