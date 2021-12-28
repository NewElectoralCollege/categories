#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <json-c/json.h>

#include "party.h"
#include "rating.h"
#include "state.h"

#include "main.h"

#ifndef INCLUDED_LIB
#    include "party.c"
#    include "rating.c"
#    include "state.c"
#endif

int main(int argc, char **argv) {
    size_t json_file_buffer_size;
    char *data_dir;
    char *svg_dir;
    char *output_p;
    char *arg;
    char *value;

    json_file_buffer_size = DEFAULT_JSON_FILE_BUFFER_SIZE;
    data_dir = DEFAULT_DATA_DIR;
    svg_dir = DEFAULT_SVG_DIR;
    output_p = DEFAULT_OUTPUT_PATH;

    for (int i = 1; i < argc; i++) {
        arg = argv[i];

        if (value = strchr(arg, '='))
            value = strchr(value, value[1]);

        if (cmp_arg(arg, "--help")) {
            printf(help, DEFAULT_JSON_FILE_BUFFER_SIZE, DEFAULT_DATA_DIR,
                   DEFAULT_SVG_DIR, DEFAULT_OUTPUT_PATH);

        } else if (cmp_arg(arg, "--version")) {
            printf("%s\n", VERSION);

        } else if (cmp_arg(arg, "--json-file-buffer-size")) {
            json_file_buffer_size = atoi(value);

        } else if (cmp_arg(arg, "--data-dir")) {
            data_dir = value;

        } else if (cmp_arg(arg, "--svg-dir")) {
            svg_dir = value;

        } else if (cmp_arg(arg, "--output")) {
            output_p = value;

        } else {
            printf("Unknown argument: %s\n", arg);
        }
    }

    char lists[7][255] = {"", "", "", "", "", "", ""};

    for (int i = 0; i < 51; i++) {
        party **pss[RECORD_SIZE];
        size_t n_parties[RECORD_SIZE];
        struct json_object *seats;

        for (int y = 0; y < RECORD_SIZE; y++) {
            FILE *fp;
            char path[100];
            char *buffer;
            size_t p_size;
            party **ps;
            struct json_object *parsed_json;
            struct json_object *parties;
            struct json_object *party;
            struct json_object *p_name;
            struct json_object *p_seats;
            struct json_object *p_votes;
            struct json_object *stats;
            struct json_object *name;

            buffer = malloc(json_file_buffer_size);

            strcpy(path, data_dir);
            strcat(path, years[y]);
            strcat(path, "/");
            strcat(path, states[i]);
            strcat(path, ".json");

            if (fp = fopen(path, "r")) {
                fread(buffer, json_file_buffer_size, 1, fp);
                fclose(fp);
            } else {
                printf("The file at %s doesn't exist.\n", path);
                return -1;
            }

            if (!((parsed_json = json_tokener_parse(buffer)) &&
                  json_object_object_get_ex(parsed_json, "parties", &parties) &&
                  json_object_object_get_ex(parsed_json, "stats", &stats))) {

                printf("JSON parse failed on %s. This could be for any of the "
                       "following reasons:\n",
                       path);
                printf("   - The JSON in the file is malformed.\n");
                printf("   - The file is too big.\n");
                return -1;
            }

            json_object_object_get_ex(stats, "total_seats", &seats);

            p_size = json_object_array_length(parties);
            ps = malloc(p_size * sizeof(party));

            for (int p = 0; p < p_size; p++) {
                party = json_object_array_get_idx(parties, p);

                json_object_object_get_ex(party, "name", &p_name);
                json_object_object_get_ex(party, "seats", &p_seats);
                json_object_object_get_ex(party, "votes", &p_votes);

                ps[p] = party__new(json_object_get_string(p_name),
                                   json_object_get_int(p_seats),
                                   json_object_get_int(p_votes));
            }

            pss[y] = ps;
            n_parties[y] = p_size;
        }

        struct state s = {states[i], json_object_get_int(seats)};
        memcpy(s.results, pss, sizeof(pss));
        memcpy(s.n_parties, n_parties, sizeof(n_parties));
        state__code(&s);

        enum category ct = state__category(&s);
        strcat(lists[ct], "#");
        strcat(lists[ct], s.code);
        strcat(lists[ct], ", ");
    }

    char *header_p = malloc(sizeof(svg_dir) + 12);
    char *stuff_p = malloc(sizeof(svg_dir) + 10);
    char header_t[255];
    char stuff_t[26955];
    FILE *header;
    FILE *stuff;

    strcpy(header_p, svg_dir);
    strcpy(stuff_p, svg_dir);
    strcat(header_p, "headers.txt");
    strcat(stuff_p, "stuff.txt");

    if (!(header = fopen(header_p, "r"))) {
        printf("%s doesn't exist.\n", header_p);
        return -1;
    }

    if (!(stuff = fopen(stuff_p, "r"))) {
        printf("%s doesn't exist.\n", stuff_p);
        return -1;
    }

    FILE *output = fopen(output_p, "w");

    fgets(header_t, sizeof(header_t), header);
    fgets(stuff_t, sizeof(stuff_t), stuff);

    fclose(header);
    fclose(stuff);

    fprintf(output, "%s", header_t);

    for (int x = 0; x < 7; x++) {
        if (!lists[x])
            continue;

        fprintf(output, "%s#a-%i { fill: #%s; }\n ", lists[x], x + 1, color(x));
    }

    fprintf(output, "%s", stuff_t);

    fclose(output);

    return 1;
}