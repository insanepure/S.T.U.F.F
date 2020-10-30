#include "include/BigUboot.h"

namespace Game
{

    CBigUboot::CBigUboot(CLuaReader* a_pLuaReader, CPlayer** a_ppPlayers, PuRe_Sprite* a_pSprite) : m_pLuaReader(a_pLuaReader), m_ppPlayers(a_ppPlayers), m_pSprite(a_pSprite)
    {
        this->m_Position = PuRe_Vector3F(-9999.0f,-9999.0f,0.0f);
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
        this->m_ShipSize.X = a_pLuaReader->PopFloat();
        this->m_ShipSize.Y = a_pLuaReader->PopFloat();
        this->m_ArraySize = a_pLuaReader->PopInt();
        //Now we set our IntArray
        //Our IntArray is used so the GameDesigner can define their variables for themself
        if (this->m_pIntArray == nullptr)
            this->m_pIntArray = new int32[this->m_ArraySize*4];
        //Clear it
        memset(this->m_pIntArray, 0, this->m_ArraySize*4*sizeof(int32));
        //he is not in use
        this->m_InUse = false;
        this->m_Lifes = 0;
        this->m_AnimationSpeed = 0.4f;
    }


    // **************************************************************************
    // **************************************************************************
    CBigUboot::~CBigUboot()
    {
        this->m_pLuaReader->SetFunction("OnDie");
        this->m_pLuaReader->CallFunction(0, 0);
        SAFE_DELETE(this->m_pLuaReader);
        SAFE_DELETE(this->m_pSprite);
    }


    // **************************************************************************
    // **************************************************************************
    void CBigUboot::Update(float32 a_DeltaTime, PuRe_IInput* a_pInput, float32 a_Cam_X, int32& a_Energy)
    {
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
        for (int32 i = 0; i < 4; i++)
        {
            if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
            {
                //start of our index
                int32 start = this->m_ArraySize*i;
                int32 end = start + this->m_ArraySize;

                //controller values
                PuRe_Vector2F controllerAxis = a_pInput->GetGamepadLeftThumb(i);
                float32 movingAngle = std::atan2(controllerAxis.Y, controllerAxis.X);
                float32 GamePadDeflection = abs(controllerAxis.X) + abs(controllerAxis.Y);

                if (GamePadDeflection < 0.5f)
                    GamePadDeflection = 0.0f;
                else if (GamePadDeflection > 1.0f)
                    GamePadDeflection = 1.0f;
                //Middle of the box
                PuRe_Vector3F Middle = this->m_BoundingBox.m_Position;
                Middle.X += this->m_BoundingBox.m_Size.X / 2.0f;
                Middle.Y += this->m_BoundingBox.m_Size.Y / 2.0f;
                //Update Loop function
                this->m_pLuaReader->SetFunction("UpdateLoop");
                //Push Int Array

                for (int32 j = start; j<end; j++)
                    this->m_pLuaReader->Push(this->m_pIntArray[j]);
                //Push Other Variables
                this->m_pLuaReader->Push(this->m_ppPlayers[i]->m_BigPosition);
                this->m_pLuaReader->Push(this->m_ppPlayers[i]->m_Ship + 1);
                this->m_pLuaReader->Push(this->m_FireRateTime > 0.0f); //fireRate
                this->m_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_X, i)); //X
                this->m_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_Y, i)); //Y
                this->m_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_B, i)); //B
                this->m_pLuaReader->Push(a_pInput->GamepadIsPressed(PuReSpace::Pad_A, i)); //A
                this->m_pLuaReader->Push(i); //PlayerNum
                this->m_pLuaReader->Push(Middle.X); //Player_X
                this->m_pLuaReader->Push(Middle.Y); //Player_Y
                this->m_pLuaReader->Push(this->m_Angle); //Player_Angle
                this->m_pLuaReader->Push(this->m_LookAngle); //Player_LookAngle
                this->m_pLuaReader->Push(this->m_Speed); //Player_Speed
                this->m_pLuaReader->Push(a_DeltaTime*60.0f); //timeMultiplicator
                //Call Function
                this->m_pLuaReader->CallFunction(this->m_ArraySize + 14, this->m_ArraySize + 9);
                //Return Values
                int32 RumbleLength = this->m_pLuaReader->PopInt();
                float32 RumbleStrength = this->m_pLuaReader->PopFloat();
                this->m_B = this->m_pLuaReader->PopFloat();
                this->m_G = this->m_pLuaReader->PopFloat();
                this->m_R = this->m_pLuaReader->PopFloat();

                //Set our special abilities
                this->m_SpeedUp = this->m_pLuaReader->PopFloat();
                int32 energy = this->m_pLuaReader->PopInt();
                a_Energy += energy;
                float32 fireRate = this->m_pLuaReader->PopFloat();
                if (fireRate != 0.0f&&this->m_FireRateTime == 0.0f)
                    this->m_FireRateTime = fireRate;
                int32 shield = this->m_pLuaReader->PopInt();
                if (shield != 0)
                    this->m_Shield = shield;
                
                if (this->m_R > 1.0f) this->m_R = 1.0f;
                else if (this->m_R < 0.0f) this->m_R = 0.0f;
                if (this->m_G > 1.0f) this->m_G = 1.0f;
                else if (this->m_G < 0.0f) this->m_G = 0.0f;
                if (this->m_B > 1.0f) this->m_B = 1.0f;
                else if (this->m_B < 0.0f) this->m_B = 0.0f;
                //return Int Array
                for (int32 j = end - 1; j >= start; j--)
                    this->m_pIntArray[j] = this->m_pLuaReader->PopInt();

                //only update when he is the first one
                if (this->m_ppPlayers[i]->m_BigPosition == 0)
                {
                    if (GamePadDeflection != 0.0f)
                    {
                        //Update Angle
                        this->m_pLuaReader->SetFunction("UpdateAngle");
                        //Push Int Array
                        for (int32 j = start; j<end; j++)
                            this->m_pLuaReader->Push(this->m_pIntArray[j]);
                        //Push Other Variables
                        this->m_pLuaReader->Push(a_DeltaTime*60.0f); //timeMultiplciator
                        this->m_pLuaReader->Push(this->m_Angle); //Angle
                        this->m_pLuaReader->Push(this->m_LookAngle); //LookAngle
                        this->m_pLuaReader->Push(movingAngle); //MovingAngle
                        this->m_pLuaReader->Push(this->m_Speed); //Speed
                        //Call Function
                        this->m_pLuaReader->CallFunction(this->m_ArraySize + 5, this->m_ArraySize + 2);
                        //Return Values
                        this->m_Angle = this->m_pLuaReader->PopFloat();
                        this->m_LookAngle = this->m_pLuaReader->PopFloat();
                        //return Int Array
                        for (int32 j = end - 1; j >= start; j--)
                            this->m_pIntArray[j] = this->m_pLuaReader->PopInt();
                    }

                    //Update Speed
                    this->m_pLuaReader->SetFunction("UpdateSpeed");
                    //Push Int Array
                    for (int32 j = start; j<end; j++)
                        this->m_pLuaReader->Push(this->m_pIntArray[j]);
                    //Push Other Variables
                    this->m_pLuaReader->Push(a_Cam_X); //Cam_X
                    this->m_pLuaReader->Push(a_DeltaTime*60.0f); //timeMultiplciator
                    this->m_pLuaReader->Push(this->m_Angle); //Angle
                    this->m_pLuaReader->Push(movingAngle); //MovingAngle
                    this->m_pLuaReader->Push(0.0f); //LT
                    this->m_pLuaReader->Push(GamePadDeflection); //RT
                    this->m_pLuaReader->Push(this->m_Speed); //Speed
                    //Call Function
                    this->m_pLuaReader->CallFunction(this->m_ArraySize + 7, this->m_ArraySize + 1);
                    //Return Values
                    this->m_Speed = this->m_pLuaReader->PopFloat();
                    //return Int Array
                    for (int32 j = end - 1; j >= start; j--)
                        this->m_pIntArray[j] = this->m_pLuaReader->PopInt();

                    a_DeltaTime *= 50.0f;

                    if (this->m_Speed+this->m_SpeedUp > 0.0f)
                    {
                        PuRe_Vector3F diffPosition = this->m_Position;

                        this->m_Position.X += (cos(this->m_Angle)*(this->m_Speed + this->m_SpeedUp))*a_DeltaTime;
                        this->m_Position.Y += (sin(this->m_Angle)*(this->m_Speed + this->m_SpeedUp))*a_DeltaTime;

                        this->m_Position.X = std::floor(this->m_Position.X);
                        this->m_Position.Y = std::floor(this->m_Position.Y);

                        diffPosition = this->m_Position - diffPosition;

                        this->m_BoundingBox.m_Position += diffPosition;

                    }
                }
            }
        }// end for loop
        this->m_AnimationTime += (a_DeltaTime * this->m_AnimationSpeed);
        while (this->m_AnimationTime > 9.0f)
        {
            this->m_AnimationTime = this->m_AnimationTime - 9.0f;
        }
        this->m_AnimationFrame = (int32)this->m_AnimationTime;
    }


    // **************************************************************************
    // **************************************************************************
    void CBigUboot::Draw(PuRe_Camera* a_pCamera, PuRe_Sprite* a_pShieldSprite, PuRe_IMaterial* a_pMaterial)
    {
        if ((int32)(this->m_BlinkTime * 10) % 2 == 0)
        {
            PuRe_Vector2F UVSize(this->m_ShipSize.X, this->m_ShipSize.Y);
            PuRe_Vector2F UVPosition = PuRe_Vector2F(UVSize.X*this->m_AnimationFrame, 0.0f);
            //use effect
            a_pMaterial->Apply();
            a_pMaterial->SetFloat(this->m_R, "R");
            a_pMaterial->SetFloat(this->m_G, "G");
            a_pMaterial->SetFloat(this->m_B, "B");
            //Draw Sprite
            this->m_pSprite->Draw(
                a_pCamera, a_pMaterial, UVPosition,
                UVSize, this->m_Position, PuRe_Vector3F(this->m_ShipSize.X, this->m_ShipSize.Y, 0.0f), PuRe_Vector3F(0.0f, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
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
            pos.Y += 110.0f;
            a_pShieldSprite->Draw(
                a_pCamera, a_pMaterial, PuRe_Vector2F(0.0f, 0.0f),
                PuRe_Vector2F(512.0f, 256.0f), pos, PuRe_Vector3F(432.0f, 258.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        }
    }


    // **************************************************************************
    // **************************************************************************
    void CBigUboot::ResetPosition(PuRe_Vector3F a_Position)
    {
        PuRe_Vector3F diffPosition = this->m_Position;
        this->m_Position = a_Position;
        diffPosition = this->m_Position - diffPosition;
        this->m_BoundingBox.m_Position += diffPosition;
    }


    // **************************************************************************
    // **************************************************************************
    void CBigUboot::Hit()
    {
        if (this->m_BlinkTime == 0.0f)
        {
            if (this->m_Shield > 0)
                this->m_Shield--;
            else
            {
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
    void CBigUboot::Spawn(PuRe_Vector3F Position)
    {
        this->m_pLuaReader->SetFunction("OnRespawn");
        this->m_pLuaReader->CallFunction(0, 0);
        //set our position accordingly
        PuRe_Vector3F diffPosition = this->m_Position;
        this->m_Position = Position;
        diffPosition = this->m_Position-diffPosition;
        this->m_BoundingBox.m_Position += diffPosition;

        //set him in use
        this->m_InUse = true;
        //Clear other Variables
        this->m_UseTimer = 0.0f;
        this->m_Lifes = 4;
        this->m_Angle = 0.0f;
        this->m_Shield = 0;
        this->m_LookAngle = 0.0f;
        this->m_Speed = 0.0f;
        this->m_FireRateTime = 0.0f;
        this->m_R = 0.0f;
        this->m_G = 0.0f;
        this->m_B = 0.0f;
        this->m_BlinkTime = 0.0f;
        //reset our positions
        memset(this->m_Positions, 0, sizeof(int32)); //empty the array

        //now go through all players
        for (int32 i = 0; i < 4; i++)
        {
            if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0) //if they are alive and playing
            {
                if(this->m_ppPlayers[i]->m_Ship == 2) //red player is always the first slot
                {
                    this->m_ppPlayers[i]->m_BigPosition = 0;
                    //someone already has 0 , so change him again
                    if (this->m_Positions[0] != 0)
                    {
                        int32 who = this->m_Positions[0] - 1;
                        for (int32 j = 0; j < 4; j++)
                        {
                            if (this->m_Positions[j] == 0)
                                this->m_Positions[j] = this->m_Positions[0];
                        }
                    }
                    //now change this one to the big one
                    this->m_Positions[0] = i + 1;
                }
                else //he is not the red player
                {
                    for (int32 j = 0; j < 4; j++) //go through the array
                    {
                        if (this->m_Positions[j] == 0) //if there is none
                        {
                            //set new and break
                            this->m_Positions[j] = i + 1;
                            this->m_ppPlayers[i]->m_BigPosition = j;
                            break;
                        }
                    }
                } //if ship is 2 or not
            } //if he is playing
        } //for loop

    }


    // **************************************************************************
    // **************************************************************************
    PuRe_Vector3F CBigUboot::GetPosition()
    {
        return this->m_Position;
    }


    // **************************************************************************
    // **************************************************************************
    PuRe_BoundingBox CBigUboot::GetBox()
    {
        return this->m_BoundingBox;
    }


    // **************************************************************************
    // **************************************************************************
    float32 CBigUboot::GetSpeed()
    {
        return this->m_Speed;
    }


    // **************************************************************************
    // **************************************************************************
    float32 CBigUboot::GetLookAngle()
    {
        return this->m_LookAngle;
    }


    // **************************************************************************
    // **************************************************************************
    int32 CBigUboot::GetLifes()
    {
        return this->m_Lifes;
    }
}