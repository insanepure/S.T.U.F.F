#include "include/Player.h"

namespace Game
{

    // **************************************************************************
    // **************************************************************************
    CPlayer::CPlayer(int32 a_Index) : m_Index(a_Index)
    {
        this->m_IsPlaying = false;
        this->m_Ready = false;
        this->m_Ship = 0;
        this->m_pIntArray = nullptr;

    }


    // **************************************************************************
    // **************************************************************************
    CPlayer::~CPlayer()
    {
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Init(CLuaReader* a_pLuaReader, PuRe_Vector3F a_Position)
    {
        this->m_Position = a_Position;
        //Init function
        a_pLuaReader->SetFunction("Init");
        //Return 7 Values
        a_pLuaReader->CallFunction(0, 7);
        //return values
        this->m_BoundingBox.m_Size.Y = a_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Size.X = a_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position.Y = a_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position.X = a_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position += this->m_Position;
        this->m_BoundingBox.m_Position.Z = 0.0f;
        this->m_ShipSize.X = a_pLuaReader->PopFloat();
        this->m_ShipSize.Y = a_pLuaReader->PopFloat();
        this->m_ArraySize = a_pLuaReader->PopInt();
        //Now we set our IntArray
        //Our IntArray is used so the GameDesigner can define their variables for themself
        if (this->m_pIntArray == nullptr)
            this->m_pIntArray = new int32[this->m_ArraySize];
        //Clear it
        memset(this->m_pIntArray, 0, this->m_ArraySize*sizeof(int32));
        //Clear other Variables
        this->m_Lifes = 9;
        this->m_Item = 0;
        this->m_Points = 0;
        this->m_Angle = 0.0f;
        this->m_Shield = 0;
        this->m_LookAngle = 0.0f;
        this->m_Speed = 0.0f;
        this->m_FireRateTime = 0.0f;
        this->m_R = 0.0f;
        this->m_G = 0.0f;
        this->m_B = 0.0f;
        this->m_BlinkTime = 0.0f;
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Move(PuRe_Vector3F a_AddPosition)
    {
        this->m_Position += a_AddPosition;
        this->m_BoundingBox.m_Position += a_AddPosition;
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Update(CLuaReader* a_pLuaReader, float32 a_DeltaTime,PuRe_IInput* a_pInput,float32 a_Cam_X,bool& a_bomb, bool& a_Energy)
    {
        PuRe_Vector2F controllerAxis = a_pInput->GetGamepadLeftThumb(this->m_Index);
        float32 movingAngle = std::atan2(controllerAxis.Y, controllerAxis.X);
        float32 GamePadDeflection = abs(controllerAxis.X) + abs(controllerAxis.Y);
        if (GamePadDeflection < 0.5f)
            GamePadDeflection = 0.0f;
        else if (GamePadDeflection > 1.0f)
            GamePadDeflection = 1.0f;
        //set firerate Time
        if (this->m_FireRateTime > 0.0f)
            this->m_FireRateTime -= a_DeltaTime;
        else
            this->m_FireRateTime = 0.0f;
        //set blink Time
        if (this->m_BlinkTime > 0.0f)
            this->m_BlinkTime -= a_DeltaTime;
        else
            this->m_BlinkTime = 0.0f;
        //Handle 
        if (a_pInput->GamepadPressed(PuReSpace::Left_Shoulder,this->m_Index))
        {
            if (this->m_Item != 0)
            {
                switch (this->m_Item)
                {
                case 1:
                    this->m_FireRateTime = 5.0f;
                    CSoundManager::m_pSoundPlayer->PlaySound("doublefirerate", false, false, CSoundManager::m_SoundVolume);
                    break;
                case 2:
                    a_bomb = true;
                    break;
                case 4:
                    this->m_Shield = 3;
                    CSoundManager::m_pSoundPlayer->PlaySound("shieldonshort", false, false, CSoundManager::m_SoundVolume);
                    break;
                case 5:
                    a_Energy = true;
                    break;
                }
                this->m_Item = 0;
            }
        }
        PuRe_Vector3F Middle = this->m_BoundingBox.m_Position;
        Middle.X += this->m_BoundingBox.m_Size.X / 2.0f;
        Middle.Y += this->m_BoundingBox.m_Size.Y / 2.0f;
        //Update Loop function
        a_pLuaReader->SetFunction("UpdateLoop");
        //Push Int Array
        for (int32 i = 0; i<this->m_ArraySize;i++)
            a_pLuaReader->Push(this->m_pIntArray[i]);
        //Push Other Variables
        a_pLuaReader->Push(this->m_Ship+1);
        a_pLuaReader->Push(this->m_FireRateTime > 0.0f); //fireRate
        a_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_X, this->m_Index)); //X
        a_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_Y, this->m_Index)); //Y
        a_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_B, this->m_Index)); //B
        a_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_A, this->m_Index)); //A
        a_pLuaReader->Push(this->m_Index); //PlayerNum
        a_pLuaReader->Push(Middle.X); //Player_X
        a_pLuaReader->Push(Middle.Y); //Player_Y
        a_pLuaReader->Push(this->m_Angle); //Player_Angle
        a_pLuaReader->Push(this->m_LookAngle); //Player_LookAngle
        a_pLuaReader->Push(this->m_Speed); //Player_Speed
        a_pLuaReader->Push(a_DeltaTime*60.0f); //timeMultiplicator
        //Call Function
        a_pLuaReader->CallFunction(this->m_ArraySize + 13, this->m_ArraySize + 5);
        //Return Values
        int32 RumbleLength = a_pLuaReader->PopInt();
        float32 RumbleStrength = a_pLuaReader->PopFloat();
        this->m_B = a_pLuaReader->PopFloat();
        this->m_G = a_pLuaReader->PopFloat();
        this->m_R = a_pLuaReader->PopFloat();
        if (this->m_R > 1.0f) this->m_R = 1.0f;
        else if (this->m_R < 0.0f) this->m_R = 0.0f;
        if (this->m_G > 1.0f) this->m_G = 1.0f;
        else if (this->m_G < 0.0f) this->m_G = 0.0f;
        if (this->m_B > 1.0f) this->m_B = 1.0f;
        else if (this->m_B < 0.0f) this->m_B = 0.0f;
        //return Int Array
        for (int32 i = this->m_ArraySize-1; i>=0; i--)
            this->m_pIntArray[i] = a_pLuaReader->PopInt();

        if (GamePadDeflection != 0.0f)
        {
            //Update Angle
            a_pLuaReader->SetFunction("UpdateAngle");
            //Push Int Array
            for (int32 i = 0; i<this->m_ArraySize; i++)
                a_pLuaReader->Push(this->m_pIntArray[i]);
            //Push Other Variables
            a_pLuaReader->Push(a_DeltaTime*60.0f); //timeMultiplciator
            a_pLuaReader->Push(this->m_Angle); //Angle
            a_pLuaReader->Push(this->m_LookAngle); //LookAngle
            a_pLuaReader->Push(movingAngle); //MovingAngle
            a_pLuaReader->Push(this->m_Speed); //Speed
            a_pLuaReader->Push(this->m_Ship); //Type
            //Call Function
            a_pLuaReader->CallFunction(this->m_ArraySize + 6, this->m_ArraySize + 2);
            //Return Values
            this->m_Angle = a_pLuaReader->PopFloat();
            this->m_LookAngle = a_pLuaReader->PopFloat();
            //return Int Array
            for (int32 i = this->m_ArraySize - 1; i >= 0; i--)
                this->m_pIntArray[i] = a_pLuaReader->PopInt();
        }

        //Update Speed
        a_pLuaReader->SetFunction("UpdateSpeed");
        //Push Int Array
        for (int32 i = 0; i<this->m_ArraySize; i++)
            a_pLuaReader->Push(this->m_pIntArray[i]);
        //Push Other Variables
        a_pLuaReader->Push(a_Cam_X); //Cam_X
        a_pLuaReader->Push(a_DeltaTime); //timeMultiplciator
        a_pLuaReader->Push(this->m_Angle); //Angle
        a_pLuaReader->Push(movingAngle); //MovingAngle
        a_pLuaReader->Push(0.0f); //LT
        a_pLuaReader->Push(GamePadDeflection); //RT
        a_pLuaReader->Push(this->m_Speed); //Speed
        //Call Function
        a_pLuaReader->CallFunction(this->m_ArraySize + 7, this->m_ArraySize + 1);
        //Return Values
        this->m_Speed = a_pLuaReader->PopFloat();
        //return Int Array
        for (int32 i = this->m_ArraySize - 1; i >= 0; i--)
            this->m_pIntArray[i] = a_pLuaReader->PopInt();
        a_DeltaTime *= 50.0f;
        if (this->m_Speed > 0.0f)
        {
            PuRe_Vector3F diffPosition = this->m_Position;

            this->m_Position.X += (cos(this->m_Angle)*this->m_Speed)*a_DeltaTime;
            this->m_Position.Y += (sin(this->m_Angle)*this->m_Speed)*a_DeltaTime;

            this->m_Position.X = std::floor(this->m_Position.X);
            this->m_Position.Y = std::floor(this->m_Position.Y);

            diffPosition = this->m_Position - diffPosition;
            diffPosition.Z = 0.0f;
            this->m_BoundingBox.m_Position += diffPosition;

        }

    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::ResetPosition(PuRe_Vector3F a_Position)
    {
        PuRe_Vector3F diffPosition = this->m_Position;
        this->m_Position = a_Position;
        diffPosition = this->m_Position - diffPosition;
        diffPosition.Z = 0.0f;
        this->m_BoundingBox.m_Position += diffPosition;
        CSoundManager::m_pSoundPlayer->PlaySound("lostship", false, false, CSoundManager::m_SoundVolume);
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Hit()
    {
        if (this->m_BlinkTime == 0.0f)
        {
            if (this->m_Shield > 0)
            {
                this->m_Shield--;
                if (this->m_Shield != 0)
                    CSoundManager::m_pSoundPlayer->PlaySound("shieldhit", false, false, CSoundManager::m_SoundVolume);
                else
                    CSoundManager::m_pSoundPlayer->PlaySound("shielddestroyed", false, false, CSoundManager::m_SoundVolume);
            }
            else
            {
                CSoundManager::m_pSoundPlayer->PlaySound("hit", false, false, CSoundManager::m_SoundVolume);
                this->m_Lifes--;
                if (this->m_Lifes != 0)
                {
                    //set blinking
                    this->m_BlinkTime = 2.0f;
                }
            }
        }
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Heal(PuRe_Vector3F a_Position)
    {
        if (this->m_Lifes == 0)
        {
            this->ResetPosition(a_Position);
            this->m_BlinkTime = 2.0f;
        }
        this->m_Lifes = 9;
    }


    // **************************************************************************
    // **************************************************************************
    void CPlayer::Draw(PuRe_Camera* a_pCamera, PuRe_Sprite* a_pSprite, PuRe_Sprite* a_pShieldSprite, PuRe_IMaterial* a_pMaterial)
    {
        if ((int32)(this->m_BlinkTime*10) % 2 == 0&&this->m_Lifes > 0)
        {
            //use effect
            a_pMaterial->Apply();
            a_pMaterial->SetFloat(this->m_R, "R");
            a_pMaterial->SetFloat(this->m_G, "G");
            a_pMaterial->SetFloat(this->m_B, "B");
            //Draw Sprite
            a_pSprite->Draw(
                a_pCamera,a_pMaterial, PuRe_Vector2F((this->m_Ship % 2)*128.0f, (float32)((int32)(this->m_Ship / 2))*128.0f),
                this->m_ShipSize, this->m_Position, PuRe_Vector3F(this->m_ShipSize.X, this->m_ShipSize.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            //Unuse effect
            a_pMaterial->Apply();
            a_pMaterial->SetFloat(0.0f, "R");
            a_pMaterial->SetFloat(0.0f, "G");
            a_pMaterial->SetFloat(0.0f, "B");
        }
        if (this->m_Shield != 0)
        {
            PuRe_Vector3F pos = this->m_Position;
            pos.Z -= 1.0f;
            a_pShieldSprite->Draw(
                a_pCamera, a_pMaterial, PuRe_Vector2F(0.0f,256.0f),
                PuRe_Vector2F(128.0f, 128.0f), pos, PuRe_Vector3F(this->m_ShipSize.X, this->m_ShipSize.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        }
    }


    // **************************************************************************
    // **************************************************************************
    PuRe_Vector3F CPlayer::GetPosition()
    {
        return this->m_Position;
    }


    // **************************************************************************
    // **************************************************************************
    PuRe_BoundingBox CPlayer::GetBox()
    {
        return this->m_BoundingBox;
    }


    // **************************************************************************
    // **************************************************************************
    float32 CPlayer::GetSpeed()
    {
        return this->m_Speed;
    }


    // **************************************************************************
    // **************************************************************************
    float32 CPlayer::GetLookAngle()
    {
        return this->m_LookAngle;
    }


    // **************************************************************************
    // **************************************************************************
    int32 CPlayer::GetLifes()
    {
        return this->m_Lifes;
    }
}