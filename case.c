#include "Case.h"

#include "affichage.h"
extern const SDL_Rect imgHerbe;
extern const SDL_Rect imgTerre;

const Case caseHerbe = {&imgHerbe,infranchissable};
const Case caseTerre = {&imgTerre,libre};
