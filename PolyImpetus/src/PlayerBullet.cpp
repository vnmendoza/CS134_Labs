#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{
}
PlayerBullet::PlayerBullet(glm::vec2 p, int s, float acc, float rotate,ofImage* PlayerBullet_image) : Bullet(p, PlayerBullet_image)
{
    rotation = rotate;
    speed = s + 3;
    accuracy = acc;
}
void PlayerBullet::setup(bool f_p, glm::vec2 p, float s, float acc, float rotate ,ofImage* PlayerBullet_image) {
    //from_player = f_p;
    pos = p;
    speed = s + 3;
    img = PlayerBullet_image;
    imgWidth = img->getWidth();
    accuracy = acc;
}
void PlayerBullet::setDirection(glm::vec2 mousePos)
{
    vel = pos - mousePos;
    vel = glm::normalize(vel);
    vel *= -speed;

}
void PlayerBullet::move()
{
    pos += vel;
}
void PlayerBullet::update()
{
    move();

}
void PlayerBullet::update(glm::vec2 mousePos) {

    cout << "not this one" << endl;
    //ofSetColor(ofColor::white);
    //img->draw(pos.x - imgWidth / 2, pos.y - imgWidth / 2);

}


