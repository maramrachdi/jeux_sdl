#include "background.h"

int main()
{
	SDL_Surface *screen;
	SDL_Event event;
	Background b;
	Uint32 prev, dt,temps;
	personne p;
	int valeur_score;
	score s;
	vie v;
   Mix_Music *music;
/*SDL_Surface *surface1, *surface2, *surface3;
SDL_Rect position1, position2, position3;
TTF_Font *police;
    ScoreInfo score;
    score.score = 100;
    score.temps = 10;
    strcpy(score.playerName, "Player 1");*/
 
	int loop=1,collision,jump=0;

    if (SDL_Init (SDL_INIT_VIDEO|SDL_INIT_AUDIO | SDL_INIT_TIMER)!=0){
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
    return 1;}
  
  screen=SDL_SetVideoMode(1090,668,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
initialiser_audio (music);

	
	init_back(&b);
	initPerso(&p);


while(loop){

prev = SDL_GetTicks();
afficher_back(screen,b); 
animerBack (&b);
afficheranim(b,screen);
afficherPerso(p, screen);






while (SDL_PollEvent(&event))
        {

            switch (event.type)
            {
            case SDL_QUIT:
                loop=0;
                break;
           case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    p.direction = 0;
         update_score_plus(&valeur_score,s,&p);
                    break;

                case SDLK_LEFT:
                    p.direction = 1;
        update_score_plus(&valeur_score,s,&p);
update_score_moins (&valeur_score,s,&p);
                    break;
                case SDLK_UP:
          gestion_vies (&v,&p);
                    jump=1;
                    break;
                /*case SDLK_DOWN:
                    p.up=0;
                    break;*/
                case SDLK_SPACE:
                    if (p.up == 0)
                    {
                        p.jump_V = -p.jump_height;
                        p.up = 1;
                    }
					
                    break;
				case SDLK_KP_PLUS:
                p.acceleration +=0,005;
                break;
			    case SDLK_KP_MINUS:
                p.acceleration -=0,01;
                break;
				
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    if (p.direction==0){
					p.posSprite.x=0;
					p.posSprite.y=0;}
					else{
					p.posSprite.x=0;
					p.posSprite.y=258;}
                    p.direction = -1;
                    break;
                   
                case SDLK_UP:
                    p.up=0;
                    break;
                case SDLK_LEFT:
                    if (p.direction==0){
					p.posSprite.x=0;
					p.posSprite.y=0;}
					else{
                    p.posSprite.x=755-p.posSprite.w;
					p.posSprite.y=258;}
                    p.direction = -1;
                    break;
             
                 }
                break;
            }
        }

if (p.direction==1 || p.direction==0){
movePerso(&p,dt);
animerPerso(&p);}

saut(&p,dt,265);
if (jump==1){
saut2(&p,dt);
}


collision=0;


    if (collision==0) {
	if ((p.posPerso.x>= 545) && ((p.posPerso.x+b.camera_pos.x)<1768) && (p.direction== 0)){
	scrolling(&b, 0, p);}
	else {
	if ((((p.posPerso.x+b.camera_pos.x) >= 545) || (b.camera_pos.x >15)) && p.direction== 1){
	scrolling(&b, 1, p);}}
	}
    else{
    if (collision==1){
    if (p.spritevie.y<=(128-p.spritevie.h)){
    p.spritevie.y+=26;
    }
    else{
    loop=0;}
    }}


dt = SDL_GetTicks() - prev;
 
SDL_Flip(screen);
}

   /* SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(surface3);
	free_back(&b);*/
    freePerso(&p);
liberer_musique (music); 
    
  
  SDL_Quit();
  return 0;
}






