#pragma once

#include "party.h"

#define RECORD_SIZE 3

struct state {
    const char *name;
    short seats;
    party **results[RECORD_SIZE];
    size_t n_parties[RECORD_SIZE];
    char code[2];
};

party *state__get_party(struct state *s, int number, const char *name);
bool state__isEven(struct state *s);
double state__quota(struct state *s);
const char *state__winner(struct state *s, int number);
int state__difference(struct state *s, int number);
bool state__battleground(struct state *s);
bool state__hotly_contested_elector(struct state *s);
enum category state__category(struct state *s);
void state__code(struct state *s);