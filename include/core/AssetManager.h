#ifndef AS_SDL_ASSET_MANAGER_H
#define AS_SDL_ASSET_MANAGER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <string>
class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void Init(SDL_Renderer* renderer);

    SDL_Texture* GetTexture(const std::string& path);
    Mix_Chunk* GetSound(const std::string& path);
    TTF_Font* GetFont(const std::string& path, int size);
    Mix_Music* GetMusic(const std::string& path);

private:
    bool LoadTexture(const std::string& path);
    bool LoadSound(const std::string& path);
    bool LoadFont(const std::string& path, int size);
    bool LoadMusic(const std::string& path);
private:
    SDL_Renderer*           m_renderer = nullptr;
    std::unordered_map<std::string, SDL_Texture*> m_textures;
    std::unordered_map<std::string, Mix_Chunk*> m_sounds;
    std::unordered_map<std::string, TTF_Font*> m_fonts;
    std::unordered_map<std::string, Mix_Music*> m_musics;
};
#endif