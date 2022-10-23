#include <Api/Card.h>

void Card::set_image(int side, QPixmap image)
{
    details[side].image = image;
}

QPixmap Card::get_image(int side)
{
    return details[side].image;
}

QString Card::get_image_url(int side)
{
    return details[side].imageUrl;
}
