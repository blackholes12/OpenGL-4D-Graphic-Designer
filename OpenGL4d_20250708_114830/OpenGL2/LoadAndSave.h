#pragma once
//#include <conio.h>
//#include<io.h>
//#include<iostream>
//#include<string>
//#include<fstream>
//#include<sstream>

//static unsigned texture3d_list(Texture3D* texture3D, vector<Texture3D*> textures3D)
//{
//	for (size_t i = 0; i < textures3D.size(); i++)
//	{
//		if (textures3D[i] == texture3D)
//		{
//			return i;
//		}
//	}
//}
//
//static unsigned shader_list(Shader* shader, vector<Shader*> shaders)
//{
//	for (size_t i = 0; i < shaders.size(); i++)
//	{
//		if (shaders[i] == shader)
//		{
//			return i;
//		}
//	}
//}

static unsigned name_index(const char* name)
{
	if (name == "4D-Object") return 0;
	else if (name == "Can-Be-Destroyed") return 1;
	else if (name == "Glass4D") return 2;
	else if (name == "Ground") return 3;
	else if (name == "Celestial4D") return 4;
	else if (name == "Billiard") return 5;
	else if (name == "Player") return 6;
	else if (name == "Portal") return 7;
	else if (name == "Obstacle") return 8;
	else if (name == "Candy") return 9;
	else if (name == "Target") return 10;
	else return 0;
}

static const char* name_list(unsigned nameIndex)
{
	switch (nameIndex)
	{
	case 0: { return "4D-Object"; break; }
	case 1: { return "Can-Be-Destroyed"; break; }
	case 2: { return "Glass4D"; break; }
	case 3: { return "Ground"; break; }
	case 4: { return "Celestial4D"; break; }
	case 5: { return "Billiard"; break; }
	case 6: { return "Player"; break; }
	case 7: { return "Portal"; break; }
	case 8: { return "Obstacle"; break; }
	case 9: { return "Candy"; break; }
	case 10: { return "Target"; break; }
	}
}

static void save_file(const char* filePath, vector<RigidBody4D*> rigidBodies4d, std::vector<Group*> groups, vector<Wall4D*> walls4d, vector<DynamiteIndex*> dynamiteIndices, vector <Terrain4D*> terrains4d, vector <Water4D*> waters4d,
	vector < Stick4D*> sticks4d, vector < Spring4D*> springs4d, vector < Shift4D*> shifts4d, vector < Float4D*> floats4d, vector < Rotate4D*> rotates4d, vector< OpenDoor4D*> openDoors4d, vector < vector < HingeConstraint4D*>> hingeConstraintsVec,
	vector < PointLight4D*> pointLights4d,const float worldTime)
{
	FILE* f0(freopen(filePath, "w", stdout));
	for (size_t i(0); i < rigidBodies4d.size(); i++)
	{
		RigidBody4D* r(rigidBodies4d[i]);
		std::cout << "0" << " " << name_index(r->objectName) << " " << primitive_index(r->primitive4D.primitiveName) << " " <<
			r->primitive4D.scale4D.x << " " << r->primitive4D.scale4D.y << " " << r->primitive4D.scale4D.z << " " << r->primitive4D.scale4D.w << " " <<
			r->position4d.x<<" "<< r->position4d.y << " " << r->position4d.z << " " << r->position4d.w << " " <<
			r->rotation4D.s << " "<<r->rotation4D.b.xy<<" "<< r->rotation4D.b.xz << " " << r->rotation4D.b.xw << " "
			<< r->rotation4D.b.yz << " " << r->rotation4D.b.yw << " " << r->rotation4D.b.zw << " " << r->rotation4D.q.xyzw<<" "<<
			r->scale4D.x << " " << r->scale4D.y << " " << r->scale4D.z << " " << r->scale4D.w << " " <<
			r->mass<<" " << r->momentInertiaScalar<<" " << r->mu << " "<<r->restitution << " "<<
			r->isGravity<<" "<< r->isFrozen<<" " <<
			r->velocity4d.x << " " << r->velocity4d.y << " " << r->velocity4d.z << " " << r->velocity4d.w << " " <<
			r->angularVelocity4D.xy << " " << r->angularVelocity4D.xz << " " << r->angularVelocity4D.xw << " "
			<< r->angularVelocity4D.yz << " " << r->angularVelocity4D.yw << " " << r->angularVelocity4D.zw << " " <<
			r->isSpecular<<" "<< r->texture3DIndex <<" " << 
			r->paintingColor.x << " " << r->paintingColor.y << " " << r->paintingColor.z << " " << r->paintingColor.w << " " <<
			r->metalColor.x << " " << r->metalColor.y << " " << r->metalColor.z << " " << r->metalColor.w << " " <<
			r->colType<<" "<< r->shaderIndex<<" "<<
			r->massCenter.x << " " << r->massCenter.y << " " << r->massCenter.z << " " << r->massCenter.w <<
			r->animatePosition4D.x << " " << r->animatePosition4D.y << " " << r->animatePosition4D.z << " " << r->animatePosition4D.w <<"\n";
	}
	for (size_t i(0); i < walls4d.size(); i++)
	{
		Wall4D* w(walls4d[i]);
		std::cout << "1" << " " << name_index(w->objectName) << " " << primitive_index(w->primitive4D.primitiveName) << " " <<
			w->primitive4D.scale4D.x << " " << w->primitive4D.scale4D.y << " " << w->primitive4D.scale4D.z << " " << w->primitive4D.scale4D.w << " " <<
			w->position4d.x << " " << w->position4d.y << " " << w->position4d.z << " " << w->position4d.w << " " <<
			w->rotation4D.s << " " << w->rotation4D.b.xy << " " << w->rotation4D.b.xz << " " << w->rotation4D.b.xw << " "
			<< w->rotation4D.b.yz << " " << w->rotation4D.b.yw << " " << w->rotation4D.b.zw << " " << w->rotation4D.q.xyzw << " " <<
			w->scale4D.x << " " << w->scale4D.y << " " << w->scale4D.z << " " << w->scale4D.w << " " <<
			w->mu << " " << w->restitution <<" "<<
			w->isSpecular << " " << w->texture3DIndex << " " << 
			w->paintingColor.x << " " << w->paintingColor.y << " " << w->paintingColor.z << " " << w->paintingColor.w << " " <<
			w->metalColor.x << " " << w->metalColor.y << " " << w->metalColor.z << " " << w->metalColor.w << " " <<
			w->colType << " "  << w->shaderIndex <<"\n";
	}
	for (size_t i(0); i < dynamiteIndices.size(); i++)
	{
		DynamiteIndex* d(dynamiteIndices[i]);
		std::cout << "2" << " " << d->index << " " << d->isExploding << "\n";
	}
	for (size_t i(0); i < terrains4d.size(); i++)
	{
		Terrain4D* t(terrains4d[i]);
		std::cout << "3" << " " << name_index(t->objectName) << " " <<
			t->position4d.x << " " << t->position4d.y << " " << t->position4d.z << " " << t->position4d.w << " " <<
			t->scale4D.x << " " << t->scale4D.y << " " << t->scale4D.z << " " << t->scale4D.w << " " <<
			t->mu <<" "<<t->restitution<<" "<< t->colType << " " << t->shaderIndex << "\n";
	}
	for (size_t i(0); i < waters4d.size(); i++)
	{
		Water4D* w2(waters4d[i]);
		std::cout << "4" << " " << name_index(w2->objectName) << " " << primitive_index(w2->primitive4D.primitiveName) << " " <<
			w2->primitive4D.scale4D.x << " " << w2->primitive4D.scale4D.y << " " << w2->primitive4D.scale4D.z << " " << w2->primitive4D.scale4D.w << " " <<
			w2->position4d.x << " " << w2->position4d.y << " " << w2->position4d.z << " " << w2->position4d.w << " " <<
			w2->scale4D.x << " " << w2->scale4D.y << " " << w2->scale4D.z << " " << w2->scale4D.w << " " <<
			w2->colType << " " << w2->shaderIndex <<"\n";
	}
	for (size_t i(0); i < sticks4d.size(); i++)
	{
		Stick4D* s(sticks4d[i]);
		std::cout << "5" << " " <<
			s->fixPoint4D.x << " " << s->fixPoint4D.y << " " << s->fixPoint4D.z << " " << s->fixPoint4D.w << " " << 
			s->index1 << " " << s->index2.n << " " << s->index2.isValid << " " <<s->stickLength << " " << s->texture3DIndex << " " <<
			s->paintingColor.x << " " << s->paintingColor.y << " " << s->paintingColor.z << " " << s->paintingColor.w << " " <<
		    s->shaderIndex <<"\n";
	}
	for (size_t i(0); i < springs4d.size(); i++)
	{
		Spring4D* s2(springs4d[i]);
		std::cout << "6" << " " <<
			s2->fixPoint4D.x << " " << s2->fixPoint4D.y << " " << s2->fixPoint4D.z << " " << s2->fixPoint4D.w << " " <<
			s2->index1 << " " << s2->index2.n << " " << s2->index2.isValid << " " << " " << s2->springLength << " " << s2->k << " " << s2->texture3DIndex << " " <<
			s2->paintingColor.x << " " << s2->paintingColor.y << " " << s2->paintingColor.z << " " << s2->paintingColor.w << " " <<
			s2->shaderIndex <<"\n";
	}
	for (size_t i(0); i < shifts4d.size(); i++)
	{
		Shift4D* s3(shifts4d[i]);
		std::cout << "7" << " " << s3->pTs.size() << " ";
		for (size_t j(0); j < s3->pTs.size(); j++)
		{
			std::cout << s3->pTs[j].positions4D.x << " " << s3->pTs[j].positions4D.y << " " << s3->pTs[j].positions4D.z << " " << s3->pTs[j].positions4D.w << " " << s3->pTs[j].dt << " ";
		}
		std::cout << s3->index <<"\n";
	}
	for (size_t i(0); i < floats4d.size(); i++)
	{
		Float4D* f(floats4d[i]);
		std::cout << "8" << " " <<
			f->position4d.x << " " << f->position4d.y << " " << f->position4d.z << " " << f->position4d.w << " " <<
			f->distance << " " << f->speed << " " << f->direction4D << " " << f->index <<"\n";
	}
	for (size_t i(0); i < rotates4d.size(); i++)
	{
		Rotate4D* r2(rotates4d[i]);
		std::cout << "9" << " " <<
			r2->position4d.x << " " << r2->position4d.y << " " << r2->position4d.z << " " << r2->position4d.w << " " <<
			r2->bodyPosition4D.x << " " << r2->bodyPosition4D.y << " " << r2->bodyPosition4D.z << " " << r2->bodyPosition4D.w << " " <<
			r2->rotation4D.s << " " << r2->rotation4D.b.xy << " " << r2->rotation4D.b.xz << " " << r2->rotation4D.b.xw << " "
			<< r2->rotation4D.b.yz << " " << r2->rotation4D.b.yw << " " << r2->rotation4D.b.zw << " " << r2->rotation4D.q.xyzw << " " <<
			r2->angularVelocity4D.xy << " " << r2->angularVelocity4D.xz << " " << r2->angularVelocity4D.xw << " "
			<< r2->angularVelocity4D.yz << " " << r2->angularVelocity4D.yw << " " << r2->angularVelocity4D.zw << " "<<
			r2->isPositionFixed << " " << r2->index1 << " " << r2->index2.n << " " << r2->index2.isValid << "\n";
	}
	for (size_t i(0); i < openDoors4d.size(); i++)
	{
		OpenDoor4D* o(openDoors4d[i]);
		std::cout << "10" << " " <<
			o->position4d.x << " " << o->position4d.y << " " << o->position4d.z << " " << o->position4d.w << " " <<
			o->duringTime << " " << o->curTime << " " << 
			o->rotateAngle4D.xy << " " << o->rotateAngle4D.xz << " " << o->rotateAngle4D.xw << " " << 
			o->rotateAngle4D.yz << " " << o->rotateAngle4D.yw << " " << o->rotateAngle4D.zw << " " <<
			o->startRotation4D.s << " " << o->startRotation4D.b.xy << " " << o->startRotation4D.b.xz << " " << o->startRotation4D.b.xw << " " <<
			o->startRotation4D.b.yz << " " << o->startRotation4D.b.yw << " " << o->startRotation4D.b.zw << " " << o->startRotation4D.q.xyzw << " " <<
			o->state << " " << o->index << "\n";
	}
	for (size_t i(0); i < hingeConstraintsVec.size(); i++)
	{
		vector<HingeConstraint4D*> hs(hingeConstraintsVec[i]);
		std::cout << "11" << " " << hs.size() << " ";
		for (size_t j(0); j < hs.size(); j++)
		{
			HingeConstraint4D* h(hs[j]);
			std::cout << h->worldPosition4D.x << " " << h->worldPosition4D.y << " " << h->worldPosition4D.z << " " << h->worldPosition4D.w << " " <<
				h->bodyPosition4D1.x << " " << h->bodyPosition4D1.y << " " << h->bodyPosition4D1.z << " " << h->bodyPosition4D1.w << " " <<
				h->bodyPosition4D2.x << " " << h->bodyPosition4D2.y << " " << h->bodyPosition4D2.z << " " << h->bodyPosition4D2.w << " " <<
				h->index1 << " " << h->index2.n << " " << h->index2.isValid << " ";
		}
		std::cout << "\n";
	}
	for (size_t i(0); i < pointLights4d.size(); i++)
	{
		PointLight4D* p(pointLights4d[i]);
		std::cout << "12" << " " << p->texture3DIndex << " " <<
			p->position4d.x << " " << p->position4d.y << " " << p->position4d.z << " " << p->position4d.w << " " <<
			p->intensity << " " <<p->color.x << " " << p->color.y << " " << p->color.z << " "<< p->radius<<"\n";
	}
	std::cout << "13" << " " << worldTime << "\n";
	f0 = freopen("CON", "w", stdout);
	f0 =nullptr, delete f0;
}

static void load_file(const char* filePath, vector<RigidBody4D*>* rigidBodies4d, 
	vector<Wall4D*>* walls4d, vector<DynamiteIndex*>* dynamiteIndices, vector < Terrain4D*>* terrains4d,vector < Water4D*>* waters4d,
	vector < Stick4D*>* sticks4d, vector < Spring4D*>* springs4d, vector < Shift4D*>* shifts4d, vector < Float4D*>* floats4d, vector < Rotate4D*>* rotates4d, vector< OpenDoor4D*>* openDoors4d, vector < vector < HingeConstraint4D*>>* hingeConstraintsVec,
	vector < PointLight4D*>* pointLights4d,float* worldTime)
{
	std::ifstream in_file(filePath);
	std::stringstream ss2;
	std::string line2("");
	unsigned prefix2;
	const char* temp_glint2("");
	//File open error check
	if (!in_file.is_open())
	{
		//std::cout << "level loading failed!" << "\n";
		//throw "ERROR::OBJLOADER::Could not open file.";
	}
	else
	{
		//Read one line at a time
		while (std::getline(in_file, line2))
		{
			//Get the prefix of the line
			ss2.clear();
			ss2.str(line2);
			ss2 >> prefix2;
			switch (prefix2)
			{
			case 0: { 
				unsigned nameIndex; unsigned primitiveIndex; glm::vec4 primitiveScale4D; glm::vec4 position4d; alg::rotor4 rotation4D; glm::vec4 scale4D; float mass; float momentInertiaScalar; glm::vec4 massCenter; glm::vec4 animatePosition4D; float mu; float restitution; bool isGravity; bool isFrozen; glm::vec4 velocity4d; alg::bivec4 angularVelocity4D; bool isSpecular; size_t texture3DIndex; glm::vec4 paintingColor; glm::vec4 metalColor; unsigned char colType; size_t shaderIndex;
				ss2 >> nameIndex >> primitiveIndex >> primitiveScale4D.x >> primitiveScale4D.y >> primitiveScale4D.z >> primitiveScale4D.w >>
					position4d.x >> position4d.y >> position4d.z >> position4d.w >>
					rotation4D.s >> rotation4D.b.xy >> rotation4D.b.xz >> rotation4D.b.xw >> rotation4D.b.yz >> rotation4D.b.yw >> rotation4D.b.zw >> rotation4D.q.xyzw >>
					scale4D.x >> scale4D.y >> scale4D.z >> scale4D.w >> mass >> momentInertiaScalar >> mu >> restitution >> isGravity >> isFrozen >>
					velocity4d.x >> velocity4d.y >> velocity4d.z >> velocity4d.w >>
					angularVelocity4D.xy >> angularVelocity4D.xz >> angularVelocity4D.xw >> angularVelocity4D.yz >> angularVelocity4D.yw >> angularVelocity4D.zw >>
					isSpecular >> texture3DIndex >> 
					paintingColor.x >> paintingColor.y >> paintingColor.z >> paintingColor.w >>
					metalColor.x >> metalColor.y >> metalColor.z >> metalColor.w >>
					colType >> shaderIndex >> massCenter.x >> massCenter.y >> massCenter.z >> massCenter.w >>
					animatePosition4D.x >> animatePosition4D.y >> animatePosition4D.z >> animatePosition4D.w;
				RigidBody4D* a(new RigidBody4D(name_list(nameIndex), primitive_list(primitiveIndex, primitiveScale4D), position4d, rotation4D, scale4D, mass, momentInertiaScalar, mu, restitution, isGravity, isFrozen, velocity4d, angularVelocity4D, isSpecular, texture3DIndex, paintingColor, metalColor, colType, shaderIndex, massCenter, animatePosition4D, true));
				rigidBodies4d->push_back(a);
				a->isSleep = false;//!(length(a->velocity4d) > 0.1f || length(a->angularVelocity4D) > 0.8f);// || length(a->position4d - a->pPosition4D) > 0.05f);
				break; }
			case 1: { 
				unsigned nameIndex; unsigned primitiveIndex; glm::vec4 primitiveScale4D; glm::vec4 position4d; alg::rotor4 rotation4D; glm::vec4 scale4D; float mu; float restitution; bool isSpecular; size_t texture3DIndex; glm::vec4 paintingColor; glm::vec4 metalColor; unsigned char colType; size_t shaderIndex;
				ss2 >> nameIndex >> primitiveIndex >> primitiveScale4D.x >> primitiveScale4D.y >> primitiveScale4D.z >> primitiveScale4D.w >>
					position4d.x >> position4d.y >> position4d.z >> position4d.w >>
					rotation4D.s >> rotation4D.b.xy >> rotation4D.b.xz >> rotation4D.b.xw >> rotation4D.b.yz >> rotation4D.b.yw >> rotation4D.b.zw >> rotation4D.q.xyzw >>
					scale4D.x >> scale4D.y >> scale4D.z >> scale4D.w >> mu >> restitution >>
					isSpecular >> texture3DIndex >> 
					paintingColor.x >> paintingColor.y >> paintingColor.z >> paintingColor.w >>
					metalColor.x >> metalColor.y >> metalColor.z >> metalColor.w >>
					colType >> shaderIndex;
				walls4d->push_back(new Wall4D(name_list(nameIndex), primitive_list(primitiveIndex, primitiveScale4D), position4d, rotation4D, scale4D, mu, restitution, isSpecular, texture3DIndex, paintingColor, metalColor, colType, shaderIndex));
				break; }
			case 2: {
				size_t index; bool isExploding;
				ss2 >> index >> isExploding;
				dynamiteIndices->push_back(new DynamiteIndex(index, isExploding));
				break;
			}
			case 3: { 
				unsigned nameIndex; glm::vec4 position4d; glm::vec4 scale4D; float mu; float restitution; unsigned char colType; size_t shaderIndex;
				ss2 >> nameIndex >>
					position4d.x >> position4d.y >> position4d.z >> position4d.w >>
					scale4D.x >> scale4D.y >> scale4D.z >> scale4D.w >> mu >> restitution >> colType >> shaderIndex;
				terrains4d->push_back(new Terrain4D(name_list(nameIndex), Terrain4d(glm::ivec4(position4d.x, 54, position4d.z, position4d.w)), position4d, scale4D, mu, restitution, colType, shaderIndex));
				break; }
			case 4: {
				unsigned nameIndex; unsigned primitiveIndex; glm::vec4 primitiveScale4D; glm::vec4 position4d; glm::vec4 scale4D; unsigned char colType; size_t shaderIndex;
				ss2 >> nameIndex >> primitiveIndex >> primitiveScale4D.x >> primitiveScale4D.y >> primitiveScale4D.z >> primitiveScale4D.w >>
					position4d.x >> position4d.y >> position4d.z >> position4d.w >>
					scale4D.x >> scale4D.y >> scale4D.z >> scale4D.w >> colType >> shaderIndex;
				waters4d->push_back(new Water4D(name_list(nameIndex), primitive_list(primitiveIndex, primitiveScale4D), position4d, scale4D, colType, shaderIndex));
				break; }
			case 5: { 
				glm::vec4 fixPoint4D; size_t index1; VectorIndex index2; float stickLength; size_t texture3DIndex; glm::vec4 paintingColor; size_t shaderIndex;
				ss2 >> fixPoint4D.x >> fixPoint4D.y >> fixPoint4D.z >> fixPoint4D.w >> index1 >> index2.n >>index2.isValid >> stickLength >> texture3DIndex >>
					paintingColor.x >> paintingColor.y >> paintingColor.z >> paintingColor.w >> shaderIndex;
				sticks4d->push_back(new Stick4D(fixPoint4D, index1, index2, stickLength, texture3DIndex, paintingColor, shaderIndex));
				break; }
			case 6: { 
				glm::vec4 fixPoint4D; size_t index1; VectorIndex index2; float springLength; float k; size_t texture3DIndex; glm::vec4 paintingColor; size_t shaderIndex;
				ss2 >> fixPoint4D.x >> fixPoint4D.y >> fixPoint4D.z >> fixPoint4D.w >> index1 >> index2.n >> index2.isValid >> springLength >> k >> texture3DIndex >>
					paintingColor.x >> paintingColor.y >> paintingColor.z >> paintingColor.w >> shaderIndex;
				springs4d->push_back(new Spring4D(fixPoint4D, index1, index2, springLength, k, texture3DIndex, paintingColor, shaderIndex));
				break; }
			case 7: { 
				std::vector<PT> pTs; size_t size; size_t index;
				ss2 >> size;
				pTs.resize(size);
				for (size_t i(0); i < size; i++)
				{
					ss2 >> pTs[i].positions4D.x >> pTs[i].positions4D.y >> pTs[i].positions4D.z >> pTs[i].positions4D.w >> pTs[i].dt;
				}
				ss2 >> index;
				shifts4d->push_back(new Shift4D(pTs, index)); 
				break; }
			case 8: { 
				glm::vec4 position4d; float distance; float speed; unsigned int direction4D; size_t index;
				ss2 >> position4d.x >> position4d.y >> position4d.z >> position4d.w >> distance >> speed >> direction4D >> index;
				floats4d->push_back(new Float4D(position4d, distance, speed, direction4D, index));
				break; }
			case 9: { 
				glm::vec4 position4d; glm::vec4 bodyPosition4D; alg::rotor4 rotation4D; alg::bivec4 angularVelocity4D; bool isPositionFixed; size_t index1; VectorIndex index2;
				ss2 >> position4d.x >> position4d.y >> position4d.z >> position4d.w >>
					bodyPosition4D.x >> bodyPosition4D.y >> bodyPosition4D.z >> bodyPosition4D.w >>
					rotation4D.s >> rotation4D.b.xy >> rotation4D.b.xz >> rotation4D.b.xw >> rotation4D.b.yz >> rotation4D.b.yw >> rotation4D.b.zw >> rotation4D.q.xyzw >>
					angularVelocity4D.xy >> angularVelocity4D.xz >> angularVelocity4D.xw >> angularVelocity4D.yz >> angularVelocity4D.yw >> angularVelocity4D.zw >>
					isPositionFixed >> index1 >> index2.n >> index2.isValid;
				rotates4d->push_back(new Rotate4D(position4d, bodyPosition4D, rotation4D, angularVelocity4D, isPositionFixed, index1, index2));
				break; }
			case 10: {
				glm::vec4 position4d;float duringTime;float curTime;alg::bivec4 rotateAngle4D;alg::rotor4 startRotation4D;unsigned char state;size_t index;
				ss2 >> position4d.x >> position4d.y >> position4d.z >> position4d.w >> duringTime >> curTime >> 
					rotateAngle4D.xy >> rotateAngle4D.xz >> rotateAngle4D.xw >> rotateAngle4D.yz >> rotateAngle4D.yw >> rotateAngle4D.zw >> 
					startRotation4D.s >> startRotation4D.b.xy >> startRotation4D.b.xz >> startRotation4D.b.xw >> startRotation4D.b.yz >> startRotation4D.b.yw >> startRotation4D.b.zw >> startRotation4D.q.xyzw >>
					state >> index;
				openDoors4d->push_back(new OpenDoor4D(position4d, duringTime, curTime, rotateAngle4D, startRotation4D, state, index));
				break;
			}
			case 11: { 
				size_t size; glm::vec4 worldPosition4D; glm::vec4 bodyPosition4D1; glm::vec4 bodyPosition4D2; size_t index1; VectorIndex index2;
				ss2 >> size;
				vector < HingeConstraint4D*> hs;
				for (size_t i(0); i < size; i++)
				{
					ss2 >> worldPosition4D.x >> worldPosition4D.y >> worldPosition4D.z >> worldPosition4D.w >>
						bodyPosition4D1.x >> bodyPosition4D1.y >> bodyPosition4D1.z >> bodyPosition4D1.w >>
						bodyPosition4D2.x >> bodyPosition4D2.y >> bodyPosition4D2.z >> bodyPosition4D2.w >>
						index1 >> index2.n >> index2.isValid;
					hs.push_back(new HingeConstraint4D(worldPosition4D, bodyPosition4D1, bodyPosition4D2, index1, VectorIndex(index2)));
				}
				hingeConstraintsVec->push_back(hs);
				break; }
			case 12: {
				size_t texture3DIndex; glm::vec4 position4d; float intensity; glm::vec3 color; float radius;
				ss2 >> texture3DIndex >> position4d.x >> position4d.y >> position4d.z >> position4d.w >> intensity >> color.x >> color.y >> color.z >>
					radius;
				pointLights4d->push_back(new PointLight4D(texture3DIndex, position4d, pointLights4d->size(), intensity, color, radius));
				break; }
			case 13: { 
				ss2 >> *worldTime;
				break; }
			}
		}
	}
}