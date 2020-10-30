#include "include/Map.h"
#include "include/SpriteManager.h"

namespace Game
{
    int32 CMap::m_MapSize;
    int32 CMap::m_TileAmount;
    SPoint* CMap::m_pPoints;
    // **************************************************************************
    // **************************************************************************

    CMap::CMap(const char8* a_pLuaPath, PuRe_IMaterial* a_pMaterial, PuRe_IGraphics* a_pGraphics)
    {
        this->m_pMaterial = a_pMaterial;
        this->m_LuaReader = new CLuaReader(a_pLuaPath);
        this->m_pTileSprite = CSpriteManager::GetSprite("Tiles");
        this->m_pFallingSprite = CSpriteManager::GetSprite("Falling");
        this->m_pStoneSprite = CSpriteManager::GetSprite("Stones");
        this->m_pTowerSprite = new CSpriteReader(a_pMaterial, CSpriteManager::GetSprite("Towers"), "data/textures/destroyable.txt");
        this->m_pAmbientSprite = new CSpriteReader(a_pMaterial, CSpriteManager::GetSprite("Ambient"), "data/textures/ambient.txt");
        //Call Init
        this->m_LuaReader->SetFunction("Init");
        //Call Function
        this->m_LuaReader->CallFunction(0, 2);
        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        //Get Values
        int32 Y = this->m_LuaReader->PopInt();
        this->m_MapSize = this->m_LuaReader->PopInt();
        //Create Points according to Values
        this->m_pPoints = new SPoint[this->m_MapSize];
        this->m_TileAmount = 30; // How many up and how many down
        this->m_pTiles = new STile[this->m_MapSize*this->m_TileAmount * 2];

        this->m_pBackground = new CBackground(a_pGraphics, PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
        this->m_pMenu = false;
        this->Generate(Y);

    }
    CMap::CMap(const char8* a_pLuaPath, PuRe_IMaterial* a_pMaterial, PuRe_IGraphics* a_pGraphics, bool a_Menu)
    {
        this->m_pMaterial = a_pMaterial;
        this->m_LuaReader = new CLuaReader(a_pLuaPath);
        this->m_pTileSprite = CSpriteManager::GetSprite("Tiles");
        this->m_pFallingSprite = CSpriteManager::GetSprite("Falling");
        this->m_pStoneSprite = CSpriteManager::GetSprite("Stones");
        this->m_pTowerSprite = new CSpriteReader(a_pMaterial, CSpriteManager::GetSprite("Towers"), "data/textures/destroyable.txt");
        this->m_pAmbientSprite = new CSpriteReader(a_pMaterial, CSpriteManager::GetSprite("Ambient"), "data/textures/ambient.txt");

        PuRe_GraphicsDescription gdesc = a_pGraphics->GetDescription();
        int32 Y = 700;
        this->m_MapSize = (gdesc.ResolutionWidth / 64) + 1;
        //Create Points according to Values
        this->m_pPoints = new SPoint[this->m_MapSize];
        this->m_TileAmount = 6; // How many up and how many down
        this->m_pTiles = new STile[this->m_MapSize*this->m_TileAmount * 2];

        this->m_pBackground = new CBackground(a_pGraphics, PuRe_Vector2F((float32)gdesc.ResolutionWidth, (float32)gdesc.ResolutionHeight));
        this->m_pMenu = true;
        this->Generate(Y);
    }

    // **************************************************************************
    // **************************************************************************

    int CMap::GetY(lua_State* a_pLuaState)
    {
        float32 xPosition = (float32)lua_tonumber(a_pLuaState, 1);
        lua_pop(a_pLuaState, 1);
        //initialize variables
        int32 x = (int32)(xPosition / 64.0f);
        //define x val
        if (x <= 0)
            x = 1;
        else if (x >= CMap::m_MapSize)
            x = CMap::m_MapSize - 1;
        //set y
        float32 y = (float32)(CMap::m_pPoints[x].Y - CMap::m_pPoints[x].TileDist);
        //push back
        lua_pushnumber(a_pLuaState, y);
        //return number of arguments we pushed
        return 1;
    }

    // **************************************************************************
    // **************************************************************************

    void CMap::Generate(int32 Y)
    {

        //Define Variables
        int32 Start = 0;
        int32 Type = 0;
        int32 Split = 0;
        int32 TileDist = 0;
        bool Fall = 0;

        int32 yDist = 0;
        int32 yDist2 = 0;
        int32 UVIndex = 0;
        for (int32 i = 0; i < this->m_MapSize; i++)
        {
            //Call Init
            this->m_LuaReader->SetFunction("GeneratePoints");
            //Call Arguments
            this->m_LuaReader->Push(i);
            this->m_LuaReader->Push(Y);
            this->m_LuaReader->Push(Start);
            this->m_LuaReader->Push(Type);
            this->m_LuaReader->Push(Split);
            //Call Function
            this->m_LuaReader->CallFunction(5, 6);
            //Get Values
            Type = this->m_LuaReader->PopInt();
            Start = this->m_LuaReader->PopInt();
            Y = this->m_LuaReader->PopInt();
            TileDist = this->m_LuaReader->PopInt();
            Split = this->m_LuaReader->PopInt();
            Fall = this->m_LuaReader->PopBool();
            //Save it
            this->m_pPoints[i].X = 64 * i;
            this->m_pPoints[i].Y = Y;
            this->m_pPoints[i].TileDist = TileDist;
            this->m_pPoints[i].Fall = Fall;
            this->m_pPoints[i].Split = Split;

            //Get smallest and biggest Y
            if (this->m_pPoints[i].Y > this->m_MinMaxY.Y)
                this->m_MinMaxY.Y = (float32)this->m_pPoints[i].Y;
            else if (this->m_pPoints[i].Y < this->m_MinMaxY.X)
                this->m_MinMaxY.X = (float32)this->m_pPoints[i].Y;

            yDist = (int32)((this->m_pPoints[i].Y + this->m_pPoints[i].TileDist) / 64) * 64;
            yDist2 = (int32)((this->m_pPoints[i].Y - this->m_pPoints[i].TileDist) / 64) * 64;
            //top or not
            bool top = false;

            for (int32 j = 0; j < this->m_TileAmount * 2; j++)
            {
                int32 index = (i*this->m_TileAmount * 2) + j;
                //calculate if we are top or not
                //Set Position
                this->m_pTiles[index].Position.X = (float32)this->m_pPoints[i].X;
                //split up if there are splits
                if (Split > 1)
                {
                    int32 tileDist = (int32)(this->m_pPoints[i].TileDist / 640) * 64;
                    if (j == 0 && Split == 2)
                        this->m_pTiles[index].Position.Y = (float32)this->m_pPoints[i].Y;
                    else if (j == this->m_TileAmount && Split == 2)
                        this->m_pTiles[index].Position.Y = (float32)this->m_pPoints[i].Y + 64.0f;
                    if (j == 0 && Split == 3)
                        this->m_pTiles[index].Position.Y = (float32)this->m_pPoints[i].Y + 256.0f;
                    else if (j == this->m_TileAmount && Split == 3)
                        this->m_pTiles[index].Position.Y = (float32)this->m_pPoints[i].Y - 192.0f;
                }
                if (j != 0 && Split > 1 && j != this->m_TileAmount || Split <= 1)
                {
                    if (j < this->m_TileAmount)
                        this->m_pTiles[index].Position.Y = (float32)yDist + j*64.0f;
                    else
                        this->m_pTiles[index].Position.Y = (float32)yDist2 - (j - this->m_TileAmount)*64.0f;
                }

                this->m_pTiles[index].Position.Z = 6.0f;
                //Set UV Index, which layer is drawn
                UVIndex = ((int32)this->m_pTiles[index].Position.Y / 64) % 6;
                if (UVIndex < 0)
                    UVIndex = 6 + UVIndex;
                //Set UV Position
                this->m_pTiles[index].UVPosition.Y = 64.0f*UVIndex;
                this->m_pTiles[index].UVPosition.X = (std::rand() % 10)*64.0f;
                this->m_pTiles[index].flip = true;
                this->m_pTiles[index].towerIndex = -1;
                this->m_pTiles[index].fallIndex = -1;
                this->m_pTiles[index].AmbientIndex = -1;
                this->m_pTiles[index].stoneStartIndex = -1;
                this->m_pTiles[index].stoneEndIndex = -1;
            }
            //Determine where the ambient and stones are located at
            if (i != 0)
            {
                this->m_pPoints[i - 1].BoundingBoxStart = this->m_BoundingBox.size();
                for (int32 j = 0; j < 2; j++)
                {
                    int32 index;
                    if (j == 0)
                        index = (i*this->m_TileAmount * 2);
                    else
                        index = (i*this->m_TileAmount * 2) + this->m_TileAmount;
                    //now calculate if there are stones/ambient for the one on the left
                    top = j == 0;
                    int32 right = index; //right is the current one
                    index = index - this->m_TileAmount * 2; //actual one is now the left of the current one
                    int32 left = index - this->m_TileAmount * 2; //left one is the one on the left side of the one on the left side
                    if (left < 0)
                        left = 0;

                    if (i > 1&&this->m_pPoints[i - 2].Split != 1)
                        left++;
                    if (this->m_pPoints[i - 1].Split != 1)
                        index++;
                    if (this->m_pPoints[i].Split != 1)
                        right++;

                    //Calculate how many tiles we have between left - index right
                    int32 leftTiles = (int32)(this->m_pTiles[index].Position.Y - this->m_pTiles[left].Position.Y) / 64;
                    int32 rightTiles = (int32)(this->m_pTiles[index].Position.Y - this->m_pTiles[right].Position.Y) / 64;
                    int32 tiles = 0; //how many tiles we have stones
                    if (top)
                    {
                        if (rightTiles < 0) //right side is above us, meaning this side is free
                            tiles = abs(rightTiles);
                        if (leftTiles < 0&&abs(leftTiles) > tiles) //right side is above us and that side is greater than our left side
                            tiles = abs(leftTiles);
                        tiles++;
                        printf("");
                    }
                    else
                    {
                        if (leftTiles > 0) //we are above left side, so that side is free
                            tiles = leftTiles;
                        if (rightTiles > 0&&rightTiles > leftTiles) //we are above right side and that side is greater than our left side
                            tiles = rightTiles;
                        tiles++;
                        printf("");
                    }
                    //add tiles for split
                    if (this->m_pPoints[i - 1].Split != 1)
                    {
                        index--;
                        tiles += 1;
                    }

                    //add bounding boxes
                    for (int32 l = 0; l < tiles; l++)
                    {
                        PuRe_BoundingBox box(this->m_pTiles[index].Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f));
                        box.m_Position.Z = 0.0f;
                        this->m_BoundingBox.push_back(box);
                        //add stones
                        this->m_pTiles[index].stoneStartIndex = this->m_Stones.size();
                        this->m_pTiles[index].stoneEndIndex = this->m_Stones.size() + 5;

                        int32 spawnAmbient = 0; // 0 - don't spawn, 1 = top, 2 = bottom
                        if (this->m_pPoints[i-1].Split == 3) //split in three
                        {
                            if (top&&l == 1)
                                spawnAmbient = 1; //top
                            else if (top&&l == 0 || !top&&l == 0 || !top&&l == 1)
                                spawnAmbient = 2; //bottom
                        }
                        else if (this->m_pPoints[i - 1].Split == 2) // split in two
                        {
                            if (top&&l == 0 || top&&l == 1)
                                spawnAmbient = 1; // top
                            else if (!top&&l == 0 || !top&&l == 1)
                                spawnAmbient = 2; //bottom
                        }
                        else
                        {
                            if (top&&l == 0)
                                spawnAmbient = 1;
                            else if (!top&&l == 0)
                                spawnAmbient = 2;
                        }

                        for (int32 k = 0; k < 5; k++)
                        {
                            //spawn Stones
                            SStone stone;
                            //calculate offset
                            PuRe_Vector2F offset = PuRe_Vector2F(-32.0f, -32.0f);
                            if (k != 4)
                            {
                                offset += PuRe_Vector2F((k % 2)*40.0f, (float32)((int32)(k / 2))*40.0f);
                                offset.X += (std::rand() % 20) - 10;
                                if (top)
                                    offset.Y += (std::rand() % 20) - 10;
                                else
                                    offset.Y += (std::rand() % 20) - 10;
                            }
                            //calculate UV Position
                            int32 uvindex = std::rand() % 4;
                            PuRe_Vector2F UVPosition = PuRe_Vector2F((uvindex % 2)*64.0f, (float32)((int32)(uvindex / 2))*64.0f);
                            //Set variables
                            stone.Position.X = (float32)this->m_pTiles[index].Position.X + offset.X;
                            stone.Position.Y = (float32)this->m_pTiles[index].Position.Y + offset.Y;
                            stone.Position.Z = 5.0f;
                            stone.UVPosition = UVPosition;
                            if (top)

                                stone.flip = true;
                            else
                            {
                                stone.Position.Y += 20.0f;
                                stone.flip = false;
                            }

                            if (top&&this->m_pPoints[i-1].Split == 3)
                            {
                                if (l == 0)
                                {
                                    stone.Position.Y += 20.0f;
                                    stone.flip = false;
                                }

                            }
                            this->m_Stones.push_back(stone);
                        } //end for loop

                        if (spawnAmbient != 0) //top and bottom
                        {
                            int32 chance = std::rand() % 1000;
                            if (i > 10 && this->m_pPoints[i - 1].Fall&&spawnAmbient == 1)
                            {
                                SFalling fall;
                                fall.Position.X = (float32)this->m_pTiles[index].Position.X;
                                fall.Position.Y = (float32)this->m_pTiles[index].Position.Y - 128.0f;
                                fall.Position.Z = 0.0f;
                                fall.fall = false;
                                fall.dead = false;
                                fall.Box = PuRe_BoundingBox(fall.Position + PuRe_Vector3F(60.0f, 0.0f, 0.0f), PuRe_Vector3F(104.0f, 256.0f, 0.0f));
                                fall.Position.Z = 7.0f;
                                //add to tiles index
                                this->m_pTiles[index].fallIndex = this->m_Falling.size();
                                this->m_Falling.push_back(fall);
                            }
                            if (i > 10 && this->m_pPoints[i - 1].Split == 1 && chance >= 990 && spawnAmbient == 2)
                            {
                                STower tower;
                                tower.Position.X = (float32)this->m_pTiles[index].Position.X;
                                tower.Position.Y = (float32)this->m_pTiles[index].Position.Y;
                                tower.Position.Z = 0.0f;
                                tower.Hitpoints = 8;
                                tower.fall = false;
                                tower.dead = false;
                                tower.Animation = 1;
                                tower.Box = PuRe_BoundingBox(tower.Position + PuRe_Vector3F(120.0f, 30.0f, 0.0f), PuRe_Vector3F(125.0f, 470.0f, 0.0f));
                                tower.Position.Z = 7.0f;
                                //add to tiles index
                                this->m_pTiles[index].towerIndex = this->m_Tower.size();
                                this->m_Tower.push_back(tower);
                            }
                            if (chance >= 300)
                            {
                                //add ambient
                                SAmbient ambient;
                                //set Position
                                ambient.Position.X = (float32)this->m_pTiles[index].Position.X + 30.0f;
                                ambient.Position.Y = (float32)this->m_pTiles[index].Position.Y;
                                ambient.Position.Z = 6.0f;
                                //set up and down
                                if (top)
                                {
                                    ambient.Position.Y -= 96.0f;
                                    ambient.flip = true;
                                }
                                else
                                {
                                    ambient.Position.Y += 64.0f;
                                    ambient.flip = false;
                                }
                                //Flip in this case cause they should be looking up
                                if (this->m_pPoints[i-1].Split == 3)
                                {
                                    if (top&&l == 0)
                                    {
                                        ambient.flip = false;
                                        ambient.Position.Y += 160.0f;
                                    }
                                    else if (l == 0)
                                    {
                                        ambient.flip = false;
                                    }

                                }
                                std::string name;
                                //add to tiles index
                                this->m_pTiles[index].AmbientIndex = this->m_Ambient.size();
                                //set name
                                if (spawnAmbient == 1)
                                {
                                    chance = std::rand() % 8;
                                    name = "Ambient_O_" + std::to_string(chance);
                                    if (chance > 2 && chance < 6)
                                    {
                                        ambient.Position.X -= 64.0f;
                                        ambient.Position.Y += 16.0f;
                                    }
                                }
                                else
                                {
                                    chance = std::rand() % 10;
                                    name = "Ambient_U_" + std::to_string(chance);
                                    if (chance == 3)
                                        ambient.Position.X -= 30.0f;
                                    else if (chance < 3)
                                        ambient.Position.Y -= 32.0f;
                                }
                                ambient.Name = name;
                                this->m_Ambient.push_back(ambient);
                            }
                        }
                        index++;
                    }
                } //for loop
                this->m_pPoints[i - 1].BoundingBoxEnd = this->m_BoundingBox.size();
            } // i != 0
        }
        //Get smallest and biggest X
        this->m_MinMaxX.X = (float32)this->m_pPoints[0].X;
        this->m_MinMaxX.Y = (float32)this->m_pPoints[this->m_MapSize - 1].X;

    }

    // **************************************************************************
    // **************************************************************************

    CMap::~CMap()
    {
        //Delete Arrays
        SAFE_DELETE(this->m_pPoints);
        SAFE_DELETE(this->m_pTiles);
        //Delete Sprites
        SAFE_DELETE(this->m_pTowerSprite);
        SAFE_DELETE(this->m_pBackground);
        SAFE_DELETE(this->m_pAmbientSprite);
        //Delete Lua
        SAFE_DELETE(this->m_LuaReader);
    }

    // **************************************************************************
    // **************************************************************************

    PuRe_Vector3F CMap::GetMiddle(PuRe_Vector3F a_Position)
    {
        //initialize variables
        PuRe_Vector3F pos;
        int32 x = (int32)(a_Position.X / 64.0f);
        //set min/max
        if (x <= 0)
            x = 1;
        else if (x >= this->m_MapSize)
            x = this->m_MapSize - 1;
        //set Position
        pos.X = (float32)this->m_pPoints[x].X;
        pos.Y = (float32)this->m_pPoints[x].Y;
        if (this->m_pPoints[x].Split == 2)
        {
            int32 chance = std::rand() % 10;
            if (chance > 5)
                pos.Y += 64.0f * 3;
            else
                pos.Y -= 64.0f * 3;
        }
        pos.Z = 0.0f;
        //return position
        return pos;
    }

    // **************************************************************************
    // **************************************************************************

    void CMap::Update(float32 a_DeltaTime, CBubbleEmitter* a_pEmitter, PuRe_Vector3F a_CamPosition, PuRe_Vector2F a_Resolution)
    {
        int32 minX = (int32)(a_CamPosition.X / 64.0f);
        int32 maxX = minX + (int32)(a_Resolution.X / 64.0f);
        minX -= 2;
        maxX += 50;
        PuRe_Vector3F Position;
        float32 Angle = 0.0f;
        float32 Speed = 0.0f;
        for (int32 i=0;i<3;i++)
        {
            Position.X = a_CamPosition.X + std::rand() % (int32)a_Resolution.X*2;
            Position.Y = a_CamPosition.Y + std::rand() % (int32)a_Resolution.Y;
            Position.Z = 9.0f;
            a_pEmitter->Emit(Position, Angle, Speed, 1, 1, 0.2f);
        }
        //Draw only in the possible Range
        if (maxX > this->m_MapSize)
            maxX = this->m_MapSize;
        if (minX < 0)
            minX = 0;

        int32 index = 0;
        int32 ambientIndex = 0;
        //Spawn Bubbles
        for (int32 i = minX; i < maxX; i++)
        {
            for (int32 j = 0; j < 8; j++)
            {
                if (j < 4) //up
                    index = (i*this->m_TileAmount * 2) + j;
                else //down
                    index = (i*this->m_TileAmount * 2) + j + this->m_TileAmount - 4;
                ambientIndex = this->m_pTiles[index].AmbientIndex;
                if (ambientIndex != -1)
                {
                    if (this->m_Ambient[ambientIndex].Name == "Ambient_U_3" || this->m_Ambient[ambientIndex].Name == "Ambient_U_4" || this->m_Ambient[ambientIndex].Name == "Ambient_O_0")
                    {
                        //Spawn Bubbles
                        Position = this->m_Ambient[ambientIndex].Position;
                        Position.Z = 7.0f;
                        Speed = 5.0f;
                        Angle = 90.0f*0.0174532925f; // in Radians
                        if (this->m_Ambient[ambientIndex].Name == "Ambient_U_3")
                        {
                            Position.X += 64.0f;
                            Position.Y += 64.0f;
                        }
                        else if (this->m_Ambient[ambientIndex].Name == "Ambient_U_4")
                        {
                            Position.X += 32.0f;
                            Position.Y += 32.0f;
                        }
                        else if (this->m_Ambient[ambientIndex].Name == "Ambient_O_0")
                        {
                            Angle += 180.0f*0.0174532925f; // in Radians
                            Position.Y += 64.0f;
                            Position.X += 32.0f;
                        }
                        int32 chance = std::rand() % 100;
                        if (chance > 97)
                            a_pEmitter->Emit(Position, Angle, Speed, 1, 1, 1.0f);
                    }
                }
            }
        }
        //update falling objects
        for (uint32 i = 0; i < this->m_Falling.size(); i++)
        {
            if (!this->m_Falling[i].dead)
            {
                PuRe_Vector3F pos = this->m_Falling[i].Position;
                if (pos.X + this->m_Falling[i].Box.m_Size.X < a_CamPosition.X)
                    this->m_Falling[i].dead = true;
                else if (!this->m_Falling[i].fall)
                {
                    if (pos.X < a_CamPosition.X + a_Resolution.X)
                    {
                        this->m_Falling[i].fall = true;
                        this->m_Falling[i].fallTime = 1.0f;
                    }
                }
                else
                {
                    if (this->m_Falling[i].fallTime < 0.0f)
                    {
                        this->m_Falling[i].Position.Y -= 10.0f*a_DeltaTime*60.0f;
                        this->m_Falling[i].Box.m_Position.Y -= 10.0f*a_DeltaTime*60.0f;
                        if (this->m_Falling[i].Position.Y + this->m_Falling[i].Box.m_Size.Y < a_CamPosition.Y)
                            this->m_Falling[i].dead = true;
                    }
                    else
                    {
                        this->m_Falling[i].fallTime -= a_DeltaTime;
                        this->m_Falling[i].Position.X += sin(this->m_Falling[i].fallTime*PuRe_PI * 4)*4.0f;
                        this->m_Falling[i].Box.m_Position.X += sin(this->m_Falling[i].fallTime*PuRe_PI * 4)*4.0f;
                    }
                }
            }
        }
        //update tower objects
        for (uint32 i = 0; i < this->m_Tower.size(); i++)
        {
            if (!this->m_Tower[i].dead)
            {
                PuRe_Vector3F pos = this->m_Tower[i].Position;
                if (pos.X + (this->m_Tower[i].Box.m_Size.X * 2) < a_CamPosition.X)
                    this->m_Tower[i].dead = true;
                else if (this->m_Tower[i].fall)
                {
                    this->m_Tower[i].AnimationTime -= a_DeltaTime*40.0f;
                    if (this->m_Tower[i].AnimationTime < 0.0f&&this->m_Tower[i].Animation != 19)
                    {
                        this->m_Tower[i].Animation++;
                        this->m_Tower[i].AnimationTime = 1.0f;
                    }
                    if (this->m_Tower[i].Animation > 10)
                    {
                        this->m_Tower[i].Position.Y -= a_DeltaTime*100.0f;
                        this->m_Tower[i].Box.m_Position.Y -= a_DeltaTime*100.0f;
                        if (this->m_Tower[i].Position.Y + this->m_Tower[i].Box.m_Size.Y < a_CamPosition.Y)
                            this->m_Tower[i].dead = true;
                    }
                }
            }
        }
        this->m_pBackground->Update(a_DeltaTime);
    }

    // **************************************************************************
    // **************************************************************************

    bool CMap::HitDestroyable(PuRe_BoundingBox& a_rBox)
    {
        //Get the range
        int32 x = (int32)(a_rBox.m_Position.X / 64.0f);
        int32 minX = x - 3;
        int32 maxX = x + 3;
        int32 index = 0;
        if (minX < 0)
            minX = 0;
        if (maxX > this->m_MapSize)
            maxX = this->m_MapSize;
        bool collision = false;
        //only check within the range
        for (int32 i = minX; i < maxX; i++)
        {
            for (int32 j = 0; j < 2; j++)
            {
                if (j == 0) //up
                    index = (i*this->m_TileAmount * 2) + j;
                else //down
                    index = (i*this->m_TileAmount * 2) + this->m_TileAmount;
                int32 fallIndex = this->m_pTiles[index].fallIndex;
                int32 towerIndex = this->m_pTiles[index].towerIndex;
                if (towerIndex != -1)
                {
                    if (this->m_Tower[towerIndex].Box.Intersect(a_rBox) && !this->m_Tower[towerIndex].fall)
                    {
                        collision = true;
                        this->m_Tower[towerIndex].Hitpoints--;
                        if (this->m_Tower[towerIndex].Hitpoints % 2)
                            this->m_Tower[towerIndex].Animation++;
                        if (this->m_Tower[towerIndex].Hitpoints == 0)
                        {
                            this->m_Tower[towerIndex].fall = true;
                            this->m_Tower[towerIndex].Animation = 5;
                            this->m_Tower[towerIndex].AnimationTime = 10;
                        }
                        break;
                    }
                }
                else if (fallIndex != -1)
                {
                    if (this->m_Falling[fallIndex].Box.Intersect(a_rBox) && !this->m_Falling[fallIndex].dead)
                    {
                        collision = true;
                        this->m_Falling[fallIndex].dead = true;
                        break;
                    }
                }
            }
            if (collision)
                break;
        }
        if (collision)
            CSoundManager::m_pSoundPlayer->PlaySound("hitrock", false, false, CSoundManager::m_SoundVolume);
        return collision;
    }

    // **************************************************************************
    // **************************************************************************

    bool CMap::Intersect(PuRe_BoundingBox& a_rBox)
    {
        //Get the range
        int32 x = (int32)(a_rBox.m_Position.X / 64.0f);
        int32 minX = x - 3;
        int32 maxX = x + 3;
        if (minX < 0)
            minX = 0;
        if (maxX > this->m_MapSize)
            maxX = this->m_MapSize;
        bool collision = false;
        //only check within the range
        for (int32 i = minX; i < maxX; i++)
        {
            int32 bstart = this->m_pPoints[i].BoundingBoxStart;
            int32 bend = this->m_pPoints[i].BoundingBoxEnd;
            for (int32 j = bstart; j < bend; j++)
            {
                if (this->m_BoundingBox[j].Intersect(a_rBox))
                {
                    collision = true;
                    break;
                }
            }
            if (collision)
                break;

        }
        return collision;
    }

    // **************************************************************************
    // **************************************************************************

    int32 CMap::GetSize()
    {
        return this->m_MapSize;
    }

    // **************************************************************************
    // **************************************************************************

    void CMap::Draw(PuRe_Camera* a_pCamera, int32 a_minXRange, int32 a_maxXRange, int32 a_minYRange, int32 a_maxYRange, PuRe_Vector3F a_CamPosition)
    {
        PuRe_Vector2F UVPosition(64.0f, 64.0f);
        int32 yDist = 0;
        int32 yDist2 = 0;
        int32 UVIndex = 0;
        //Draw only in the possible Range
        if (a_maxXRange > this->m_MapSize)
            a_maxXRange = this->m_MapSize;
        if (a_minXRange < 0)
            a_minXRange = 0;

        for (int32 i = a_minXRange; i < a_maxXRange; i++)
        {
            for (int32 j = 0; j < this->m_TileAmount * 2; j++)
            {
                int32 index = (i * this->m_TileAmount * 2) + j;
                if (this->m_pTiles[index].Position.Y > a_minYRange&&this->m_pTiles[index].Position.Y < a_maxYRange)
                {
                    float32 angle = 0.0f;
                    if (this->m_pTiles[index].flip)
                        angle = 180.0f * 0.0174532925f;
                    this->m_pTileSprite->Draw(a_pCamera, this->m_pMaterial, this->m_pTiles[index].UVPosition, PuRe_Vector2F(64.0f, 64.0f), this->m_pTiles[index].Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, angle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                    int32 ambientIndex = this->m_pTiles[index].AmbientIndex;
                    int32 towerIndex = this->m_pTiles[index].towerIndex;
                    int32 fallIndex = this->m_pTiles[index].fallIndex;
                    if (towerIndex > -1 && !this->m_Tower[towerIndex].dead)
                    {
                        this->m_pTowerSprite->Draw(a_pCamera, std::to_string(this->m_Tower[towerIndex].Animation).c_str(), this->m_Tower[towerIndex].Position, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector2F(1.0f, 1.0f));
                        //this->m_pFallingSprite->Draw(a_pCamera, PuRe_Vector2F(128.0f, 128.0f), PuRe_Vector2F(32.0f, 32.0f), this->m_Tower[towerIndex].Box.m_Position, this->m_Tower[towerIndex].Box.m_Size, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                    }
                    if (fallIndex > -1 && !this->m_Falling[fallIndex].dead)
                    {
                        this->m_pFallingSprite->Draw(a_pCamera, this->m_pMaterial, PuRe_Vector2F(0.0f, 0.0f), PuRe_Vector2F(256.0f, 256.0f), this->m_Falling[fallIndex].Position, PuRe_Vector3F(256.0f, 256.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                        //this->m_pFallingSprite->Draw(a_pCamera, PuRe_Vector2F(128.0f, 128.0f), PuRe_Vector2F(32.0f, 32.0f), this->m_Falling[fallIndex].Box.m_Position, this->m_Falling[fallIndex].Box.m_Size, PuRe_Vector3F(0.0f, 0.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                    }
                    if (ambientIndex > -1)
                    {
                        angle = 0.0f;
                        if (this->m_Ambient[ambientIndex].flip)
                            angle = 180.0f * 0.0174532925f;
                        this->m_pAmbientSprite->Draw(a_pCamera, this->m_Ambient[ambientIndex].Name.c_str(), this->m_Ambient[ambientIndex].Position, PuRe_Vector3F(0.0f, 0.0f, angle), PuRe_Vector2F(1.0f, 1.0f));
                    }
                    if (this->m_pTiles[index].stoneStartIndex != -1)
                    {
                        for (int32 k = this->m_pTiles[index].stoneStartIndex; k < this->m_pTiles[index].stoneEndIndex; k++)
                        {
                            angle = 0.0f;
                            if (this->m_Stones[k].flip)
                                angle = 180.0f * 0.0174532925f;
                            this->m_pStoneSprite->Draw(a_pCamera, this->m_pMaterial, this->m_Stones[k].UVPosition, PuRe_Vector2F(64.0f, 64.0f), this->m_Stones[k].Position, PuRe_Vector3F(64.0f, 64.0f, 0.0f), PuRe_Vector3F(0.0f, 0.0f, angle), PuRe_Vector3F(0.0f, 0.0f, 0.0f));
                        }
                    }
                }
            }
        }
        this->m_pBackground->Draw(a_pCamera, a_CamPosition, this->m_MinMaxX, this->m_MinMaxY);
    }

}