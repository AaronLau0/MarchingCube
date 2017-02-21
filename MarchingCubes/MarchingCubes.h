
/****************************************************************************

										Marching Cube
											���ߣ�����
		�ƶ��������㷨����Ȼ�Ҳ�֪�������֮'�ƶ�'����ô����....
		��Ȼ1987��ͱ�������SIGGRAPH��666.���ı���Ҳ˵��������
		CT����MRIɨ���в�ȽϺ��ʣ���Ϊ����㷨Ҫ��֪��ĳ���㣨�����嶥�㣩
		�Ƿ���ڡ�������ڲ�������ôֱ����CTͼ�ͺ��ˡ�Ȼ�����ģ��
		Ϊ���ʺ���Ŀ���壬Ҫ���������һ�ѡ���ֵ�����������ؾ����ǣ���
		Ҳ����ÿ������ֻ��ȡֵ0��1������1�ʹ��������ڲ���0���������ⲿ��
		Ȼ������ΪMC�㷨����ÿ��С�����壬Ҫ�ֱ��ж�8�����㶼�Ƿ���
		�����ڲ������ݲ�ͬ��������ܻ����ɲ�ͬ�ĵ�ֵ�棨������������
		�����ֵ��ľ��庬�廹����һ����ԣ���8������������״̬������������ڣ�
		��0��1������һ��2^8=256����������ɵĵ�ֵ����ز�Ҳ������
		256�������Ȼ����˱�̬�������Ҿʹ�VTK��Դ�������˹����á�
		ÿ��TriangleCase�Ͷ�Ӧ��1987�����ĵ���Щ�����е�ı��
		�������㿴ÿ��TriangleCase��������ֶ���0-11֮��ģ�
		

**************************************************************************/


#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "CommonDataStructure.h"

using namespace ParamProtocol;

struct TriangleCase
{
	char index[16];
};

//CT�в㣬�Ѿ������˸��ִ�����ֵ���˵�
struct CTSlice
{
	CTSlice() =delete;
	CTSlice(int pxWidth, int pxHeight) { pixelWidth = pxWidth; pixelHeight = pxHeight; };

	unsigned char GetPixel(int pixelX, int pixelY)
	{
		return bitArray.at(pixelY *pixelWidth + pixelX);
	}

	int pixelWidth;
	int pixelHeight;
	std::vector<unsigned char> bitArray;

};

struct MarchingCubeParam
{
	int cubeCountX; 
	//int cubeCountY = slices -1
	int cubeCountZ;
	float cubeWidth;
	float cubeHeight; 
	float cubeDepth;
};

//Marching Cube �����ؽ���
class MCMeshReconstructor
{
public:

	MCMeshReconstructor();

	//�ļ���ǰ׺,CT��Ƭ����
	bool LoadCTSlicerFromFiles(std::string fileNamePrefix,std::string fileNameSubfix,int sliceStartIndex,int sliceEndIndex,int pixelWidth,int pixelHeight);

	//ע����㷨�õ���XZY�ѿ�������ϵ��Y�ᴹֱ��ˮƽ��
	void Reconstruct(const MarchingCubeParam& mcInfo);

	void GetMesh(std::vector<VECTOR3>& output);

private:

	std::vector<CTSlice>		mCTSlices;//CT��Ƭ
	std::vector<VECTOR3>	mMeshOutput;

	//256��Triangle cases����8�������嶥���״̬ȷ���Ժ�����������������Ƭ����ֵ�棿��
	static const TriangleCase c_MarchingCubeTriangleCase[256];
};