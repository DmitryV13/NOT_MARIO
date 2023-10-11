#pragma once
#include "Tile.h"

class TileFactory{
private:

    std::string template_1[20] = {
    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
    "A                                                                                                 A",
    "A                                                                                                 A",
    "A  IIIIIIIIIIIIII                                                                                 A",
    "A                                                                                                 A",
    "A                                                                                                 A",
    "A  IIIIIIIIIIIIII                                                                                 A",
    "A                                                                                                 A",
    "A                                                                                                 A",
    "A                 7                                                                               A",
    "A                OPQ                                                                              A",
    "A     0  98            9 0                                                                        A",
    "A    BCCCCCCCCD        OPQ                                                                        A",
    "A)   EFFFFFFFFG                                                                                   A",
    "AD   NIIIIIIIIM    17 0  )                                                                        A",
    "AG      0          BCCCCCCCCD                                                                     A",
    "AG 19 BCCCD   0   9EFFFFFFFFG                                                                     A",
    "AJKCCLHFFFJKCCCCCCLHFFFFFFFFJKFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA",
    "AIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIA",
    };

    
    sf::IntRect initRect_tile(char tile);
    
public:
    TileFactory();
    Tile tile_map_inFactory[20][100];


};

