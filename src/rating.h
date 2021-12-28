#pragma once

enum category {
    /**
     * Odd number of electors, Party A has 1 more than Party B, Safe State.
     * Virtually impossible for elector configuration to change.
     */
    maroon,
    /**
     * Equal number of electors for each party. The state must flip in order to
     * change the elector configuration, which is unlikely.
     */
    red,
    /**
     * Battleground state under the old system with an even number of electors.
     */
    orange,
    /**
     * Safe State where an elector could be gained without flipping the state.
     */
    sky_blue,
    /**
     * Safe State with a hotly contested elector.
     */
    blue,
    /**
     * Large number of electors that results in small swings in the vote share
     * causing an elector(s) to flip.
     */
    light_green,
    /**
     * Battleground state under the old system with an odd number of electors.
     * This means that who wins the state is relevant.
     */
    green
};

char *color(enum category c);