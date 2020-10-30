#ifndef _SPRITEREADER_H_
#define _SPRITEREADER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include <cstring> // std::string
#include <cstdio> // fopen
#include <unordered_map>

// Declare namespace Game
namespace Game
{
    /// @brief Data of Our Sprite to make a map out of it
    ///
    struct SSpriteData
    {
        PuRe_Vector2F Position;
        PuRe_Vector2F Size;
    };
    /// @brief A SpriteReader to read the Position of Sprites from a Textfile
    ///
    class CSpriteReader
    {
    private:
        PuRe_IMaterial* m_pMaterial;
        /// @brief Used Sprite to render
        ///
        PuRe_Sprite* m_pSprite;
        /// @brief We save our Data into a map
        ///
        std::unordered_map<std::string, SSpriteData> m_Reader;

        bool m_OwnerOfSprite;
    private:
        void LoadTextFile(const char8* a_pTextPath);
    public:
        /// @brief Constructor to initialize a SpriteReader
        ///
        /// @param Graphic pointer to initialize our Sprite
        /// @param Used Material to draw
        /// @param Sprite to initialize from
        ///
        CSpriteReader(PuRe_IMaterial* a_pMaterial, PuRe_Sprite* m_pSprite, const char8* a_pTextPath);
        /// @brief Constructor to initialize a SpriteReader
        ///
        /// @param Graphic pointer to initialize our Sprite
        /// @param Used Material to draw
        /// @param Path to our Sprite
        /// @param Path to our Textfile
        ///
        CSpriteReader(PuRe_IGraphics* a_pGraphics, PuRe_IMaterial* a_pMaterial, const char8* a_pSpritePath, const char8* a_pTextPath);
        /// @brief Destructor to destroy a SpriteReader
        ///
        ~CSpriteReader();
    public:
        /// @brief Draw a Part of the Sprite
        ///
        /// @param Camera used to draw it to
        /// @param Name of the rendered Part
        /// @param Position where to render
        /// @param Rotation of the Sprite
        /// @param Size in Range from 0 to 1
        ///
        void Draw(PuRe_Camera* a_pCamera, const char8* a_pName, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector2F Size);
        /// @brief Draw a Part of the Sprite
        ///
        /// @param Camera used to draw it to
        /// @param Name of the rendered Part
        /// @param Position where to render
        /// @param Rotation of the Sprite
        /// @param Size in Range from 0 to 1 for SIZE
        /// @param Size in Range from 0 to 1 for UVSIZE
        ///
        void Draw(PuRe_Camera* a_pCamera, const char8* a_pName, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector2F Size, PuRe_Vector2F UVSize);
    };
}
#endif /* _SPRITEREADER_H_ */