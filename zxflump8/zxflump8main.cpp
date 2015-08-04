#include <irrlicht.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>
#include "Main2.cpp"


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1,
	IDFlag_IsHighlightable2 = 1 << 2
};
int main(int argc, char* args[]){
	//
		MyEventReceiver receiver;
	IrrlichtDevice *device =
		createDevice(E_DRIVER_TYPE::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false, false, true, &receiver);
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* env = device->getGUIEnvironment();
	scene::IAnimatedMesh* mesh = smgr->getMesh("Data/xbullet1.x");
	scene::IAnimatedMeshSceneNode* node = 0;
	scene::IAnimatedMeshSceneNode* xnode = 0;
	scene::IAnimatedMeshSceneNode* xmonsternode = 0;
	scene::IAnimatedMeshSceneNode* node2[16] = {0};
	node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("Data/xchargun1.x"), 0, ID_IsNotPickable);
	for(int xint = 0;xint < 16;xint++){
		node2[xint] = smgr->addAnimatedMeshSceneNode(mesh, 0, ID_IsNotPickable);
		//node2[xint]->setParent(node);
		node2[xint]->setScale(core::vector3df(0.8f, 0.8f, 0.8f));
		node2[xint]->setVisible(false);
	}
	node->setScale(core::vector3df(0.1f, 0.1f, 0.1f));
	xnode = smgr->addAnimatedMeshSceneNode(mesh, 0, ID_IsNotPickable);
	xmonsternode = smgr->addAnimatedMeshSceneNode(smgr->getMesh("Data/Slime/Slime.md2"), 0, IDFlag_IsHighlightable2);
	xmonsternode->setMaterialTexture(0, driver->getTexture("Data/Slime/slime.tga"));
	xmonsternode->setScale(core::vector3df(0.1f, 0.1f, 0.1f));
	xmonsternode->setPosition(core::vector3df(0.0f, 0.0f, -30.0f));
	xmonsteraccountdata zmonsterdata;
	node->setMaterialTexture(0, driver->getTexture("Data/t0178_0.tga"));
	node->setAnimationSpeed(0.0f);
	xmonsternode->setAnimationSpeed(0.0f);
	//node->setPosition(core::vector3df(9.0f, -8.5f, 28.5f));
	node->setPosition(core::vector3df(2.0f, -1.5f, 3.0f));
	node->setRotation(core::vector3df(3.0f, 169.5f, 0.0f));
	scene::ISkinnedMesh *znode = (ISkinnedMesh*)node->getMesh();
	cout << "node = " << node->getJointCount() << endl;
	for(int xint = 0;xint < node->getJointCount();xint++){
		std::string xstring = "";
		xstring += node->getJointNode(xint)->getName();
		cout << "joint[" << xint << "] = " << xstring << endl;
	}
	cout << "xnode = " << node->getJointCount() << endl;
	for(int xint = 0;xint < xnode->getJointCount();xint++){
		std::string xstring = "";
		xstring += xnode->getJointNode(xint)->getName();
		cout << "joint[" << xint << "] = " << xstring << endl;
	}
	cout << "znode = " << znode->getJointCount() << endl;
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
		"Data/terrain-heightmap.bmp",
		0,					// parent node
		3,					// node id
		core::vector3df(-1300.f, -2200.f, -1050.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		5,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);
	//terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
			driver->getTexture("Data/DarkVallyVertexcolor.bmp"));

	terrain->scaleTexture(1.0f, 20.0f);
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
	//camera->bindTargetAndRotation(true);
	//camera->setParent(xnode);
	camera->setPosition(core::vector3df(0, 5, -5));
	xnode->setPosition(core::vector3df(0, 0, 0));
	if(camera){
		scene::ITriangleSelector* selector = 0;
		selector = smgr->createTriangleSelector(xnode);
		xnode->setTriangleSelector(selector);
		selector->drop();
		selector = smgr->createTriangleSelector(xmonsternode);
		xmonsternode->setTriangleSelector(selector);
		selector->drop();
	selector = smgr->createTerrainTriangleSelector(terrain);
	terrain->setTriangleSelector(selector);
	selector->drop();
	}
	node->setParent(camera);
	//camera->setTarget(xnode->getAbsolutePosition());
	scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
	gui::IGUISpriteBank * SpriteBankIcons;
	SpriteBankIcons = env->addEmptySpriteBank(io::path("cursor_icons"));
	rect<s32> rectIcon;
	SCursorSprite spriteNonAnimated(SpriteBankIcons, 0, position2d<s32>(0,0));
	SCursorSprite spriteNonAnimated2(SpriteBankIcons, 0, position2d<s32>(0,0));
	rectIcon = rect<s32>(0,0, 32, 32);
	spriteNonAnimated.SpriteId = AddIconToSpriteBank( SpriteBankIcons, driver, io::path("Data/NpcCursor.png"), rectIcon );
	spriteNonAnimated2.SpriteId = AddIconToSpriteBank( SpriteBankIcons, driver, io::path("Data/NorCursor.png"), rectIcon );
	gui::ECURSOR_ICON zxcursor1 = device->getCursorControl()->addIcon(spriteNonAnimated);
	gui::ECURSOR_ICON zxcursor2 = device->getCursorControl()->addIcon(spriteNonAnimated2);
	device->getCursorControl()->setActiveIcon(zxcursor2);
	scene::ILightSceneNode * light = smgr->addLightSceneNode(0, core::vector3df(-60,100,400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 600.0f);
	scene::ILightSceneNode * light2 = smgr->addLightSceneNode(camera, core::vector3df(0.2f,0.0f,-100.5f),
		video::SColorf(82.0f,255.0f,255.0f,255.0f), 1.0f);
	light2->setLightType(video::E_LIGHT_TYPE::ELT_SPOT);
	if(light2){
		SLight xlight2 = light2->getLightData();
		xlight2.InnerCone = 5.2f;
		xlight2.OuterCone = 32.0f;
		xlight2.Falloff = 1.0f;
		xlight2.AmbientColor = video::SColorf(1.0f,1.0f,1.0f,255.0f);
		light2->setLightData(xlight2);
	}
	light2->setParent(node);
	int lastFPS = 0;
	xfpslimiter xfps;
	xfps.timer = device->getTimer();
	bool xhadmouse = false;
	bool xhadmouse2 = false;
	bool xhadbtn = false;
	int xbulletnumber = 0;
	int xbulletnumberint[16] = {0};
	core::vector3df xbulletdirint[16] = {core::vector3df(0, 0, 0)};
	core::vector3df xgunpositions[4] = {core::vector3df(0, 0, 0)};
	core::vector3df xgunrotations[4] = {core::vector3df(0, 0, 0)};
	int xbulletdistanceint[16] = {0};
	xgunpositions[0] = node->getPosition();
	xgunrotations[0] = node->getRotation();
	xgunpositions[1] = core::vector3df(0.0f, -11.5f, 22.5f);
	xgunrotations[1] = core::vector3df(0.0f, 180.0f, 0.0f);
	int xmouseposx = 0;
	int xmouseposy = 0;
	int xzcharmovespeed = 30;
	xcharaccountdata x;
	std::wstring xcharammo = L"";
	std::wstring xmonsterhp = L"";
	int xlastammo = 0;
	int xlasthp = 0;
	core::vector3df xcamerapos = camera->getPosition();
	//camera->setTarget(core::vector3df(0, 0, 50));
	core::vector3df xnodepos = camera->getTarget();
	IGUIFont *xfont = env->getFont("ressystem/myfont.xml");
	while(device->run()){
		xfps.nowTime = xfps.timer->getTime();
		if (device->isWindowActive())
		{
			//
			if(receiver.IsKeyDown(KEY_KEY_W)){
				if(!xhadbtn){
				//node->setRotation(vector3df(0,-90,0));
				//xcamerapos.Z = xintz;
				core::vector3df xzintx = camera->getRotation();
				xnodepos = camera->getTarget();
				xcamerapos = camera->getPosition();
				if(xzintx.Y < 90){
					xnodepos.X -= 0 + ((xzintx.Y / 90) * xzcharmovespeed);
					xnodepos.Z -= xzcharmovespeed - ((xzintx.Y / 90) * xzcharmovespeed);
					xcamerapos.X -= 0 + ((xzintx.Y / 90) * xzcharmovespeed);
					xcamerapos.Z -= xzcharmovespeed - ((xzintx.Y / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 90 && xzintx.Y < 180){
					float zxintx2 = xzintx.Y - 90;
					xnodepos.X -= xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X -= xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z += 0 + ((zxintx2 / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 180 && xzintx.Y < 270){
					float zxintx2 = xzintx.Y - 180;
					xnodepos.X += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 270){
					float zxintx2 = xzintx.Y - 270;
					xnodepos.X += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z -= 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z -= 0 + ((zxintx2 / 90) * xzcharmovespeed);
				}
				camera->setTarget(xnodepos);
				camera->setPosition(xcamerapos);
				xhadbtn = true;
				}
			}else
			if(receiver.IsKeyDown(KEY_KEY_S)){
				if(!xhadbtn){
				core::vector3df xzintx = camera->getRotation();
				xnodepos = camera->getTarget();
				xcamerapos = camera->getPosition();
				if(xzintx.Y < 90){
					xnodepos.X -= 0 + ((xzintx.Y / 90) * xzcharmovespeed);
					xnodepos.Z -= xzcharmovespeed - ((xzintx.Y / 90) * xzcharmovespeed);
					xcamerapos.X -= 0 + ((xzintx.Y / 90) * xzcharmovespeed);
					xcamerapos.Z -= xzcharmovespeed - ((xzintx.Y / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 90 && xzintx.Y < 180){
					float zxintx2 = xzintx.Y - 90;
					xnodepos.X -= xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X -= xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z += 0 + ((zxintx2 / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 180 && xzintx.Y < 270){
					float zxintx2 = xzintx.Y - 180;
					xnodepos.X += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X += 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
				}else if(xzintx.Y >= 270){
					float zxintx2 = xzintx.Y - 270;
					xnodepos.X += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xnodepos.Z -= 0 + ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.X += xzcharmovespeed - ((zxintx2 / 90) * xzcharmovespeed);
					xcamerapos.Z -= 0 + ((zxintx2 / 90) * xzcharmovespeed);
				}
				camera->setTarget(xnodepos);
				camera->setPosition(xcamerapos);
				xhadbtn = true;
				}
			}else{
				if(xhadbtn){
					xhadbtn = false;
				}
			}
			if(receiver.IsKeyDown(KEY_KEY_2)){
				core::vector3df xzintx = node->getPosition();
				xzintx.Z -= 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.z = " << xzintx.Z << endl;
			}else if(receiver.IsKeyDown(KEY_KEY_3)){
				core::vector3df xzintx = node->getPosition();
				xzintx.Z += 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.z = " << xzintx.Z << endl;
			}
			if(receiver.IsKeyDown(KEY_KEY_1)){
				core::vector3df xzintx = node->getPosition();
				xzintx.Y -= 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.y = " << xzintx.Y << endl;
			}else if(receiver.IsKeyDown(KEY_KEY_4)){
				core::vector3df xzintx = node->getPosition();
				xzintx.Y += 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.y = " << xzintx.Y << endl;
			}
			if(receiver.IsKeyDown(KEY_KEY_5)){
				core::vector3df xzintx = node->getPosition();
				xzintx.X -= 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.x = " << xzintx.X << endl;
			}else if(receiver.IsKeyDown(KEY_KEY_6)){
				core::vector3df xzintx = node->getPosition();
				xzintx.X += 1.5f;
				node->setPosition(xzintx);
						cout << "xzintx.x = " << xzintx.X << endl;
			}
			if(receiver.IsKeyDown(KEY_KEY_7)){
				core::vector3df xzintx = node->getRotation();
				xzintx.X -= 1.5f;
				node->setRotation(xzintx);
						cout << "xzintx.x = " << xzintx.X << endl;
			}else if(receiver.IsKeyDown(KEY_KEY_8)){
				core::vector3df xzintx = node->getRotation();
				xzintx.X += 1.5f;
				node->setRotation(xzintx);
						cout << "xzintx.x = " << xzintx.X << endl;
			}
			if(receiver.IsKeyDown(KEY_KEY_9)){
				core::vector3df xzintx = node->getRotation();
				xzintx.Y -= 1.5f;
				node->setRotation(xzintx);
						cout << "xzintx.y = " << xzintx.Y << endl;
			}else if(receiver.IsKeyDown(KEY_KEY_0)){
				core::vector3df xzintx = node->getRotation();
				xzintx.Y += 1.5f;
				node->setRotation(xzintx);
						cout << "xzintx.y = " << xzintx.Y << endl;
			}
			if(receiver.IsKeyDown(KEY_MINUS)){
				core::vector3df xzintx = xnode->getPosition();
				xzintx.X -= 1.5f;
				xnode->setPosition(node->getAbsolutePosition());
						cout << "xzintx.x *= " << xzintx.X << endl;
			}else if(receiver.IsKeyDown(KEY_PLUS)){
				core::vector3df xzintx = xnode->getPosition();
				xzintx.X += 1.5f;
				xnode->setPosition(((node->getAbsolutePosition() - znode->getAllJoints()[4]->LocalAnimatedMatrix.getTranslation()) * (camera->getTarget() - camera->getAbsolutePosition()).normalize()));
						cout << "xzintx.x -= " << xzintx.X << endl;
			}
			if(receiver.IsKeyDown(KEY_HOME)){
				core::vector3df xzintx = xnode->getPosition();
				xzintx.Z -= 1.5f;
				xnode->setPosition(((node->getAbsolutePosition() + znode->getAllJoints()[4]->LocalAnimatedMatrix.getTranslation()) * (camera->getTarget() - camera->getAbsolutePosition()).normalize()));
						cout << "xzintx.z += " << xzintx.Z << endl;
			}else if(receiver.IsKeyDown(KEY_END)){
				core::vector3df xzintx = xnode->getPosition();
				xzintx.Z += 1.5f;
				xnode->setPosition(node->getJointNode(4)->getAbsolutePosition());
						cout << "xzintx.z += " << xzintx.Z << endl;
			}
			if(receiver.IsKeyDown(KEY_LSHIFT)){
				break;
			}
			if(receiver.IsKeyDown(KEY_LCONTROL)){
				cout << "camera.x = " << camera->getRotation().X << endl;
				camera->setTarget(xnode->getAbsolutePosition());
			}/**
				if(receiver.MouseState.Position.X != xmouseposx){
					core::vector3df xzintx = camera->getRotation();
					xzintx.Y -= (xmouseposx - receiver.MouseState.Position.X);
					camera->setRotation(xzintx);
					xmouseposx = receiver.MouseState.Position.X;
				}
				if(receiver.MouseState.Position.Y != xmouseposy){
					//zxinty += (xmouseposy - receiver.MouseState.Position.Y);
					core::vector3df xzintx = camera->getRotation();
					int xzintx2 = 0;
					xzintx2 -= (xmouseposy - receiver.MouseState.Position.Y);
					int xzintx3 = 0;
					xzintx3 = xzintx.X - 90;
					if(xzintx3 < 0){
						xzintx3 += 360;
					}
					if((xzintx3 + xzintx2) > 355){
						xzintx.X = 85;
					}else if((xzintx3 + xzintx2) < 185){
						xzintx.X = 275;
					}else{
						xzintx.X += xzintx2;
					}
					camera->setRotation(xzintx);
					xmouseposy = receiver.MouseState.Position.Y;
				}**/
					core::vector3df intersection;
					core::triangle3df hitTriangle;
					core::line3d<f32> ray;
		//ray.start = camera->getPosition();
		//ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;
					ray = collMan->getRayFromScreenCoordinates(core::vector2d<s32>(receiver.MouseState.Position.X, receiver.MouseState.Position.Y), camera);
		scene::ISceneNode * selectedSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
					ray,
					intersection, // This will be the position of the collision
					hitTriangle, // This will be the triangle hit in the collision
					4, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0);
					if(selectedSceneNode){
						if(device->getCursorControl()->getActiveIcon() != zxcursor1){
							device->getCursorControl()->setActiveIcon(zxcursor1);
							cout << "rolled over npc" << endl;
						}
					}else{
						if(device->getCursorControl()->getActiveIcon() != zxcursor2){
							device->getCursorControl()->setActiveIcon(zxcursor2);
							cout << "rolled off npc" << endl;
						}
					}
			if(receiver.MouseState.LeftButtonDown){
				if(!xhadmouse){
					if(xbulletnumber < 16){
						if(x.zguninfo.xbulletcount2 > 0){
						if(xfps.timer->getTime() - x.zguninfo.xattackspeed >= x.xlasthadmouse){
						int zxint = 0;
						for(int xint = 0;xint < 16;xint++){
							if(xbulletnumberint[xint] == 0){
								xbulletnumberint[xint] = 1;
								node2[xint]->setPosition(node->getJointNode(4)->getAbsolutePosition());
								node2[xint]->setRotation(znode->getAllJoints()[4]->GlobalAnimatedMatrix.getRotationDegrees().normalize() + core::vector3df(90.0f, 0.0f, 0.0f));
								core::vector3df xbulletdir = ((camera->getTarget() - node->getJointNode(4)->getAbsolutePosition()).normalize());
								core::vector3df xbulletdir2 = core::vector3df(x.zguninfo.xattackaccuracyint);
								xbulletdir2 /= core::vector3df(100.0f);
								srand(xfps.timer->getTime());
								xbulletdir2.X *= ((((rand() % int((100.0f - x.zguninfo.xattackaccuracy) * 100)) + 1) / 100));
								xbulletdir2.Y *= ((((rand() % int((100.0f - x.zguninfo.xattackaccuracy) * 100)) + 1) / 100));
								xbulletdir2.Z *= ((((rand() % int((100.0f - x.zguninfo.xattackaccuracy) * 100)) + 1) / 100));
								//xbulletdir2.X *= (rand() % 2) == 1 ? (-1 * ((rand() % 25) / 100) + 1) : (1 * ((rand() % 125) / 100) -1);
								//xbulletdir2.Y *= (rand() % 2) == 1 ? (-1 * ((rand() % 25) / 100) + 1) : (1 * ((rand() % 125) / 100) -1);
								//xbulletdir2.Z *= (rand() % 2) == 1 ? (-1 * ((rand() % 25) / 100) + 1) : (1 * ((rand() % 125) / 100) - 1);
								xbulletdir2.X -= (rand() % (int(2 * (xbulletdir2.X * 100)) + 1) / 100);
								xbulletdir2.Y -= (rand() % (int(2 * (xbulletdir2.Y * 100)) + 1) / 100);
								xbulletdir2.Z -= (rand() % (int(2 * (xbulletdir2.Z * 100)) + 1) / 100);
								xbulletdir2.X += xbulletdir.X;
								xbulletdir2.Y += xbulletdir.Y;
								xbulletdir2.Z += xbulletdir.Z;
								xbulletdir2.X *= (rand() % 2) == 1 ? (1) : (1);
								xbulletdir2.Y *= (rand() % 2) == 1 ? (1) : (1);
								xbulletdir2.Z *= (rand() % 2) == 1 ? (1) : (1);
								xbulletdirint[xint] = xbulletdir2;
								cout << "xbulletdir = " << (camera->getTarget() - camera->getAbsolutePosition()).X << " + " << xbulletdir2.X << ", " << endl;
								cout << (camera->getTarget() - camera->getAbsolutePosition()).Y << " + " << xbulletdir2.Y << ", " << endl;
								cout << (camera->getTarget() - camera->getAbsolutePosition()).Z << " + " << xbulletdir2.Z << ", " << endl;
								cout << "x = " << node2[xint]->getAbsolutePosition().X << ", " << endl;
								cout << "y = " << node2[xint]->getAbsolutePosition().Y << ", " << endl;
								cout << "z = " << node2[xint]->getAbsolutePosition().Z << endl;
								node2[xint]->setRotation(node2[xint]->getRotation() + camera->getRotation());
								xbulletdistanceint[xint] = 0;
								xbulletnumber++;
								x.zguninfo.xbulletcount2--;
								x.xlasthadmouse = xfps.timer->getTime();
								node2[xint]->setVisible(true);
								cout << "xhadmouse" << endl;
								zxint = 1;
								break;
							}
						}
						if(zxint == 0){
							cout << "no free bullets found D: and xbulletnumber(" << xbulletnumber << ") < 16" << endl;
						}
						}
						}else if(x.zguninfo.xbulletcount > 0){
							if(x.zguninfo.xbulletcount >= x.zguninfo.xmaxbulletcount2){
								x.zguninfo.xbulletcount2 += x.zguninfo.xmaxbulletcount2;
								x.zguninfo.xbulletcount -= x.zguninfo.xmaxbulletcount2;
							}else{
								x.zguninfo.xbulletcount2 += x.zguninfo.xbulletcount;
								x.zguninfo.xbulletcount = 0;
							}
						}
					}else{
						cout << "no free bullets found D:" << endl;
					}
					//xhadmouse = true;
				}
			}else if(xhadmouse){
				xhadmouse = false;
			}
			light2->setPosition(znode->getAllJoints()[3]->GlobalAnimatedMatrix.getTranslation());
			light2->setRotation(znode->getAllJoints()[3]->GlobalAnimatedMatrix.getRotationDegrees());
			driver->beginScene(true, true, video::SColor(255,100,50,220));
			smgr->drawAll();
			env->drawAll();
			if(xbulletnumber > 0){
				for(int xint = 0;xint < 16;xint++){
					if(xbulletnumberint[xint] == 1){
					core::vector3df intersection2;
					core::triangle3df hitTriangle2;
					core::line3d<f32> ray2;
		ray2.start = node2[xint]->getPosition() - xbulletdirint[xint];
		ray2.end = node2[xint]->getPosition() + xbulletdirint[xint];
		scene::ISceneNode * selectedSceneNode2 =
			collMan->getSceneNodeAndCollisionPointFromRay(
					ray2,
					intersection2, // This will be the position of the collision
					hitTriangle2, // This will be the triangle hit in the collision
					IDFlag_IsHighlightable2, // This ensures that only nodes that we have
							// set up to be pickable are considered
					0);
						if(zmonsterdata.xalive && selectedSceneNode2){
							srand(xfps.timer->getTime());
							int xattackstr = int((rand() % int((x.zguninfo.xattackstr * 10))) / 10);
							xattackstr *= rand() % 2 == 1 ? (-1) : (1);
							xattackstr += x.zguninfo.xattackstr * (rand() % 2 == 1 ? (1) : (1));
							if(zmonsterdata.xhp >= xattackstr){
								zmonsterdata.xhp -= xattackstr;
								cout << "attackstr = " << xattackstr << endl;
							}else{
								cout << "attackstr(" << xattackstr << ") = " << zmonsterdata.xhp << endl;
								zmonsterdata.xhp = 0;
							}
							if(zmonsterdata.xhp == 0){
								zmonsterdata.xalive = false;
								xmonsternode->setVisible(false);
								zmonsterdata.xdefeattime = xfps.timer->getTime();
							}
							xbulletdistanceint[xint] = 64;
						}
						if(xbulletdistanceint[xint] < 64){
							//float zxint = (xbulletdistanceint[xint] * 0.01f);
							core::vector3df zxint2 = xbulletdirint[xint];
							node2[xint]->setPosition(node2[xint]->getPosition() + zxint2);
							driver->draw3DLine(ray2.start, ray2.end);
							xbulletdistanceint[xint]++;
						}else{
							xbulletnumberint[xint] = 0;
							xbulletnumber--;
							node2[xint]->setVisible(false);
							cout << "bullet disappeared" << endl;
						}
					}
				}
				driver->draw3DLine(ray.start, ray.end, video::SColor(82, 255, 255, 255));
			}
			if(!zmonsterdata.xalive){
				if(xfps.timer->getTime() > (zmonsterdata.xdefeattime + zmonsterdata.xrespawntime)){
					zmonsterdata.xhp = zmonsterdata.xhpmax;
					zmonsterdata.xalive = true;
					xmonsternode->setVisible(true);
				}
			}
			if(xlastammo != x.zguninfo.xbulletcount2){
				xcharammo = L"";
				xcharammo += zgetintstr2(x.zguninfo.xbulletcount2);
				xcharammo += L" / ";
				xcharammo += zgetintstr2(x.zguninfo.xbulletcount);
				xlastammo = x.zguninfo.xbulletcount2;
			}
			if(xlasthp != zmonsterdata.xhp){
				xmonsterhp = L"";
				xmonsterhp += zgetintstr2(zmonsterdata.xhp);
				xmonsterhp += L" / ";
				xmonsterhp += zgetintstr2(zmonsterdata.xhpmax);
				xlasthp = zmonsterdata.xhp;
			}
			xfont->draw(xcharammo.data(), core::rect<s32>(0, 0, 100, 40), video::SColor(255, 255, 255, 255));
			xfont->draw(xmonsterhp.data(), core::rect<s32>(0, 150, 250, 40), video::SColor(82, 255, 255, 255));
			driver->endScene();
			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw str = L"Irrlicht Engine - example [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
		else
			device->yield();
			xfps.sdlwait();
	}
	device->drop();
	return 0;
}