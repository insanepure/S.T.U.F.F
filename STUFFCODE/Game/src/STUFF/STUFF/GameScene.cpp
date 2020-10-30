#include "include/GameScene.h"
#include "include/SpriteManager.h"
namespace Game
{
    CLuaReader* CGameScene::m_pLaserLua;
    CLuaReader* CGameScene::m_pBulletLua;
    CLuaReader** CGameScene::m_ppEnemyLua;
    PuRe_List<CLaser*> CGameScene::m_Lasers;
    PuRe_List<CBullet*> CGameScene::m_Bullets;
    PuRe_List<CEnemy*> CGameScene::m_Enemies;
    PuRe_List<CItem*> CGameScene::m_Items;

    CGameScene::CGameScene(PuRe_Application* a_pApplication, CPlayer** a_ppPlayers)
    {
        this->m_ppPlayers = a_ppPlayers;
        srand((uint32)time(NULL));
        this->m_DisplayUI = true;
    }

    // **************************************************************************
    // **************************************************************************
    int CGameScene::CreateLaser(lua_State* a_pLuaState)
    {
        //CreateLaser(PlayerNum, 104, Player_X, Player_Y, 0, 60, 2000, 1, false, false);
        //get values
        int32 PlayerNum = (int32)lua_tointeger(a_pLuaState, 1);
        int32 Type = (int32)lua_tointeger(a_pLuaState, 2);
        int32 X = (int32)lua_tointeger(a_pLuaState, 3);
        int32 Y = (int32)lua_tointeger(a_pLuaState, 4);
        int32 Speed = (int32)lua_tointeger(a_pLuaState, 5);
        float32 Damage = (float32)lua_tonumber(a_pLuaState, 6)/10;
        int32 Length = (int32)lua_tointeger(a_pLuaState, 7);
        float32 Stay = (float32)lua_tonumber(a_pLuaState, 8);
        bool collide = lua_toboolean(a_pLuaState, 9) != 0;
        bool bounce = lua_toboolean(a_pLuaState, 10) != 0;

        CGameScene::m_pLaserLua->SetFunction("Init");
        CGameScene::m_pLaserLua->Push(Type);
        CGameScene::m_pLaserLua->CallFunction(1, 21);

        // Start Image and Values
        float32 H_E = CGameScene::m_pLaserLua->PopFloat();
        float32 W_E = CGameScene::m_pLaserLua->PopFloat();
        float32 Y_E = CGameScene::m_pLaserLua->PopFloat();
        float32 X_E = CGameScene::m_pLaserLua->PopFloat();
        int32 Image_E = CGameScene::m_pLaserLua->PopInt();
        //First part of the Middle and Values
        float32 H_ML = CGameScene::m_pLaserLua->PopFloat();
        float32 W_ML = CGameScene::m_pLaserLua->PopFloat();
        float32 Y_ML = CGameScene::m_pLaserLua->PopFloat();
        float32 X_ML = CGameScene::m_pLaserLua->PopFloat();
        int32 Image_ML = CGameScene::m_pLaserLua->PopInt();
        //Looping Part and Values
        float32 H_MS = CGameScene::m_pLaserLua->PopFloat();
        float32 W_MS = CGameScene::m_pLaserLua->PopFloat();
        float32 Y_MS = CGameScene::m_pLaserLua->PopFloat();
        float32 X_MS = CGameScene::m_pLaserLua->PopFloat();
        int32 Image_MS = CGameScene::m_pLaserLua->PopInt();
        //EndPart and Values
        float32 H_B = CGameScene::m_pLaserLua->PopFloat();
        float32 W_B = CGameScene::m_pLaserLua->PopFloat();
        float32 Y_B = CGameScene::m_pLaserLua->PopFloat();
        float32 X_B = CGameScene::m_pLaserLua->PopFloat();
        int32 Image_B = CGameScene::m_pLaserLua->PopInt();

        bool hitPlayer = CGameScene::m_pLaserLua->PopBool();

        //set Bounding Box
        PuRe_BoundingBox box;
        box.m_Position.X = (float32)X;
        box.m_Position.Y = (float32)Y + (H_ML / 4.0f);
        box.m_Size.X = Length*W_ML;
        box.m_Size.Y = H_ML/2.0f;
        CLaser* laser = new CLaser(
        box, 
        PuRe_Vector3F((float32)X,(float32)Y,0.0f),
        Image_B,
        Image_MS,
        Image_ML,
        Image_E,
        W_B,
        W_MS,
        W_ML,
        W_E,
        PlayerNum,
        Stay,
        Damage,
        hitPlayer,
        Length);
        CGameScene::m_Lasers.push_back(laser);
        lua_pop(a_pLuaState, 10);
        return 0;
    }

    // **************************************************************************
    // **************************************************************************
    int CGameScene::CreateBullet(lua_State* a_pLuaState)
    {
        //get values
        int32 PlayerNum = (int32)lua_tointeger(a_pLuaState, 1);
        int32 Type = (int32)lua_tointeger(a_pLuaState, 2);
        int32 X = (int32)lua_tointeger(a_pLuaState, 3);
        int32 Y = (int32)lua_tointeger(a_pLuaState, 4);
        float32 Speed = (float32)lua_tonumber(a_pLuaState, 5);
        float32 Angle = (float32)lua_tonumber(a_pLuaState, 6) * -1;

        CGameScene::m_pBulletLua->SetFunction("Init");
        CGameScene::m_pBulletLua->Push(Type);
        CGameScene::m_pBulletLua->Push(X);
        CGameScene::m_pBulletLua->Push(Y);
        CGameScene::m_pBulletLua->Push(Angle);
        CGameScene::m_pBulletLua->Push(Speed);
        CGameScene::m_pBulletLua->CallFunction(5, 14);
        bool hitplayer = CGameScene::m_pBulletLua->PopBool();
        bool collide = CGameScene::m_pBulletLua->PopBool();
        int32 bounce = CGameScene::m_pBulletLua->PopInt();
        float32 Y_Abstand = CGameScene::m_pBulletLua->PopFloat();
        float32 X_Abstand = CGameScene::m_pBulletLua->PopFloat();
        float32 Height = CGameScene::m_pBulletLua->PopFloat();
        float32 Width = CGameScene::m_pBulletLua->PopFloat();
        int32 BHeight = CGameScene::m_pBulletLua->PopInt();
        int32 BWidth = CGameScene::m_pBulletLua->PopInt();
        float32 Damage = CGameScene::m_pBulletLua->PopFloat()/10.0f;
        int32 Image = CGameScene::m_pBulletLua->PopInt();
        float32 speed = CGameScene::m_pBulletLua->PopFloat();
        float32 stay = CGameScene::m_pBulletLua->PopFloat();
        int32 arraySize = CGameScene::m_pBulletLua->PopInt();


        PuRe_BoundingBox box(PuRe_Vector3F(X + X_Abstand, Y + Y_Abstand, 0.0f), PuRe_Vector3F(Width, Height, 0.0f));

        CBullet* bullet = new CBullet(box, PuRe_Vector3F((float32)X, (float32)Y, 2.0f), Image, Type, arraySize, PlayerNum, stay, Damage, speed, bounce, hitplayer, collide, Angle, Angle);
        CGameScene::m_Bullets.push_back(bullet);
        //remove elements from stack
        lua_pop(a_pLuaState, 6);
        return 0;
    }

    // **************************************************************************
    // **************************************************************************
    int CGameScene::Spawn(lua_State* a_pLuaState)
    {
        //Spawn(5, Cam_X + Screen_W + 200, Cam_Y + Screen_H / 2, 1500, 3);
        int32 Type = (int32)lua_tointeger(a_pLuaState, 1);
        float32 X = (float32)lua_tonumber(a_pLuaState, 2);
        float32 Y = (float32)lua_tonumber(a_pLuaState, 3);
        float32 Lifes = (float32)lua_tonumber(a_pLuaState, 4);
        int32 Size = (int32)lua_tointeger(a_pLuaState, 5);
        CEnemy* enemy = NULL;
        bool boss = Size != 0;
        switch (Type)
        {
        case 0: //Echse
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[0], Type, X, Y,Lifes,Size);
            break;
        case 1: //Seeigel
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[1], Type, X, Y, Lifes, Size);
            break;
        case 2: //Raketen
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[2], Type, X, Y, Lifes, Size);
            break;
        case 3: //Stachel
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[3], Type, X, Y, Lifes, Size);
            break;
        case 4: //Nashorn
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[4], Type, X, Y, Lifes, Size);
            break;
        case 5: //fetze
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[5], Type, X, Y, Lifes, Size);
            break;
        case 6: //Endboss
            enemy = new CEnemy(CGameScene::m_ppEnemyLua[6], Type, X, Y, Lifes, Size);
            boss = true;
            break;
        default:
            break;
        }
        if (boss)
        {
            CSoundManager::StopMainSound();
            CSoundManager::PlayMainSound("boss", true, true, CSoundManager::m_MusicVolume*0.5f);
        }
        CGameScene::m_Enemies.push_back(enemy);
        lua_pop(a_pLuaState, 5);
        return 0;
    }

    // **************************************************************************
    // **************************************************************************
    int CGameScene::SpawnItem(lua_State* a_pLuaState)
    {
        //SpawnItem(0, Block_X, Block_Y);
        int32 Type = (int32)lua_tointeger(a_pLuaState, 1);
        float32 X = (float32)lua_tonumber(a_pLuaState, 2);
        float32 Y = (float32)lua_tonumber(a_pLuaState, 3);
        CItem* item = new CItem(Type,PuRe_Vector2F(X,Y));
        CGameScene::m_Items.push_back(item);
        lua_pop(a_pLuaState, 3);
        return 0;
    }

    // **************************************************************************
    // **************************************************************************
    void CGameScene::Initialize(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_GraphicsDescription gDesc = a_pGraphics->GetDescription();
        PuRe_Vector2F Resolution = PuRe_Vector2F((float32)gDesc.ResolutionWidth, (float32)gDesc.ResolutionHeight);
        //Create Materials
        this->m_pMaterial = a_pGraphics->LoadMaterial("data/effects/default/default");
        this->m_pFontMaterial = a_pGraphics->LoadMaterial("data/effects/font/default");
        this->m_pBulletMaterial = a_pGraphics->LoadMaterial("data/effects/bullets/default");
        //Create Camera
        this->m_pCamera = new PuRe_Camera(Resolution, PuRe_Camera_Orthogonal);
        this->m_pGameCamera = new CGameCamera("data/lua/cam.lua");
        //Init Highscore
        this->m_pHighscore = new CHighscore("high.score");
        //Set Time
        this->m_Time = 0.0f;
        //Create Sprites
        this->m_pPlayerSprite = CSpriteManager::GetSprite("Players");
        this->m_pItemSprite = CSpriteManager::GetSprite("Items");
        this->m_pShieldSprite = CSpriteManager::GetSprite("Shields");
        this->m_pBulletSprite = new CSpriteReader(this->m_pBulletMaterial, CSpriteManager::GetSprite("Bullets"), "data/textures/shots.txt");
        this->m_pExplosionSprite = new CSpriteReader(this->m_pFontMaterial, CSpriteManager::GetSprite("Explosions"), "data/textures/explosion.txt");
        //Create Lua Readers
        this->m_pLaserLua = new CLuaReader("data/lua/laser.lua");
        this->m_pPlayerLua = new CLuaReader("data/lua/player.lua");
        this->m_pPlayerLua->RegisterFunction("CreateBullet", this->CreateBullet);
        this->m_pPlayerLua->RegisterFunction("PlaySound", CSoundManager::PlaySound);
        this->m_pBulletLua = new CLuaReader("data/lua/bullet.lua");
        this->m_pBulletLua->RegisterFunction("CreateBullet", this->CreateBullet);
        this->m_pBulletLua->RegisterFunction("PlaySound", CSoundManager::PlaySound);
        this->m_pSpawnLua = new CLuaReader("data/lua/spawn.lua");
        this->m_pSpawnLua->RegisterFunction("GetY", this->m_pMap->GetY); //Get the Y Position at a given X Position where the ground is
        this->m_pSpawnLua->RegisterFunction("Spawn", this->Spawn); //spawn a fish
        this->m_pSpawnLua->RegisterFunction("SpawnItem", this->SpawnItem); // spawn an item
        this->m_ppEnemyLua = new CLuaReader*[7];
        this->m_ppEnemyLua[0] = new CLuaReader("data/lua/enemies/echse.lua");
        this->m_ppEnemyLua[1] = new CLuaReader("data/lua/enemies/seeigel.lua");
        this->m_ppEnemyLua[2] = new CLuaReader("data/lua/enemies/raketen.lua");
        this->m_ppEnemyLua[3] = new CLuaReader("data/lua/enemies/stachel.lua");
        this->m_ppEnemyLua[4] = new CLuaReader("data/lua/enemies/ramm.lua");
        this->m_ppEnemyLua[5] = new CLuaReader("data/lua/enemies/fetze.lua");
        this->m_ppEnemyLua[6] = new CLuaReader("data/lua/enemies/endboss.lua");
        for (int32 i = 0; i < 7; i++)
        {
            this->m_ppEnemyLua[i]->RegisterFunction("CreateBullet", this->CreateBullet);
            this->m_ppEnemyLua[i]->RegisterFunction("PlaySound", CSoundManager::PlaySound);
        }

        this->m_ppEnemySprite = new PuRe_Sprite*[7];
        this->m_ppEnemySprite[0] = new PuRe_Sprite(a_pGraphics,  "data/textures/echsenfisch.dds");
        this->m_ppEnemySprite[1] = new PuRe_Sprite(a_pGraphics,  "data/textures/seeigel.dds");
        this->m_ppEnemySprite[2] = new PuRe_Sprite(a_pGraphics,  "data/textures/maskenfisch_gelb.dds");
        this->m_ppEnemySprite[3] = new PuRe_Sprite(a_pGraphics,  "data/textures/stachelfisch.dds");
        this->m_ppEnemySprite[4] = new PuRe_Sprite(a_pGraphics,  "data/textures/rammfisch.dds");
        this->m_ppEnemySprite[5] = new PuRe_Sprite(a_pGraphics,  "data/textures/fetzenfisch.dds");
        this->m_ppEnemySprite[6] = new PuRe_Sprite(a_pGraphics,  "data/textures/boss.dds");
        //Create Bubble Emitter
        this->m_pBubbleEmitter = new CBubbleEmitter(CSpriteManager::GetSprite("Bubbles"));
        //Create Map
        this->m_pMap = new CMap("data/lua/map.lua", this->m_pFontMaterial, a_pGraphics);
        //Initialize Players
        for (int32 i = 0; i < 4; i++)
        {
            if (this->m_ppPlayers[i]->m_IsPlaying)
            {
                this->m_ppPlayers[i]->Init(this->m_pPlayerLua, PuRe_Vector3F(0.0f, 300.0f + (i*100.0f), 2.0f));
            }
        }
        this->m_Points = 0;
        //create hud
        this->m_pHud = new CHUD(Resolution,a_pGraphics,this->m_pFontMaterial,this->m_pBulletMaterial);
        //create big one
        CLuaReader* bigUbootReader = new CLuaReader("data/lua/bigone.lua"); //destroyed inside of bigUboot
        PuRe_Sprite* bigUbootSprite = new PuRe_Sprite(a_pGraphics, "data/textures/biguboot.dds"); //destroyed inside of bigUboot
        bigUbootReader->RegisterFunction("CreateBullet", this->CreateBullet);
        bigUbootReader->RegisterFunction("PlaySound", CSoundManager::PlaySound);
        bigUbootReader->RegisterFunction("CreateLaser", this->CreateLaser);
        this->m_pBigUboot = new CBigUboot(bigUbootReader, this->m_ppPlayers, bigUbootSprite);
        //set other variables
        this->m_GameEnd = false;
        this->m_GameEndTime = 0.0f;
        this->m_GameEndLeft = true;
        this->m_GamePaused = false;
        this->m_PauseSwitch = false;
        this->m_PauseWhere = 0;
        this->m_Hearts = 0;
        this->m_Energy = 0.0f;
        this->m_ToEnergy = 0.0f;
        this->m_BossKilled = false;
        this->m_BossTimer = 0.0f;
        this->m_Combining = false;
        this->m_Deaths = 0;
    }

    // **************************************************************************
    // **************************************************************************
    int CGameScene::Update(PuRe_IGraphics* a_pGraphics, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer)
    {

        if (a_pInput->KeyPressed(PuReSpace::IInput::F3))
        {
            this->m_DisplayUI = !this->m_DisplayUI;
        }

        float32 toEnergy = this->m_ToEnergy;
        float32 Energy = this->m_Energy;
        float32 Seconds = a_pTimer->GetDeltaTime();
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        PuRe_Vector3F CamPos = this->m_pGameCamera->GetPosition();
        this->m_Time += Seconds;


        if (this->m_Combining)
        {
            float32 maxDistance = 50.0f;
            bool combine = true; //if they can combine or no
            PuRe_Vector2F middlePoint = PuRe_Vector2F(0.0f,0.0f);
            int32 active = 0;
            //calculate a middle Point
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                {
                    //calculate the center of the player
                    PuRe_BoundingBox box = this->m_ppPlayers[i]->GetBox();
                    PuRe_Vector2F center;
                    center.X = box.m_Position.X + box.m_Size.X / 2.0f;
                    center.Y = box.m_Position.Y + box.m_Size.Y / 2.0f;
                    middlePoint += center;
                    active++;
                }
            }
            middlePoint.X /= active;
            middlePoint.Y /= active;
            //check if distance to Middle point is smaller than maxDistance
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                {
                    //calculate the center of the player
                    PuRe_BoundingBox box = this->m_ppPlayers[i]->GetBox();
                    PuRe_Vector2F center;
                    center.X = box.m_Position.X + box.m_Size.X / 2.0f;
                    center.Y = box.m_Position.Y + box.m_Size.Y / 2.0f;
                    //calculate the Position we move to
                    PuRe_Vector2F movePosition = middlePoint - center;
                    movePosition.Normalize();
                    movePosition.X *= 60.0f*Seconds;
                    movePosition.Y *= 60.0f*Seconds;
                    //add our Position we move to the actual Position
                    this->m_ppPlayers[i]->Move(PuRe_Vector3F(movePosition.X,movePosition.Y,0.0f));
                    center += movePosition;
                    
                    //if distance to middlepoint is greater than our maxDistance, it won't work
                    if((middlePoint - center).Length() > maxDistance)
                        combine = false;
                }
            } //for loop
            if (combine)
            {
                //combine is possible
                this->m_pBigUboot->Spawn(PuRe_Vector3F(middlePoint.X, middlePoint.Y, 0.0f));
                CSoundManager::m_pSoundPlayer->PlaySound("assemble",false,true,CSoundManager::m_SoundVolume);
                this->m_Combining = false;

            }
        }
        else if (this->m_BossKilled)
        {

            //what happens at the start
            if (this->m_BossTimer == 0)
            {
                this->m_BossTimer += Seconds; //increase timer
                //Kill all other enemies at the start
                for (uint32 j = 0; j < this->m_Enemies.size(); j++)
                {
                    CEnemy* enemy = this->m_Enemies[j];
                    bool dead = false;
                    if (enemy != NULL)
                    {
                        if (enemy->m_Type != 6)
                        {
                            dead = true;
                            float32 size = enemy->GetSize();
                            PuRe_BoundingBox enemyBox = enemy->GetBox();
                            //do explosion
                            PuRe_Vector3F explosionPosition = enemyBox.m_Position;
                            explosionPosition.X -= 32.0f*size;
                            explosionPosition.Y -= 32.0f*size;
                            explosionPosition.Z = 2.0f;
                            CExplosion* explosion = new CExplosion(20.0f, explosionPosition, size);
                            this->m_Explosions.push_back(explosion);
                        }
                    }
                    else
                        dead = true;
                    if (dead)
                    {
                        if (enemy->GetSize() > 1.0f)
                        {
                            if (enemy->m_Type != 3)
                            {
                                CSoundManager::StopMainSound();
                                CSoundManager::PlayMainSound("level", true, true, CSoundManager::m_MusicVolume*0.5f);
                            }
                        }
                        SAFE_DELETE(enemy);
                        if (CGameScene::m_Enemies.begin() + j < CGameScene::m_Enemies.end())
                            CGameScene::m_Enemies.erase(CGameScene::m_Enemies.begin() + j);
                        j--;
                    }

                }
            }
            else
            {
                this->m_BossTimer += Seconds; //increase timer
                PuRe_Vector3F bossPos = this->m_Enemies[0]->GetBox().m_Position;
                PuRe_Vector3F explosionPosition = bossPos;
                int32 bossTime = (int32)(this->m_BossTimer*10.0f) % 9;
                if ((int32)this->m_BossTimer < 3)
                {
                    printf("Time: %i\n", bossTime);
                    if (bossTime == 0)
                    {
                        explosionPosition.Y += 200.0f + std::rand() % 50 - 50;
                        explosionPosition.X -= 200.0f + std::rand() % 50 - 50;
                        CExplosion* explosion = new CExplosion(20.0f, explosionPosition, 0.5f);
                        this->m_Explosions.push_back(explosion);
                    }
                }
                else if ((int32)this->m_BossTimer < 5)
                {
                    printf("Time: %i\n", bossTime);
                    if (bossTime == 0)
                    {
                        explosionPosition.Y += (std::rand() % 100) - 50;
                        explosionPosition.X += 400.0f + (std::rand() % 100) - 100;
                        CExplosion* explosion = new CExplosion(20.0f, explosionPosition, 0.5f);
                        this->m_Explosions.push_back(explosion);
                    }
                }
                else if ((int32)this->m_BossTimer < 9)
                {
                    printf("Time: %i\n", bossTime);
                    if (bossTime == 0)
                    {
                        explosionPosition.Y += (std::rand() % 100) - 50;
                        explosionPosition.X += 100.0f + (std::rand() % 300) - 300;
                        CExplosion* explosion = new CExplosion(20.0f, explosionPosition, 0.5f);
                        this->m_Explosions.push_back(explosion);
                    }
                }
                else if ((int32)this->m_BossTimer < 13)
                {
                    explosionPosition.Y += 500.0f + (std::rand() % 750) - 750;
                    explosionPosition.X += 600.0f + (std::rand() % 750) - 750;
                    CExplosion* explosion = new CExplosion(20.0f, explosionPosition, 0.5f);
                    this->m_Explosions.push_back(explosion);
                }
                else if ((int32)this->m_BossTimer < 30)
                {
                    //Set first Explosion
                    explosionPosition.Y += 500.0f + (std::rand() % 750) - 750;
                    explosionPosition.X += 600.0f + (std::rand() % 750) - 750;
                    CExplosion* explosion = new CExplosion(20.0f, explosionPosition, 0.5f);
                    this->m_Explosions.push_back(explosion);
                    //Size depending on the Time
                    float32 size = 0.5f + this->m_BossTimer - 13.0f;
                    //set next explosion
                    int32 yrand = std::rand() % gdesc.ResolutionHeight - (int32)(256*size);
                    int32 xrand = std::rand() % gdesc.ResolutionWidth - (int32)(256 * size);
                    explosionPosition.Y = (float32)yrand;
                    explosionPosition.X = (float32)xrand;
                    explosionPosition.Y += CamPos.Y;
                    explosionPosition.X += CamPos.X;
                    //spawn it
                    explosion = new CExplosion(20.0f, explosionPosition, size);
                    this->m_Explosions.push_back(explosion);
                }
                else
                {
                    int32 alive = 0;
                    int32 death = 0;
                    for (int32 i = 0; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying)
                        {
                            if (this->m_ppPlayers[i]->GetLifes() == 0)
                                death++;
                            else
                                alive++;
                        }
                    }
                    this->m_pHighscore->SaveScore(this->m_Points,true,alive,death,this->m_Deaths);
                    return 3;
                }
            }
            //update player
            bool bomb = false;
            bool energy = false;
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                    this->m_ppPlayers[i]->Update(this->m_pPlayerLua, Seconds, a_pInput, CamPos.X, bomb, energy);
            }
            //update shots
            bool dead = false;
            for (uint32 i = 0; i < CGameScene::m_Bullets.size(); i++)
            {
                CBullet* bullet = CGameScene::m_Bullets[i];
                float32 bulletSpeed = bullet->GetSpeed();
                PuRe_Vector3F bulletPos = bullet->GetPosition();
                if (bullet->GetImage() == 29)
                {
                    int32 chance = std::rand() % 100;
                    if (chance >(99 - bulletSpeed * 10))
                        this->m_pBubbleEmitter->Emit(bulletPos, bullet->GetLookAngle(), bulletSpeed, 1, 1, 0.2f);
                }
                PuRe_BoundingBox box = bullet->GetBoundingBox();
                bullet->PreUpdate(this->m_pBulletLua, Seconds, this->m_ppPlayers, PuRe_Vector3F(99999.0f,0.0f,0.0f));
                for (int32 j = 0; j<bulletSpeed; j++)
                {
                    dead = bullet->Update(this->m_pBulletLua, Seconds, this->m_ppPlayers, PuRe_Vector3F(99999.0f, 0.0f, 0.0f));
                    //check boundaries
                    if (bulletPos.X + box.m_Size.X < CamPos.X || bulletPos.Y + box.m_Size.Y < CamPos.Y || bulletPos.X > CamPos.X + (float32)gdesc.ResolutionWidth || bulletPos.Y > CamPos.Y + (float32)gdesc.ResolutionHeight)
                        dead = true;
                    if (dead)
                        break;
                }
                if (dead)
                {
                    //Activate
                    bullet->OnDie(this->m_pBulletLua);
                    SAFE_DELETE(bullet);
                    if (CGameScene::m_Bullets.begin() + i < CGameScene::m_Bullets.end())
                        CGameScene::m_Bullets.erase(CGameScene::m_Bullets.begin() + i);
                    i--;

                }
            }

            //Update Bubbles
            this->m_pBubbleEmitter->Update(Seconds);
            /// Update Speed and Position
            float32 playerSpeed = 0.0f;
            PuRe_Vector3F playerPosition;
            bool alive = false;
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                {
                    alive = true;
                    PuRe_BoundingBox pos = this->m_ppPlayers[i]->GetBox();
                    if (pos.m_Position.X + pos.m_Size.X / 2.0f > playerPosition.X)
                    {
                        playerSpeed = this->m_ppPlayers[i]->GetSpeed();
                        playerPosition = pos.m_Position;
                        playerPosition.X += pos.m_Size.X / 2.0f;
                        playerPosition.Y += pos.m_Size.Y / 2.0f;
                    }
                }
            }
            if ((int32)this->m_BossTimer < 9)
            {
                this->m_Enemies[0]->BossAnimation((int32)this->m_BossTimer);
            }
            //Update Explosions
            for (uint32 i = 0; i < this->m_Explosions.size(); i++)
            {
                bool dead = this->m_Explosions[i]->Update(Seconds);
                if (dead)
                {
                    SAFE_DELETE(this->m_Explosions[i]);
                    if (this->m_Explosions.begin() + i < this->m_Explosions.end())
                        this->m_Explosions.erase(this->m_Explosions.begin() + i);
                    i--;
                }
            }
        }
        else if (this->m_GameEnd)
        {
            this->m_GameEndTime += Seconds;
            bool startPressed = false;
            for (int32 i = 0; i < 4; i++)
            {
                if (a_pInput->GamepadPressed(PuReSpace::Pad_Start, i) || a_pInput->GamepadPressed(PuReSpace::Pad_A, i))
                    startPressed = true;
                if (a_pInput->GetGamepadLeftThumb(i).X > 0.75f)
                    this->m_GameEndLeft = false;
                else  if (a_pInput->GetGamepadLeftThumb(i).X < -0.75f)
                    this->m_GameEndLeft = true;
            }
            if (this->m_GameEndLeft&&startPressed)
                return 2;
            else if (!this->m_GameEndLeft&&startPressed)
                return 0;
        }
        else if (this->m_GamePaused)
        {
            bool switchable = true;
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GamepadPressed(PuReSpace::Pad_Start, i))
                    this->m_GamePaused = false;
                if (this->m_PauseWhere == 3)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GamepadPressed(PuReSpace::Pad_B, i))
                        this->m_PauseWhere = 1;
                }
                else
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GamepadPressed(PuReSpace::Pad_A, i))
                    {
                        switch (this->m_PauseWhere)
                        {
                        case 0:
                            this->m_GamePaused = false;
                            break;
                        case 1:
                            this->m_PauseWhere = 3;
                            break;
                        case 2:
                            return 0;
                            break;
                        }
                    }
                    else if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GetGamepadLeftThumb(i).Y > 0.9f&&this->m_PauseSwitch)
                    {
                        this->m_PauseWhere--;
                        if (this->m_PauseWhere < 0)
                            this->m_PauseWhere = 2;
                        this->m_PauseSwitch = false;
                    }
                    else if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GetGamepadLeftThumb(i).Y < -0.9f&&this->m_PauseSwitch)
                    {
                        this->m_PauseWhere++;
                        if (this->m_PauseWhere > 2)
                            this->m_PauseWhere = 0;
                        this->m_PauseSwitch = false;
                    }
                    if (this->m_ppPlayers[i]->m_IsPlaying&&!this->m_PauseSwitch)
                    {
                        if (a_pInput->GetGamepadLeftThumb(i).Y < -0.2f || a_pInput->GetGamepadLeftThumb(i).Y > 0.2f)
                            switchable = false;
                    }
                }
            }
            if (switchable)
                this->m_PauseSwitch = true;
        }
        else
        {
            if (this->m_Energy != this->m_ToEnergy)
            {
                this->m_Energy += Seconds*5.0f;
                if (this->m_Energy > this->m_ToEnergy)
                    this->m_Energy = this->m_ToEnergy;
            }
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying&&a_pInput->GamepadPressed(PuReSpace::Pad_Start, i))
                    this->m_GamePaused = true;
            }
            //spawn enemies
            this->m_pSpawnLua->SetFunction("EnemySpawn");
            this->m_pSpawnLua->Push(this->m_Points);
            this->m_pSpawnLua->Push(CamPos.X);
            this->m_pSpawnLua->Push(CamPos.Y);
            this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
            this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
            this->m_pSpawnLua->Push(Seconds);
            this->m_pSpawnLua->CallFunction(6,0);
        
            //Update Camera
            PuRe_Vector3F pPosition = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
            PuRe_Vector3F dPosition = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
            float32 pSpeed = 0.0f;
            if (this->m_pBigUboot->m_InUse)
            {
                pSpeed = this->m_pBigUboot->GetSpeed();
                dPosition = this->m_pBigUboot->GetPosition();
                pPosition = dPosition;
            }
            else
            {
                int32 playerPlaying = 0;
                //define our average Position, which is between all players
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                    {
                        PuRe_Vector3F playerPosition = this->m_ppPlayers[i]->GetPosition();
                        playerPlaying++;
                        dPosition += playerPosition;
                        if (playerPosition.X > pPosition.X)
                        {
                            pPosition = playerPosition;
                            pSpeed = this->m_ppPlayers[i]->GetSpeed();
                        }
                    }
                }
                dPosition.X /= playerPlaying;
                dPosition.Y /= playerPlaying;
            }

            //Update BigUboot
            if (this->m_pBigUboot->m_InUse)
            {
                bool energy = false;
                int32 addEnergy = 0;
                this->m_pBigUboot->Update(Seconds, a_pInput, CamPos.X, addEnergy);
                //update energy
                if (addEnergy != 0)
                {
                    if (this->m_ToEnergy < 100.0f)
                    {
                        this->m_ToEnergy += (float32)addEnergy;
                        if (this->m_ToEnergy > 100.0f)
                            this->m_ToEnergy = 100.0f;
                        this->m_Energy = m_ToEnergy;
                    }
                }
                //check for collision
                bool hitMap = false;
                PuRe_BoundingBox pbox = this->m_pBigUboot->GetBox();
                if (this->m_pMap->Intersect(pbox) || this->m_pMap->HitDestroyable(pbox))
                {
                    this->m_pBigUboot->Hit();
                    PuRe_BoundingBox bigbox = this->m_pBigUboot->GetBox();
                    PuRe_Vector3F bigpos = bigbox.m_Position;
                    bigpos.X += bigbox.m_Size.X / 2.0f;
                    bigpos.Y += bigbox.m_Size.Y / 2.0f;
                    this->m_pBigUboot->ResetPosition(this->m_pMap->GetMiddle(bigpos));
                }
            }
            else
            {
                //update Players
                bool combine = true; //if all players are pressing right shoulder, do combine
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                    {
                        bool bomb = false;
                        bool energy = false;
                        //if one does not press right shoulder, do not combine
                        if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0 &&!a_pInput->GamepadIsPressed(PuReSpace::Right_Shoulder, i))
                            combine = false;
                        this->m_ppPlayers[i]->Update(this->m_pPlayerLua, Seconds, a_pInput, CamPos.X,bomb,energy);
                        if (energy)
                        {
                            if (this->m_ToEnergy < 100.0f)
                            {
                                this->m_ToEnergy += 20.0f;
                                if (this->m_ToEnergy > 100.0f)
                                    this->m_ToEnergy = 100.0f;
                            }
                        }
                        //bomb has been planted, KILL ALL
                        if (bomb)
                        {
                            for (uint32 j = 0; j < this->m_Enemies.size(); j++)
                            {
                                CEnemy* enemy = this->m_Enemies[j];
                                bool dead = false;
                                if (enemy != NULL)
                                {
                                    dead = enemy->DealDamage(100.0f);
                                    float32 size = enemy->GetSize();
                                    PuRe_BoundingBox enemyBox = enemy->GetBox();
                                    if (dead)
                                    {
                                        this->m_ppPlayers[i]->m_Points += enemy->GetPoints();
                                        this->m_Points += enemy->GetPoints();
                                        if (this->m_ToEnergy < 100.0f)
                                        {
                                            this->m_ToEnergy += enemy->GetPoints() / 100.0f;
                                            if (this->m_ToEnergy > 100.0f)
                                                this->m_ToEnergy = 100.0f;
                                        }
                                        this->m_pSpawnLua->SetFunction("OnDie");
                                        this->m_pSpawnLua->Push(enemyBox.m_Position.X);
                                        this->m_pSpawnLua->Push(enemyBox.m_Position.Y);
                                        this->m_pSpawnLua->Push(this->m_Points);
                                        this->m_pSpawnLua->Push(CamPos.X);
                                        this->m_pSpawnLua->Push(CamPos.Y);
                                        this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
                                        this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
                                        this->m_pSpawnLua->Push(Seconds);
                                        this->m_pSpawnLua->CallFunction(8, 0);
                                    }
                                    //do explosion
                                    PuRe_Vector3F explosionPosition = enemyBox.m_Position;
                                    explosionPosition.X -= 32.0f*size;
                                    explosionPosition.Y -= 32.0f*size;
                                    explosionPosition.Z = 2.0f;
                                    CExplosion* explosion = new CExplosion(20.0f, explosionPosition, size);
                                    this->m_Explosions.push_back(explosion);
                                }
                                else
                                    dead = true;
                                if (dead)
                                {
                                    if (enemy->m_Type == 6)
                                        this->m_BossKilled = true;
                                    else
                                    {
                                        if (enemy->GetSize() > 1.0f)
                                        {
                                            if (enemy->m_Type != 3)
                                            {
                                                CSoundManager::StopMainSound();
                                                CSoundManager::PlayMainSound("level", true, true, CSoundManager::m_MusicVolume*0.5f);
                                            }
                                        }
                                        SAFE_DELETE(enemy);
                                        if (CGameScene::m_Enemies.begin() + j < CGameScene::m_Enemies.end())
                                            CGameScene::m_Enemies.erase(CGameScene::m_Enemies.begin() + j);
                                        j--;
                                    }
                                }

                            }
                        }
                        bool hitMap = false;
                        PuRe_BoundingBox pbox = this->m_ppPlayers[i]->GetBox();
                        if (this->m_pMap->Intersect(pbox) || this->m_pMap->HitDestroyable(pbox))
                        {
                            this->m_ppPlayers[i]->Hit();
                            this->m_ppPlayers[i]->ResetPosition(this->m_pMap->GetMiddle(this->m_ppPlayers[i]->GetPosition()));
                            if (this->m_ppPlayers[i]->GetLifes() == 0)
                                this->m_Deaths++;
                        }
                        else
                        {
                            //Spawn Bubbles
                            PuRe_Vector3F playerPosition = this->m_ppPlayers[i]->GetPosition();
                            float32 playerSpeed = this->m_ppPlayers[i]->GetSpeed() + 2.0f;
                            float32 playerAngle = this->m_ppPlayers[i]->GetLookAngle(); // in Radians
                            playerPosition.X += 64.0f;
                            playerPosition.Y += 64.0f;
                            playerAngle -= 180 * 0.0174532925f; //rotate it around
                            int32 chance = std::rand() % 100;
                            if (chance > (99 - playerSpeed*10))
                                this->m_pBubbleEmitter->Emit(playerPosition,playerAngle,playerSpeed,1,1,1.0f);
                        }
                    }
                }
                if (combine&&this->m_Energy == 100.0f)
                {
                    //calculate distance to eachother
                    float32 maxDistance = 300.0f;
                    bool canStart = true;

                    for (int32 i = 0; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                        {
                            //calculate the center of the player
                            PuRe_BoundingBox box = this->m_ppPlayers[i]->GetBox();
                            PuRe_Vector2F center;
                            PuRe_Vector2F center2;
                            center.X = box.m_Position.X + box.m_Size.X / 2.0f;
                            center.Y = box.m_Position.Y + box.m_Size.Y / 2.0f;
                            //go through all other players
                            for (int32 j = 0; j < 4; j++)
                            {
                                //if self go further
                                if (j == i)
                                    j++;
                                if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->GetLifes() > 0)
                                {
                                    //calculate center
                                    box = this->m_ppPlayers[j]->GetBox();
                                    center2.X = box.m_Position.X + box.m_Size.X / 2.0f;
                                    center2.Y = box.m_Position.Y + box.m_Size.Y / 2.0f;
                                    //if the distance is greater than the maxDistance, we can't start.
                                    if ((center2 - center).Length() > maxDistance)
                                        canStart = false;
                                }
                            }
                        }
                    } //for loop
                    if (canStart)
                        this->m_Combining = true;

                }
            }
            //Update Map
            this->m_pMap->Update(Seconds, this->m_pBubbleEmitter, CamPos, PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
            //UPdate Items
            for (uint32 i = 0; i < CGameScene::m_Items.size(); i++)
            {
                CItem* item = CGameScene::m_Items[i];
                bool remove = false;
                PuRe_Vector3F aimPlayer = PuRe_Vector3F(99999999.0f,0.0f,0.0f);
                PuRe_BoundingBox playerBox;
                if (item != NULL)
                {
                    item->Update(Seconds);
                    for (int32 j = 0; j < 4; j++)
                    {
                        if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->GetLifes() > 0)
                        {
                            playerBox = this->m_ppPlayers[j]->GetBox();
                            //calculate distance from player to box and from aimplayer to box
                            PuRe_Vector3F diff = playerBox.m_Position - item->m_BoundingBox.m_Position;
                            PuRe_Vector3F diffaim = aimPlayer - item->m_BoundingBox.m_Position;
                            //if player to box is smaller than aim to box, set new aim
                            if (diff.Length() < diffaim.Length())
                                aimPlayer = playerBox.m_Position;

                            if (item->m_BoundingBox.Intersect(playerBox))
                            {
                                if (item->m_Type == 5)
                                {
                                    CSoundManager::m_pSoundPlayer->PlaySound("grabcoin", false, false, CSoundManager::m_SoundVolume);
                                    this->m_ppPlayers[j]->m_Points += 100;
                                    this->m_Points += 100;
                                    if (this->m_ToEnergy < 100.0f)
                                    {
                                        this->m_ToEnergy += 1.0f;
                                        if (this->m_ToEnergy > 100.0f)
                                            this->m_ToEnergy = 100.0f;
                                    }
                                }
                                else if (item->m_Type == 2)
                                {
                                    if (this->m_Hearts != 4&&this->m_ExtraLife||this->m_Hearts != 8&&!this->m_ExtraLife)
                                        this->m_Hearts++;
                                    if (this->m_Hearts >= 4 && !this->m_ExtraLife&&!this->m_pHud->m_ExtraLifeStart)
                                    {
                                        //Actually start flash here which set extralife and hearts to 0
                                        this->m_pHud->m_ExtraLifeStart = true;
                                        this->m_pHud->m_ExtraLifeTimer = 0.0f;
                                    }
                                }
                                else
                                {
                                    CSoundManager::m_pSoundPlayer->PlaySound("grabitem", false, false, CSoundManager::m_SoundVolume);
                                    this->m_ppPlayers[j]->m_Item = item->m_Type+1;
                                }
                                remove = true;
                                break;
                            }
                        }
                    }
                    if (item->m_BoundingBox.m_Position.X + item->m_BoundingBox.m_Size.X < CamPos.X)
                        remove = true;
                    if (!remove)
                    {
                        //if he should not be remove, move him to the nearest player
                        PuRe_Vector3F diffaim = aimPlayer - item->m_BoundingBox.m_Position;
                        float32 Speed = 400.0f - diffaim.Length();
                        if (Speed < 0.0f)
                            Speed = 0.0f;
                        Speed /= 10.0f;
                        item->m_BoundingBox.m_Position.X += diffaim.X / 40.0f*Speed;
                        item->m_BoundingBox.m_Position.Y += diffaim.Y / 40.0f*Speed;
                    }
                }
                else
                    remove = true;
                if (remove)
                {
                    SAFE_DELETE(item);
                    if (CGameScene::m_Items.begin() + i < CGameScene::m_Items.end())
                        CGameScene::m_Items.erase(CGameScene::m_Items.begin() + i);
                    i--;
                }
            }
            //Update Lasers
            for (uint32 i = 0; i < CGameScene::m_Lasers.size(); i++)
            {
                //define our variables
                CLaser* laser = CGameScene::m_Lasers[i];
                PuRe_Vector3F position;
                //set the position the laser is drawn at
                if (this->m_pBigUboot->m_InUse)
                {
                    PuRe_BoundingBox box = this->m_pBigUboot->GetBox();
                    position = box.m_Position;
                    position.X += box.m_Size.X;
                }
                else
                {
                    int32 playerIndex = laser->GetPlayer();
                    PuRe_BoundingBox box = this->m_ppPlayers[playerIndex]->GetBox();
                    position = box.m_Position;
                    position.X += box.m_Size.X;
                }
                //update the laser
                bool dead = laser->Update(position,Seconds);
                if (dead)
                {
                    SAFE_DELETE(laser);
                    if (CGameScene::m_Lasers.begin() + i < CGameScene::m_Lasers.end())
                        CGameScene::m_Lasers.erase(CGameScene::m_Lasers.begin() + i);
                    i--;
                }
                else
                {
                    PuRe_BoundingBox box = laser->GetBoundingBox();
                    //Deal Damage to enemies
                    for (uint32 j = 0; j < CGameScene::m_Enemies.size(); j++)
                    {
                        CEnemy* enemy = CGameScene::m_Enemies[j];
                        bool remove = false;
                        if (enemy != NULL)
                        {
                            PuRe_BoundingBox enemyBox = enemy->GetBox();
                            if (box.Intersect(enemyBox))
                            {
                                if (enemy->DealDamage(laser->GetDamage()))
                                {
                                    CSoundManager::m_pSoundPlayer->PlaySound("grabenemy", false, false, CSoundManager::m_SoundVolume);
                                    int32 pIndex = laser->GetPlayer();
                                    this->m_ppPlayers[pIndex]->m_Points += enemy->GetPoints();
                                    this->m_Points += enemy->GetPoints();
                                    if (this->m_ToEnergy < 100.0f)
                                    {
                                        this->m_ToEnergy += enemy->GetPoints() / 100.0f;
                                        if (this->m_ToEnergy > 100.0f)
                                            this->m_ToEnergy = 100.0f;
                                    }
                                    this->m_pSpawnLua->SetFunction("OnDie");
                                    this->m_pSpawnLua->Push(enemyBox.m_Position.X);
                                    this->m_pSpawnLua->Push(enemyBox.m_Position.Y);
                                    this->m_pSpawnLua->Push(this->m_Points);
                                    this->m_pSpawnLua->Push(CamPos.X);
                                    this->m_pSpawnLua->Push(CamPos.Y);
                                    this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
                                    this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
                                    this->m_pSpawnLua->Push(Seconds);
                                    this->m_pSpawnLua->CallFunction(8, 0);
                                    remove = true;
                                }
                            }
                        }
                        else
                            remove = true;
                        if (remove)
                        {
                            if (enemy->m_Type == 6)
                                this->m_BossKilled = true;
                            else
                            {
                                if (enemy->GetSize() > 1.0f)
                                {
                                    if (enemy->m_Type != 3)
                                    {
                                        CSoundManager::StopMainSound();
                                        CSoundManager::PlayMainSound("level", true, true, CSoundManager::m_MusicVolume*0.5f);
                                    }
                                }
                                SAFE_DELETE(enemy);
                                if (CGameScene::m_Enemies.begin() + j < CGameScene::m_Enemies.end())
                                    CGameScene::m_Enemies.erase(CGameScene::m_Enemies.begin() + j);
                                j--;
                            }
                        }
                    } //for loop enemies
                } //if dead
            }
            //Update Bullets
            for (uint32 i = 0; i < CGameScene::m_Bullets.size(); i++)
            {
                //Initialize variables
                CBullet* bullet = CGameScene::m_Bullets[i];
                if (bullet->GetImage() == 29)
                {
                    int32 chance = std::rand() % 100;
                    if (chance >(99 - bullet->GetSpeed() * 10))
                        this->m_pBubbleEmitter->Emit(bullet->GetPosition(), bullet->GetLookAngle(), bullet->GetSpeed(), 1, 1,0.2f);
                }
                PuRe_Vector3F bulletPos = bullet->GetPosition();
                bool dead = false;
                bool collide = false;
                PuRe_BoundingBox box = bullet->GetBoundingBox();
                PuRe_Vector3F aimPosition = PuRe_Vector3F(999999999.0f,0.0f,0.0f);
                if (bullet->HitPlayer())
                {
                    //Hit BigUboot
                    if (this->m_pBigUboot->m_InUse)
                    {
                        if (box.Intersect(this->m_pBigUboot->GetBox()))
                        {
                            dead = true;
                            this->m_pBigUboot->Hit();
                        }
                    }
                    //Hit players
                    for (int32 j = 0; j < 4; j++)
                    {
                        if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->GetLifes() > 0)
                        {
                            PuRe_BoundingBox playerBox = this->m_ppPlayers[j]->GetBox();
                            if (box.Intersect(playerBox))
                            {
                                this->m_ppPlayers[j]->Hit();
                                if (this->m_ppPlayers[j]->GetLifes() == 0)
                                    this->m_Deaths++;
                                dead = true;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    //Deal Damage to enemies
                    for (uint32 j = 0; j < CGameScene::m_Enemies.size(); j++)
                    {
                        CEnemy* enemy = CGameScene::m_Enemies[j];
                        bool remove = false;
                        if (enemy != NULL)
                        {
                            PuRe_BoundingBox enemyBox = enemy->GetBox();
                            if (box.Intersect(enemyBox))
                            {
                                if (enemy->DealDamage(bullet->GetDamage()))
                                {
                                    CSoundManager::m_pSoundPlayer->PlaySound("grabenemy", false, false, CSoundManager::m_SoundVolume);
                                    int32 pIndex = bullet->GetPlayer();
                                    this->m_ppPlayers[pIndex]->m_Points += enemy->GetPoints();
                                    this->m_Points += enemy->GetPoints();
                                    if (this->m_ToEnergy < 100.0f)
                                    {
                                        this->m_ToEnergy += enemy->GetPoints() / 100.0f;
                                        if (this->m_ToEnergy > 100.0f)
                                            this->m_ToEnergy = 100.0f;
                                    }
                                    this->m_pSpawnLua->SetFunction("OnDie");
                                    this->m_pSpawnLua->Push(enemyBox.m_Position.X);
                                    this->m_pSpawnLua->Push(enemyBox.m_Position.Y);
                                    this->m_pSpawnLua->Push(this->m_Points);
                                    this->m_pSpawnLua->Push(CamPos.X);
                                    this->m_pSpawnLua->Push(CamPos.Y);
                                    this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
                                    this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
                                    this->m_pSpawnLua->Push(Seconds);
                                    this->m_pSpawnLua->CallFunction(8, 0);
                                    remove = true;
                                }
                                if (bullet->DieHit())
                                    dead = true;
                            }
                            else
                            {
                                //Calculate nearest enemy
                                PuRe_Vector3F positionDiff = box.m_Position - enemyBox.m_Position;
                                PuRe_Vector3F aimDiff = box.m_Position - aimPosition;
                                if (positionDiff.Length() < aimDiff.Length())
                                {
                                    aimPosition = enemyBox.m_Position;
                                }
                            }
                        }
                        else
                            remove = true;
                        if (remove)
                        {
                            if (enemy->m_Type == 6)
                                this->m_BossKilled = true;
                            else
                            {
                                if (enemy->GetSize() > 1.0f)
                                {
                                    if (enemy->m_Type != 3)
                                    {
                                        CSoundManager::StopMainSound();
                                        CSoundManager::PlayMainSound("level", true, true, CSoundManager::m_MusicVolume*0.5f);
                                    }
                                }
                                SAFE_DELETE(enemy);
                                if (CGameScene::m_Enemies.begin() + j < CGameScene::m_Enemies.end())
                                    CGameScene::m_Enemies.erase(CGameScene::m_Enemies.begin() + j);
                                j--;
                            }
                        }
                        if (dead)
                            break;
                    }
                }

                if (!dead)
                {
                    //if the bullet did not hit anything, update
                    float32 bulletSpeed = bullet->GetSpeed();
                    bullet->PreUpdate(this->m_pBulletLua, Seconds, this->m_ppPlayers, aimPosition);
                    for (int32 j=0;j<bulletSpeed;j++)
                    {
                        dead = bullet->Update(this->m_pBulletLua, Seconds, this->m_ppPlayers,aimPosition);
                        collide = this->m_pMap->HitDestroyable(box); //collide with destroyables
                        if (!collide)
                        {
                            if (bullet->GetCollide() || bullet->GetBounce())
                            {
                                collide = this->m_pMap->Intersect(box); //collide with map
                            }
                            if (collide&&bullet->GetBounce())
                                bullet->Bounce();
                            else if (collide)
                                dead = true;
                        }
                        else
                        {
                            this->m_pSpawnLua->SetFunction("OnDieBlock");
                            this->m_pSpawnLua->Push(bulletPos.X);
                            this->m_pSpawnLua->Push(bulletPos.Y);
                            this->m_pSpawnLua->Push(this->m_Points);
                            this->m_pSpawnLua->Push(CamPos.X);
                            this->m_pSpawnLua->Push(CamPos.Y);
                            this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
                            this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
                            this->m_pSpawnLua->Push(Seconds);
                            this->m_pSpawnLua->CallFunction(8, 0);
                            dead = true;
                        }
                        //check boundaries
                        if (bulletPos.X + box.m_Size.X < CamPos.X || bulletPos.Y+box.m_Size.Y < CamPos.Y || bulletPos.X > CamPos.X + (float32)gdesc.ResolutionWidth || bulletPos.Y > CamPos.Y + (float32)gdesc.ResolutionHeight)
                            dead = true;
                        if (dead)
                            break;
                    }
                }
                if(dead) //if he is dead remove him
                {
                    //Activate
                    bullet->OnDie(this->m_pBulletLua);
                    SAFE_DELETE(bullet);
                    if (CGameScene::m_Bullets.begin() + i < CGameScene::m_Bullets.end())
                        CGameScene::m_Bullets.erase(CGameScene::m_Bullets.begin() + i);
                    i--;
                }
            }
            //Update Bubbles
            this->m_pBubbleEmitter->Update(Seconds);
            /// Update Speed and Position
            float32 playerSpeed = 0.0f;
            PuRe_Vector3F playerPosition;
            bool alive = false;
            //if biguboot is in use, aim for him
            if (this->m_pBigUboot->m_InUse)
            {
                PuRe_BoundingBox pos = this->m_pBigUboot->GetBox();
                playerSpeed = this->m_pBigUboot->GetSpeed();
                playerPosition = pos.m_Position;
                playerPosition.X += pos.m_Size.X / 2.0f;
                playerPosition.Y += pos.m_Size.Y / 2.0f;
                alive = true;
            }
            else // no big uboot
            {
                //aim for the players
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                    {
                        alive = true;
                        PuRe_BoundingBox pos = this->m_ppPlayers[i]->GetBox();
                        if (pos.m_Position.X + pos.m_Size.X/2.0f > playerPosition.X)
                        {
                            playerSpeed = this->m_ppPlayers[i]->GetSpeed();
                            playerPosition = pos.m_Position;
                            playerPosition.X += pos.m_Size.X / 2.0f;
                            playerPosition.Y += pos.m_Size.Y / 2.0f;
                        }
                    }
                } //for loop
            }
            /// Update Enemies
            for (uint32 i = 0; i <CGameScene::m_Enemies.size(); i++)
            {
                CEnemy* enemy = CGameScene::m_Enemies[i];
                bool dead = false;
                if (enemy != NULL)
                {
                    PuRe_BoundingBox enemyBox = enemy->GetBox();
                    dead = enemy->Update(Seconds,playerSpeed,playerPosition,CamPos,PuRe_Vector2F((float32)gdesc.ResolutionWidth,(float32)gdesc.ResolutionHeight));
                    if (enemy->CollideDamage())
                    {
                        bool collide = false;
                        //Hit Players
                        for (int32 j = 0; j < 4; j++)
                        {
                            if (this->m_ppPlayers[j]->m_IsPlaying&&this->m_ppPlayers[j]->GetLifes() > 0)
                            {
                                if (enemyBox.Intersect(this->m_ppPlayers[j]->GetBox()))
                                {
                                    collide = true;
                                    if (!dead)
                                        dead = enemy->DieCollide();
                                    this->m_ppPlayers[j]->Hit();
                                    if (this->m_ppPlayers[j]->GetLifes() == 0)
                                        this->m_Deaths++;
                                }
                            }
                        }
                        //Hit BigUboot
                        if (this->m_pBigUboot->m_InUse)
                        {
                            if (enemyBox.Intersect(this->m_pBigUboot->GetBox()))
                            {
                                collide = true;
                                if (!dead)
                                    dead = enemy->DieCollide();
                                this->m_pBigUboot->Hit();
                            }
                        }
                        //if he is dead
                        if (dead) //he explodes
                        {
                            if (collide)
                            {
                                int32 impact = (std::rand() % 3) + 13;
                                CSoundManager::m_pSoundPlayer->PlaySound(std::to_string(impact).c_str(), false, true, CSoundManager::m_SoundVolume);
                            }
                            float32 size = enemy->GetSize();
                            PuRe_Vector3F ExplodePosition = enemyBox.m_Position;
                            CExplosion* explosion = new CExplosion(20.0f, ExplodePosition, size);
                            this->m_Explosions.push_back(explosion);
                        }
                    }
                    if (dead)
                    {
                        this->m_pSpawnLua->SetFunction("OnDie");
                        this->m_pSpawnLua->Push(enemyBox.m_Position.X);
                        this->m_pSpawnLua->Push(enemyBox.m_Position.Y);
                        this->m_pSpawnLua->Push(this->m_Points);
                        this->m_pSpawnLua->Push(CamPos.X);
                        this->m_pSpawnLua->Push(CamPos.Y);
                        this->m_pSpawnLua->Push(gdesc.ResolutionWidth);
                        this->m_pSpawnLua->Push(gdesc.ResolutionHeight);
                        this->m_pSpawnLua->Push(Seconds);
                        this->m_pSpawnLua->CallFunction(8, 0);
                    }
                }
                else
                    dead = true;
                if (dead)
                {
                    if (enemy->m_Type == 6)
                        this->m_BossKilled = true;
                    else
                    {
                        if (enemy->GetSize() > 1.0f)
                        {
                            if (enemy->m_Type != 3)
                            {
                                CSoundManager::StopMainSound();
                                CSoundManager::PlayMainSound("level", true, true, CSoundManager::m_MusicVolume*0.5f);
                            }
                        }
                        SAFE_DELETE(enemy);
                        if (CGameScene::m_Enemies.begin() + i < CGameScene::m_Enemies.end())
                            CGameScene::m_Enemies.erase(CGameScene::m_Enemies.begin() + i);
                        i--;
                    }
                }
            }

            if (!alive)
            {
                int32 alive = 0;
                int32 death = 0;
                for (int32 i = 0; i < 4; i++)
                {
                    if (this->m_ppPlayers[i]->m_IsPlaying)
                    {
                        if (this->m_ppPlayers[i]->GetLifes() == 0)
                            death++;
                        else
                            alive++;
                    }
                }
                this->m_pHighscore->SaveScore(this->m_Points, false, alive, death, this->m_Deaths);
                this->m_GameEnd = true;
                CSoundManager::StopMainSound();
                CSoundManager::PlayMainSound("dead", false, true, CSoundManager::m_SoundVolume);
            }
            else
                this->m_pGameCamera->Update(pPosition, dPosition, pSpeed, PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight), this->m_pMap->GetSize()*64.0f, Seconds, this->m_pCamera);

            //Update Explosions
            for (uint32 i = 0; i < this->m_Explosions.size(); i++)
            {
                bool dead = this->m_Explosions[i]->Update(Seconds);
                if (dead)
                {
                    SAFE_DELETE(this->m_Explosions[i]);
                    if (this->m_Explosions.begin() + i < this->m_Explosions.end())
                        this->m_Explosions.erase(this->m_Explosions.begin() + i);
                    i--;
                }
            }
            //Update HUD
            this->m_pHud->Update(Seconds);
            if (this->m_pHud->m_ExtraLifeStart&&this->m_pHud->ExtraLifeUpdate(Seconds))
            {
                CSoundManager::m_pSoundPlayer->PlaySound("extralife", false, true, CSoundManager::m_SoundVolume);
                this->m_ExtraLife = 3;
                this->m_Hearts -= 4;
                this->m_pHud->m_ExtraLifeStart = false;
            }
            //IF all are alive and not in the big uboot, do reviving of players
            if (alive&&!this->m_pBigUboot->m_InUse)
            {
                if (!this->m_pHud->m_ReviveStart&&this->m_ExtraLife != 0)
                {
                    bool startRevive = false;
                    for (uint32 i = 0; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() != 9)
                            startRevive= true;
                    }
                    if (startRevive)
                    {
                        this->m_pHud->m_ReviveStart = true;
                        this->m_pHud->m_ReviveTimer = 0.0f;
                        this->m_ExtraLife--;
                    }
                }
                if (this->m_pHud->m_ReviveStart&&this->m_pHud->ReviveUpdate(Seconds))
                {
                    this->m_pHud->m_ReviveStart = false;
                    PuRe_Vector3F middle = this->m_pMap->GetMiddle(playerPosition);
                    for (uint32 i = 0; i < 4; i++)
                    {
                        if (this->m_ppPlayers[i]->m_IsPlaying)
                            this->m_ppPlayers[i]->Heal(middle);
                    }
                }
            }

            if (this->m_pBigUboot->m_InUse)
            {
                this->m_pBigUboot->m_UseTimer += Seconds;
                this->m_ToEnergy -= this->m_pBigUboot->m_UseTimer/100.0f;
                this->m_Energy = m_ToEnergy;
                if (this->m_Energy < 0.0f || this->m_pBigUboot->GetLifes() == 0)
                {
                    CSoundManager::m_pSoundPlayer->PlaySound("dismantle", false, true, CSoundManager::m_SoundVolume);
                    this->m_pBigUboot->m_InUse = false;
                    this->m_Energy = 0.0f;
                    this->m_ToEnergy = 0.0f;
                    PuRe_Vector3F diffPosition;
                    //Calculate the ship Position
                    diffPosition = this->m_pBigUboot->GetBox().m_Position;
                    diffPosition.X += this->m_pBigUboot->GetBox().m_Size.X / 2.0f;
                    diffPosition.Y += this->m_pBigUboot->GetBox().m_Size.Y / 2.0f;
                    //move players there
                    for (int32 i = 0; i < 4; i++)
                    {
                        PuRe_Vector3F ppos = this->m_ppPlayers[i]->GetBox().m_Position;
                        PuRe_Vector3F psize = this->m_ppPlayers[i]->GetBox().m_Size;
                        ppos.X += psize.X/2.0f;
                        ppos.Y += psize.Y/2.0f;
                        if (this->m_ppPlayers[i]->m_IsPlaying&&this->m_ppPlayers[i]->GetLifes() > 0)
                            this->m_ppPlayers[i]->Move(diffPosition - ppos);
                    }
                }
            }

        } //if not paused etc
        return 1;
    }

    // **************************************************************************
    // **************************************************************************
    void CGameScene::Render(PuRe_IGraphics* a_pGraphics)
    {
        PuRe_Color clear = PuRe_Color(0.0f, 0.4f, 1.0f);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();

        PuRe_BoundingBox viewport;
        viewport.m_Position = PuRe_Vector3F(0.0f, 0.0f, 0.0f);
        viewport.m_Size = PuRe_Vector3F((float)gdesc.ResolutionWidth, (float)gdesc.ResolutionHeight, 0.0f);


        a_pGraphics->Clear(PuRe_Color(0.0f, 0.4f, 1.0f));
        a_pGraphics->Begin(viewport);

        //Get camera position
        PuRe_Vector3F CamPos = this->m_pGameCamera->GetPosition();

        ////// Set range within we draw the map /////
        int32 minX = (int32)(CamPos.X / 64.0f);
        int32 maxX = minX + (gdesc.ResolutionWidth / 64);
        int32 minY = (int32)CamPos.Y - 64;
        int32 maxY = minY + gdesc.ResolutionHeight+64;

        minX -= 4;
        maxX += 2;
        minY -= 8 * 64;
        maxY += 8 * 64;
        if (this->m_GameEnd||this->m_GamePaused)
        {
            this->m_pBulletMaterial->Apply();
            this->m_pBulletMaterial->SetFloat(1.0f, "Gray");
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(1.0f, "Gray");
            this->m_pMaterial->Apply();
            this->m_pMaterial->SetFloat(1.0f, "Gray");
            CBackground::m_pMaterial->Apply();
            CBackground::m_pMaterial->SetFloat(1.0f, "Gray");
        }
        else if (this->m_BossKilled&&this->m_BossTimer > 13)
        {
            float32 time = (((this->m_BossTimer-13.4f)/17.0f)/4);
            this->m_pBulletMaterial->Apply();
            this->m_pBulletMaterial->SetFloat(time, "Time");
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(time, "Time");
            this->m_pMaterial->Apply();
            this->m_pMaterial->SetFloat(time, "Time");
            CBackground::m_pMaterial->Apply();
            CBackground::m_pMaterial->SetFloat(time, "Time");
        }
        ////// DRAW Bubbles /////
        this->m_pBubbleEmitter->Draw(this->m_pCamera, this->m_pFontMaterial);

        ////// DRAW Map /////
        this->m_pMap->Draw(this->m_pCamera, minX, maxX, minY, maxY, CamPos);

        ////// DRAW BigUboot /////
        if (this->m_pBigUboot->m_InUse)
        {
            this->m_pBigUboot->Draw(this->m_pCamera, this->m_pShieldSprite, this->m_pFontMaterial);
        }
        else
        {
            ////// DRAW Players /////
            for (int32 i = 0; i < 4; i++)
            {
                if (this->m_ppPlayers[i]->m_IsPlaying)
                {
                    this->m_ppPlayers[i]->Draw(this->m_pCamera, this->m_pPlayerSprite,this->m_pShieldSprite,this->m_pFontMaterial);
                }
            }
        }
        ////// DRAW BULLETS /////
        for (uint32 i = 0; i < CGameScene::m_Bullets.size(); i++)
        {
            CBullet* bullet = CGameScene::m_Bullets[i];
            if (bullet->GetImage() != 0)
                this->m_pBulletSprite->Draw(this->m_pCamera, std::to_string(bullet->GetImage()).c_str(), bullet->GetPosition(), PuRe_Vector3F(0.0f, 0.0f, bullet->GetLookAngle()), PuRe_Vector2F(bullet->GetSize(), bullet->GetSize()));
        }
        ////// DRAW LASERS /////
        for (uint32 i = 0; i < CGameScene::m_Lasers.size(); i++)
        {
            CLaser* laser = CGameScene::m_Lasers[i];
            laser->Draw(this->m_pCamera, this->m_pBulletSprite, this->m_pBulletMaterial);
         }
        ////// DRAW EXPLOSIONS /////
        for (uint32 i = 0; i<this->m_Explosions.size(); i++)
            this->m_Explosions[i]->Draw(this->m_pExplosionSprite, this->m_pCamera);
        ////// DRAW Enemies /////
        for (uint32 i = 0; i < CGameScene::m_Enemies.size(); i++)
        {
            CEnemy* enemy = CGameScene::m_Enemies[i];
            if (enemy != NULL)
                enemy->Draw(this->m_pCamera, this->m_ppEnemySprite, this->m_pBulletMaterial);
        }
        ////// DRAW Items /////
        for (uint32 i = 0; i < CGameScene::m_Items.size(); i++)
        {
            CItem* item = CGameScene::m_Items[i];
            item->Draw(this->m_pCamera, this->m_pItemSprite, this->m_pFontMaterial);
        }
        int32 bigLifes = this->m_pBigUboot->GetLifes();
        if (!this->m_pBigUboot->m_InUse)
            bigLifes = 0;

        if (this->m_DisplayUI)
        {
            if (this->m_GameEnd)
                this->m_pHud->Draw(this->m_GameEndTime, this->m_pBulletMaterial, this->m_pFontMaterial, m_GameEndLeft);
            else if (this->m_GamePaused)
                this->m_pHud->Draw(this->m_PauseWhere, this->m_pBulletMaterial, this->m_pFontMaterial);
            else if (!this->m_BossKilled)
                this->m_pHud->Draw(this->m_Points, this->m_Hearts, bigLifes, this->m_ExtraLife != 0, this->m_Energy, this->m_ToEnergy, this->m_ppPlayers, this->m_pItemSprite, this->m_pFontMaterial);
        }
   
        if (this->m_GameEnd || this->m_GamePaused)
        {
            this->m_pBulletMaterial->Apply();
            this->m_pBulletMaterial->SetFloat(0.0f, "Gray");
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(0.0f, "Gray");
            this->m_pMaterial->Apply();
            this->m_pMaterial->SetFloat(0.0f, "Gray");
            CBackground::m_pMaterial->Apply();
            CBackground::m_pMaterial->SetFloat(0.0f, "Gray");
        }
        else if (this->m_BossKilled)
        {
            float32 time = -0.4f;
            this->m_pBulletMaterial->Apply();
            this->m_pBulletMaterial->SetFloat(time, "Time");
            this->m_pFontMaterial->Apply();
            this->m_pFontMaterial->SetFloat(time, "Time");
            this->m_pMaterial->Apply();
            this->m_pMaterial->SetFloat(time, "Time");
            CBackground::m_pMaterial->Apply();
            CBackground::m_pMaterial->SetFloat(time, "Time");
        }
        a_pGraphics->End();
    }
    // **************************************************************************
    // **************************************************************************
    void CGameScene::Exit()
    {
        for (uint32 i = 0; i<CGameScene::m_Lasers.size(); i++)
            SAFE_DELETE(CGameScene::m_Lasers[i]);
        CGameScene::m_Lasers.clear();

        for (uint32 i = 0; i<CGameScene::m_Items.size(); i++)
            SAFE_DELETE(CGameScene::m_Items[i]);
        CGameScene::m_Items.clear();

        for (uint32 i = 0; i<CGameScene::m_Bullets.size(); i++)
            SAFE_DELETE(CGameScene::m_Bullets[i]);
        CGameScene::m_Bullets.clear();

        for (uint32 i = 0; i<CGameScene::m_Enemies.size(); i++)
            SAFE_DELETE(CGameScene::m_Enemies[i]);
        CGameScene::m_Enemies.clear();

        for (uint32 i = 0; i<7; i++)
            SAFE_DELETE(this->m_ppEnemySprite[i]);

        for (uint32 i = 0; i<7; i++)
            SAFE_DELETE(CGameScene::m_ppEnemyLua[i]);

        for (uint32 i = 0; i<this->m_Explosions.size(); i++)
            SAFE_DELETE(this->m_Explosions[i]);
        this->m_Explosions.clear();

        // DELETE HIGHSCORE
        SAFE_DELETE(this->m_pHighscore);
        // DELETE GAMESTUFF
        SAFE_DELETE(this->m_pBigUboot);
        SAFE_DELETE(this->m_pMap);
        // DELETE SPRITES
        SAFE_DELETE(this->m_pBubbleEmitter);
        SAFE_DELETE(this->m_ppEnemySprite);
        SAFE_DELETE(this->m_pExplosionSprite);
        SAFE_DELETE(this->m_pBulletSprite);
        // DELETE MATERIAL
        SAFE_DELETE(this->m_pFontMaterial);
        SAFE_DELETE(this->m_pMaterial);
        SAFE_DELETE(this->m_pBulletMaterial);
        // DELETE CAMS
        SAFE_DELETE(this->m_pCamera);
        // DELETE LUA
        SAFE_DELETE(CGameScene::m_ppEnemyLua);
        SAFE_DELETE(this->m_pLaserLua);
        SAFE_DELETE(this->m_pSpawnLua);
        SAFE_DELETE(this->m_pPlayerLua);
        SAFE_DELETE(this->m_pBulletLua);
        // DELETE HUD
        SAFE_DELETE(this->m_pHud);
    }
}
