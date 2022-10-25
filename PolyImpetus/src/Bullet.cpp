#include "Bullet.h"

Bullet::Bullet()
{
    pos = glm::vec3(0, 0,0);
    vel = pos;
    rotation = 0;

}

Bullet::Bullet(glm::vec3 p, ofImage* bullet_image) {
    //from_player = f_p;
    pos = p;
    img = bullet_image;
    imgWidth = img->getWidth();
    imgHeight = img->getHeight();
}
void Bullet::setup(glm::vec3 p,  ofImage* bullet_image) {
    //from_player = f_p;
    pos = p;
    img = bullet_image;
    imgWidth = img->getWidth();

}
void Bullet::update() {
    /*
    if (from_player) {
        pos.y -= speed;
    }
    else {
        pos.y += speed;
    }
*/
    cout << "super bullet" << endl;
}
void Bullet::draw() {
    ofPushMatrix();
    ofSetColor(ofColor::white);
    ofMultMatrix(getMatrix());
    img->setAnchorPoint(imgWidth / 2, imgHeight / 2);
    img->draw(0, 0, imgWidth, imgHeight);
    ofPopMatrix();

}

glm::vec3 Bullet::getPos()
{
    return pos;
}

float Bullet::getWidth()
{
    return imgWidth;
}

float Bullet::getDamage()
{
    return damage;
}

void Bullet::setDamage(float dmg)
{
    damage = dmg;
}

glm::mat4 Bullet::getMatrix() {
    glm::mat4 trans = glm::translate(glm::mat4(1.0), pos);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler);
    return (trans * rot * scale);
}

// PLAYER BULLET
PlayerBullet::PlayerBullet()
{
}
PlayerBullet::PlayerBullet(glm::vec3 p, int s, float acc, float rotate,ofImage* PlayerBullet_image) : Bullet(p, PlayerBullet_image)
{
    rotation = rotate;
    speed = s + 3;
    accuracy = acc;
}

PlayerBullet::PlayerBullet(glm::vec3 p, int s, float acc, ofImage* PlayerBullet_image) : Bullet(p, PlayerBullet_image)
{
    speed = s + 3;
    accuracy = acc;
}
void PlayerBullet::setup(bool f_p, glm::vec3 p, float s, float acc, float rotate ,ofImage* PlayerBullet_image) {
    //from_player = f_p;
    pos = p;
    speed = s + 3;
    img = PlayerBullet_image;
    imgWidth = img->getWidth();
    accuracy = acc;
}
void Bullet::setDirection(glm::vec3 mousePos)
{
    vel = pos - mousePos;
    vel = glm::normalize(vel);
    rotation = glm::orientedAngle(vel, glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
    rotation = glm::degrees(rotation);
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
void PlayerBullet::update(glm::vec3 mousePos) {

    cout << "not this one" << endl;
    //ofSetColor(ofColor::white);
    //img->draw(pos.x - imgWidth / 2, pos.y - imgWidth / 2);

}

EnemyBullet::EnemyBullet() : Bullet()
{
}

void EnemyBullet::setup(glm::vec3 position, int speed, float rotate, ofImage* bulletImg)
{
    pos = position;
    this->speed = speed;
    img = bulletImg;
    imgWidth = img->getWidth();
    imgHeight = img->getHeight();
    rotation = rotate;
}


void EnemyBullet::update()
{
    pos += vel;
}
