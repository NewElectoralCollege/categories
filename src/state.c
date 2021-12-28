#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rating.h"
#include "state.h"

party *state__get_party(struct state *s, int number, const char *name) {
    party **ps = s->results[number];
    party *n;

    for (int i = 0; i < s->n_parties[number]; i++) {
        n = *ps++;

        if (strcmp(n->name, name) == 0) {
            return n;
        }
    }
}

bool state__isEven(struct state *s) {
    return s->seats % 2 == 0;
}

double state__quota(struct state *s) {
    return 1 / s->seats;
}

const char *state__winner(struct state *s, int number) {
    party **ps = s->results[number];
    party *n;
    party m;
    m.votes = 0;

    for (int i = 0; i < s->n_parties[number]; i++) {
        n = *ps++;

        if (n->votes > m.votes) {
            m = *n;
        }
    }

    return m.name;
}

int state__difference(struct state *s, int number) {
    const char *w = state__winner(s, number);
    party *wp = state__get_party(s, number, w);

    return wp->seats - floor(s->seats / 2);
}

bool state__battleground(struct state *s) {
    int dem, gop;
    dem = gop = 0;

    for (int i = 0; i < RECORD_SIZE; i++) {
        if (strcmp(state__winner(s, i), "Democratic") == 0) {

            dem++;
        } else {

            gop++;
        }
    }

    return !(dem == RECORD_SIZE || gop == RECORD_SIZE);
}

bool state__hotly_contested_elector(struct state *s) {
    int dem_c, gop_c;
    int dem_ct, gop_ct;
    int counter;

    dem_c = gop_c = dem_ct = gop_ct = counter = 0;

    for (int i = 0; i < RECORD_SIZE - 1; i++) {
        dem_c = state__get_party(s, i, "Democratic")->seats -
                state__get_party(s, i + 1, "Democratic")->seats;
        gop_c = state__get_party(s, i, "Republican")->seats -
                state__get_party(s, i + 1, "Republican")->seats;

        if (dem_c + gop_c == 0 && dem_c != gop_c) {
            counter++;
            dem_ct += dem_c;
            gop_ct += gop_ct;
        }
    }

    return (counter > 0 && dem_ct < 2 && gop_ct < 2);
}

enum category state__category(struct state *s) {
    bool e = state__isEven(s);
    bool b = state__battleground(s);
    bool l = s->seats > 30;
    int d = state__difference(s, 0);
    bool h = state__hotly_contested_elector(s);

    return (l)                          ? light_green
           : (b && e)                   ? orange
           : (b)                        ? green
           : (h)                        ? blue
           : (d == 0)                   ? red
           : ((e && d == 1) || (d > 1)) ? sky_blue
                                        : maroon;
}

void state__code(struct state *s) {
    s->code[0] = s->name[0];

    if (strchr(s->name, ' ') == 0 ||
        strcmp(s->name, "District of Columbia") == 0) {

        s->code[1] = (strcmp(s->name, "Alaska") == 0)                 ? 'K'
                     : (strcmp(s->name, "Arizona") == 0)              ? 'Z'
                     : (strcmp(s->name, "Connecticut") == 0)          ? 'T'
                     : (strcmp(s->name, "District of Columbia") == 0) ? 'C'
                     : (strcmp(s->name, "Georgia") == 0)              ? 'A'
                     : (strcmp(s->name, "Hawaii") == 0)               ? 'I'
                     : (strcmp(s->name, "Iowa") == 0)                 ? 'A'
                     : (strcmp(s->name, "Kansas") == 0)               ? 'S'
                     : (strcmp(s->name, "Kentucky") == 0)             ? 'Y'
                     : (strcmp(s->name, "Louisiana") == 0)            ? 'A'
                     : (strcmp(s->name, "Maine") == 0)                ? 'E'
                     : (strcmp(s->name, "Maryland") == 0)             ? 'D'
                     : (strcmp(s->name, "Minnesota") == 0)            ? 'N'
                     : (strcmp(s->name, "Mississippi") == 0)          ? 'S'
                     : (strcmp(s->name, "Missouri") == 0)             ? 'O'
                     : (strcmp(s->name, "Montana") == 0)              ? 'T'
                     : (strcmp(s->name, "Nevada") == 0)               ? 'V'
                     : (strcmp(s->name, "Pennsylvania") == 0)         ? 'A'
                     : (strcmp(s->name, "Tennessee") == 0)            ? 'N'
                     : (strcmp(s->name, "Texas") == 0)                ? 'X'
                     : (strcmp(s->name, "Vermont") == 0)              ? 'T'
                     : (strcmp(s->name, "Virginia") == 0)
                         ? 'A'
                         : (toupper(s->name[1]));
    } else {

        s->code[1] = strchr(s->name, ' ')[1];
    }
}