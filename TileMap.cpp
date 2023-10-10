#include "stdafx.h"
#include "TileMap.h"
//
//TileMap::TileMap():Width(100), Height(20),sizeTexture(73.f), sandbox(Height, std::vector<Tile*>(Width)) {
//    initSandbox();
//}
//
//void TileMap::initSandbox(){
//	TileFactory tileFactory;
//	std::string charMap[] = {
//        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//        "F                                                    FF                                            F",
//        "F                                               FF                                                 F",
//        "F                                           FF                                                     F",
//        "F                                                                                                  F",
//        "F                                    FFFFFFF                                                       F",
//        "F                                   FF                                                             F",
//        "F                             FF   FF                                                              F",
//        "F                                                                                                  F",
//        "F                        FFFFFF                                                                    F",
//        "F                             FF                                                                   F",
//        "F                              FF                                                                  F",
//        "F                               FFF                                                                F",
//        "F                                    FFF                                                           F",
//        "F                                         FFFF                                                     F",
//        "F                                           FFFF                                                   F",
//        "FF                 FFFFF       FFFFF                                                              FF",
//        "FFFFFFFF    FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//        "FFFFFFFF   FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
//    };
//    for (int i = 0; i < Height; i++) {
//        for (int j = 0; j < Width; j++) {
//            if (charMap[i][j] == 'F') {
//                sandbox[i][j] = tileFactory.getBlock(1);
//                sandbox[i][j]->setPosition(j * sizeTexture, i * sizeTexture);
//            }
//            sandbox[i][j] = tileFactory.getBlock(2);
//            sandbox[i][j]->setPosition(j * sizeTexture, i * sizeTexture);
//        }
//    }
//}
//
//void TileMap::render(sf::RenderTarget& target){
//    for (int i = 0; i < Height; i++) {
//        for (int j = 0; j < Width; j++) {
//            sandbox[i][j]->render(target);
//        }
//    }
//}
