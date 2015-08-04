// Connecting_with_SQLConnect.cpp
// compile with: user32.lib odbc32.lib
#include <windows.h>
#include "Shlwapi.h"
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int checkForFile(char *fname){
	int exists = 0;
	exists = PathFileExistsA(fname);
	return exists;
}int zgetExponent(int xint, int zExponent){
	//
	int zint = 0;
	int zxint = 0;
	zint = xint;
	for(zxint = 1;zxint < zExponent;zxint++){
		zint *= xint;
	}
	return zint;
}
float zgetExponent2(float xint, float zExponent){
	//
	float zint = 0;
	int zxint = 0;
	zint = xint;
	for(zxint = 1;zxint < zExponent;zxint++){
		zint *= xint;
	}
	return zint;
}
bool zControlKeyEnterLetter(char xchar){
	//
	switch(xchar){
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case '/':
		case '.':
		case '_':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':{
			return true;
			break;
			   }
		default:{
			return false;
				}
	}
}
bool zControlKeyEnterSyntax(char xchar){
	//
	switch(xchar){
		case '(':
		case ')':{
			return true;
			break;
				 }
		case ',':{
			return true;
			break;
				 }
		default:{
			return false;
				}
	}
}
bool zControlKeyEnterNumber(char xchar){
	//
	switch(xchar){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':{
			return true;
			break;
				 }
		default:{
			return false;
				}
	}
}
int intconvchar(std::string xchar){
	//
	char zchar = xchar[0];
	//zchar = xchar.data();
	switch(zchar){
		case '0':{
			return 0;
			break;
				 }
		case '1':{
			return 1;
			break;
				 }
		case '2':{
			return 2;
			break;
				 }
		case '3':{
			return 3;
				 }
		case '4':{
			return 4;
			break;
				 }
		case '5':{
			return 5;
			break;
				 }
		case '6':{
			return 6;
			break;
				 }
		case '7':{
			return 7;
			break;
				 }
		case '8':{
			return 8;
			break;
				 }
		case '9':{
			return 9;
			break;
				 }
		default:{
			return 0;
				}
	}
}
int intconvstr(std::string xchar){
	//
	if(xchar.length() < 1){
		return 0;
	}
	int xint = 0;
	std::string xstring = "";
	for(int i=0;i<xchar.length();i++){
		xstring = xchar[((xchar.length() - 1) - i)];
		xint += (intconvchar(xstring) * (i > 0 ? (zgetExponent(10, i)) : (1)));
	}
	if(xchar[0] == '-'){
		//xint -= 2;
		/**
		float xint2 = 0;;
		xint2 = xint;
		xint2 *= -1;
		return xint2;**/
	}
	return xint;
}
int intconvstr2(std::string xchar, int xint2){
	//
	if(xchar.length() < 1){
		return 0;
	}
	int xint = 0;
	int xint3 = 0;
	xint3 = xchar.length();
	if(xint2 < xint3){
		xint3 = xint2;
	}
	std::string xstring = "";
	for(int i=0;i<xint3;i++){
		xstring = xchar[((xchar.length() - 1) - i)];
		if(xstring == "."){
			break;
		}
		xint += (intconvchar(xstring) * (i > 0 ? (zgetExponent(10, i)) : (1)));
	}
	if(xchar[0] == '-'){
		//xint -= 2;
		/**
		float xint2 = 0;;
		xint2 = xint;
		xint2 *= -1;
		return xint2;**/
	}
	return xint;
}
float floatconvstr(std::string xchar){
	//
	if(xchar.length() < 1){
		return 0;
	}
	float xint = 0;
	float xint2 = 0;
	int xint3 = 0;
	bool xbool = false;
	int xint4 = xchar.length();
	int xint5 = 0;
	for(int i=0;i<xint4;i++){
		if(xchar[i] == '.'){
			xbool = true;
			xint5 = i;
			break;
		}
	}
	std::string xstring = "";
	if(xbool){
		for(int i=0;i<xint4;i++){
			xstring = xchar[((xchar.length() - 1) - i)];
			if(xstring == "."){
				xint3 = i;
				//xint3++;
				break;
			}
			xint2 = float((xint4 + 1) - i);
			xint2 *= -1;
			xint += (intconvchar(xstring) * (i > 0 ? (zgetExponent2(10, xint2)) : (1)));
		}
	}
	for(int i=xint3;i<xint4;i++){
		xstring = xchar[((xchar.length() - 1) - i)];
		if(xstring == "."){
			break;
		}
		xint += (intconvchar(xstring) * (i > 0 ? (zgetExponent(10, i)) : (1)));
	}
	if(xchar[0] == '-'){
		//xint -= 2;
		/**
		float xint2 = 0;;
		xint2 = xint;**/
		xint2 = xint;
		xint2 *= -1;
		return xint2;
	}
	return xint;
}
std::string zgetintstr(int xint){
	ostringstream osstream;
	osstream << xint;
	return osstream.str();
}
std::wstring zgetintstr2(int xint){
	wostringstream osstream;
	osstream << xint;
	return osstream.str();
}
class MyEventReceiver : public IEventReceiver
{
public:
    struct SMouseState
    {
        core::position2di Position;
        bool LeftButtonDown;
        bool RightButtonDown;
		float wheel;
        SMouseState() : LeftButtonDown(false), wheel(7) { }
    } MouseState;
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.LeftButtonDown = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.LeftButtonDown = false;
                break;

            case EMIE_RMOUSE_PRESSED_DOWN:
                MouseState.RightButtonDown = true;
                break;

            case EMIE_RMOUSE_LEFT_UP:
                MouseState.RightButtonDown = false;
                break;

            case EMIE_MOUSE_MOVED:
                MouseState.Position.X = event.MouseInput.X;
                MouseState.Position.Y = event.MouseInput.Y;
                break;

			case irr::EMOUSE_INPUT_EVENT::EMIE_MOUSE_WHEEL:
				MouseState.wheel += event.MouseInput.Wheel;
				break;

            default:
                // We won't use the wheel
                break;
            }
        }
		//if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
			//KeyIsDown[event.MouseInput.ButtonStates] = event.MouseInput.isLeftPressed;
		//if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
			//KeyIsDown[event.MouseInput.ButtonStates] = event.MouseInput.Event;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

	virtual bool ControlKeyCheck(int keyint) const{
		return KeyIsDown[keyint];
	}
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
class xfpslimiter{
	//
	int MaxFPS;
	int MaxSDLFPS;
	int FPS;
public:
	int nowTime;
	xfpslimiter();
	void sdlwait();
	irr::ITimer *timer;
};
xfpslimiter::xfpslimiter(){
	//
	MaxFPS = 30;
	MaxSDLFPS = 30;
	FPS = 0;
	nowTime = 0;
}
void xfpslimiter::sdlwait(){
	if(timer->getTime() - nowTime < 1000/MaxFPS){
		FPS = timer->getTime() - nowTime;
		if(FPS == 0){
			Sleep(1000/MaxSDLFPS);
		}else{
			Sleep(int((int((1000/FPS)))/MaxSDLFPS));
		}
	}
}
struct accountdata{
	//
	int chartype;
	int charclass;
	int promotion;
	int expe;
	int charlevel;
	int expeNeeded;
	std::string charname;
	int money;
	std::string xloc;
	int hudcharint;
	//xCharParty xpt;
};
void xblit(video::IImage *xint, video::IImage *xint2, core::rect<s32> xrect){
	//
	if(xrect.isPointInside(core::vector2di(xint2->getDimension().Width, xint2->getDimension().Height)) || (xrect.LowerRightCorner.X <= xint2->getDimension().Width && xrect.LowerRightCorner.Y <= xint2->getDimension().Height)){
		cout << "xint = " << xint->getDimension().Width << ", " << xint->getDimension().Height << endl;
		cout << "xint2 = " << xint2->getDimension().Width << ", " << xint2->getDimension().Height << endl;
		cout << "xrect = " << xrect.UpperLeftCorner.X << ", " << xrect.UpperLeftCorner.Y << ", " << xrect.LowerRightCorner.X << ", " << xrect.LowerRightCorner.Y << endl;
		for(int zxint = xrect.UpperLeftCorner.X;zxint < xrect.LowerRightCorner.X;zxint++){
			for(int zxint2 = xrect.UpperLeftCorner.Y;zxint2 < xrect.LowerRightCorner.Y;zxint2++){
				xint2->setPixel(zxint, zxint2, xint->getPixel((zxint - 8), (zxint2 - 8)));
			}
		}
	}else{
		cout << "blit would not fit" << endl;
	}
}
void xblit2(video::IImage *xint, video::IImage *xint2, core::rect<s32> xrect, bool xpixelbool, video::SColor xpixel){
	//
	if(xrect.isPointInside(core::vector2di(xint2->getDimension().Width, xint2->getDimension().Height)) || (xrect.LowerRightCorner.X <= xint2->getDimension().Width && xrect.LowerRightCorner.Y <= xint2->getDimension().Height)){
		if(xpixelbool){
			for(int zxint = xrect.UpperLeftCorner.X;zxint < xrect.LowerRightCorner.X;zxint++){
				for(int zxint2 = xrect.UpperLeftCorner.Y;zxint2 < xrect.LowerRightCorner.Y;zxint2++){
					if(xint->getPixel(zxint, zxint2) != xpixel){
						xint2->setPixel(zxint, zxint2, xint->getPixel(zxint, zxint2));
					}
				}
			}
		}else{
			for(int zxint = xrect.UpperLeftCorner.X;zxint < xrect.LowerRightCorner.X;zxint++){
				for(int zxint2 = xrect.UpperLeftCorner.Y;zxint2 < xrect.LowerRightCorner.Y;zxint2++){
					xint2->setPixel(zxint, zxint2, xint->getPixel(zxint, zxint2));
				}
			}
		}
	}
}
s32 AddIconToSpriteBank( gui::IGUISpriteBank * spriteBank, video::IVideoDriver* driver, const io::path& file, const core::rect<s32>& rect )
{
if ( !spriteBank || !driver )
return -1;
video::ITexture * tex = driver->getTexture( file );
if ( tex )
{
core::array< core::rect<irr::s32> >& spritePositions = spriteBank->getPositions();
spritePositions.push_back( rect );
array< SGUISprite >& sprites = spriteBank->getSprites();
spriteBank->addTexture( tex );
gui::SGUISpriteFrame frame;
frame.rectNumber = spritePositions.size()-1;
frame.textureNumber = spriteBank->getTextureCount()-1;
SGUISprite sprite;
sprite.frameTime = 0;
sprite.Frames.push_back( frame );
sprites.push_back( sprite );
return sprites.size()-1;
}
return -1;
}
struct xguninfo{
	float xbulletspeed;
	int xbulletcount;
	int xbulletcount2;
	int reloadtime;
	int xattackspeed;
	int xmaxbulletcount2;
	int xmaxbulletcount;
	int xattackstr;
	float xattackaccuracy;
	float xattackaccuracyint;
};
struct xhud{
	video::ITexture *xmainhud;
	video::ITexture *xmain2;
};
class xcharaccountdata{
public:
	xcharaccountdata();
	accountdata z;
	xguninfo zguninfo;
	int xlasthadmouse;
	xhud zhud;
};
xcharaccountdata::xcharaccountdata(){
	//
	zguninfo.xbulletspeed = 0.01f;
	zguninfo.xbulletcount2 = 30;
	zguninfo.xbulletcount = 180;
	zguninfo.xattackspeed = 100;
	zguninfo.xmaxbulletcount2 = 30;
	zguninfo.xmaxbulletcount = 180;
	zguninfo.xattackaccuracy = 90.0f;
	zguninfo.xattackaccuracyint = 2.0f;
	zguninfo.xattackstr = 10;
	xlasthadmouse = 0;
}
class xmonsteraccountdata{
public:
	xmonsteraccountdata();
	int xrespawntime;
	int xdefeattime;
	int xhp;
	int xhpmax;
	bool xalive;
};
xmonsteraccountdata::xmonsteraccountdata(){
	//
	xrespawntime = 1000;
	xdefeattime = 0;
	bool xalive = false;
	xhp = 0;
	xhpmax = 100;
}