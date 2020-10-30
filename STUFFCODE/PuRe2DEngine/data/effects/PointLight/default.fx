float4x4 InvertViewProjection;

float3 LightPos;
float4 LightColor;
float2 Resolution;
float AttenuationConst;
float AttenuationLin;
float AttenuationExp;

Texture2D NormalMap;
Texture2D DepthMap;

SamplerState TextureSampler
{
  Filter = MIN_MAG_MIP_Linear;
  AddressU = WRAP;
  AddressV = WRAP;
};
struct VertexShaderInput
{
  float3 Position : POSITION0;
  float2 UV       : TEXCOORD0;
  float3 Color    : COLOR0;
  float3 Normal   : NORMAL;
};

struct VertexShaderOutput
{
  float4 Position : SV_POSITION;
  float2 UV       : TEXCOORD0;
  float3 Color    : COLOR0;
  float3 Normal   : NORMAL;
};

struct PixelShaderOutput
{
  float4 color: SV_TARGET0;
};

float2 CalcTexCoord(float4 Position)
{
    return Position.xy / Resolution;
}

float4 CalcPointLight(float3 WorldPosition,float3 LightPosition, float3 Normal)
{
    float3 LightDirection = WorldPosition - LightPosition;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    float DiffuseFactor = dot(Normal, -LightDirection);

    float4 Color = LightColor * DiffuseFactor;
    float Attenuation = AttenuationConst +
                        AttenuationLin * Distance +
                        AttenuationExp * Distance * Distance;

    return Color / Attenuation;
}


VertexShaderOutput VS_MAIN(VertexShaderInput input)
{
  VertexShaderOutput Output = (VertexShaderOutput)0;
  
  float4 pos = float4(input.Position.xyz, 1);

  Output.Position = pos;

  Output.UV = input.UV;

  Output.Color = input.Color;

  Output.Normal = input.Normal;
  
  return Output;
}

PixelShaderOutput PS_MAIN(VertexShaderOutput input)
{
  PixelShaderOutput output;


  float2 TexCoord = CalcTexCoord(input.Position);

  float4 norm = (NormalMap.Sample(TextureSampler, TexCoord)*2)-1;
  float4 depth = DepthMap.Sample(TextureSampler, TexCoord);


  float4 worldpos;

  worldpos.x = TexCoord.x * 2.0f -1.0f;

  worldpos.y = (1.0f-TexCoord.y) * 2.0f -1.0f;

  worldpos.z = depth.r;

  worldpos.w = 1.0f;


  worldpos = mul(worldpos,InvertViewProjection);

  worldpos /= worldpos.w;

  float4 lights = CalcPointLight(worldpos.xyz,LightPos,norm.xyz);

  output.color = lights;

  return output;
}

RasterizerState Culling
{
  CullMode = 1;
};

technique10 Main
{
  pass p0
  {
    SetRasterizerState(Culling);
    SetVertexShader(CompileShader(vs_4_0, VS_MAIN()));
    SetGeometryShader(NULL);
    SetPixelShader(CompileShader(ps_4_0, PS_MAIN()));
   }
};