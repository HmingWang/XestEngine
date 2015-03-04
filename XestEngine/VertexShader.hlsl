////--------------------------------------------------------------------------------------
//// Constant Buffer Variables
////--------------------------------------------------------------------------------------
//cbuffer ConstantBuffer : register(b0)
//{
//	matrix World;
//	matrix View;
//	matrix Projection;
//}
//
////--------------------------------------------------------------------------------------
//struct VS_OUTPUT
//{
//	float4 Pos : SV_POSITION;
//	float4 Color : COLOR0;
//};
//
//
////--------------------------------------------------------------------------------------
//// Vertex Shader
////--------------------------------------------------------------------------------------
//VS_OUTPUT main(float4 Pos : POSITION, float4 Color : COLOR)
//{
//	VS_OUTPUT output = (VS_OUTPUT)0;
//	output.Pos = mul(Pos, World);
//	output.Pos = mul(output.Pos, View);
//	output.Pos = mul(output.Pos, Projection);
//	output.Color = Color;
//	return output;
//}







// �洢������ϼ���ͼ�ε��������������Ⱦ���ĳ�����������
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// �����Զ�����ɫ���������ÿ����������ݡ�
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// ͨ��������ɫ�����ݵ�ÿ�����ص���ɫ���ݡ�
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// ������ GPU ��ִ�ж��㴦��ļ���ɫ����
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

		// ������λ��ת��ΪͶӰ�ռ䡣
		pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// �����޸ĵش�����ɫ��
	output.color = input.color;

	return output;
}
