#include "rating.h"

char *color(enum category c) {
    switch (c) {

    case maroon: return "7f0000";

    case red: return "BD0026";

    case orange: return "FC4E2A";

    case sky_blue: return "41B6C4";

    case blue: return "225EA8";

    case light_green: return "41AE76";

    case green: return "006D2C";

    default: return "dddddd";
    }
}