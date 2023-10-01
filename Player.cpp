#include "Player.h"
class Player
{
    void moveRight() {
        if (spritePosition.x + ball_S.getLocalBounds().width + ballSpeed >= windowRight) {
            if (spritePosition.x + ball_S.getLocalBounds().width + ballSpeed >= absoluteRight) {
                windowLeft = absoluteRight - screenWidth;
                windowRight = absoluteRight;
                spritePosition.x = absoluteRight - ball_S.getLocalBounds().width;
                ball_S.setPosition(spritePosition);
                view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                window.setView(view);
            }
            else {
                float offset = ballSpeed - (windowRight - (spritePosition.x + ball_S.getLocalBounds().width));
                view.move(offset, 0);
                window.setView(view);

                windowLeft += offset;
                windowRight += offset;

                ball_S.move(ballSpeed, 0);
            }
        }
        else {
            ball_S.move(ballSpeed, 0);
        }
    }
    void moveLeft() {
        if (spritePosition.x - ballSpeed <= windowLeft) {
            if (spritePosition.x - ballSpeed <= absoluteLeft) {
                windowLeft = absoluteLeft;
                windowRight = absoluteLeft + screenWidth;
                spritePosition.x = absoluteLeft;
                ball_S.setPosition(spritePosition);
                view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                window.setView(view);
            }
            else {
                float offset = ballSpeed - (spritePosition.x - windowLeft);
                view.move(-offset, 0);
                window.setView(view);
                windowLeft -= offset;
                windowRight -= offset;

                ball_S.move(-ballSpeed, 0);
            }
        }
        else {
            ball_S.move(-ballSpeed, 0);
        }
    }
    void moveUp() {
        if (spritePosition.y - ballSpeed <= windowTop) {
            if (spritePosition.y - ballSpeed <= absoluteTop) {
                windowBottom = absoluteTop + screenHeight;
                windowTop = absoluteTop;
                spritePosition.y = absoluteTop;
                ball_S.setPosition(spritePosition);
                view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                window.setView(view);
            }
            else {
                float offset = ballSpeed - (spritePosition.y - windowTop);
                view.move(0, -offset);
                window.setView(view);
                windowTop -= offset;
                windowBottom -= offset;

                ball_S.move(0, -ballSpeed);
            }
        }
        else {
            ball_S.move(0, -ballSpeed);
        }
    }
    void moveDown() {
        if (spritePosition.y + ball_S.getLocalBounds().height + ballSpeed >= windowBottom) {
            if (spritePosition.y + ball_S.getLocalBounds().height + ballSpeed >= absoluteBottom) {
                windowBottom = absoluteBottom;
                windowTop = absoluteBottom - screenHeight;
                spritePosition.y = absoluteBottom - ball_S.getLocalBounds().height;
                ball_S.setPosition(spritePosition);
                view.setCenter(windowRight - (screenWidth / 2), windowBottom - (screenHeight / 2));
                window.setView(view);
            }
            else {
                float offset = ballSpeed - (windowBottom - (spritePosition.y + ball_S.getLocalBounds().height));
                view.move(0, offset);
                window.setView(view);

                windowTop += offset;
                windowBottom += offset;

                ball_S.move(0, ballSpeed);
            }
        }
        else {
            ball_S.move(0, ballSpeed);
        }
    }
};