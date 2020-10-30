#include "include/Highscore.h"

namespace Game
{

    CHighscore::CHighscore(const char8* a_pHighscorePath)
    {

        std::string userpath = std::getenv("USERPROFILE");
        userpath += "\\Documents\\S.T.U.F.F\\";
        userpath += a_pHighscorePath;

        this->m_pFilePath = userpath;
        this->m_pFile = NULL; 
        char8* pbuffer;
        fopen_s(&this->m_pFile, this->m_pFilePath.c_str(), "r"); //always writes at the end, created if it does not exist
        if (m_pFile != NULL)
        {
            // obtain file size
            fseek(this->m_pFile, 0, SEEK_END);
            long lSize = ftell(this->m_pFile);
            rewind(this->m_pFile);

            // allocate memory to contain the whole file:
            pbuffer = (char8*)malloc(sizeof(char8)*lSize);

            // copy the file into the buffer:
            fread(pbuffer, 1, lSize, this->m_pFile);


            int32 textFilePosition = 0;
            int32 lastTextFilePosition = 0;
            char8 readChar = pbuffer[0];
            int32 readWhat = 0;
            char buffer[64] = "";

            SScore score;

            //we read our Buffer and set our map
            while (readChar != '\0')
            {
                readChar = pbuffer[textFilePosition];
                int32 size = textFilePosition - lastTextFilePosition;
                if (readChar == ' ')
                {
                    //set memory
                    memset(buffer, 0, 64);
                    memcpy(buffer, &pbuffer[lastTextFilePosition], size);
                    //set our data to our buffer
                    switch (readWhat)
                    {
                    case 0:
                        score.Points = atoi(buffer);
                        break;
                    case 1:
                        if (buffer[0] == '0')
                            score.Win = false;
                        else
                            score.Win = true;
                        break;
                    case 2:
                        score.Alive = atoi(buffer);
                        break;
                    case 3:
                        score.Death = atoi(buffer);
                        break;
                    case 4:
                        score.Deaths = atoi(buffer);
                        break;
                    }
                    //set what to read next
                    readWhat++;
                    if (readWhat > 4)
                    {
                        this->m_Scores.push_back(score);
                        readWhat = 0;
                    }
                    lastTextFilePosition = textFilePosition + 1;
                }
                textFilePosition++;
            }
            free(pbuffer);
            //close file
            fclose(this->m_pFile);
        }
    }

    // **************************************************************************
    // **************************************************************************

    CHighscore::~CHighscore()
    {
    }

    // **************************************************************************
    // **************************************************************************

    void CHighscore::SaveScore(int32 a_Points, bool a_Win, int32 a_Alive, int32 a_Death, int32 a_Deaths)
    {
        //Save Data
        SScore score;
        score.Points = a_Points;
        score.Win = a_Win;
        score.Alive = a_Alive;
        score.Death = a_Death;
        score.Deaths = a_Deaths;
        this->m_Scores.push_back(score);
        //Sort and remove oversize
        std::sort(this->m_Scores.begin(), this->m_Scores.end());
        while (this->m_Scores.size() > 7)
            this->m_Scores.erase(this->m_Scores.begin() + 7);

        std::string write;
        fopen_s(&this->m_pFile, this->m_pFilePath.c_str(), "w"); //always writes at the end, created if it does not exist
        for (uint32 i = 0; i < this->m_Scores.size(); i++)
        {
            write = "";
            write += std::to_string(this->m_Scores[i].Points) + " ";
            write += std::to_string(this->m_Scores[i].Win) + " ";
            write += std::to_string(this->m_Scores[i].Alive) + " ";
            write += std::to_string(this->m_Scores[i].Death) + " ";
            write += std::to_string(this->m_Scores[i].Deaths) + " ";
            size_t test = fwrite(write.c_str(), sizeof(char), write.length(), this->m_pFile);
        }
        fclose(this->m_pFile);
    }

    // **************************************************************************
    // **************************************************************************

    void CHighscore::Draw(CSpriteReader* a_pMenuSprite, PuRe_Font* a_pActiveFont, PuRe_Camera* a_pCamera, PuRe_Vector3F Position, PuRe_IMaterial* a_pMaterial)
    {
        PuRe_Vector3F startPosition = Position;
        a_pMenuSprite->Draw(a_pCamera, "screen_highscore", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

        startPosition += PuRe_Vector3F(10.0f, 680.0f, -1.0f); // 1
        a_pActiveFont->Draw(a_pCamera, a_pMaterial, "SCORE", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f,1.0f,1.0f,1.0f));
        startPosition += PuRe_Vector3F(170.0f, 0.0f, 0.0f);
        a_pActiveFont->Draw(a_pCamera, a_pMaterial, "GAME", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(200.0f, 0.0f, 0.0f);
        a_pActiveFont->Draw(a_pCamera, a_pMaterial, "PLAYER", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition += PuRe_Vector3F(330.0f, 0.0f, 0.0f);
        a_pActiveFont->Draw(a_pCamera, a_pMaterial, "DEATHS", startPosition, PuRe_Vector3F(56.0f, 56.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 30.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
        startPosition -= PuRe_Vector3F(690.0f, 90.0f, -1.0f); // 2

        for (uint32 i = 0; i < this->m_Scores.size(); i++)
        {
            startPosition -= PuRe_Vector3F(0.0f, 0.0f, 1.0f); // 1
            a_pActiveFont->Draw(a_pCamera, a_pMaterial, std::to_string(this->m_Scores[i].Points).c_str(), startPosition, PuRe_Vector3F(42.0f, 42.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));
            startPosition += PuRe_Vector3F(170.0f, 0.0f, 0.0f); // 1

            if (this->m_Scores[i].Win)
            {
                if (this->m_Scores[i].Deaths == 0)
                    a_pMenuSprite->Draw(a_pCamera, "epic-win", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
                else
                    a_pMenuSprite->Draw(a_pCamera, "win", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            }
            else
                a_pMenuSprite->Draw(a_pCamera, "lose", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));

            startPosition += PuRe_Vector3F(100.0f, 0.0f, 0.0f); // 1
            for (int32 j = 0; j < this->m_Scores[i].Alive; j++)
            {
                startPosition += PuRe_Vector3F(60.0f, 0.0f, 0.0f);
                a_pMenuSprite->Draw(a_pCamera, "player_alive", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            }
            for (int32 j = 0; j < this->m_Scores[i].Death; j++)
            {
                startPosition += PuRe_Vector3F(60.0f, 0.0f, 0.0f);
                a_pMenuSprite->Draw(a_pCamera, "player_death", startPosition, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
            }
            startPosition += PuRe_Vector3F(220.0f + (4 - (this->m_Scores[i].Alive + this->m_Scores[i].Death))*60.0f, 0.0f, 0.0f);
            a_pActiveFont->Draw(a_pCamera, a_pMaterial, std::to_string(this->m_Scores[i].Deaths).c_str(), startPosition, PuRe_Vector3F(46.0f, 46.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), 20.0f, PuRe_Color(1.0f, 1.0f, 1.0f, 1.0f));


            startPosition -= PuRe_Vector3F(730.0f, 90.0f, -1.0f); // 2
        }
    }


}