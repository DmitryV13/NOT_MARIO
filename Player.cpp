//#include "Player.h"
//
//
//Player::Player(Texture hero_T, const float mapW, const float mapH, const float size_texture, const float sH, const float sW) 
//    : absoluteRight(mapW * size_texture), 
//    absoluteBottom(mapH * size_texture), 
//    absoluteTop(0.0f), 
//    absoluteLeft(0.0f), 
//    windowLeft(0.0f), 
//    windowTop(0.0f), 
//    windowRight(sW), 
//    windowBottom(sH),
//    screenHeight(sH), 
//    screenWidth(sW){
//    player_S.setTexture(hero_T);
//    player_S.setPosition(0, 0);
//}
//
//void Player::moveRight(RenderWindow& window, View& view) {
//    Vector2f spritePosition = player_S.getPosition();
//    if (spritePosition.x + player_S.getLocalBounds().width + playerSpeed >= windowRight) {
//        if (spritePosition.x + player_S.getLocalBounds().width + playerSpeed >= absoluteRight) {
//            windowLeft = absoluteRight - screenWidth;
//            windowRight = absoluteRight;
//            spritePosition.x = absoluteRight - player_S.getLocalBounds().width;
//            player_S.setPosition(spritePosition);
//            view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
//            window.setView(view);
//        }
//        else {
//            float offset = playerSpeed - (windowRight - (spritePosition.x + player_S.getLocalBounds().width));
//            view.move(offset, 0);
//            window.setView(view);
//
//            windowLeft += offset;
//            windowRight += offset;
//
//            player_S.move(playerSpeed, 0);
//        }
//    }
//    else {
//        player_S.move(playerSpeed, 0);
//    }
//}
//void Player::moveLeft(RenderWindow& window, View& view) {
//    Vector2f spritePosition = player_S.getPosition();
//    if (spritePosition.x - playerSpeed <= windowLeft) {
//        if (spritePosition.x - playerSpeed <= absoluteLeft) {
//            windowLeft = absoluteLeft;
//            windowRight = absoluteLeft + screenWidth;
//            spritePosition.x = absoluteLeft;
//            player_S.setPosition(spritePosition);
//            view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
//            window.setView(view);
//        }
//        else {
//            float offset = playerSpeed - (spritePosition.x - windowLeft);
//            view.move(-offset, 0);
//            window.setView(view);
//            windowLeft -= offset;
//            windowRight -= offset;
//
//            player_S.move(-playerSpeed, 0);
//        }
//    }
//    else {
//        player_S.move(-playerSpeed, 0);
//    }
//}
//
//void Player::moveUp(RenderWindow& window, View& view) {
//    Vector2f spritePosition = player_S.getPosition();
//    if (spritePosition.y - playerSpeed <= windowTop) {
//        if (spritePosition.y - playerSpeed <= absoluteTop) {
//            windowBottom = absoluteTop + screenHeight;
//            windowTop = absoluteTop;
//            spritePosition.y = absoluteTop;
//            player_S.setPosition(spritePosition);
//            view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
//            window.setView(view);
//        }
//        else {
//            float offset = playerSpeed - (spritePosition.y - windowTop);
//            view.move(0, -offset);
//            window.setView(view);
//            windowTop -= offset;
//            windowBottom -= offset;
//
//            player_S.move(0, -playerSpeed);
//        }
//    }
//    else {
//        player_S.move(0, -playerSpeed);
//    }
//}
//
//void Player::moveDown(RenderWindow& window, View& view) {
//    Vector2f spritePosition = player_S.getPosition();
//    if (spritePosition.y + player_S.getLocalBounds().height + playerSpeed >= windowBottom) {
//        if (spritePosition.y + player_S.getLocalBounds().height + playerSpeed >= absoluteBottom) {
//            windowBottom = absoluteBottom;
//            windowTop = absoluteBottom - screenHeight;
//            spritePosition.y = absoluteBottom - player_S.getLocalBounds().height;
//            player_S.setPosition(spritePosition);
//            view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
//            window.setView(view);
//        }
//        else {
//            float offset = playerSpeed - (windowBottom - (spritePosition.y + player_S.getLocalBounds().height));
//            view.move(0, offset);
//            window.setView(view);
//
//            windowTop += offset;
//            windowBottom += offset;
//
//            player_S.move(0, playerSpeed);
//        }
//    }
//    else {
//        player_S.move(0, playerSpeed);
//    }
//}
//