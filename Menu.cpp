#include "Menu.h"
#include "main_include.h"

TextObject::TextObject(void)
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
}


TextObject::~TextObject(void)
{
}


bool TextObject::loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen)
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface(screen, textSurface);
        if (texture_ != NULL)
        {
            //Get image dimensions
            width_ = textSurface->w;
            height_ = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return texture_ != NULL;
}

void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::setColor(Uint32 red, Uint32 green, Uint32 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        text_color_ = color;
    }
    else
    {
        SDL_Color color = { 0, 0, 0 };
        text_color_ = color;
    }
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y)
{
    SDL_Rect* clip; double angle; SDL_Point* center;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    center = NULL;
    clip = NULL;
    angle = 0.0;
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width_, height_ };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}


int ShowMenu(SDL_Renderer* g_screen,
    const std::string& menu1,
    const std::string& menu2,
    const std::string& img_name)
{
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 2;
    char* labels[kMenuNum];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1 + 1, ch1);
    strcpy_s(labels[1], size2 + 1, ch2);

    SDL_Texture* menu[kMenuNum];
    bool selected[kMenuNum] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    TextObject text_object[kMenuNum];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);

    TTF_Font *font = NULL;
    font = TTF_OpenFont("font-times-new-roman/dlxfont_.ttf", 24);
    text_object[0].loadFromRenderedText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, g_screen);


    SDL_Rect pos[kMenuNum];
    pos[0].x = max_x /2 - 150;
    pos[0].y = max_y/2  - 40;
    pos[1].x = max_x/2  - 150;
    pos[1].y = max_y/2  + 40;

    BaseObject gBackground;
    bool ret = gBackground.loadImg(img_file, g_screen);

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        gBackground.Free();
                        std::cout << i; // player
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    gBackground.Free();
                    return 1;
                }
            }
        }

        gBackground.Render(g_screen, NULL);

        for (int i = 0; i < kMenuNum; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }


        SDL_RenderPresent(g_screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }

    return 0;
}