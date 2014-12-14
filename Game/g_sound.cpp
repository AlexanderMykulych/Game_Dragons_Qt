#include "g_sound.h"

G_Sound::G_Sound()
{

}

void G_Sound::P_Click()
{
    QSound S(SOUND_CLICK);
    S.play();
}

void G_Sound::P_Expl()
{
    QSound S(SOUND_EXPL);
    S.play();
}

void G_Sound::P_Fire()
{
    QSound S(SOUND_FIRE);
    S.play();
}

void G_Sound::P_Soung()
{
    QSound S(SOUND_BACKGROUND);
    S.play();
}
