#pragma once

typedef struct {
    const char *name;
    short seats;
    int votes;
} party;

party *party__new(const char *name, short seats, int votes);
