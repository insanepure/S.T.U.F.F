#ifndef _LASER_H_
#define _LASER_H_


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include "SpriteReader.h"
#include "LuaReader.h"
#include "Player.h"

// Declare namespace Game
namespace Game
{
    /// @brief LASER which can be shot by the bigUboot
    ///
    class CLaser
    {
    private:
        /// @brief If the laser hits the player
        ///
        bool m_HitPlayer;
        /// @brief How much damage the Laser deals
        ///
        float32 m_Damage;
        /// @brief Which Player shot the Laser
        ///
        int32 m_PlayerNum;
        /// @brief Image ID of the First Part
        ///
        int32 m_Image_B;
        /// @brief Width of the First Part
        ///
        float32 m_Image_B_Width;
        /// @brief Image ID of the Second Part
        ///
        int32 m_Image_MS;
        /// @brief Width of the Second Part
        ///
        float32 m_Image_MS_Width;
        /// @brief Image ID of the Looping Part
        ///
        int32 m_Image_ML;
        /// @brief Width of the Looping Part
        ///
        float32 m_Image_ML_Width;
        /// @brief Image ID of the End Part
        ///
        int32 m_Image_E;
        /// @brief Width of the End Part
        ///
        float32 m_Image_E_Width;
        /// @brief time the laser has been existing
        ///
        float32 m_LifeTime;
        /// @brief Position of the Laser
        ///
        PuRe_Vector3F m_Position;
        /// @brief BoundingBox for the Laser
        ///
        PuRe_BoundingBox m_BoundingBox;
        /// @brief Length of the Laser
        ///
        int32 m_Length;
    public:
        /// @brief Constructor to initialize the laser
        ///
        /// @param Bounding Box
        /// @param DrawPosition
        /// @param Which Image is for the first part
        /// @param Which Image is for the next part
        /// @param Which Image is for the looping part
        /// @param Which Image is for the end part
        /// @param Which Image is for the first part
        /// @param Width for the first part
        /// @param Width for the next part
        /// @param Width for the looping part
        /// @param Width for the end part
        /// @param Player Index
        /// @param How long the Laser stays
        /// @param Damage dealt
        /// @param If it hits the player
        /// @param length
        ///
        CLaser(
            PuRe_BoundingBox a_BoundingBox,
            PuRe_Vector3F a_Position,
            int32 a_Image_B,
            int32 a_Image_MS,
            int32 a_Image_ML,
            int32 a_Image_E,
            float32 a_Image_B_Width,
            float32 a_Image_MS_Width,
            float32 a_Image_ML_Width,
            float32 a_Image_E_Width,
            int32 a_PlayerNum,
            float32 a_LifeTime,
            float32 a_Damage,
            bool a_HitPlayer,
            int32 a_Length);
        /// @brief destructor to destroy the laser
        ///
        ~CLaser();
        /// @brief Update the Laser
        ///
        /// @param Position the Laser is at
        /// @param DeltaTime
        ///
        /// @returns returns if it is dead or not
        ///
        bool Update(PuRe_Vector3F a_Position, float32 a_DeltaTime);
        /// @brief draw the Laser
        ///
        /// @param Camera Object
        /// @param Sprite used
        /// @param Material used
        ///
        void Draw(PuRe_Camera* a_pCamera, CSpriteReader* a_pSprite, PuRe_IMaterial* a_pMaterial);
        /// @brief Returns Bounding Box
        ///
        /// @returns A Bounding Box
        ///
        PuRe_BoundingBox& GetBoundingBox();
        /// @brief Returns damage the laser deals
        ///
        /// @returns damage as float32
        ///
        float32 GetDamage();
        /// @brief Returns the index of the Player that shot
        ///
        /// @returns index as int32
        ///
        int32 GetPlayer();
    };
}
#endif /* _LASER_H_ */