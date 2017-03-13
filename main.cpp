#include <iostream>
#define NO_NEED_TO_AVERT_RACES
#include <cpprs.h>
#include <SDL.h>
#define LOG_ERR_TRY_GET_SDL_ERRs {sdlgeterrorwritelog();}
#include <sdlminwrapper.h>

using namespace std;

int main(int argc, char *argv[])
{
	try{
		sdl sdl_ph{SDL_INIT_VIDEO};
		if(!SDL_HasClipboardText()){std::clog<<"No text found\n"; return 1;}
		auto ctext=SDL_GetClipboardText();
		if(!ctext){LOG_ERR_TRY_GET_SDL_ERRs STD_CLOG_FILE_FUNC_LINE; return 1;}
		auto rem=strchr(ctext,'\\');
		if(rem){
			do{
				*rem='/';
				rem=strchr(rem+1,'\\');
			}while(rem);
		}else{
			for(rem=ctext;;){
				rem=strchr(rem,'/');
				if(!rem)break;
				*rem='\\';
				++rem;
			}
		}
		if(SDL_SetClipboardText(ctext)){LOG_ERR_TRY_GET_SDL_ERRs STD_CLOG_FILE_FUNC_LINE; return 1;}
		return 0;
	}catch(const std::exception &e){
		STD_CLOG_FILE_FUNC_LINE_EX_FLUSH_NOEXCEPTs(e)
	}catch(...){
		STD_CLOG_FILE_FUNC_LINE_FLUSH_NOEXCEPTs
	}
	return 1;
}
