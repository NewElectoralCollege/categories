#include <stdlib.h>

#include "party.h"

party *party__new(const char *name, short seats, int votes) {
    party *p = malloc(sizeof(party));
    p->name = name;
    p->seats = seats;
    p->votes = votes;

    return p;
}