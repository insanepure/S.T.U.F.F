#include "include\SpriteReader.h"

namespace Game
{
    CSpriteReader::CSpriteReader(PuRe_IMaterial* a_pMaterial, PuRe_Sprite* m_pSprite, const char8* a_pTextPath)
    {
        this->m_pSprite = m_pSprite;
        this->m_pMaterial = a_pMaterial;
        LoadTextFile(a_pTextPath);
        m_OwnerOfSprite = false;
    }

    CSpriteReader::CSpriteReader(PuRe_IGraphics* a_pGraphics, PuRe_IMaterial* a_pMaterial, const char8* a_pSpritePath, const char8* a_pTextPath)
    {
        this->m_pSprite = new PuRe_Sprite(a_pGraphics, a_pSpritePath);
        this->m_pMaterial = a_pMaterial;
        LoadTextFile(a_pTextPath);
        m_OwnerOfSprite = true;
    }

    void CSpriteReader::LoadTextFile(const char8* a_pTextPath)
    {
        //Now read the Sprite Textfile
        FILE* pfile;
        char8* pbuffer;
        long lSize;

        fopen_s(&pfile, a_pTextPath, "r");

        if (pfile == NULL)
            printf("File does not exist %s!\n", a_pTextPath);

        // obtain file size:
        fseek(pfile, 0, SEEK_END);
        lSize = ftell(pfile);
        rewind(pfile);

        // allocate memory to contain the whole file:
        pbuffer = (char8*)malloc(sizeof(char8)*lSize);

        // copy the file into the buffer:
        fread(pbuffer, 1, lSize, pfile);


        int32 textFilePosition = 0;
        int32 lastTextFilePosition = 0;
        char8 readChar = pbuffer[0];
        int32 readWhat = 0;

        SSpriteData spriteData;
        std::string spriteText;
        char buffer[64] = "";

        //we read our Buffer and set our map
        while (readChar != '\0')
        {
            readChar = pbuffer[textFilePosition];
            int32 size = textFilePosition - lastTextFilePosition;
            if (readChar == '\n')
            {
                //set memory
                memset(buffer, 0, 64);
                memcpy(buffer, &pbuffer[lastTextFilePosition], size);
                //set our data to our buffer
                spriteData.Size.Y = (float32)(atoi(buffer));
                //free memory
                //set what to read next and where to start
                readWhat = 0;
                lastTextFilePosition = textFilePosition + 1;
                //save our Data
                this->m_Reader[spriteText] = spriteData;
            }
            else if (readChar == ' ')
            {
                //set memory
                memset(buffer, 0, 64);
                memcpy(buffer, &pbuffer[lastTextFilePosition], size);
                //set our data to our buffer
                switch (readWhat)
                {
                case 0:
                    spriteText = std::string(buffer, 0, size);
                    break;
                case 2:
                    spriteData.Position.X = (float32)(atoi(buffer));
                    break;
                case 3:
                    spriteData.Position.Y = (float32)(atoi(buffer));
                    break;
                case 4:
                    spriteData.Size.X = (float32)(atoi(buffer));
                    break;
                };
                //set what to read next
                readWhat++;
                lastTextFilePosition = textFilePosition + 1;
            }
            textFilePosition++;
        }


        // terminate
        fclose(pfile);
        free(pbuffer);
    }

    // **************************************************************************
    // **************************************************************************

    CSpriteReader::~CSpriteReader()
    {
        if (m_OwnerOfSprite)
        {
            SAFE_DELETE(this->m_pSprite);
        }
    }

    // **************************************************************************
    // **************************************************************************

    void CSpriteReader::Draw(PuRe_Camera* a_pCamera, const char8* a_pName, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector2F Size)
    {

        auto got = m_Reader.find(a_pName);
        this->m_pSprite->Draw(a_pCamera, this->m_pMaterial, got->second.Position, got->second.Size, a_Position, PuRe_Vector3F(got->second.Size.X*Size.X, got->second.Size.Y*Size.Y, 1.0f), a_Rotation, PuRe_Vector3F(0.0f, 0.0f, 0.0f));
    }

    // **************************************************************************
    // **************************************************************************

    void CSpriteReader::Draw(PuRe_Camera* a_pCamera, const char8* a_pName, PuRe_Vector3F a_Position, PuRe_Vector3F a_Rotation, PuRe_Vector2F Size, PuRe_Vector2F UVSize)
    {

        auto got = m_Reader.find(a_pName);
        this->m_pSprite->Draw(a_pCamera, this->m_pMaterial, got->second.Position, PuRe_Vector2F(got->second.Size.X*UVSize.X, got->second.Size.Y*UVSize.Y), a_Position, PuRe_Vector3F(got->second.Size.X*Size.X, got->second.Size.Y*Size.Y, 1.0f), a_Rotation, PuRe_Vector3F(0.0f, 0.0f, 0.0f));
    }
}