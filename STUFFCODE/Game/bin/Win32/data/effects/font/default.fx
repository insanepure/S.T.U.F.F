float4x4 Scale;
float4x4 Rotation;
float4x4 Translation;
float4x4 View;
float4x4 Projection;

float2 UVPosition;
float2 UVSize;

float Time;
float R;
float G;
float B;
float Gray;

Texture2D Diffuse;

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


VertexShaderOutput VS_MAIN(VertexShaderInput input)
{
  VertexShaderOutput Output = (VertexShaderOutput)0;
  
  float4 pos = float4(input.Position.xyz, 1);

  float4x4 Model = mul(mul(Scale,Rotation),Translation);
  float4x4 MVP = mul(mul(Model,View),Projection);

  Output.Position = mul(pos,MVP);

  float2 NUV = float2((input.UV.x*UVSize.x)+UVPosition.x,(input.UV.y*UVSize.y)+UVPosition.y);

  Output.UV = NUV;

  Output.Color = input.Color;

  Output.Normal = input.Normal;
  
  return Output;
}

float4 PS_MAIN(VertexShaderOutput input) : SV_TARGET
{
  float val = 0;
  if(Time > 0)
    val = (sin(Time*4)+1)/2;

  float4 white = float4(val,val,val,0);
  float4 rgb = float4(R,G,B,0);
  float4 blend = Diffuse.Sample(TextureSampler, input.UV);

  float4 color = blend+white+rgb;


  float greyscale = dot(color.rgb,float3(0.3, 0.59, 0.11));
  float4 colorgrey = float4(greyscale,greyscale,greyscale,color.a);

  if(blend.a < 0.5)
    discard;

  if(Gray > 0.0)
    return colorgrey;
  else
    return color;
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