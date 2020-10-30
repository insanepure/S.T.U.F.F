#include "include/Enemy.h"

namespace Game
{
    CEnemy::CEnemy(CLuaReader* a_pLuaReader, int32 Type, float32 X, float32 Y, float32 a_Lifes, int32 a_Size) : m_pLuaReader(a_pLuaReader)
    {
        this->m_Type = Type;
        this->m_Position.X = X;
        this->m_Position.Y = Y;
        this->m_pLuaReader->SetFunction("Init");
        //call function
        this->m_pLuaReader->CallFunction(0, 14);
        //return values
        this->m_BoundingBox.m_Size.Y = this->m_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Size.X = this->m_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position.Y = this->m_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position.X = this->m_pLuaReader->PopFloat();
        this->m_BoundingBox.m_Position += this->m_Position;
        this->m_AngleSpin = this->m_pLuaReader->PopFloat();
        this->m_MaxSpeed = this->m_pLuaReader->PopFloat();
        this->m_Width = this->m_pLuaReader->PopFloat();
        this->m_Height = this->m_pLuaReader->PopFloat();
        this->m_Lifes = this->m_pLuaReader->PopInt() + a_Lifes;
        this->m_Points = this->m_pLuaReader->PopInt();
        this->m_ArraySize = this->m_pLuaReader->PopInt();
        this->m_CollideDamage = this->m_pLuaReader->PopInt();
        this->m_DieOnCollide = this->m_pLuaReader->PopBool();
        this->m_DamageRadius = this->m_pLuaReader->PopFloat();
        this->m_pIntArray = new int32[this->m_ArraySize];
        this->m_DeleteHim = false;
        this->m_Angle = 0.0f;
        this->m_LookAngle = 0.0f;
        this->m_Speed = 0.0f;
        this->m_Animation = 0;
        this->m_AnimationTime = 0.0f;
        this->m_AnimationFrame = 0;
        this->m_AnimationSpeed = 20.0f;
        this->m_Position.Z = 2.0f;
        this->m_Size = 1.0f + (float32)a_Size;
        if (this->m_Type == 6)
            this->m_Size = 1.5f;
        if (this->m_Size != 1.0f)
        {
            this->m_BoundingBox.m_Position.Y -= this->m_BoundingBox.m_Size.Y / 2.0f;
            this->m_BoundingBox.m_Position.X -= this->m_BoundingBox.m_Size.X / 2.0f;
            this->m_BoundingBox.m_Size.Y *= this->m_Size;
            this->m_BoundingBox.m_Size.X *= this->m_Size;
            this->m_BoundingBox.m_Position.Y += this->m_BoundingBox.m_Size.Y / 2.0f;
            this->m_BoundingBox.m_Position.X += this->m_BoundingBox.m_Size.X / 2.0f;
        }
        //Clear it
        memset(this->m_pIntArray, 0, this->m_ArraySize*sizeof(int32));
    }
    // **************************************************************************
    // **************************************************************************
    CEnemy::~CEnemy()
    {
        this->m_pLuaReader->SetFunction("OnDie");
        this->m_pLuaReader->CallFunction(0, 0);
    }
    // **************************************************************************
    // **************************************************************************
    void CEnemy::BossAnimation(int32 Frame)
    {
        this->m_LookAngle = 0.0f;
        this->m_Animation = 10;
        this->m_AnimationFrame = Frame;
        this->m_HitTime = 0.0f;
        this->m_Flip = true;
    }
    // **************************************************************************
    // **************************************************************************
    int32 CEnemy::GetPoints()
    {
        return this->m_Points;
    }
    // **************************************************************************
    // **************************************************************************
    float32 CEnemy::GetDamageRadius()
    {
        return this->m_DamageRadius;
    }
    // **************************************************************************
    // **************************************************************************
    bool CEnemy::DieCollide()
    {
        return this->m_DieOnCollide;
    }
    // **************************************************************************
    // **************************************************************************
    bool CEnemy::Update(float32 a_DeltaTime, float32 a_PlayerSpeed, PuRe_Vector3F a_PlayerPosition, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_Resolution)
    {
        //set blink Time
        if (this->m_HitTime > 0.0f)
            this->m_HitTime -= a_DeltaTime;
        else
            this->m_HitTime = 0.0f;
        //Define the center of the Enemy
        PuRe_Vector3F Middle = this->m_BoundingBox.m_Position;
        Middle.X += this->m_BoundingBox.m_Size.X / 2.0f;
        Middle.Y += this->m_BoundingBox.m_Size.Y / 2.0f;
        //set our difference Position so we know how the enemy is moved
        PuRe_Vector3F diffPosition = Middle;

        float32 startSize = this->m_Size;
        //Update Loop function
        this->m_pLuaReader->SetFunction("Update");
        //Push Int Array
        for (int32 i = 0; i < this->m_ArraySize; i++)
            this->m_pLuaReader->Push(this->m_pIntArray[i]);
        // DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y)
        //Push Other Variables
        this->m_pLuaReader->Push(this->m_DamageRadius);
        this->m_pLuaReader->Push(this->m_Size);
        this->m_pLuaReader->Push(a_PlayerSpeed);
        this->m_pLuaReader->Push(a_DeltaTime*60.0f);
        this->m_pLuaReader->Push(this->m_Animation);
        this->m_pLuaReader->Push(this->m_DeleteHim);
        this->m_pLuaReader->Push(Middle.X);
        this->m_pLuaReader->Push(Middle.Y);
        this->m_pLuaReader->Push(this->m_Speed);
        this->m_pLuaReader->Push(this->m_LookAngle);
        this->m_pLuaReader->Push(this->m_Angle);
        this->m_pLuaReader->Push(a_CamPosition.X);
        this->m_pLuaReader->Push(a_CamPosition.Y);
        this->m_pLuaReader->Push(a_Resolution.X);
        this->m_pLuaReader->Push(a_Resolution.Y);
        this->m_pLuaReader->Push(a_PlayerPosition.X);
        this->m_pLuaReader->Push(a_PlayerPosition.Y);

        this->m_pLuaReader->CallFunction(this->m_ArraySize + 17, this->m_ArraySize + 10);
        //DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
        this->m_LookAngle = this->m_pLuaReader->PopFloat();
        this->m_Speed = this->m_pLuaReader->PopFloat();
        Middle.Y = this->m_pLuaReader->PopFloat();
        Middle.X = this->m_pLuaReader->PopFloat();
        this->m_Angle = this->m_pLuaReader->PopFloat();
        this->m_DeleteHim = this->m_pLuaReader->PopBool();
        if (this->m_DeleteHim)
            printf("");
        this->m_Animation = this->m_pLuaReader->PopInt();
        this->m_CollideDamage = this->m_pLuaReader->PopInt();
        this->m_Size = this->m_pLuaReader->PopFloat();
        this->m_DamageRadius = this->m_pLuaReader->PopFloat();
        //return Int Array
        for (int32 i = this->m_ArraySize - 1; i >= 0; i--)
            this->m_pIntArray[i] = this->m_pLuaReader->PopInt();


        diffPosition = Middle - diffPosition;
        diffPosition.Z = 0.0f;
        //change size of the bounding box
        this->m_BoundingBox.m_Position += diffPosition;
        this->m_BoundingBox.m_Size.X /= startSize;
        this->m_BoundingBox.m_Size.Y /= startSize;
        this->m_BoundingBox.m_Size.X *= this->m_Size;
        this->m_BoundingBox.m_Size.Y *= this->m_Size;

        this->m_Position += diffPosition;
        if (Middle.X > a_PlayerPosition.X)
            this->m_Flip = true;
        else
            this->m_Flip = false;

        this->m_AnimationTime += (a_DeltaTime * this->m_AnimationSpeed);
        while (this->m_AnimationTime > 9.0f)
        {
            this->m_AnimationTime = this->m_AnimationTime - 9.0f;
        }
        this->m_AnimationFrame = (int32)this->m_AnimationTime;

        return this->m_DeleteHim;
    }
    // **************************************************************************
    // **************************************************************************
    void CEnemy::Draw(PuRe_Camera* a_pCamera, PuRe_Sprite** a_ppSprite,PuRe_IMaterial* a_pMaterial)
    {
        PuRe_Vector3F Size;
        Size.X = this->m_Width * this->m_Size;
        Size.Y = this->m_Height * this->m_Size;
        Size.Z = 0.0f;
        float32 yRotation = 0.0f;

        PuRe_Vector2F UVSize(this->m_Width, this->m_Height);
        PuRe_Vector2F UVPosition = PuRe_Vector2F(UVSize.X*this->m_AnimationFrame, this->m_Animation*UVSize.Y);
        a_pMaterial->Apply();
        a_pMaterial->SetFloat(this->m_HitTime*2.0f,"Time");
        printf("Fish Pos: %f %f %f\n", this->m_Position.X, this->m_Position.Y, this->m_Position.Z);
        if (this->m_Flip)
            yRotation = 180.0f*0.0174532925f;
        switch (this->m_Type)
        {
        case 0:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 1: 
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 2:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 3:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 4:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 5:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        case 6:
            a_ppSprite[this->m_Type]->Draw(a_pCamera, a_pMaterial, UVPosition, UVSize,
                this->m_Position, Size, PuRe_Vector3F(this->m_LookAngle, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
            break;
        default:
            break;
        }
        //a_ppSprite[0]->Draw(a_pCamera, PuRe_Vector2F(90.0f, 120.0f), PuRe_Vector2F(10.0f, 10.0f),
        //    this->m_BoundingBox.m_Position, this->m_BoundingBox.m_Size, PuRe_Vector3F(yRotation, 0.0f, this->m_LookAngle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
        a_pMaterial->Apply();
        a_pMaterial->SetFloat(0.0f, "Time");
    }


    // **************************************************************************
    // **************************************************************************
    PuRe_BoundingBox CEnemy::GetBox()
    {
        return this->m_BoundingBox;
    }


    // **************************************************************************
    // **************************************************************************
    bool CEnemy::DealDamage(float32 a_Damage)
    {
        CSoundManager::m_pSoundPlayer->PlaySound("14", false, true, CSoundManager::m_SoundVolume);
        this->m_Lifes -= a_Damage;
        this->m_HitTime = 1.0f;
        return this->m_Lifes < 0.0f;
    }


    // **************************************************************************
    // **************************************************************************
    bool CEnemy::CollideDamage()
    {
        return this->m_CollideDamage != 0;
    }


    // **************************************************************************
    // **************************************************************************
    float32 CEnemy::GetSize()
    {
        return this->m_Size;
    }

}