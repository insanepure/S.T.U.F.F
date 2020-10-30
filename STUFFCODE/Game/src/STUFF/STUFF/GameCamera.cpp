#include "include/GameCamera.h"

namespace Game
{
    // **************************************************************************
    // **************************************************************************
    CGameCamera::CGameCamera(const char8* a_pLuaPath)
    {
        this->m_pLuaReader = new CLuaReader(a_pLuaPath);
        this->m_Position = PuRe_Vector3F(0.0f, -380.0f, 0.0f);
        this->m_ToPosition = PuRe_Vector3F(0.0f, -380.0f, 0.0f);

    }


    // **************************************************************************
    // **************************************************************************
    CGameCamera::~CGameCamera()
    {
        SAFE_DELETE(this->m_pLuaReader);
    }


    // **************************************************************************
    // **************************************************************************
    PuRe_Vector3F CGameCamera::GetPosition()
    {
        return this->m_Position;
    }


    // **************************************************************************
    // **************************************************************************
    void CGameCamera::Update(PuRe_Vector3F a_PlayerPosition, PuRe_Vector3F a_AveragePosition, float32 a_Speed, PuRe_Vector2F a_Resolution, float32 a_LevelEnd, float32 a_DeltaTime, PuRe_Camera* a_pCamera)
    {
        //define our variables
        float32 dAngle = 0.0f;

        //Init Function
        this->m_pLuaReader->SetFunction("SetCam");
        //Push Arguments
        this->m_pLuaReader->Push(a_PlayerPosition.X); //Player_X
        this->m_pLuaReader->Push(a_PlayerPosition.Y); //Player_Y
        this->m_pLuaReader->Push(a_Resolution.X); //Screen_Width
        this->m_pLuaReader->Push(a_Resolution.Y); //Screen_Height
        this->m_pLuaReader->Push(this->m_ToPosition.X); //Cam_to_X
        this->m_pLuaReader->Push(this->m_ToPosition.Y); //Cam_to_Y
        this->m_pLuaReader->Push(a_AveragePosition.X); //Cam_D_X
        this->m_pLuaReader->Push(a_AveragePosition.Y); //Cam_D_Y
        this->m_pLuaReader->Push(dAngle); //Cam_D_Angle
        this->m_pLuaReader->Push(a_LevelEnd); //LevelEnd
        //Call Function
        this->m_pLuaReader->CallFunction(10, 2);
        //Return
        this->m_ToPosition.Y = std::floor(this->m_pLuaReader->PopFloat());
        this->m_ToPosition.X = std::floor(this->m_pLuaReader->PopFloat());

        //Init Function
        this->m_pLuaReader->SetFunction("UpdateCam");
        //Push Arguments
        this->m_pLuaReader->Push(this->m_ToPosition.X); //Cam_to_X
        this->m_pLuaReader->Push(this->m_ToPosition.Y); //Cam_to_Y
        this->m_pLuaReader->Push(this->m_Position.X); //Cam_X
        this->m_pLuaReader->Push(this->m_Position.Y); //Cam_Y
        this->m_pLuaReader->Push(a_Speed); //PlayerSpeed
        this->m_pLuaReader->Push(a_DeltaTime*40.0f); //LevelEnd
        //Call Function
        this->m_pLuaReader->CallFunction(6, 2);
        //Return
        PuRe_Vector3F camPos = this->m_Position;

        this->m_Position.Y = this->m_pLuaReader->PopFloat();
        this->m_Position.X = this->m_pLuaReader->PopFloat();

        this->m_Position.X = std::floor(this->m_Position.X);
        this->m_Position.Y = std::floor(this->m_Position.Y);

        camPos = this->m_Position-camPos;
        //Set Camera's Position
        a_pCamera->Move(camPos);



    }

}