#include"libs.h"
//1=x,3=z,4=w,5=-x,7=-z,8=-w
//a direction
static void generate_room4D(glm::vec4 position, glm::vec4 scale, const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d, const unsigned int e, const unsigned int f, bool isFloor, bool isGroundReflect,unsigned int groundTextureIndex, glm::vec4 groundColor, unsigned int groundShaderIndex, bool isBaseBoardReflect, unsigned int baseBoardTextureIndex, glm::vec4 baseBoardColor, unsigned int baseBoardShaderIndex, bool isWallReflect, unsigned int wallTextureIndex, glm::vec4 wallColor, unsigned int wallShaderIndex, bool isTopReflect, unsigned int topTextureIndex, glm::vec4 topColor, unsigned int topShaderIndex, std::vector<Wall4D*>* walls4D) {
	if (a != 4 && b != 4&&c!=4&&d!=4&&e!=4&&f!=4) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f)/2.f), glm::vec4(0.f, scale.y / 2.f-0.1f, 0.f, scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f), 0.7f, 0.25f, isWallReflect,wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0.f, 0.05f, 0.f, scale.w / 2.f - 0.005f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	if (a != 8 && b != 8 && c != 8 && d != 8 && e != 8 && f != 8) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0.f, scale.y / 2.f - 0.1f, 0.f, -scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0.f, 0.05f, 0.f, -scale.w / 2.f + 0.005f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	if (a != 3 && b != 3 && c != 3 && d != 3 && e !=3 && f != 3) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w) / 2.f), glm::vec4(0.f, scale.y / 2.f - 0.1f, scale.z / 2.f + 0.1f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w-0.02f) / 2.f), glm::vec4(0.f, 0.05f, scale.z / 2.f - 0.005f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w-0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	if (a != 7 && b != 7 && c != 7 && d != 7 && e != 7 && f != 7) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w) / 2.f), glm::vec4(0.f, scale.y / 2.f - 0.1f, -scale.z / 2.f - 0.1f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0.f, 0.05f, -scale.z / 2.f + 0.005f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f) / 2.f), glm::vec4(0.f, scale.y+0.1f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f), 0.7f, 0.25f, isTopReflect, topTextureIndex,topColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,topShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.2, scale.z, scale.w) / 2.f), glm::vec4(0.f, -0.1f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x, 0.2, scale.z, scale.w), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, groundShaderIndex));
	if (a != 1 && b != 1 && c != 1 && d != 1 && e != 1 && f != 1) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, scale.y + 0.2f, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2.f + 0.1f, scale.y / 2.f - 0.1f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.2f, scale.y + 0.2f, scale.z, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(scale.x / 2.f - 0.005f, 0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	if (a != 5 && b != 5 && c != 5 && d != 5 && e != 5 && f != 5) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2, scale.y + 0.2f, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2.f - 0.1f, scale.y / 2.f - 0.1f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.2, scale.y + 0.2f, scale.z, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(-scale.x / 2.f + 0.005f, 0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
	walls4D->push_back(new Wall4D("AmbientOcclusion", Hypercubecol(glm::vec4()), glm::vec4(0.f, scale.y / 2.f, 0.f, 0.f) + position, alg::bivec4(), scale - glm::vec4(0.001f), 0.f, 0.f, true, GRID, glm::vec4(1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, AMBIENT_OCCLUSION));
}

static void generate_pool4D(glm::vec4 position, glm::vec4 scale,bool isGroundReflect, unsigned int groundTextureIndex, glm::vec4 groundColor, unsigned int groundShaderIndex, bool isWallReflect, unsigned int wallTextureIndex, glm::vec4 wallColor, unsigned int wallShaderIndex, std::vector<Wall4D*> *walls4D) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0.f, -scale.y / 2.f, 0.f, scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0.f, -scale.y / 2.f, 0.f, -scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w) / 2.f), glm::vec4(0.f, -scale.y / 2.f, scale.z / 2.f + 0.1f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w) / 2.f), glm::vec4(0.f, -scale.y / 2.f, -scale.z / 2.f - 0.1f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	    walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f) / 2.f), glm::vec4(0.f, -scale.y-0.1f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, groundShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, scale.y, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2.f + 0.1f, -scale.y / 2.f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.2f, scale.y, scale.z, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2, scale.y, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2.f - 0.1f, -scale.y / 2.f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.2, scale.y, scale.z, scale.w), 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
}
//a=1,x,b=0 Pos fit with a room,b=1 Pos not fit with a room
static void generate_door4D(glm::vec4 position, glm::vec4 scale, glm::vec4 door,glm::vec2 doorScale, const unsigned int a, const unsigned int b, bool isFloor, const float floorThickness, bool isGroundReflect, unsigned int groundTextureIndex, glm::vec4 groundColor, unsigned int groundShaderIndex, bool isBaseBoardReflect, unsigned int baseBoardTextureIndex,glm::vec4 baseBoardColor, unsigned int baseBoardShaderIndex, bool isFrame,bool isFrameReflect, unsigned int frameTextureIndex, glm::vec4 frameColor, unsigned int frameShaderIndex, bool isWallReflect, unsigned int wallTextureIndex, glm::vec4 wallColor, unsigned int wallShaderIndex, std::vector<Wall4D*> *walls4D) {
	const float doorSize(doorScale.x);
	const float doorHeight(doorScale.y + floorThickness);
	float doorSize2,doorSize3, doorHeight2;
	const float frameScale(0.07f);
	const float frameThickness(0.0125f);
	int a2,c, d,sign;
	float offset, baseBoardOffset, baseBoardThickness;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5,framePos1, framePos2, framePos3, framePos4, framePos5,baseBoardPos1, baseBoardPos2, baseBoardPos3, baseBoardPos4;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, frameScale1, frameScale2, frameScale3, frameScale4, frameScale5, baseBoardScale1, baseBoardScale2, baseBoardScale3, baseBoardScale4;
		if (a == 1||a==5) 
		{
			a2=0.f,c = 2,d=3;
		}
		if (a == 3||a==7)
		{
			a2=2,c = 0.f, d = 3;
		}
		if (a == 4||a==8)
		{
			a2=3,c = 2, d = 0;
		}
		if (a == 1 || a == 3 || a == 4) {
			sign = 1;
		}
		if (a == 5 || a == 7 || a == 8) {
			sign = -1;
		}
		if (b == 0.f) {
			offset = sign * (scale[a2] / 2.f+0.1f);
			if (isFloor)
			{
				baseBoardOffset = -sign * 0.105f;
				baseBoardThickness = 0.01f;
			}
		}
		if (b == 1) {
			offset = 0.f;
			if (isFloor)
			{
				baseBoardOffset = 0.f;
				baseBoardThickness = 0.22f;
			}
		}

		if (isFrame)
		{
			doorSize2 = doorSize + 0.02f;
			doorSize3 = doorSize + 2.f * frameScale;
			doorHeight2 = doorHeight + 0.01f;
		}
		else {
			doorSize2 = doorSize;
			if(b==0.f)
			doorSize3 = doorSize;
			if(b==1)
			doorSize3 = doorSize - 2.f * frameThickness;
			doorHeight2 = doorHeight;
		}
		wallPos1[a2] = offset,wallPos1[1] = scale[1] / 2.f - 0.1f,wallPos1[c]=0.f, wallPos1[d]= scale[d] / 4 + door[d] / 2.f + doorSize2 / 4.f;
		wallPos2[a2] = offset, wallPos2[1] = scale[1] / 2.f - 0.1f, wallPos2[c] = 0.f, wallPos2[d] = -scale[d] / 4 + door[d] / 2.f - doorSize2 / 4.f;
		wallPos3[a2] = offset, wallPos3[1] = scale[1] / 2.f + (doorHeight2) / 2.f, wallPos3[c] = door[c], wallPos3[d] =door[d];
		wallPos4[a2] = offset, wallPos4[1] = scale[1] / 2.f - 0.1f, wallPos4[c] = scale[c] / 4 + door[c] / 2.f + doorSize2 / 4.f, wallPos4[d] = door[d];
		wallPos5[a2] = offset, wallPos5[1] = scale[1] / 2.f - 0.1f, wallPos5[c] = -scale[c] / 4 + door[c] / 2.f - doorSize2 / 4.f, wallPos5[d] = door[d];
		wallScale1[a2] = 0.2f, wallScale1[1] = scale[1] + 0.2f, wallScale1[c] = scale[c], wallScale1[d] = scale[d] / 2.f - door[d] - doorSize2 / 2.f;
		wallScale2[a2] = 0.2f, wallScale2[1] = scale[1] + 0.2f, wallScale2[c] = scale[c], wallScale2[d] = scale[d] / 2.f + door[d] - doorSize2 / 2.f;
		wallScale3[a2] = 0.2f, wallScale3[1] = scale[1] - (doorHeight2), wallScale3[c] = doorSize2, wallScale3[d] = doorSize2;
		wallScale4[a2] = 0.2f, wallScale4[1] = scale[1] + 0.2f, wallScale4[c] = scale[c] / 2.f - door[c] - doorSize2 / 2.f, wallScale4[d] = doorSize2;
		wallScale5[a2] = 0.2f, wallScale5[1] = scale[1] + 0.2f, wallScale5[c] = scale[c] / 2.f + door[c] - doorSize2 / 2.f, wallScale5[d] = doorSize2;
		if (isFrame)
		{
			framePos1[a2] = offset, framePos1[1] = (doorHeight+floorThickness) / 2.f, framePos1[c] = door[c] - doorSize / 2.f - frameScale/2.f, framePos1[d] = door[d];
			framePos2[a2] = offset, framePos2[1] = (doorHeight+floorThickness) / 2.f, framePos2[c] = door[c] + doorSize / 2.f + frameScale/2.f, framePos2[d] = door[d];
			framePos3[a2] = offset, framePos3[1] = doorHeight + frameScale/2.f, framePos3[c] = door[c], framePos3[d] = door[d];
			framePos4[a2] = offset, framePos4[1] = (doorHeight+floorThickness) / 2.f, framePos4[c] = door[c], framePos4[d] = door[d] - doorSize / 2.f - frameScale/2.f;
			framePos5[a2] = offset, framePos5[1] = (doorHeight+floorThickness) / 2.f, framePos5[c] = door[c], framePos5[d] = door[d] + doorSize / 2.f + frameScale/2.f;
			frameScale1[a2] = 0.2f+2.f*frameThickness, frameScale1[1] = doorHeight-floorThickness, frameScale1[c] = frameScale, frameScale1[d] = doorSize + 2.f*frameScale;
			frameScale2[a2] = 0.2f+2.f*frameThickness, frameScale2[1] = doorHeight-floorThickness, frameScale2[c] = frameScale, frameScale2[d] = doorSize + 2.f*frameScale;
			frameScale3[a2] = 0.2f+2.f*frameThickness, frameScale3[1] = frameScale, frameScale3[c] = doorSize + 2.f*frameScale, frameScale3[d] = doorSize + 2.f* frameScale;
			frameScale4[a2] = 0.2f+2.f*frameThickness, frameScale4[1] = doorHeight-floorThickness, frameScale4[c] = doorSize, frameScale4[d] = frameScale;
			frameScale5[a2] = 0.2f+2.f*frameThickness, frameScale5[1] = doorHeight-floorThickness, frameScale5[c] = doorSize, frameScale5[d] = frameScale;
		}
		if (isFloor)
		{
			baseBoardPos1[a2] = offset + baseBoardOffset, baseBoardPos1[1] = 0.05f + floorThickness, baseBoardPos1[c] = 0.f, baseBoardPos1[d] = scale[d] / 4 + door[d] / 2.f + doorSize3 / 4.f;
			baseBoardPos2[a2] = offset + baseBoardOffset, baseBoardPos2[1] = 0.05f + floorThickness, baseBoardPos2[c] = 0.f, baseBoardPos2[d] = -scale[d] / 4 + door[d] / 2.f - doorSize3 / 4.f;
			baseBoardPos3[a2] = offset + baseBoardOffset, baseBoardPos3[1] = 0.05f + floorThickness, baseBoardPos3[c] = scale[c] / 4 + door[c] / 2.f + doorSize3 / 4.f, baseBoardPos3[d] = door[d];
			baseBoardPos4[a2] = offset + baseBoardOffset, baseBoardPos4[1] = 0.05f + floorThickness, baseBoardPos4[c] = -scale[c] / 4 + door[c] / 2.f - doorSize3 / 4.f, baseBoardPos4[d] = door[d];
			baseBoardScale1[a2] = baseBoardThickness, baseBoardScale1[1] = 0.1f, baseBoardScale1[c] = scale[c], baseBoardScale1[d] = scale[d] / 2.f - door[d] - doorSize3 / 2.f;
			baseBoardScale2[a2] = baseBoardThickness, baseBoardScale2[1] = 0.1f, baseBoardScale2[c] = scale[c], baseBoardScale2[d] = scale[d] / 2.f + door[d] - doorSize3 / 2.f;
			baseBoardScale3[a2] = baseBoardThickness, baseBoardScale3[1] = 0.1f, baseBoardScale3[c] = scale[c] / 2.f - door[c] - doorSize3 / 2.f, baseBoardScale3[d] = doorSize3;
			baseBoardScale4[a2] = baseBoardThickness, baseBoardScale4[1] = 0.1f, baseBoardScale4[c] = scale[c] / 2.f + door[c] - doorSize3 / 2.f, baseBoardScale4[d] = doorSize3;
		}
			
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,wallShaderIndex));
			
			if (b == 0.f) {
				glm::vec4 groundPos, groundScale;
				groundPos[a2] = offset- sign * 0.05f, groundPos[1] = -0.1f, groundPos[c] = door[c], groundPos[d] = door[d];
				groundScale[a2] = 0.1f, groundScale[1] = 0.2f, groundScale[c] = doorSize2, groundScale[d] = doorSize2;
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(groundScale / 2.f), groundPos + position, alg::bivec4(), groundScale, 0.7f, 0.25f, isGroundReflect, groundTextureIndex, groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, groundShaderIndex));
			}

			if (isFrame)
			{
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale1/2.f), framePos1 + position, alg::bivec4(), frameScale1, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale2/2.f), framePos2 + position, alg::bivec4(), frameScale2, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale3/2.f), framePos3 + position, alg::bivec4(), frameScale3, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale4/2.f), framePos4 + position, alg::bivec4(), frameScale4, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale5/2.f), framePos5 + position, alg::bivec4(), frameScale5, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
			}
			
			if (isFloor)
			{
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale1 / 2.f), baseBoardPos1 + position, alg::bivec4(), baseBoardScale1, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex, baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale2 / 2.f), baseBoardPos2 + position, alg::bivec4(), baseBoardScale2, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex, baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale3 / 2.f), baseBoardPos3 + position, alg::bivec4(), baseBoardScale3, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex, baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale4 / 2.f), baseBoardPos4 + position, alg::bivec4(), baseBoardScale4, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex, baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
			}
}
//b=0 Pos fit with a room,b=1 Pos not fit with a room
static void generate_window4D(glm::vec4 position, glm::vec4 scale, glm::vec4 windowPos, glm::vec2 windowScale, const unsigned int a, const unsigned int b,bool isFloor, const float floorThickness, bool isBaseBoardReflect,unsigned int baseBoardTextureIndex, glm::vec4 baseBoardColor, unsigned int baseBoardShaderIndex, bool isFrame, bool isFrameReflect,unsigned int frameTextureIndex, glm::vec4 frameColor, unsigned int frameShaderIndex, bool isWindowReflect, unsigned int windowTextureIndex, glm::vec4 windowColor, unsigned int windowShader, bool isWallReflect, unsigned int wallTextureIndex, glm::vec4 wallColor, unsigned int wallShaderIndex, std::vector<Wall4D*> *walls4D) {
	const float windowSize(windowScale.x);
	const float windowHeight(windowScale.y);
	float windowSize2, windowHeight2;
	const float frameScale(0.03f);
	const float frameThickness(0.0125);
	int a2, c, d, sign;
	float offset, baseBoardOffset, baseBoardThickness;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5, wallPos6, framePos1, framePos2, framePos3, framePos4, framePos5, framePos6, baseBoardPos,glassPos;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, wallScale6,frameScale1, frameScale2, frameScale3, frameScale4, frameScale5, frameScale6, baseBoardScale,glassScale;
	if (a == 1 || a == 5)
	{
		a2 = 0.f, c = 2, d = 3;
	}
	if (a == 3 || a == 7)
	{
		a2 = 2, c = 0.f, d = 3;
	}
	if (a == 4 || a == 8)
	{
		a2 = 3, c = 2, d = 0;
	}
	if (a == 1 || a == 3 || a == 4) {
		sign = 1;
	}
	if (a == 5 || a == 7 || a == 8) {
		sign = -1;
	}
	if (b == 0.f) {
		offset = sign * (scale[a2] / 2.f + 0.1f);
		if (isFloor) {
			baseBoardOffset = -sign * 0.105f;
			baseBoardThickness = 0.01f;
		}
	}
	if (b == 1) {
		offset = 0.f;
		if (isFloor)
		{
			baseBoardOffset = 0.f;
			baseBoardThickness = 0.22f;
		}
	}
	if (isFrame)
	{
		windowSize2 = windowSize + 0.02f;
		windowHeight2 = windowHeight + 0.01f;
	}
	else
	{
		windowSize2 = windowSize;
		windowHeight2 = windowHeight;
	}
	wallPos1[a2] = offset, wallPos1[1] = scale[1] / 2.f - 0.1f, wallPos1[c] = 0.f, wallPos1[d] = scale[d] / 4 + windowPos[d] / 2.f +windowSize2 / 4.f;
	wallPos2[a2] = offset, wallPos2[1] = scale[1] / 2.f - 0.1f, wallPos2[c] = 0.f, wallPos2[d] = -scale[d] / 4 + windowPos[d] / 2.f -windowSize2 / 4.f;
	wallPos3[a2] = offset, wallPos3[1] = scale[1] / 2.f + (windowPos[1]+ windowHeight2 /2.f+ floorThickness) / 2.f, wallPos3[c] = windowPos[c], wallPos3[d] = windowPos[d];
	wallPos4[a2] = offset, wallPos4[1] = (windowPos[1] - 0.2f - windowHeight2/2.f+ floorThickness) / 2.f, wallPos4[c] = windowPos[c], wallPos4[d] = windowPos[d];
	wallPos5[a2] = offset, wallPos5[1] = scale[1] / 2.f - 0.1f, wallPos5[c] = scale[c] / 4 + windowPos[c] / 2.f +windowSize2 / 4.f, wallPos5[d] = windowPos[d];
	wallPos6[a2] = offset, wallPos6[1] = scale[1] / 2.f - 0.1f, wallPos6[c] = -scale[c] / 4 + windowPos[c] / 2.f -windowSize2 / 4.f, wallPos6[d] = windowPos[d];
	wallScale1[a2] = 0.2f, wallScale1[1] = scale[1] + 0.2f, wallScale1[c] = scale[c], wallScale1[d] = scale[d] / 2.f - windowPos[d] -windowSize2 / 2.f;
	wallScale2[a2] = 0.2f, wallScale2[1] = scale[1] + 0.2f, wallScale2[c] = scale[c], wallScale2[d] = scale[d] / 2.f + windowPos[d] -windowSize2 / 2.f;
	wallScale3[a2] = 0.2f, wallScale3[1] = scale[1] - (windowPos[1] + windowHeight2 /2.f+ floorThickness), wallScale3[c] =windowSize2, wallScale3[d] =windowSize2;
	wallScale4[a2] = 0.2f, wallScale4[1] = windowPos[1] + 0.2f - windowHeight2 / 2.f+ floorThickness, wallScale4[c] =windowSize2, wallScale4[d] =windowSize2;
	wallScale5[a2] = 0.2f, wallScale5[1] = scale[1] + 0.2f, wallScale5[c] = scale[c] / 2.f - windowPos[c] -windowSize2 / 2.f, wallScale5[d] =windowSize2;
	wallScale6[a2] = 0.2f, wallScale6[1] = scale[1] + 0.2f, wallScale6[c] = scale[c] / 2.f + windowPos[c] -windowSize2 / 2.f, wallScale6[d] =windowSize2;

	if (isFrame)
	{
		framePos1[a2] = offset, framePos1[1] = windowPos[1]+floorThickness, framePos1[c] = windowPos[c] - windowSize / 2.f - frameScale/2.f, framePos1[d] = windowPos[d];
		framePos2[a2] = offset, framePos2[1] = windowPos[1]+floorThickness, framePos2[c] = windowPos[c] + windowSize / 2.f + frameScale/2.f, framePos2[d] = windowPos[d];
		framePos3[a2] = offset, framePos3[1] = windowHeight / 2.f + windowPos[1] + frameScale/2.f+ floorThickness, framePos3[c] = windowPos[c], framePos3[d] = windowPos[d];
		framePos4[a2] = offset, framePos4[1] = -windowHeight / 2.f + windowPos[1] - frameScale/2.f+ floorThickness, framePos4[c] = windowPos[c], framePos4[d] = windowPos[d];
		framePos5[a2] = offset, framePos5[1] = windowPos[1]+floorThickness, framePos5[c] = windowPos[c], framePos5[d] = windowPos[d] - windowSize / 2.f - frameScale/2.f;
		framePos6[a2] = offset, framePos6[1] = windowPos[1]+floorThickness, framePos6[c] = windowPos[c], framePos6[d] = windowPos[d] + windowSize / 2.f + frameScale/2.f;
		frameScale1[a2] = 0.2f+2.f*frameThickness, frameScale1[1] = windowHeight, frameScale1[c] = frameScale, frameScale1[d] = windowSize + 2.f*frameScale;
		frameScale2[a2] = 0.2f+2.f*frameThickness, frameScale2[1] = windowHeight, frameScale2[c] = frameScale, frameScale2[d] = windowSize + 2.f*frameScale;
		frameScale3[a2] = 0.2f+2.f*frameThickness, frameScale3[1] = frameScale, frameScale3[c] = windowSize + 2.f*frameScale, frameScale3[d] = windowSize + 2.f*frameScale;
		frameScale4[a2] = 0.2f+2.f*frameThickness, frameScale4[1] = frameScale, frameScale4[c] = windowSize + 2.f*frameScale, frameScale4[d] = windowSize + 2.f*frameScale;
		frameScale5[a2] = 0.2f+2.f*frameThickness, frameScale5[1] = windowHeight, frameScale5[c] = windowSize + 2.f*frameScale, frameScale5[d] = frameScale;
		frameScale6[a2] = 0.2f+2.f*frameThickness, frameScale6[1] = windowHeight, frameScale6[c] = windowSize + 2.f*frameScale, frameScale6[d] = frameScale;
	}

	glassPos[a2] = offset, glassPos[1] = windowPos[1]+ floorThickness, glassPos[c] = windowPos[c] , glassPos[d] = windowPos[d];
	glassScale[a2]= 0.02f, glassScale[1]= windowHeight, glassScale[c]= windowSize, glassScale[d] = windowSize;
	if (isFloor) {
		baseBoardPos[a2] = offset + baseBoardOffset, baseBoardPos[1] = 0.05f + floorThickness, baseBoardPos[c] = 0.f, baseBoardPos[d] = 0;
		baseBoardScale[a2] = baseBoardThickness, baseBoardScale[1] = 0.1f, baseBoardScale[c] = scale[c], baseBoardScale[d] = scale[d];
	}

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale6 / 2.f), wallPos6 + position, alg::bivec4(), wallScale6, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));

	if (isFrame)
	{
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale1/2.f), framePos1 + position, alg::bivec4(), frameScale1, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale2/2.f), framePos2 + position, alg::bivec4(), frameScale2, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale3/2.f), framePos3 + position, alg::bivec4(), frameScale3, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale4/2.f), framePos4 + position, alg::bivec4(), frameScale4, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale5/2.f), framePos5 + position, alg::bivec4(), frameScale5, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale6/2.f), framePos6 + position, alg::bivec4(), frameScale6, 0.7f, 0.25f, isFrameReflect, frameTextureIndex, frameColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, frameShaderIndex));
	}

	walls4D->push_back(new Wall4D("Glass4D", Hypercube(glassScale / 2.f), glassPos + position, alg::bivec4(), glassScale, 0.7f, 0.25f, isWindowReflect, windowTextureIndex, windowColor, glm::vec4(1.f,1.f,1.f,0.5f), BOX4D, windowShader));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale / 2.f), baseBoardPos + position, alg::bivec4(), baseBoardScale, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
}

static void generate_walkway4D(glm::vec4 position, glm::vec4 scale, const unsigned int a, bool isFloor,bool isGroundReflect, unsigned int groundTextureIndex, glm::vec4 groundColor, unsigned int groundShaderIndex, bool isBaseBoardReflect, unsigned int baseBoardTextureIndex, glm::vec4 baseBoardColor, unsigned int baseBoardShaderIndex, bool isWallReflect,unsigned int wallTextureIndex,glm::vec4 wallColor, unsigned int wallShaderIndex, bool isTopReflect,unsigned int topTextureIndex, glm::vec4 topColor, unsigned int topShaderIndex, std::vector<Wall4D*> *walls4D) {
	
	int a2, c, d;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5, wallPos6,baseBoardPos1, baseBoardPos2, baseBoardPos3, baseBoardPos4;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, wallScale6, baseBoardScale1, baseBoardScale2, baseBoardScale3, baseBoardScale4;

	if (a == 1)
	{
		a2 = 0.f, c = 2, d = 3;
	}
	if (a == 3)
	{
		a2 = 2, c = 0.f, d = 3;
	}
	if (a == 4)
	{
		a2 = 3, c = 2, d = 0;
	}

	wallPos1[a2] = 0.f, wallPos1[1] = scale[1] / 2.f-0.1f, wallPos1[c] = scale[c] / 2.f+0.1f, wallPos1[d] = 0;
	wallPos2[a2] = 0.f, wallPos2[1] = scale[1] / 2.f-0.1f, wallPos2[c] = -scale[c] / 2.f-0.1f, wallPos2[d] = 0;
	wallPos3[a2] = 0.f, wallPos3[1] = scale[1]+0.1f , wallPos3[c] = 0.f, wallPos3[d] = 0;
	wallPos4[a2] = 0.f, wallPos4[1] = -0.1f, wallPos4[c] = 0.f, wallPos4[d] = 0;
	wallPos5[a2] = 0.f, wallPos5[1] = scale[1] / 2.f-0.1f, wallPos5[c] = 0.f, wallPos5[d] = scale[d] / 2.f+0.1f;
	wallPos6[a2] = 0.f, wallPos6[1] = scale[1] / 2.f-0.1f, wallPos6[c] = 0.f, wallPos6[d] = -scale[d] / 2.f-0.1f;

	wallScale1[a2] = scale[a2] , wallScale1[1] = scale[1] +0.2f, wallScale1[c] = 0.2f, wallScale1[d] = scale[d] ;
	wallScale2[a2] = scale[a2] , wallScale2[1] = scale[1] +0.2f, wallScale2[c] = 0.2f, wallScale2[d] = scale[d] ;
	wallScale3[a2] = scale[a2] , wallScale3[1] = 0.2f, wallScale3[c] = scale[c] + 0.4f, wallScale3[d] = scale[d] + 0.4f;
	wallScale4[a2] = scale[a2] , wallScale4[1] = 0.2f, wallScale4[c] = scale[c] , wallScale4[d] = scale[d] ;
	wallScale5[a2] = scale[a2] , wallScale5[1] = scale[1] +0.2f, wallScale5[c] = scale[c]+0.4f , wallScale5[d] = 0.2f;
	wallScale6[a2] = scale[a2] , wallScale6[1] = scale[1] +0.2f, wallScale6[c] = scale[c]+0.4f , wallScale6[d] = 0.2f;

	baseBoardPos1[a2] = 0.f, baseBoardPos1[1] = 0.05f, baseBoardPos1[c] = scale[c] / 2.f - 0.005f,baseBoardPos1[d] = 0;
	baseBoardPos2[a2] = 0.f, baseBoardPos2[1] = 0.05f, baseBoardPos2[c] = -scale[c] / 2.f + 0.005f, baseBoardPos2[d] = 0;
	baseBoardPos3[a2] = 0.f, baseBoardPos3[1] = 0.05f, baseBoardPos3[c] = 0.f, baseBoardPos3[d] = scale[d] / 2.f - 0.005f;
	baseBoardPos4[a2] = 0.f, baseBoardPos4[1] = 0.05f, baseBoardPos4[c] = 0.f, baseBoardPos4[d] = -scale[d] / 2.f + 0.005f;

	baseBoardScale1[a2] = scale[a2], baseBoardScale1[1] = 0.1f, baseBoardScale1[c] = 0.01f, baseBoardScale1[d] = scale[d];
	baseBoardScale2[a2] = scale[a2], baseBoardScale2[1] = 0.1f, baseBoardScale2[c] = 0.01f, baseBoardScale2[d] = scale[d];
	baseBoardScale3[a2] = scale[a2], baseBoardScale3[1] = 0.1f, baseBoardScale3[c] = scale[c], baseBoardScale3[d] = 0.01f;
	baseBoardScale4[a2] = scale[a2], baseBoardScale4[1] = 0.1f, baseBoardScale4[c] = scale[c], baseBoardScale4[d] = 0.01f;

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 0.7f, 0.25f, isTopReflect, topTextureIndex,topColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, topShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale6 / 2.f), wallPos6 + position, alg::bivec4(), wallScale6, 0.7f, 0.25f, isWallReflect, wallTextureIndex,wallColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, wallShaderIndex));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale1 / 2.f), baseBoardPos1 + position, alg::bivec4(), baseBoardScale1, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale2 / 2.f), baseBoardPos2 + position, alg::bivec4(), baseBoardScale2, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale3 / 2.f), baseBoardPos3 + position, alg::bivec4(), baseBoardScale3, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale4 / 2.f), baseBoardPos4 + position, alg::bivec4(), baseBoardScale4, 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
}

static void generate_steps4D(glm::vec4 startPos, glm::vec4 endPos,glm::vec4 scale, const unsigned int a, const unsigned int steps, bool isReflect,size_t texture3DIndex, std::vector<Wall4D*> *walls4D, unsigned int shaderIndex) {
	glm::vec4 offset;
	for (size_t i(0.f);i < steps;i++) {
		if (a == 1) {
			offset = glm::vec4(scale.x/2.f, scale.y / 2.f,0.f,0.f);
		}
		if (a == 3) {
			offset = glm::vec4(0.f, scale.y / 2.f, scale.z / 2.f, 0.f);
		}
		if (a == 4) {
			offset = glm::vec4(0.f, scale.y / 2.f, 0.f, scale.w / 2.f);
		}
		if (a == 5) {
			offset = glm::vec4(-scale.x / 2.f, scale.y / 2.f, 0.f, 0.f);
		}
		if (a == 7) {
			offset = glm::vec4(0.f, scale.y / 2.f, -scale.z / 2.f, 0.f);
		}
		if (a == 8) {
			offset = glm::vec4(0.f, scale.y / 2.f, 0.f, -scale.w / 2.f);
		}
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(scale / 2.f), mix(startPos+ offset, endPos- offset, (float)i / (float)(steps - 1)), alg::bivec4(), scale, 0.7f, 0.25f, isReflect, texture3DIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), STEP4D, shaderIndex));
	}
}

static void generate_floor4D(glm::vec4 pos, glm::vec4 scale, glm::vec4 holePos, glm::vec4 holeSize,bool isFloor, bool isCeilReflect,unsigned int ceilTextureIndex,glm::vec4 ceilColor, unsigned int ceilShaderIndex, bool isGroundReflect, unsigned int groundTextureIndex, glm::vec4 groundColor, unsigned int groundShaderIndex, bool isBaseBoardReflect, unsigned int baseBoardTextureIndex, glm::vec4 baseBoardColor, unsigned int baseBoardShaderIndex, std::vector<Wall4D*> *walls4D)
{
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.01f, scale.z / 2.f + holePos.z - holeSize.z / 2.f, holeSize.w) / 2.f), glm::vec4(0.f, 0.095f, holePos.z - holeSize.z / 2.f - (scale.z / 2.f + holePos.z - holeSize.z / 2.f) / 2.f, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.01f, scale.z / 2.f + holePos.z - holeSize.z / 2.f, holeSize.w), 0.7f, 0.25f, isGroundReflect,groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.01f, scale.z / 2.f - holePos.z - holeSize.z / 2.f, holeSize.w) / 2.f), glm::vec4(0.f, 0.095f, holePos.z + holeSize.z / 2.f + (scale.z / 2.f - holePos.z - holeSize.z / 2.f) / 2.f, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.01f, scale.z / 2.f - holePos.z - holeSize.z / 2.f, holeSize.w), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2.f - holePos.x - holeSize.x / 2.f, 0.01f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x + holeSize.x / 2.f + (scale.x / 2.f - holePos.x - holeSize.x / 2.f) / 2.f, 0.095f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2.f - holePos.x - holeSize.x / 2.f, 0.01f, holeSize.z, holeSize.w), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2.f + holePos.x - holeSize.x / 2.f, 0.01f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x - holeSize.x / 2.f - (scale.x / 2.f + holePos.x - holeSize.x / 2.f) / 2.f, 0.095f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2.f + holePos.x - holeSize.x / 2.f, 0.01f, holeSize.z, holeSize.w), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.01f, scale.z, scale.w / 2.f - holePos.w - holeSize.w / 2.f) / 2.f), glm::vec4(0.f, 0.095f, 0.f, holePos.w + holeSize.w / 2.f + (scale.w / 2.f - holePos.w - holeSize.w / 2.f) / 2.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.01f, scale.z, scale.w / 2.f - holePos.w - holeSize.w / 2.f), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.01f, scale.z, scale.w / 2.f + holePos.w - holeSize.w / 2.f) / 2.f), glm::vec4(0.f, 0.095f, 0.f, holePos.w - holeSize.w / 2.f - (scale.w / 2.f + holePos.w - holeSize.w / 2.f) / 2.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.01f, scale.z, scale.w / 2.f + holePos.w - holeSize.w / 2.f), 0.7f, 0.25f, isGroundReflect, groundTextureIndex,groundColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,groundShaderIndex));

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.19f, scale.z / 2.f + holePos.z - holeSize.z / 2.f, holeSize.w) / 2.f), glm::vec4(0.f, -0.005f, holePos.z - holeSize.z / 2.f - (scale.z / 2.f + holePos.z - holeSize.z / 2.f) / 2.f, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.19f, scale.z / 2.f + holePos.z - holeSize.z / 2.f, holeSize.w), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.19f, scale.z / 2.f - holePos.z - holeSize.z / 2.f, holeSize.w) / 2.f), glm::vec4(0.f, -0.005f, holePos.z + holeSize.z / 2.f + (scale.z / 2.f - holePos.z - holeSize.z / 2.f) / 2.f, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.19f, scale.z / 2.f - holePos.z - holeSize.z / 2.f, holeSize.w), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2.f - holePos.x - holeSize.x / 2.f, 0.19f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x + holeSize.x / 2.f + (scale.x / 2.f - holePos.x - holeSize.x / 2.f) / 2.f, -0.005f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2.f - holePos.x - holeSize.x / 2.f, 0.19f, holeSize.z, holeSize.w), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2.f + holePos.x - holeSize.x / 2.f, 0.19f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x - holeSize.x / 2.f - (scale.x / 2.f + holePos.x - holeSize.x / 2.f) / 2.f, -0.005f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2.f + holePos.x - holeSize.x / 2.f, 0.19f, holeSize.z, holeSize.w), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.19f, scale.z, scale.w / 2.f - holePos.w - holeSize.w / 2.f) / 2.f), glm::vec4(0.f, -0.005f, 0.f, holePos.w + holeSize.w / 2.f + (scale.w / 2.f - holePos.w - holeSize.w / 2.f) / 2.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.19f, scale.z, scale.w / 2.f - holePos.w - holeSize.w / 2.f), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.19f, scale.z, scale.w / 2.f + holePos.w - holeSize.w / 2.f) / 2.f), glm::vec4(0.f, -0.005f, 0.f, holePos.w - holeSize.w / 2.f - (scale.w / 2.f + holePos.w - holeSize.w / 2.f) / 2.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.19f, scale.z, scale.w / 2.f + holePos.w - holeSize.w / 2.f), 0.7f, 0.25f, isCeilReflect, ceilTextureIndex,ceilColor,glm::vec4(1.f,1.f,1.f,0.f), BOX4D,ceilShaderIndex));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(scale.x / 2.f - 0.005f, 0.15f, 0.f, 0.f) + pos, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f),NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(-scale.x / 2.f + 0.005f, 0.15f, 0.f, 0.f) + pos, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0.f, 0.15f, scale.z / 2.f - 0.005f, 0.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f),NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0.f, 0.15f, -scale.z / 2.f + 0.005f, 0.f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0.f, 0.15f, 0.f, scale.w / 2.f - 0.005f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f),NONE, baseBoardShaderIndex));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0.f, 0.15f, 0.f, -scale.w / 2.f + 0.005f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 0.7f, 0.25f, isBaseBoardReflect, baseBoardTextureIndex,baseBoardColor,glm::vec4(1.f,1.f,1.f,0.f), NONE, baseBoardShaderIndex));
	}
}

static void generate_table4D(glm::vec4 position, glm::vec4 scale, float height, bool isTopReflect,unsigned int topTextureIndex, bool isLagReflect, unsigned int lagTextureIndex, std::vector<Wall4D*> *walls4D, unsigned int shaderIndex)
{
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.04, scale.z, scale.w) / 2.f), glm::vec4(0.f, height, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x, 0.04, scale.z, scale.w), 0.7f, 0.25f, isTopReflect,topTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, scale.z / 2.f - 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, scale.z / 2.f - 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, scale.z / 2.f - 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, scale.z / 2.f - 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE,shaderIndex));
}
static void generate_pool_table4D(glm::vec4 position, glm::vec4 scale, float height, bool isFrameReflect, unsigned int framecolor, bool isTopReflect, unsigned int topTextureIndex, bool isLagReflect, unsigned int lagTextureIndex, std::vector<Wall4D*> *walls4D, unsigned int shaderIndex)
{

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.04f, 0.04f, scale.z + 0.04f, scale.w + 0.04f) / 2.f), glm::vec4(0.f, height, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.04f, 0.04f, scale.z + 0.04f, scale.w + 0.04f), 0.f, 0.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0.f, height+0.01f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x, 0.04f, scale.z, scale.w), 0.f, 0.f, isTopReflect, topTextureIndex,glm::vec4(0.5f, 1.25f, 0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), BOX4D, shaderIndex));

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.025f, 0.1f, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2.f + 0.0125f, height + 0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.025f, 0.1f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.025f, 0.1f, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2.f - 0.0125f, height + 0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.025f, 0.1f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w) / 2.f), glm::vec4(0.f, height + 0.05f, scale.z / 2.f + 0.0125f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w) / 2.f), glm::vec4(0.f, height + 0.05f, -scale.z / 2.f - 0.0125f, 0.f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f) / 2.f), glm::vec4(0.f, height + 0.05f, 0.f, scale.w / 2.f + 0.0125f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f) / 2.f), glm::vec4(0.f, height + 0.05f, 0.f, -scale.w / 2.f - 0.0125f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f), 0.f, 1.f, isTopReflect, topTextureIndex,glm::vec4(0.5f,1.25f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)) / 2.f), glm::vec4((scale.x+0.05f)  / 2.f + 0.02f, height+0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)) / 2.f), glm::vec4(-(scale.x+0.05f) / 2.f - 0.02f, height + 0.05f, 0.f, 0.f) + position, alg::bivec4(), glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)) / 2.f), glm::vec4(0.f, height + 0.05f, (scale.z+0.05f) / 2.f + 0.02f, 0.f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)) / 2.f), glm::vec4(0.f, height + 0.05f, -(scale.z+0.05f) / 2.f - 0.02f, 0.f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f) / 2.f), glm::vec4(0.f, height + 0.05f, 0.f, (scale.w+0.05f) / 2.f + 0.02f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f) / 2.f), glm::vec4(0.f, height + 0.05f, 0.f, -(scale.w+0.05f) / 2.f - 0.02f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f), 0.f, 1.f, isFrameReflect, framecolor,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));

	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, scale.z / 2.f - 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(0.f,0.f,0.f,90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f),NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, scale.z / 2.f - 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, scale.w / 2.f - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, scale.z / 2.f - 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f),NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, scale.z / 2.f - 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2.f - 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2.f + 0.1f, height / 2.f, -scale.z / 2.f + 0.1f, -scale.w / 2.f + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 0.7f, 0.25f, isLagReflect, lagTextureIndex,glm::vec4(1.f,0.75f,0.5f,1.f),glm::vec4(1.f,1.f,1.f,0.f), NONE, shaderIndex));

	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, scale.z / 2.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, scale.z / 2.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, -scale.z / 2.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, -scale.z / 2.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, scale.z / 2.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, scale.z / 2.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, -scale.z / 2.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, -scale.z / 2.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, 0.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, 0.f, scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(scale.x / 2.f, height + 0.02f, 0.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(1.f)), glm::vec4(-scale.x / 2.f, height + 0.02f, 0.f, -scale.w / 2.f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.1f, 0.1f, 0.01f, 0.1f), 0.7f, 0.25f, isLagReflect, lagTextureIndex, glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), NONE, EMITD4));
}

static void generate_billiard4D(glm::vec4 position,glm::vec4 velocity4D,alg::bivec4 angularVelocity,unsigned int textureIndex, std::vector<RigidBody4D*>* rigidBodies4D, bool isGravity, glm::vec4 color, glm::vec4 buildMetalColor, unsigned int shaderIndex)
{
	rigidBodies4D->push_back(new RigidBody4D("Billiard", Hypersphere(glm::vec4(0.0525f)), position, alg::bivec4(30.f, 30.f, 30.f, 30.f, 30.f, 30.f), glm::vec4(0.0525f), 0.25f, 0.000675f, 0.f, 1.f, isGravity,false, velocity4D, angularVelocity, true, textureIndex, color, buildMetalColor,SPHERE4D, shaderIndex));
}

static void generate_dynamite4D(glm::vec4 position, unsigned int textureIndex, std::vector<RigidBody4D*>* dynamites4D2, std::vector<Wall4D*>* dynamites4D, std::vector<DynamiteIndex*>* dynamiteIndices, unsigned int shaderIndex)
{
	if(dynamiteIndices!=nullptr)dynamiteIndices->push_back(new DynamiteIndex(size_of_objects4d(*dynamites4D2, *dynamites4D), false));
	dynamites4D->push_back(new Wall4D("Dynamite", Hypercylinder(glm::vec4(0.2f, 0.2f, 1.f, 0.2f) / 2.f), position+glm::vec4(0.f, 0.5f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.2f, 0.2f, 1.f, 0.2f), 0.7f, 0.25f, true, textureIndex, glm::vec4(0.77f, 0.3f, 0.2f,0.5f) * 2.f, glm::vec4(1.f, 1.f, 1.f, 0.f), BOX4D, shaderIndex));
}

static void generate_dynamite4D(glm::vec4 position, glm::vec4 velocity4D, alg::bivec4 angularVelocity, unsigned int textureIndex, std::vector<RigidBody4D*>* dynamites4D, std::vector<DynamiteIndex*>* dynamiteIndices, bool isGravity,unsigned int shaderIndex)
{
	if (dynamiteIndices != nullptr)dynamiteIndices->push_back(new DynamiteIndex(dynamites4D->size(),false));
	dynamites4D->push_back(new RigidBody4D("Dynamite", Hypercylinder(glm::vec4(0.2f, 0.2f, 1.f, 0.2f) / 2.f), position + glm::vec4(0.f, 0.5f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.2f, 0.2f, 1.f, 0.2f), 1.f, 0.1f, 0.7f, 0.25f, isGravity, false, velocity4D, angularVelocity, true, textureIndex,glm::vec4(0.77f, 0.3f, 0.2f,0.5f) * 2.f,glm::vec4(1.f,1.f,1.f,0.f), BOX4D, shaderIndex));
}

static void generate_terrain4D(int size, glm::ivec4 scale, std::vector<Terrain4D*>* terrains4D, unsigned int shaderIndex)
{
	for (int w(-scale.w * size / 2.f + size / 2.f); w <= scale.w * size / 2.f - size / 2.f; w += size) {
		for (int z(-scale.z * size / 2.f + size / 2.f); z <= scale.z * size / 2.f - size / 2.f; z += size) {
			for (int x(-scale.x * size / 2.f + size / 2.f); x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w)), glm::vec4(x, 0.f, z, w), glm::vec4(size), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	/*
	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z, w - 198), glm::vec4(4.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z, w + 198), glm::vec4(4.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z - 198, w), glm::vec4(4.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z + 198, w), glm::vec4(4.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
		for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
			{
				int x = -(scale.x + 2) * size / 2.f + size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z, w), glm::vec4(400.f, 4.f, 4.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
		for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
			{
				int x = (scale.x + 2) * size / 2.f - size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z, w), glm::vec4(400.f, 4.f, 4.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z - 198, w - 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z + 198, w - 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z - 198, w + 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			for (int x = -scale.x * size / 2.f + size / 2.f; x <= scale.x * size / 2.f - size / 2.f; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0.f, z + 198, w + 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int x = -(scale.x + 2) * size / 2.f + size / 2.f;
			for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z, w - 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int x = (scale.x + 2) * size / 2.f - size / 2.f;
			for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z, w - 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int x = -(scale.x + 2) * size / 2.f + size / 2.f;
			for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z, w + 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int x = (scale.x + 2) * size / 2.f - size / 2.f;
			for (int z = -scale.z * size / 2.f + size / 2.f; z <= scale.z * size / 2.f - size / 2.f; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z, w + 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int x = -(scale.x + 2) * size / 2.f + size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z - 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int x = -(scale.x + 2) * size / 2.f + size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z + 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int x = (scale.x + 2) * size / 2.f - size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z - 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}

	{
		int x = (scale.x + 2) * size / 2.f - size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			for (int w = -scale.w * size / 2.f + size / 2.f; w <= scale.w * size / 2.f - size / 2.f; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z + 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	///////////////////////////////////////////
	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			{
				int x = (scale.x + 2) * size / 2.f - size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z + 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			{
				int x = -(scale.x + 2) * size / 2.f + size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z + 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			{
				int x = (scale.x + 2) * size / 2.f - size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z - 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2.f - size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			{
				int x = -(scale.x + 2) * size / 2.f + size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z - 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			{
				int x = (scale.x + 2) * size / 2.f - size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z + 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = (scale.z + 2) * size / 2.f - size / 2.f;
			{
				int x = -(scale.x + 2) * size / 2.f + size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z + 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			{
				int x = (scale.x + 2) * size / 2.f - size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0.f, z - 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2.f + size / 2.f;
		{
			int z = -(scale.z + 2) * size / 2.f + size / 2.f;
			{
				int x = -(scale.x + 2) * size / 2.f + size / 2.f;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0.f, z - 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 0.7f, 0.25f, TERRAIN4D, shaderIndex));
			}
		}
	}
	*/
}

