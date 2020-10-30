#ifndef _MAP_H_
#define _MAP_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "LuaReader.h"
#include "SpriteReader.h"
#include "Background.h"
#include "BubbleEmitter.h"
#include "SoundManager.h"

// Declare namespace Game
namespace Game
{
    /// @brief Points where the Map is generated at
    ///
    struct SPoint
    {
        int32 X;
        int32 Y;
        int32 TileDist;
        int32 BoundingBoxStart;
        int32 BoundingBoxEnd;
        bool Fall;
        int32 Split;
    };
    /// @brief Tile which is drawn
    ///
    struct STile
    {
        PuRe_Vector3F Position;
        PuRe_Vector2F UVPosition;
        bool flip;
        int32 stoneStartIndex;
        int32 stoneEndIndex;
        int32 AmbientIndex;
        int32 fallIndex;
        int32 towerIndex;
    };
    /// @brief Stone which is drawn
    ///
    struct SStone
    {
        PuRe_Vector3F Position;
        PuRe_Vector2F UVPosition;
        bool flip;
    };
    /// @brief Ambient  which is drawn
    ///
    struct SAmbient
    {
        PuRe_Vector3F Position;
        std::string Name;
        bool flip;
    };
    /// @brief It's a falling Object
    ///
    struct SFalling
    {
        PuRe_Vector3F Position;
        PuRe_BoundingBox Box;
        bool fall;
        bool dead;
        float32 fallTime;
    };
    /// @brief It's a tower Object
    ///
    struct STower
    {
        PuRe_Vector3F Position;
        PuRe_BoundingBox Box;
        int32 Hitpoints;
        bool fall;
        bool dead;
        int32 Animation;
        float32 AnimationTime;
    };
    /// @brief Map which is drawn 
    ///
    class CMap
    {
    private:
        /// @brief if its a MenuMap or not
        ///
        bool m_pMenu;
        /// @brief Background behind the Map
        ///
        CBackground* m_pBackground;
        /// @brief Min Max of the X Axis
        ///
        PuRe_Vector2F m_MinMaxX;
        /// @brief Min Max of the Y Axis
        ///
        PuRe_Vector2F m_MinMaxY;
        /// @brief Amount of Tiles each Point
        ///
        static int32 m_TileAmount;
        /// @brief Tile Array
        ///
        STile* m_pTiles;
        /// @brief All Bounding Boxes
        ///
        std::vector<PuRe_BoundingBox> m_BoundingBox;
        /// @brief FallingObjects Array
        ///
        std::vector<STower> m_Tower;
        /// @brief FallingObjects Array
        ///
        std::vector<SFalling> m_Falling;
        /// @brief Ambient Array
        ///
        std::vector<SAmbient> m_Ambient;
        /// @brief Stone Array
        ///
        std::vector<SStone> m_Stones;
        /// @brief Falling Sprites
        ///
        PuRe_Sprite* m_pFallingSprite;
        /// @brief Tower Sprites
        ///
        CSpriteReader* m_pTowerSprite;
        /// @brief Stone Sprites
        ///
        PuRe_Sprite* m_pStoneSprite;
        /// @brief Tiles as Sprite
        ///
        PuRe_Sprite* m_pTileSprite;
        /// @brief Tiles for the Ambient
        ///
        CSpriteReader* m_pAmbientSprite;
        /// @brief Point Array
        ///
        static SPoint* m_pPoints;
        /// @brief LuaReader to read map Lua File
        ///
        CLuaReader* m_LuaReader;
        /// @brief Size of the Map
        ///
        static int32 m_MapSize;

        PuRe_IMaterial* m_pMaterial;
    public:
        /// @brief Initializes a Map Instance
        ///
        /// @param Path to the Lua File
        /// @param Material object
        /// @param Graphics object
        /// @param bool just for the Menu
        ///
        CMap(const char8* a_pLuaPath, PuRe_IMaterial* a_pMaterial, PuRe_IGraphics* a_pGraphics,bool a_Menu);
        /// @brief Initializes a Map Instance
        ///
        /// @param Path to the Lua File
        /// @param Material object
        /// @param Graphics object
        ///
        CMap(const char8* a_pLuaPath, PuRe_IMaterial* a_pMaterial, PuRe_IGraphics* a_pGraphics);
        /// @brief Destroyes a Map Instance
        ///
        ~CMap();
    public:
        /// @brief Draw the map within a range
        ///
        /// @param Camera Object
        /// @param minimal X range to draw
        /// @param maximal X range to draw
        /// @param minimal Y range to draw
        /// @param maximal Y range to draw
        ///
        void Draw(PuRe_Camera* a_pCamera, int32 a_minXRange, int32 a_maxXRange, int32 a_minYRange, int32 a_maxYRange, PuRe_Vector3F a_CamPosition);
        /// @brief Checks if the Box intersects with the Map
        ///
        /// @param The other Box
        ///
        /// @returns if it collides
        ///
        bool Intersect(PuRe_BoundingBox& a_rBox);
        /// @brief Checks if the Box intersects with the Map's Fall or Tower
        ///
        /// @param The other Box
        ///
        /// @returns if it collides
        ///
        bool HitDestroyable(PuRe_BoundingBox& a_rBox);
        /// @brief Returns the Map'size
        ///
        /// @returns Map Size
        ///
        int32 GetSize();
        /// @brief Returns the Map's Middle which can be moved to
        ///
        /// @param Position of the Point where we cant to check for the middle
        ///
        /// @returns Map Middle at the Position
        ///
        PuRe_Vector3F GetMiddle(PuRe_Vector3F a_Position);
        /// @brief Update Map's Data
        ///
        /// @param Delta time
        /// @param Bubble Emitter
        /// @param Position which we currently see
        /// @param Resolution of the Screen
        ///
        void Update(float32 a_DeltaTime, CBubbleEmitter* a_pEmitter, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_Resolution);
        /// @brief Function to get the Y Position of the tile at the bottom of x position
        ///
        /// @param LuaState
        ///
        static int GetY(lua_State* a_pLuaState);
    private:
        /// @brief Generate The Map
        ///
        /// @param Y Coordinate
        ///
        void Generate(int32 Y);
    };
}
#endif /* _MAP_H_ */