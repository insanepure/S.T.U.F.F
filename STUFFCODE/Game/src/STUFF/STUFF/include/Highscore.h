#ifndef _HIGHSCORE_H_
#define _HIGHSCORE_H_
#define _CRT_SECURE_NO_WARNINGS


// Framework specific includes
#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>

#include <cstdio> // fopen
#include <algorithm>    // std::sort
#include "stdlib.h"

#include "SpriteReader.h"

// Declare namespace Game
namespace Game
{
    /// @brief Score Struct to save the score
    ///
    struct SScore
    {
        int32 Points; //points that one can have
        bool Win; //Win or loose
        int32 Alive; //Who is still alive at the end
        int32 Death; //Deaths at the End
        int32 Deaths; //deaths total, cause player can also be revived

        bool operator<(const SScore& a_Score) const // for std::sort
        {
            return Points > a_Score.Points;
        }
    };
    /// @brief Highscore System used to save and display score of before played games
    ///
    class CHighscore
    {
    private:
        /// @brief File Path
        ///
        std::string m_pFilePath;
        /// @brief File Object to access our File
        ///
        FILE* m_pFile;
        /// @brief Scores we had
        ///
        PuRe_List<SScore> m_Scores;
    public:
        /// @brief Initializes an Highscore Object
        ///
        /// @param Path to the Highscore textfile
        ///
        CHighscore(const char8* a_pHighscorePath);
        /// @brief Destroyes an Highscore Object
        ///
        ~CHighscore();
    public:
        /// @brief Saves the Score
        ///
        /// @param Points to Save
        /// @param if the game is won or not
        /// @param how many players were alive at the end
        /// @param how many players were dead at the end
        /// @param how many deaths have happend
        ///
        void SaveScore(int32 a_Points, bool a_Win, int32 a_Alive, int32 a_Death, int32 a_Deaths);
        /// @brief Draw the Highscore
        ///
        /// @param MenuSpriteReader
        /// @param Font used
        /// @param Camera used
        /// @param Position where the Highscore is drawn
        ///
        void Draw(CSpriteReader* a_pMenuSprite,PuRe_Font* a_pActiveFont,PuRe_Camera* a_pCamera,PuRe_Vector3F Position, PuRe_IMaterial* a_pMaterial);
    };
}
#endif /* _HIGHSCORE_H_ */