#include "cmd_line.h"
#include <stdio.h>
#include <string.h>

uint8_t status_led = 0;
char name[50];

void cmd_help_handler(uint8_t *argc) {
  printf("Available commant: [led] to control the LED\n");
  printf("                   [exit] to exit the program\n");
}
void cmd_led_handler(uint8_t *argc) { printf("Usage: [on / off / toggle]\n"); }

void cmd_led_on_handler(uint8_t *argc) {
  printf("LED turned ON\n");
  status_led = 1;
}

void cmd_led_off_handler(uint8_t *argc) {
  printf("LED turned OFF\n");
  status_led = 0;
}

void cmd_led_toggle_handler(uint8_t *argc) {
  if (status_led) {
    printf("LED turned OFF\n");
    status_led = 0;
  } else {
    printf("LED turned ON\n");
    status_led = 1;
  }
}

void cmd_exit_handler(uint8_t *argc) {
  printf("Goodbye, %s!\n", name);
  printf("Exiting...\n");
}

cmd_line_t cmd_tbl[] = {{"help", cmd_help_handler, "Show this help message"},
                        {"led", cmd_led_handler, "Control the LED"},
                        {"on", cmd_led_on_handler, "Turn the LED ON"},
                        {"off", cmd_led_off_handler, "Turn the LED OFF"},
                        {"toggle", cmd_led_toggle_handler, "Toggle the LED"},
                        {"exit", cmd_exit_handler, "Exit the program"},
                        {NULL, NULL, NULL}};

int main() {
  char input[50];
  printf("-------------------------------------------------------------\n");
  printf("              Welcome to the Command Line Interface!         \n");
  printf("-------------------------------------------------------------\n");
  printf("Please enter your name: ");
  scanf("%s", name);
  getchar();
  printf("Hello, %s! \r\nType 'help' to see available commands.\n", name);
  while (1) {
    printf("Enter command: ");
    fgets(input, sizeof(input), stdin);
    cmd_line_parser(cmd_tbl, input);
    if (strcmp(input, "exit\n") == 0) {
      break;
    }
  }
  return 0;
}
