cbuffer MatrixBuffer
{
	matrix Scale;
	matrix Rotation;
	matrix Translation;
	matrix View;
	matrix Projection;

	float2 UVPosition;
	float2 UVSize;
};
tbuffer textureBuffer
{
	Texture2D Diffuse;
};

SamplerState TextureSampler;


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
  float4 blend = Diffuse.Sample(TextureSampler, input.UV);
  if(blend.a < 0.1)
    discard;
  return Diffuse.Sample(TextureSampler, input.UV);
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
    SetVertexShader(CompileShader(vs_5_0, VS_MAIN()));
    SetGeometryShader(NULL);
    SetPixelShader(CompileShader(ps_5_0, PS_MAIN()));
  }
};