#include"libs.h"
//1=x,3=z,4=w,5=-x,7=-z,8=-w
//a direction
static void generate_room4D(glm::vec4 position, glm::vec4 scale, const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d, const unsigned int e, const unsigned int f, bool isFloor, bool isGroundReflect,Texture3D* groundTexture, glm::vec4 groundColor, Shader* groundShader, bool isBaseBoardReflect, Texture3D* baseBoardTexture, glm::vec4 baseBoardColor, Shader* baseBoardShader, bool isWallReflect, Texture3D* wallTexture, glm::vec4 wallColor, Shader* wallShader, bool isTopReflect, Texture3D* topTexture, glm::vec4 topColor, Shader* topShader, std::vector<Wall4D*>* walls4D) {
	if (a != 4 && b != 4&&c!=4&&d!=4&&e!=4&&f!=4) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f)/2.f), glm::vec4(0, scale.y / 2-0.1f, 0, scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f), 1.6f, 0.25f, isWallReflect,wallTexture,0.f, wallColor, BOX4D,wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0, 0.05f, 0, scale.w / 2 - 0.005f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
	if (a != 8 && b != 8 && c != 8 && d != 8 && e != 8 && f != 8) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0, scale.y / 2 - 0.1f, 0, -scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, scale.z + 0.4f, 0.2f), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0, 0.05f, 0, -scale.w / 2 + 0.005f) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
	if (a != 3 && b != 3 && c != 3 && d != 3 && e !=3 && f != 3) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w) / 2.f), glm::vec4(0, scale.y / 2 - 0.1f, scale.z / 2 + 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w-0.02f) / 2.f), glm::vec4(0, 0.05f, scale.z / 2 - 0.005f, 0) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w-0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
	if (a != 7 && b != 7 && c != 7 && d != 7 && e != 7 && f != 7) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w) / 2.f), glm::vec4(0, scale.y / 2 - 0.1f, -scale.z / 2 - 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y + 0.2f, 0.2f, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0, 0.05f, -scale.z / 2 + 0.005f, 0) + position, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f) / 2.f), glm::vec4(0, scale.y+0.1f, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f), 1.6f, 0.25f, isTopReflect, topTexture,0.f, topColor, BOX4D,topShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.2, scale.z, scale.w) / 2.f), glm::vec4(0, -0.1f, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x, 0.2, scale.z, scale.w), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D, groundShader));
	if (a != 1 && b != 1 && c != 1 && d != 1 && e != 1 && f != 1) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, scale.y + 0.2f, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2 + 0.1f, scale.y / 2 - 0.1f, 0, 0) + position, alg::bivec4(), glm::vec4(0.2f, scale.y + 0.2f, scale.z, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(scale.x / 2 - 0.005f, 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
	if (a != 5 && b != 5 && c != 5 && d != 5 && e != 5 && f != 5) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2, scale.y + 0.2f, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2 - 0.1f, scale.y / 2 - 0.1f, 0, 0) + position, alg::bivec4(), glm::vec4(0.2, scale.y + 0.2f, scale.z, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		if (isFloor)walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(-scale.x / 2 + 0.005f, 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
}

static void generate_pool4D(glm::vec4 position, glm::vec4 scale,bool isGroundReflect, Texture3D* groundTexture, glm::vec4 groundColor, Shader* groundShader, bool isWallReflect, Texture3D* wallTexture, glm::vec4 wallColor, Shader* wallShader, std::vector<Wall4D*> *walls4D) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0, -scale.y / 2, 0, scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f) / 2.f), glm::vec4(0, -scale.y / 2, 0, -scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, scale.z + 0.4f, 0.2f), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w) / 2.f), glm::vec4(0, -scale.y / 2, scale.z / 2 + 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w) / 2.f), glm::vec4(0, -scale.y / 2, -scale.z / 2 - 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, scale.y, 0.2f, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	    walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f) / 2.f), glm::vec4(0, -scale.y-0.1f, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.2, scale.z + 0.4f, scale.w + 0.4f), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D, groundShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2f, scale.y, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2 + 0.1f, -scale.y / 2, 0, 0) + position, alg::bivec4(), glm::vec4(0.2f, scale.y, scale.z, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.2, scale.y, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2 - 0.1f, -scale.y / 2, 0, 0) + position, alg::bivec4(), glm::vec4(0.2, scale.y, scale.z, scale.w), 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
}
//a=1,x,b=0 Pos fit with a room,b=1 Pos not fit with a room
static void generate_door4D(glm::vec4 position, glm::vec4 scale, glm::vec4 door,glm::vec2 doorScale, const unsigned int a, const unsigned int b, bool isFloor, const float floorThickness, bool isGroundReflect, Texture3D* groundTexture, glm::vec4 groundColor, Shader* groundShader, bool isBaseBoardReflect, Texture3D* baseBoardTexture,glm::vec4 baseBoardColor, Shader* baseBoardShader, bool isFrame,bool isFrameReflect, Texture3D* frameTexture, glm::vec4 frameColor, Shader* frameShader, bool isWallReflect, Texture3D* wallTexture, glm::vec4 wallColor, Shader* wallShader, std::vector<Wall4D*> *walls4D) {
	const float doorSize = doorScale.x;
	const float doorHeight = doorScale.y + floorThickness;
	float doorSize2,doorSize3, doorHeight2;
	const float frameScale = 0.1f;
	const float frameThickness = 0.0125f;
	int a2,c, d,sign;
	float offset, baseBoardOffset, baseBoardThickness;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5,framePos1, framePos2, framePos3, framePos4, framePos5,baseBoardPos1, baseBoardPos2, baseBoardPos3, baseBoardPos4;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, frameScale1, frameScale2, frameScale3, frameScale4, frameScale5, baseBoardScale1, baseBoardScale2, baseBoardScale3, baseBoardScale4;
		if (a == 1||a==5) 
		{
			a2=0,c = 2,d=3;
		}
		if (a == 3||a==7)
		{
			a2=2,c = 0, d = 3;
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
		if (b == 0) {
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
			if(b==0)
			doorSize3 = doorSize;
			if(b==1)
			doorSize3 = doorSize - 2.f * frameThickness;
			doorHeight2 = doorHeight;
		}
		wallPos1[a2] = offset,wallPos1[1] = scale[1] / 2.f - 0.1f,wallPos1[c]=0, wallPos1[d]= scale[d] / 4 + door[d] / 2 + doorSize2 / 4.f;
		wallPos2[a2] = offset, wallPos2[1] = scale[1] / 2.f - 0.1f, wallPos2[c] = 0, wallPos2[d] = -scale[d] / 4 + door[d] / 2 - doorSize2 / 4.f;
		wallPos3[a2] = offset, wallPos3[1] = scale[1] / 2.f + (doorHeight2) / 2.f, wallPos3[c] = door[c], wallPos3[d] =door[d];
		wallPos4[a2] = offset, wallPos4[1] = scale[1] / 2.f - 0.1f, wallPos4[c] = scale[c] / 4 + door[c] / 2 + doorSize2 / 4.f, wallPos4[d] = door[d];
		wallPos5[a2] = offset, wallPos5[1] = scale[1] / 2.f - 0.1f, wallPos5[c] = -scale[c] / 4 + door[c] / 2 - doorSize2 / 4.f, wallPos5[d] = door[d];
		wallScale1[a2] = 0.2f, wallScale1[1] = scale[1] + 0.2f, wallScale1[c] = scale[c], wallScale1[d] = scale[d] / 2 - door[d] - doorSize2 / 2.f;
		wallScale2[a2] = 0.2f, wallScale2[1] = scale[1] + 0.2f, wallScale2[c] = scale[c], wallScale2[d] = scale[d] / 2 + door[d] - doorSize2 / 2.f;
		wallScale3[a2] = 0.2f, wallScale3[1] = scale[1] - (doorHeight2), wallScale3[c] = doorSize2, wallScale3[d] = doorSize2;
		wallScale4[a2] = 0.2f, wallScale4[1] = scale[1] + 0.2f, wallScale4[c] = scale[c] / 2 - door[c] - doorSize2 / 2.f, wallScale4[d] = doorSize2;
		wallScale5[a2] = 0.2f, wallScale5[1] = scale[1] + 0.2f, wallScale5[c] = scale[c] / 2 + door[c] - doorSize2 / 2.f, wallScale5[d] = doorSize2;
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
			baseBoardPos1[a2] = offset + baseBoardOffset, baseBoardPos1[1] = 0.05f + floorThickness, baseBoardPos1[c] = 0, baseBoardPos1[d] = scale[d] / 4 + door[d] / 2 + doorSize3 / 4.f;
			baseBoardPos2[a2] = offset + baseBoardOffset, baseBoardPos2[1] = 0.05f + floorThickness, baseBoardPos2[c] = 0, baseBoardPos2[d] = -scale[d] / 4 + door[d] / 2 - doorSize3 / 4.f;
			baseBoardPos3[a2] = offset + baseBoardOffset, baseBoardPos3[1] = 0.05f + floorThickness, baseBoardPos3[c] = scale[c] / 4 + door[c] / 2 + doorSize3 / 4.f, baseBoardPos3[d] = door[d];
			baseBoardPos4[a2] = offset + baseBoardOffset, baseBoardPos4[1] = 0.05f + floorThickness, baseBoardPos4[c] = -scale[c] / 4 + door[c] / 2 - doorSize3 / 4.f, baseBoardPos4[d] = door[d];
			baseBoardScale1[a2] = baseBoardThickness, baseBoardScale1[1] = 0.1f, baseBoardScale1[c] = scale[c], baseBoardScale1[d] = scale[d] / 2 - door[d] - doorSize3 / 2.f;
			baseBoardScale2[a2] = baseBoardThickness, baseBoardScale2[1] = 0.1f, baseBoardScale2[c] = scale[c], baseBoardScale2[d] = scale[d] / 2 + door[d] - doorSize3 / 2.f;
			baseBoardScale3[a2] = baseBoardThickness, baseBoardScale3[1] = 0.1f, baseBoardScale3[c] = scale[c] / 2 - door[c] - doorSize3 / 2.f, baseBoardScale3[d] = doorSize3;
			baseBoardScale4[a2] = baseBoardThickness, baseBoardScale4[1] = 0.1f, baseBoardScale4[c] = scale[c] / 2 + door[c] - doorSize3 / 2.f, baseBoardScale4[d] = doorSize3;
		}
			
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D,wallShader));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D,wallShader));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D,wallShader));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D,wallShader));
			walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D,wallShader));
			
			if (b == 0) {
				glm::vec4 groundPos, groundScale;
				groundPos[a2] = offset, groundPos[1] = -0.1f, groundPos[c] = door[c], groundPos[d] = door[d];
				groundScale[a2] = 0.2f, groundScale[1] = 0.2f, groundScale[c] = doorSize2, groundScale[d] = doorSize2;
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(groundScale / 2.f), groundPos + position, alg::bivec4(), groundScale, 1.6f, 0.25f, isGroundReflect, groundTexture, 0.f, groundColor, BOX4D, groundShader));
			}

			if (isFrame)
			{
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale1/2.f), framePos1 + position, alg::bivec4(), frameScale1, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale2/2.f), framePos2 + position, alg::bivec4(), frameScale2, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale3/2.f), framePos3 + position, alg::bivec4(), frameScale3, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale4/2.f), framePos4 + position, alg::bivec4(), frameScale4, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale5/2.f), framePos5 + position, alg::bivec4(), frameScale5, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
			}
			
			if (isFloor)
			{
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale1 / 2.f), baseBoardPos1 + position, alg::bivec4(), baseBoardScale1, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture, 0.f, baseBoardColor, NONE, baseBoardShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale2 / 2.f), baseBoardPos2 + position, alg::bivec4(), baseBoardScale2, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture, 0.f, baseBoardColor, NONE, baseBoardShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale3 / 2.f), baseBoardPos3 + position, alg::bivec4(), baseBoardScale3, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture, 0.f, baseBoardColor, NONE, baseBoardShader));
				walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale4 / 2.f), baseBoardPos4 + position, alg::bivec4(), baseBoardScale4, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture, 0.f, baseBoardColor, NONE, baseBoardShader));
			}
}
//b=0 Pos fit with a room,b=1 Pos not fit with a room
static void generate_window4D(glm::vec4 position, glm::vec4 scale, glm::vec4 windowPos, glm::vec2 windowScale, const unsigned int a, const unsigned int b,bool isFloor, const float floorThickness, bool isBaseBoardReflect,Texture3D* baseBoardTexture, glm::vec4 baseBoardColor, Shader* baseBoardShader, bool isFrame, bool isFrameReflect,Texture3D* frameTexture, glm::vec4 frameColor, Shader* frameShader, bool isWindowReflect, Texture3D* windowTexture, glm::vec4 windowColor, Shader* windowShader, bool isWallReflect, Texture3D* wallTexture, glm::vec4 wallColor, Shader* wallShader, std::vector<Wall4D*> *walls4D) {
	const float windowSize = windowScale.x;
	const float windowHeight = windowScale.y;
	float windowSize2, windowHeight2;
	const float frameScale = 0.1f;
	const float frameThickness = 0.0125;
	int a2, c, d, sign;
	float offset, baseBoardOffset, baseBoardThickness;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5, wallPos6, framePos1, framePos2, framePos3, framePos4, framePos5, framePos6, baseBoardPos,glassPos;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, wallScale6,frameScale1, frameScale2, frameScale3, frameScale4, frameScale5, frameScale6, baseBoardScale,glassScale;
	if (a == 1 || a == 5)
	{
		a2 = 0, c = 2, d = 3;
	}
	if (a == 3 || a == 7)
	{
		a2 = 2, c = 0, d = 3;
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
	if (b == 0) {
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
	wallPos1[a2] = offset, wallPos1[1] = scale[1] / 2.f - 0.1f, wallPos1[c] = 0, wallPos1[d] = scale[d] / 4 + windowPos[d] / 2 +windowSize2 / 4.f;
	wallPos2[a2] = offset, wallPos2[1] = scale[1] / 2.f - 0.1f, wallPos2[c] = 0, wallPos2[d] = -scale[d] / 4 + windowPos[d] / 2 -windowSize2 / 4.f;
	wallPos3[a2] = offset, wallPos3[1] = scale[1] / 2.f + (windowPos[1]+ windowHeight2 /2.f+ floorThickness) / 2.f, wallPos3[c] = windowPos[c], wallPos3[d] = windowPos[d];
	wallPos4[a2] = offset, wallPos4[1] = (windowPos[1] - 0.2f - windowHeight2/2.f+ floorThickness) / 2.f, wallPos4[c] = windowPos[c], wallPos4[d] = windowPos[d];
	wallPos5[a2] = offset, wallPos5[1] = scale[1] / 2.f - 0.1f, wallPos5[c] = scale[c] / 4 + windowPos[c] / 2 +windowSize2 / 4.f, wallPos5[d] = windowPos[d];
	wallPos6[a2] = offset, wallPos6[1] = scale[1] / 2.f - 0.1f, wallPos6[c] = -scale[c] / 4 + windowPos[c] / 2 -windowSize2 / 4.f, wallPos6[d] = windowPos[d];
	wallScale1[a2] = 0.2f, wallScale1[1] = scale[1] + 0.2f, wallScale1[c] = scale[c], wallScale1[d] = scale[d] / 2 - windowPos[d] -windowSize2 / 2.f;
	wallScale2[a2] = 0.2f, wallScale2[1] = scale[1] + 0.2f, wallScale2[c] = scale[c], wallScale2[d] = scale[d] / 2 + windowPos[d] -windowSize2 / 2.f;
	wallScale3[a2] = 0.2f, wallScale3[1] = scale[1] - (windowPos[1] + windowHeight2 /2.f+ floorThickness), wallScale3[c] =windowSize2, wallScale3[d] =windowSize2;
	wallScale4[a2] = 0.2f, wallScale4[1] = windowPos[1] + 0.2f - windowHeight2 / 2.f+ floorThickness, wallScale4[c] =windowSize2, wallScale4[d] =windowSize2;
	wallScale5[a2] = 0.2f, wallScale5[1] = scale[1] + 0.2f, wallScale5[c] = scale[c] / 2 - windowPos[c] -windowSize2 / 2.f, wallScale5[d] =windowSize2;
	wallScale6[a2] = 0.2f, wallScale6[1] = scale[1] + 0.2f, wallScale6[c] = scale[c] / 2 + windowPos[c] -windowSize2 / 2.f, wallScale6[d] =windowSize2;

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
		baseBoardPos[a2] = offset + baseBoardOffset, baseBoardPos[1] = 0.05f + floorThickness, baseBoardPos[c] = 0, baseBoardPos[d] = 0;
		baseBoardScale[a2] = baseBoardThickness, baseBoardScale[1] = 0.1f, baseBoardScale[c] = scale[c], baseBoardScale[d] = scale[d];
	}

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale6 / 2.f), wallPos6 + position, alg::bivec4(), wallScale6, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));

	if (isFrame)
	{
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale1/2.f), framePos1 + position, alg::bivec4(), frameScale1, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale2/2.f), framePos2 + position, alg::bivec4(), frameScale2, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale3/2.f), framePos3 + position, alg::bivec4(), frameScale3, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale4/2.f), framePos4 + position, alg::bivec4(), frameScale4, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale5/2.f), framePos5 + position, alg::bivec4(), frameScale5, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(frameScale6/2.f), framePos6 + position, alg::bivec4(), frameScale6, 1.6f, 0.25f, isFrameReflect, frameTexture, 0.f, frameColor, NONE, frameShader));
	}

	walls4D->push_back(new Wall4D("Glass4D", Hypercube(glassScale / 2.f), glassPos + position, alg::bivec4(), glassScale, 1.6f, 0.25f, isWindowReflect, windowTexture,0.5f, windowColor, BOX4D, windowShader));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale / 2.f), baseBoardPos + position, alg::bivec4(), baseBoardScale, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
}

static void generate_walkway4D(glm::vec4 position, glm::vec4 scale, const unsigned int a, bool isFloor,bool isGroundReflect, Texture3D* groundTexture, glm::vec4 groundColor, Shader* groundShader, bool isBaseBoardReflect, Texture3D* baseBoardTexture, glm::vec4 baseBoardColor, Shader* baseBoardShader, bool isWallReflect,Texture3D* wallTexture,glm::vec4 wallColor, Shader* wallShader, bool isTopReflect,Texture3D* topTexture, glm::vec4 topColor, Shader* topShader, std::vector<Wall4D*> *walls4D) {
	
	int a2, c, d;
	glm::vec4 wallPos1, wallPos2, wallPos3, wallPos4, wallPos5, wallPos6,baseBoardPos1, baseBoardPos2, baseBoardPos3, baseBoardPos4;
	glm::vec4 wallScale1, wallScale2, wallScale3, wallScale4, wallScale5, wallScale6, baseBoardScale1, baseBoardScale2, baseBoardScale3, baseBoardScale4;

	if (a == 1)
	{
		a2 = 0, c = 2, d = 3;
	}
	if (a == 3)
	{
		a2 = 2, c = 0, d = 3;
	}
	if (a == 4)
	{
		a2 = 3, c = 2, d = 0;
	}

	wallPos1[a2] = 0, wallPos1[1] = scale[1] / 2.f-0.1f, wallPos1[c] = scale[c] / 2.f+0.1f, wallPos1[d] = 0;
	wallPos2[a2] = 0, wallPos2[1] = scale[1] / 2.f-0.1f, wallPos2[c] = -scale[c] / 2.f-0.1f, wallPos2[d] = 0;
	wallPos3[a2] = 0, wallPos3[1] = scale[1]+0.1f , wallPos3[c] = 0, wallPos3[d] = 0;
	wallPos4[a2] = 0, wallPos4[1] = -0.1f, wallPos4[c] = 0, wallPos4[d] = 0;
	wallPos5[a2] = 0, wallPos5[1] = scale[1] / 2.f-0.1f, wallPos5[c] = 0, wallPos5[d] = scale[d] / 2.f+0.1f;
	wallPos6[a2] = 0, wallPos6[1] = scale[1] / 2.f-0.1f, wallPos6[c] = 0, wallPos6[d] = -scale[d] / 2.f-0.1f;

	wallScale1[a2] = scale[a2] , wallScale1[1] = scale[1] +0.2f, wallScale1[c] = 0.2f, wallScale1[d] = scale[d] ;
	wallScale2[a2] = scale[a2] , wallScale2[1] = scale[1] +0.2f, wallScale2[c] = 0.2f, wallScale2[d] = scale[d] ;
	wallScale3[a2] = scale[a2] , wallScale3[1] = 0.2f, wallScale3[c] = scale[c] + 0.4f, wallScale3[d] = scale[d] + 0.4f;
	wallScale4[a2] = scale[a2] , wallScale4[1] = 0.2f, wallScale4[c] = scale[c] , wallScale4[d] = scale[d] ;
	wallScale5[a2] = scale[a2] , wallScale5[1] = scale[1] +0.2f, wallScale5[c] = scale[c]+0.4f , wallScale5[d] = 0.2f;
	wallScale6[a2] = scale[a2] , wallScale6[1] = scale[1] +0.2f, wallScale6[c] = scale[c]+0.4f , wallScale6[d] = 0.2f;

	baseBoardPos1[a2] = 0, baseBoardPos1[1] = 0.05f, baseBoardPos1[c] = scale[c] / 2 - 0.005f,baseBoardPos1[d] = 0;
	baseBoardPos2[a2] = 0, baseBoardPos2[1] = 0.05f, baseBoardPos2[c] = -scale[c] / 2 + 0.005f, baseBoardPos2[d] = 0;
	baseBoardPos3[a2] = 0, baseBoardPos3[1] = 0.05f, baseBoardPos3[c] = 0, baseBoardPos3[d] = scale[d] / 2 - 0.005f;
	baseBoardPos4[a2] = 0, baseBoardPos4[1] = 0.05f, baseBoardPos4[c] = 0, baseBoardPos4[d] = -scale[d] / 2 + 0.005f;

	baseBoardScale1[a2] = scale[a2], baseBoardScale1[1] = 0.1f, baseBoardScale1[c] = 0.01f, baseBoardScale1[d] = scale[d];
	baseBoardScale2[a2] = scale[a2], baseBoardScale2[1] = 0.1f, baseBoardScale2[c] = 0.01f, baseBoardScale2[d] = scale[d];
	baseBoardScale3[a2] = scale[a2], baseBoardScale3[1] = 0.1f, baseBoardScale3[c] = scale[c], baseBoardScale3[d] = 0.01f;
	baseBoardScale4[a2] = scale[a2], baseBoardScale4[1] = 0.1f, baseBoardScale4[c] = scale[c], baseBoardScale4[d] = 0.01f;

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale1 / 2.f), wallPos1 + position, alg::bivec4(), wallScale1, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale2 / 2.f), wallPos2 + position, alg::bivec4(), wallScale2, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale3 / 2.f), wallPos3 + position, alg::bivec4(), wallScale3, 1.6f, 0.25f, isTopReflect, topTexture,0.f, topColor, BOX4D, topShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale4 / 2.f), wallPos4 + position, alg::bivec4(), wallScale4, 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D, groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale5 / 2.f), wallPos5 + position, alg::bivec4(), wallScale5, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(wallScale6 / 2.f), wallPos6 + position, alg::bivec4(), wallScale6, 1.6f, 0.25f, isWallReflect, wallTexture,0.f, wallColor, BOX4D, wallShader));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale1 / 2.f), baseBoardPos1 + position, alg::bivec4(), baseBoardScale1, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale2 / 2.f), baseBoardPos2 + position, alg::bivec4(), baseBoardScale2, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale3 / 2.f), baseBoardPos3 + position, alg::bivec4(), baseBoardScale3, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(baseBoardScale4 / 2.f), baseBoardPos4 + position, alg::bivec4(), baseBoardScale4, 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
}

static void generate_steps4D(glm::vec4 startPos, glm::vec4 endPos,glm::vec4 scale, const unsigned int a, const unsigned int steps, bool isReflect,Texture3D* color, std::vector<Wall4D*> *walls4D, Shader* shader) {
	glm::vec4 offset;
	for (size_t i = 0;i < steps;i++) {
		if (a == 1) {
			offset = glm::vec4(scale.x/2.f, scale.y / 2.f,0,0);
		}
		if (a == 3) {
			offset = glm::vec4(0, scale.y / 2.f, scale.z / 2.f, 0);
		}
		if (a == 4) {
			offset = glm::vec4(0, scale.y / 2.f, 0, scale.w / 2.f);
		}
		if (a == 5) {
			offset = glm::vec4(-scale.x / 2.f, scale.y / 2.f, 0, 0);
		}
		if (a == 7) {
			offset = glm::vec4(0, scale.y / 2.f, -scale.z / 2.f, 0);
		}
		if (a == 8) {
			offset = glm::vec4(0, scale.y / 2.f, 0, -scale.w / 2.f);
		}
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(scale / 2.f), mix(startPos+ offset, endPos- offset, (float)i / (float)(steps - 1)), alg::bivec4(), scale, 1.6f, 0.25f, isReflect, color,0.f, glm::vec4(1.f), STEP4D, shader));
	}
}

static void generate_floor4D(glm::vec4 pos, glm::vec4 scale, glm::vec4 holePos, glm::vec4 holeSize,bool isFloor, bool isCeilReflect,Texture3D* ceilTexture,glm::vec4 ceilColor, Shader* ceilShader, bool isGroundReflect, Texture3D* groundTexture, glm::vec4 groundColor, Shader* groundShader, bool isBaseBoardReflect, Texture3D* baseBoardTexture, glm::vec4 baseBoardColor, Shader* baseBoardShader, std::vector<Wall4D*> *walls4D)
{
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z / 2 + holePos.z - holeSize.z / 2, holeSize.w) / 2.f), glm::vec4(0, 0.05f, holePos.z - holeSize.z / 2 - (scale.z / 2 + holePos.z - holeSize.z / 2) / 2, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z / 2 + holePos.z - holeSize.z / 2, holeSize.w), 1.6f, 0.25f, isGroundReflect,groundTexture,0.f, groundColor, BOX4D,groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z / 2 - holePos.z - holeSize.z / 2, holeSize.w) / 2.f), glm::vec4(0, 0.05f, holePos.z + holeSize.z / 2 + (scale.z / 2 - holePos.z - holeSize.z / 2) / 2, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z / 2 - holePos.z - holeSize.z / 2, holeSize.w), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D,groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2 - holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x + holeSize.x / 2 + (scale.x / 2 - holePos.x - holeSize.x / 2) / 2, 0.05f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2 - holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D,groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2 + holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x - holeSize.x / 2 - (scale.x / 2 + holePos.x - holeSize.x / 2) / 2, 0.05f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2 + holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D,groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 - holePos.w - holeSize.w / 2) / 2.f), glm::vec4(0, 0.05f, 0, holePos.w + holeSize.w / 2 + (scale.w / 2 - holePos.w - holeSize.w / 2) / 2) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 - holePos.w - holeSize.w / 2), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D,groundShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 + holePos.w - holeSize.w / 2) / 2.f), glm::vec4(0, 0.05f, 0, holePos.w - holeSize.w / 2 - (scale.w / 2 + holePos.w - holeSize.w / 2) / 2) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 + holePos.w - holeSize.w / 2), 1.6f, 0.25f, isGroundReflect, groundTexture,0.f, groundColor, BOX4D,groundShader));

	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z / 2 + holePos.z - holeSize.z / 2, holeSize.w) / 2.f), glm::vec4(0, -0.05f, holePos.z - holeSize.z / 2 - (scale.z / 2 + holePos.z - holeSize.z / 2) / 2, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z / 2 + holePos.z - holeSize.z / 2, holeSize.w), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z / 2 - holePos.z - holeSize.z / 2, holeSize.w) / 2.f), glm::vec4(0, -0.05f, holePos.z + holeSize.z / 2 + (scale.z / 2 - holePos.z - holeSize.z / 2) / 2, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z / 2 - holePos.z - holeSize.z / 2, holeSize.w), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2 - holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x + holeSize.x / 2 + (scale.x / 2 - holePos.x - holeSize.x / 2) / 2, -0.05f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2 - holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x / 2 + holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w) / 2.f), glm::vec4(holePos.x - holeSize.x / 2 - (scale.x / 2 + holePos.x - holeSize.x / 2) / 2, -0.05f, holePos.z, holePos.w) + pos, alg::bivec4(), glm::vec4(scale.x / 2 + holePos.x - holeSize.x / 2, 0.1f, holeSize.z, holeSize.w), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 - holePos.w - holeSize.w / 2) / 2.f), glm::vec4(0, -0.05f, 0, holePos.w + holeSize.w / 2 + (scale.w / 2 - holePos.w - holeSize.w / 2) / 2) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 - holePos.w - holeSize.w / 2), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 + holePos.w - holeSize.w / 2) / 2.f), glm::vec4(0, -0.05f, 0, holePos.w - holeSize.w / 2 - (scale.w / 2 + holePos.w - holeSize.w / 2) / 2) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, scale.w / 2 + holePos.w - holeSize.w / 2), 1.6f, 0.25f, isCeilReflect, ceilTexture,0.f, ceilColor, BOX4D,ceilShader));
	if (isFloor) {
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(scale.x / 2 - 0.005f, 0.15f, 0, 0) + pos, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor,NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f) / 2.f), glm::vec4(-scale.x / 2 + 0.005f, 0.15f, 0, 0) + pos, alg::bivec4(), glm::vec4(0.01f, 0.1f, scale.z - 0.02f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0, 0.15f, scale.z / 2 - 0.005f, 0) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor,NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f) / 2.f), glm::vec4(0, 0.15f, -scale.z / 2 + 0.005f, 0) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, 0.01f, scale.w - 0.02f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0, 0.15f, 0, scale.w / 2 - 0.005f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor,NONE, baseBoardShader));
		walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.1f, scale.z, 0.01f) / 2.f), glm::vec4(0, 0.15f, 0, -scale.w / 2 + 0.005f) + pos, alg::bivec4(), glm::vec4(scale.x, 0.1f, scale.z, 0.01f), 1.6f, 0.25f, isBaseBoardReflect, baseBoardTexture,0.f, baseBoardColor, NONE, baseBoardShader));
	}
}

static void generate_table4D(glm::vec4 position, glm::vec4 scale, float height, bool isTopReflect,Texture3D* topColor, bool isLagReflect, Texture3D* lagcolor, std::vector<Wall4D*> *walls4D, Shader* shader)
{
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(scale.x, 0.04, scale.z, scale.w) / 2.f), glm::vec4(0, height, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x, 0.04, scale.z, scale.w), 1.6f, 0.25f, isTopReflect,topColor,0.f, glm::vec4(1.f), BOX4D,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, scale.z / 2 - 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, scale.z / 2 - 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, -scale.z / 2 + 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, -scale.z / 2 + 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, scale.z / 2 - 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, scale.z / 2 - 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, -scale.z / 2 + 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
	walls4D->push_back(new Wall4D("Hypercube", Hypercube(glm::vec4(0.05f, height, 0.05f, 0.05f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, -scale.z / 2 + 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(), glm::vec4(0.05f, height, 0.05f, 0.05f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f), NONE,shader));
}
static void generate_pool_table4D(glm::vec4 position, glm::vec4 scale, float height, bool isFrameReflect, Texture3D* framecolor, bool isTopReflect, Texture3D* topColor, bool isLagReflect, Texture3D* lagcolor, std::vector<Wall4D*> *walls4D, Shader* shader)
{

	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(scale.x + 0.04f, 0.04f, scale.z + 0.04f, scale.w + 0.04f) / 2.f), glm::vec4(0, height, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.04f, 0.04f, scale.z + 0.04f, scale.w + 0.04f), 0.f, 0.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0, height/2.f+0.01f, 0, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.02f+ height, scale.z + 0.4f, scale.w + 0.4f), 0.f, 0.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));

	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(0.025f, 0.1f, scale.z, scale.w) / 2.f), glm::vec4(scale.x / 2.f + 0.0125f, height + 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.025f, 0.1f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(0.025f, 0.1f, scale.z, scale.w) / 2.f), glm::vec4(-scale.x / 2.f - 0.0125f, height + 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.025f, 0.1f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w) / 2.f), glm::vec4(0, height + 0.05f, scale.z / 2.f + 0.0125f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w) / 2.f), glm::vec4(0, height + 0.05f, -scale.z / 2.f - 0.0125f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, 0.025f, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f) / 2.f), glm::vec4(0, height + 0.05f, 0, scale.w / 2.f + 0.0125f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f) / 2.f), glm::vec4(0, height + 0.05f, 0, -scale.w / 2.f - 0.0125f) + position, alg::bivec4(), glm::vec4(scale.x + 0.05f, 0.1f, scale.z + 0.05f, 0.025f), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f,1.25f,0.5f,1.f), NONE, shader));
	
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)) / 2.f), glm::vec4((scale.x+0.05f)  / 2.f + 0.02f, height+0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)) / 2.f), glm::vec4(-(scale.x+0.05f) / 2.f - 0.02f, height + 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.04f, 0.1f, (scale.z+0.05f), (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)) / 2.f), glm::vec4(0, height + 0.05f, (scale.z+0.05f) / 2.f + 0.02f, 0) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)) / 2.f), glm::vec4(0, height + 0.05f, -(scale.z+0.05f) / 2.f - 0.02f, 0) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, 0.04f, (scale.w+0.05f)), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f) / 2.f), glm::vec4(0, height + 0.05f, 0, (scale.w+0.05f) / 2.f + 0.02f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Billiard", Hypercube(glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f) / 2.f), glm::vec4(0, height + 0.05f, 0, -(scale.w+0.05f) / 2.f - 0.02f) + position, alg::bivec4(), glm::vec4((scale.x+0.05f) + 0.08f, 0.1f, (scale.z+0.05f) + 0.08f, 0.04f), 0.f, 1.f, isFrameReflect, framecolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));

	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(scale.x / 2.f + 0.1f, height + 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.2f, 0.6f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(-scale.x / 2.f - 0.1f, height + 0.05f, 0, 0) + position, alg::bivec4(), glm::vec4(0.2f, 0.6f, scale.z, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0, height + 0.05f, scale.z / 2.f + 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.6f, 0.2f, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0, height + 0.05f, -scale.z / 2.f - 0.1f, 0) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.6f, 0.2f, scale.w), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0, height + 0.05f, 0, scale.w / 2.f + 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.6f, scale.z + 0.4f, 0.2f), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));
	walls4D->push_back(new Wall4D("Billiard", Noneshape(), glm::vec4(0, height + 0.05f, 0, -scale.w / 2.f - 0.1f) + position, alg::bivec4(), glm::vec4(scale.x + 0.4f, 0.6f, scale.z + 0.4f, 0.2f), 0.f, 1.f, isTopReflect, topColor,0.f, glm::vec4(0.5f, 1.25f, 0.5f,1.f), BOX4D, shader));

	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, scale.z / 2 - 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(0.f,0.f,0.f,90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f),NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, scale.z / 2 - 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f,glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, -scale.z / 2 + 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f,glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, -scale.z / 2 + 0.1f, scale.w / 2 - 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, scale.z / 2 - 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f),NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, scale.z / 2 - 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f,glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(scale.x / 2 - 0.1f, height / 2, -scale.z / 2 + 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f,glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
	walls4D->push_back(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.18f, 0.18f, height, 0.18f)/2.f), glm::vec4(-scale.x / 2 + 0.1f, height / 2, -scale.z / 2 + 0.1f, -scale.w / 2 + 0.1f) + position, alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.18f, 0.18f, height, 0.18f), 1.6f, 0.25f, isLagReflect, lagcolor,0.f, glm::vec4(1.f,0.75f,0.5f,1.f), NONE, shader));
}

static void generate_billiard4D(glm::vec4 position,glm::vec4 velocity4D,alg::bivec4 angularVelocity,Texture3D* texture, std::vector<RigidBody4D*>* rigidBodies4D, bool isGravity, float metal,glm::vec4 color, Shader* shader)
{
	rigidBodies4D->push_back(new RigidBody4D("Billiard", Hypersphere(glm::vec4(0.0525f)), position, alg::bivec4(30, 30, 30, 30, 30, 30), glm::vec4(0.0525f), 0.25f, 0.000675f, 0.f, 1.f, isGravity,false, velocity4D, angularVelocity, true, texture, metal, color, SPHERE4D, shader));
}

static void generate_dynamite4D(glm::vec4 position, Texture3D* texture,std::vector<Wall4D*>* dynamites4D, Shader* shader)
{
	dynamites4D->push_back(new Wall4D("Dynamite", Hypercylinder(glm::vec4(0.2f, 0.2f, 1.f, 0.2f) / 2.f), position+glm::vec4(0.f, 0.5f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.2f, 0.2f, 1.f, 0.2f), 1.6f, 0.25f, true, texture, 0.f,glm::vec4(0.77f, 0.3f, 0.2f,0.5f) * 2.f, BOX4D, shader));
}

static void generate_dynamite4D(glm::vec4 position, glm::vec4 velocity4D, alg::bivec4 angularVelocity, Texture3D* texture, std::vector<RigidBody4D*>* dynamites4D, bool isGravity,Shader* shader)
{
	dynamites4D->push_back(new RigidBody4D("Dynamite", Hypercylinder(glm::vec4(0.2f, 0.2f, 1.f, 0.2f) / 2.f), position + glm::vec4(0.f, 0.5f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.2f, 0.2f, 1.f, 0.2f), 1.f, 0.1f, 1.6f, 0.25f, isGravity, false, velocity4D, angularVelocity, true, texture,0.f, glm::vec4(0.77f, 0.3f, 0.2f,0.5f) * 2.f, BOX4D, shader));
}

static void generate_terrain4D(int size, glm::ivec4 scale, std::vector<Terrain4D*>* terrains4D, Shader* shader)
{
	for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
		for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z, w), glm::vec4(size), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	/*
	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z, w - 198), glm::vec4(4.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z, w + 198), glm::vec4(4.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z - 198, w), glm::vec4(4.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z + 198, w), glm::vec4(4.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
		for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
			{
				int x = -(scale.x + 2) * size / 2 + size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z, w), glm::vec4(400.f, 4.f, 4.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
		for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
			{
				int x = (scale.x + 2) * size / 2 - size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z, w), glm::vec4(400.f, 4.f, 4.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z - 198, w - 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z + 198, w - 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z - 198, w + 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			for (int x = -scale.x * size / 2 + size / 2; x <= scale.x * size / 2 - size / 2; x += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x, 0, z + 198, w + 198), glm::vec4(4.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int x = -(scale.x + 2) * size / 2 + size / 2;
			for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z, w - 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int x = (scale.x + 2) * size / 2 - size / 2;
			for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z, w - 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int x = -(scale.x + 2) * size / 2 + size / 2;
			for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z, w + 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int x = (scale.x + 2) * size / 2 - size / 2;
			for (int z = -scale.z * size / 2 + size / 2; z <= scale.z * size / 2 - size / 2; z += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z, w + 198), glm::vec4(400.f, 4.f, 4.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int x = -(scale.x + 2) * size / 2 + size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z - 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int x = -(scale.x + 2) * size / 2 + size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z + 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int x = (scale.x + 2) * size / 2 - size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z - 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}

	{
		int x = (scale.x + 2) * size / 2 - size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			for (int w = -scale.w * size / 2 + size / 2; w <= scale.w * size / 2 - size / 2; w += size) {
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z + 198, w), glm::vec4(400.f, 4.f, 400.f, 4.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	///////////////////////////////////////////
	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			{
				int x = (scale.x + 2) * size / 2 - size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z + 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			{
				int x = -(scale.x + 2) * size / 2 + size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z + 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			{
				int x = (scale.x + 2) * size / 2 - size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z - 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = (scale.w + 2) * size / 2 - size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			{
				int x = -(scale.x + 2) * size / 2 + size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z - 198, w + 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			{
				int x = (scale.x + 2) * size / 2 - size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z + 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = (scale.z + 2) * size / 2 - size / 2;
			{
				int x = -(scale.x + 2) * size / 2 + size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z + 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			{
				int x = (scale.x + 2) * size / 2 - size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x + 198, 0, z - 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	{
		int w = -(scale.w + 2) * size / 2 + size / 2;
		{
			int z = -(scale.z + 2) * size / 2 + size / 2;
			{
				int x = -(scale.x + 2) * size / 2 + size / 2;
				terrains4D->push_back(new Terrain4D("Terrain", Terrain4d(glm::ivec4(x, 54, z, w), size), glm::vec4(x - 198, 0, z - 198, w - 198), glm::vec4(400.f, 4.f, 400.f, 400.f), 1.6f, 0.25f, TERRAIN4D, shader));
			}
		}
	}
	*/
}

