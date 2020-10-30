#include "include/Bullet.h"

namespace Game
{
    CBullet::CBullet(PuRe_BoundingBox a_BoundingBox,
        PuRe_Vector3F a_Position,
        int32 a_Image,
        int32 a_Type,
        int32 a_ArraySize,
        int32 a_PlayerNum,
        float32 a_Stay,
        float32 a_Damage,
        float32 a_Speed,
        int32 a_Bounce,
        bool a_HitPlayer,
        bool a_Collide,
        float32 a_Angle,
        float32 a_LookAngle) :m_BoundingBox(a_BoundingBox),
        m_Position(a_Position),
        m_Image(a_Image),
        m_Type(a_Type),
        m_ArraySize(a_ArraySize),
        m_PlayerNum(a_PlayerNum),
        m_Stay(a_Stay),
        m_Damage(a_Damage),
        m_Speed(a_Speed),
        m_Bounce(a_Bounce),
        m_HitPlayer(a_HitPlayer),
        m_Collide(a_Collide),
        m_Angle(a_Angle),
        m_LookAngle(a_LookAngle)
    {
        this->m_Size = 1.0f;
        this->m_dead = false;
        if (this->m_pIntArray == nullptr)
            this->m_pIntArray = new int32[this->m_ArraySize];
        //Clear it
        memset(this->m_pIntArray, 0, this->m_ArraySize*sizeof(int32));
    }
    // **************************************************************************
    // **************************************************************************
    CBullet::~CBullet()
    {

    }
    // **************************************************************************
    // **************************************************************************
    void CBullet::OnDie(CLuaReader* a_pLuaReader)
    {
        a_pLuaReader->SetFunction("OnDie");
        a_pLuaReader->Push(this->m_Position.X);
        a_pLuaReader->Push(this->m_Position.Y);
        a_pLuaReader->Push(this->m_Type);
        a_pLuaReader->CallFunction(3, 0);
    }
    // **************************************************************************
    // **************************************************************************
    float32 CBullet::GetLookAngle()
    {
        return this->m_LookAngle;
    }
    // **************************************************************************
    // **************************************************************************
    bool CBullet::HitPlayer()
    {
        return this->m_HitPlayer;
    }
    // **************************************************************************
    // **************************************************************************
    float32 CBullet::GetSpeed()
    {
        return this->m_Speed;
    }
    // **************************************************************************
    // **************************************************************************
    float32 CBullet::GetSize()
    {
        return this->m_Size;
    }
    // **************************************************************************
    // **************************************************************************
    PuRe_BoundingBox& CBullet::GetBoundingBox()
    {
        return this->m_BoundingBox;
    }
    // **************************************************************************
    // **************************************************************************
    int32 CBullet::GetImage()
    {
        return this->m_Image;
    }
    // **************************************************************************
    // **************************************************************************
    int32 CBullet::GetPlayer()
    {
        return this->m_PlayerNum;
    }
    // **************************************************************************
    // **************************************************************************
    bool CBullet::GetBounce()
    {
        return this->m_Bounce != 0;
    }
    // **************************************************************************
    // **************************************************************************
    float32 CBullet::GetDamage()
    {
        return this->m_Damage;
    }
    // **************************************************************************
    // **************************************************************************
    bool CBullet::DieHit()
    {
        return this->m_Stay <= 0.0f;
    }
    // **************************************************************************
    // **************************************************************************
    bool CBullet::GetCollide()
    {
        return this->m_Collide;
    }
    // **************************************************************************
    // **************************************************************************
    void CBullet::Bounce()
    {
        this->m_Angle -= 90 * 0.0174532925f;
        this->m_LookAngle -= 90 * 0.0174532925f;
        this->m_Bounce--;
        if (this->m_Bounce == 0)
            this->m_Collide = true;
    }
    // **************************************************************************
    // **************************************************************************
    PuRe_Vector3F CBullet::GetPosition()
    {
        return this->m_Position;
    }
    // **************************************************************************
    // **************************************************************************
    void CBullet::PreUpdate(CLuaReader* a_pLuaReader, float32 a_DeltaTime, CPlayer** a_ppPlayers, PuRe_Vector3F a_Aim)
    {
        //Update Loop function
        a_pLuaReader->SetFunction("PreUpdate");
        //Push Int Array
        for (int32 i = 0; i<this->m_ArraySize; i++)
            a_pLuaReader->Push(this->m_pIntArray[i]);
        //Push Other Variables
        a_pLuaReader->Push(this->m_Image);
        a_pLuaReader->Push(this->m_Size);
        a_pLuaReader->Push(a_DeltaTime*60.0f);
        a_pLuaReader->Push(this->m_LookAngle);
        a_pLuaReader->Push(this->m_Angle);
        a_pLuaReader->Push(this->m_Type);
        a_pLuaReader->Push(a_Aim.X);
        a_pLuaReader->Push(a_Aim.Y);
        PuRe_Vector3F playerPos = a_ppPlayers[this->m_PlayerNum]->GetPosition();
        a_pLuaReader->Push(playerPos.X);
        a_pLuaReader->Push(playerPos.Y);
        a_pLuaReader->Push(this->m_Speed);
        //Call Function
        a_pLuaReader->CallFunction(this->m_ArraySize + 11, this->m_ArraySize + 5);
        //Return Values
        this->m_Speed = a_pLuaReader->PopFloat();
        this->m_Angle = a_pLuaReader->PopFloat();
        this->m_LookAngle = a_pLuaReader->PopFloat();
        this->m_Size = a_pLuaReader->PopFloat();
        this->m_Image = a_pLuaReader->PopInt();
        //return Int Array
        for (int32 i = this->m_ArraySize - 1; i >= 0; i--)
            this->m_pIntArray[i] = a_pLuaReader->PopInt();
    }
    // **************************************************************************
    // **************************************************************************
    bool CBullet::Update(CLuaReader* a_pLuaReader, float32 a_DeltaTime, CPlayer** a_ppPlayers,PuRe_Vector3F a_Aim)
    {
        PuRe_Vector3F diffPosition = this->m_Position;
        PuRe_Vector3F bSize = this->m_BoundingBox.m_Size;
        PuRe_Vector3F playerPos = a_ppPlayers[this->m_PlayerNum]->GetPosition();

        bSize.X = bSize.X / this->m_Size;
        bSize.Y = bSize.Y / this->m_Size;

        bool die = false;
        if (this->m_dead&&this->m_Stay > 0.0f)
            this->m_Stay -= a_DeltaTime;
        else if (this->m_dead)
            die = true;
        else
        {
            ////Update Loop function
            a_pLuaReader->SetFunction("Update");
            //Push Int Array
            for (int32 i = 0; i<this->m_ArraySize; i++)
                a_pLuaReader->Push(this->m_pIntArray[i]);
            //Push Other Variables
            a_pLuaReader->Push(this->m_PlayerNum);
            a_pLuaReader->Push(this->m_Type);
            a_pLuaReader->Push(this->m_Position.X);
            a_pLuaReader->Push(this->m_Position.Y);
            a_pLuaReader->Push(this->m_Angle);
            a_pLuaReader->Push(a_Aim.X);
            a_pLuaReader->Push(a_Aim.Y);
            a_pLuaReader->Push(playerPos.X);
            a_pLuaReader->Push(playerPos.Y);
            a_pLuaReader->Push(a_DeltaTime*60.0f);
            //Call Function
            a_pLuaReader->CallFunction(this->m_ArraySize + 10, this->m_ArraySize + 3);
            //Return Values
            this->m_Position.Y = a_pLuaReader->PopFloat();
            this->m_Position.X = a_pLuaReader->PopFloat();
            this->m_dead = a_pLuaReader->PopBool();
            //return Int Array
            for (int32 i = this->m_ArraySize - 1; i >= 0; i--)
                this->m_pIntArray[i] = a_pLuaReader->PopInt();
        }
        diffPosition = this->m_Position - diffPosition;
        diffPosition.Z = 0.0f;

        this->m_BoundingBox.m_Position += diffPosition;

        bSize.X = bSize.X * this->m_Size;
        bSize.Y = bSize.Y * this->m_Size;

        this->m_Position.X -= (bSize.X - this->m_BoundingBox.m_Size.X)/2.0f;
        this->m_Position.Y -= (bSize.Y - this->m_BoundingBox.m_Size.Y)/2.0f;

        this->m_BoundingBox.m_Size = bSize;
        return die;
    }
}