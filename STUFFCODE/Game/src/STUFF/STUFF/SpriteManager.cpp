#include "include/SpriteManager.h"

namespace Game
{
    static bool isReady = false;
    static std::unordered_map<std::string, PuRe_Sprite*> m_Sprites;

    void CSpriteManager::Clear()
    {
        typedef std::unordered_map<std::string, PuRe_Sprite*>::iterator it_type;
        for (it_type iterator = m_Sprites.begin(); iterator != m_Sprites.end(); iterator++)
        {
            PuRe_Sprite* sprite = iterator->second;
            SAFE_DELETE(sprite);
        }

        m_Sprites.clear();
    }

    bool CSpriteManager::IsReady()
    {
        return isReady;
    }

    void CSpriteManager::Update()
    {
        if (isReady)
        {
            return;
        }

        isReady = true;
        typedef std::unordered_map<std::string, PuRe_Sprite*>::iterator it_type;
        for (it_type iterator = m_Sprites.begin(); iterator != m_Sprites.end(); iterator++) 
        {
            PuRe_Sprite* sprite = iterator->second;
            if (!sprite->FinishedLoading())
            {
                isReady = false;
                sprite->Update();
            }
        }
    }

    PuRe_Sprite* CSpriteManager::GetSprite(std::string a_SpriteName)
    {
        return m_Sprites.find(a_SpriteName)->second;
    }

    void CSpriteManager::AddSprite(std::string a_SpriteName, PuRe_Sprite* a_pSprite)
    {
        isReady = false;

        std::unordered_map<std::string, PuRe_Sprite*>::iterator it = m_Sprites.begin();

        std::pair<std::string, PuRe_Sprite*> pair = std::pair<std::string, PuRe_Sprite*>(a_SpriteName, a_pSprite);

        m_Sprites.insert(it, pair);
    }
}