
#define VERSION "1.0.0"
#define DEFAULT_JSON_FILE_BUFFER_SIZE 15000
#define DEFAULT_DATA_DIR "./data/"
#define DEFAULT_SVG_DIR "./"
#define DEFAULT_OUTPUT_PATH "./categories.svg"

static const char *states[] = {
    "Alabama",        "Alaska",         "Arizona",
    "Arkansas",       "California",     "Colorado",
    "Connecticut",    "Delaware",       "District of Columbia",
    "Florida",        "Georgia",        "Hawaii",
    "Idaho",          "Illinois",       "Indiana",
    "Iowa",           "Kansas",         "Kentucky",
    "Louisiana",      "Maine",          "Maryland",
    "Massachusetts",  "Michigan",       "Minnesota",
    "Mississippi",    "Missouri",       "Montana",
    "Nebraska",       "Nevada",         "New Hampshire",
    "New Jersey",     "New Mexico",     "New York",
    "North Carolina", "North Dakota",   "Ohio",
    "Oklahoma",       "Oregon",         "Pennsylvania",
    "Rhode Island",   "South Carolina", "South Dakota",
    "Tennessee",      "Texas",          "Utah",
    "Vermont",        "Virginia",       "Washington",
    "West Virginia",  "Wisconsin",      "Wyoming"};

static const char *years[RECORD_SIZE] = {"2020", "2016", "2012"};

static const char *help =
    "------------------------------------------------------------------------\n"
    "Thank You for using this program!\n"
    "  x --help, -h                       Display this menu.\n"
    "  x --version, -v                    Show the version of the program.\n"
    "  x --json-file-buffer-size=*, -j=*  Set max buffer size for JSON files.\n"
    "                                     Default is %i.\n"
    "  x --data-dir=*, -d=*               Sets directory for data files.\n"
    "                                     Default is %s.\n"
    "  x --svg-dir=*, -s=*                Sets directory for svg data files.\n"
    "                                     Default is %s.\n"
    "  x --output=*.svg, -o=*.svg         Sets path for output.\n"
    "                                     Default is %s.\n"
    "\n"
    "Source files:\n"
    "  https://github.com/NewElectoralCollege/categories\n"
    "\n"
    "Copyright info:\n"
    "  Copyright 2021 - The New Electoral College\n"
    "------------------------------------------------------------------------"
    "\n";

bool cmp_arg(const char *arg, char *c) {
    char shorthand[2];
    shorthand[0] = '-';
    shorthand[1] = c[2];

    return (strncmp(arg, c, strlen(c)) == 0) ||
           (strncmp(arg, shorthand, 2) == 0);
}