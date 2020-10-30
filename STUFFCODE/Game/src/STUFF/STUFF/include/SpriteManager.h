#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include <map>
#include <cstring>
// Declare namespace Game
namespace Game
{
    /// @brief Manager to manage Sprites
    ///
    class CSpriteManager
    {
    public:
        static bool IsReady();
        static void Update();
        static void Clear();
        static PuRe_Sprite* GetSprite(std::string);
        static void AddSprite(std::string, PuRe_Sprite*);
    };
}
#endif /* _SPRITEMANAGER_H_ */