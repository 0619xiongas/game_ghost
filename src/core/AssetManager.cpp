#include "core/AssetManager.h"

AssetManager::AssetManager()
{
    m_renderer = nullptr;
}

AssetManager::~AssetManager()
{
    for(auto& itr : m_textures)
    {
        SDL_DestroyTexture(itr.second);
    }
    for(auto& itr : m_sounds)
    {
        Mix_FreeChunk(itr.second);
    }
    for(auto& itr : m_fonts)
    {
        TTF_CloseFont(itr.second);
    }
    for(auto& itr : m_musics)
    {
        Mix_FreeMusic(itr.second);
    }
    m_fonts.clear();
    m_musics.clear();
    m_textures.clear();
    m_sounds.clear();
}

void AssetManager::Init(SDL_Renderer *renderer)
{
    if(renderer)
    {
        m_renderer = renderer;
    }
}

SDL_Texture *AssetManager::GetTexture(const std::string &path)
{
    SDL_Texture* ret = nullptr;
    auto itr = m_textures.find(path);
    if(itr == m_textures.end())
    {
        if(LoadTexture(path))
        {
            ret = m_textures[path];
        }
    }
    else
    {
        ret = itr->second;
    }
    return ret;
}

Mix_Chunk *AssetManager::GetSound(const std::string &path)
{
    Mix_Chunk* ret = nullptr;
    auto itr = m_sounds.find(path);
    if(itr == m_sounds.end())
    {
        if(LoadSound(path))
        {
            ret = m_sounds[path];
        }
    }
    else
    {
        ret = itr->second;
    }
    return ret;
}

TTF_Font *AssetManager::GetFont(const std::string &path, int size)
{
    TTF_Font* ret = nullptr;
    auto itr = m_fonts.find(path + std::to_string(size));
    if(itr == m_fonts.end())
    {
        if(LoadFont(path, size))
        {
            ret = m_fonts[path + "--" + std::to_string(size)];
        }
    }
    else
    {
        ret = itr->second;
    }
    return ret;
}

Mix_Music *AssetManager::GetMusic(const std::string &path)
{
    Mix_Music* ret = nullptr;
    auto itr = m_musics.find(path);
    if(itr == m_musics.end())
    {
        if(LoadMusic(path))
        {
            ret = m_musics[path];
        }
    }
    else
    {
        ret = itr->second;
    }
    return ret;
}

bool AssetManager::LoadTexture(const std::string &path)
{
    SDL_Texture* texture = IMG_LoadTexture(m_renderer, path.c_str());
    if(texture)
    {
        m_textures[path] = texture;
    }
    return texture != nullptr;
}

bool AssetManager::LoadSound(const std::string &path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if(sound)
    {
        m_sounds[path] = sound;
    }
    return sound != nullptr;
}

bool AssetManager::LoadFont(const std::string &path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(font)
    {
        m_fonts[path + "--" + std::to_string(size)] = font;
    }
    return font != nullptr;
}

bool AssetManager::LoadMusic(const std::string &path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(music)
    {
        m_musics[path] = music;
    }
    return music != nullptr;
}
