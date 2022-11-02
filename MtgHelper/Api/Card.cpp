#include <Api/Card.h>

QString Card::get_name()
{
    return details[SIDE_FACE].name;
}

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
