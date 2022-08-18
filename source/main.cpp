#include <RSGL/RSGL.hpp>
#include "../include/parser.hpp"
bool running=true;
RSGL::window win("RSGL Calculator",{500,500,350,320},{37,37,37});

struct button{
	RSGL::rect r;
	RSGL::color c;
	RSGL::color hoverC;
	RSGL::color clickC;
	RSGL::color color;
	std::string text;
	bool pressed=false; bool clicked=false;
	void events();
};

void button::events(){
	if (win.event.type == RSGL::MouseButtonPressed && RSGL::RectCollidePoint(r,{win.event.mouse.x,win.event.mouse.y}) || clicked){ color = clickC; clicked=true;}
	else if (RSGL::RectCollidePoint(r,{win.event.mouse.x,win.event.mouse.y})) color = hoverC;
	else color=c;
	if (win.event.type == RSGL::MouseButtonReleased) clicked=false;
	if (win.event.type == RSGL::MouseButtonReleased && RSGL::RectCollidePoint(r,{win.event.mouse.x,win.event.mouse.y})) pressed=true;
	else pressed=false;
}

std::vector<button> buttons;
std::string sbuttons = "789/<C456*()123-^v0.%+=";

std::string lowerl = "abcdefghijklmnopqrstuvwxyz";  std::string bigl = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::vector <std::string> answers={};
std::vector <std::string> answers2={};

std::string lower(std::string letter){
	std::string output=letter;
	for (int i=0; i < bigl.size(); i++){ if (letter.at(0) == bigl.at(i)){ output=lowerl.at(i); break;}}
	return output;
}


int main(){
	int answery=0; 
	int p=0; std::string text="";
	for (int y=0; y < 4; y++){
		for (int x=0; x < 6; x++){
			if (y == 3 && x == 4){ std::string text="";  
				buttons.insert(buttons.end(),{{ 13 + (x* (23 + 30)) , 190 + (y* (32)),45*2,26},.c={45,174,148},.hoverC={51,198,168},.clickC={69,207,178}, .text= text+text+sbuttons.at(p)}); break;
			}
			else if (y == 3 && x > 3) break;
			buttons.insert(buttons.end(),{{ 13 + (x* (23 + 30)) , 190 + (y* (32)),45,26},.c={43,43,43},.hoverC={64,64,64},.clickC={240,84,76}, .text= text+text+sbuttons.at(p) }); p++;
		}
	}
	
	std::string textBox=""; int x1=0;
	button answerScroll = {{345,64,5,50},.c={43,43,43},.hoverC={64,64,64},.clickC={240,84,76}};
	int pmouseY=0; bool pressed=false;
	
	while (running){
		win.checkEvents();
		answerScroll.events();
		for (int i=0; i < answers.size(); i++){
			int y=0;
			if (answers.size() > 3) y= answery * 35;
			if (answers.at(i).size() < 15) RSGL::drawText(answers.at(i),{10,(92 - i*35) + y,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{200,188,188});
			else{ 
				std::string text="";
				for (int j=0; j < 15; j++) text+= answers.at(i).at(j);
				RSGL::drawText(text+"...",{10,(92 - i*35) + y,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{200,188,188});
			}
			RSGL::drawText("=",{200,(92 - i*35) + y,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{104,99,99});
			if (answers2.at(i).size() < 10) RSGL::drawText(answers2.at(i),{320 - (11*((int)answers2.at(i).size()-1)),(92 - i*35) + y,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{200,188,188});
			else{ 
				std::string text="";
				for (int j=0; j < 10; j++) text+= answers2.at(i).at(j);
				RSGL::drawText( text+"...",{320 - (11*(10-1)),(92 - i*35) + y,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{200,188,188});
			}
			if (win.event.type == RSGL::MouseButtonReleased && RSGL::RectCollidePoint({10,(92 - i*35) + y,20 * (int)answers.at(i).size(),20},{win.event.mouse.x,win.event.mouse.y})){
				textBox += answers.at(i);
			}
			else if (win.event.type == RSGL::MouseButtonReleased && RSGL::RectCollidePoint({320 - (11*(10-1)),(92 - i*35) + y,20,20* (int)answers.at(i).size()},{win.event.mouse.x,win.event.mouse.y}) ||
				win.event.type == RSGL::MouseButtonReleased && RSGL::RectCollidePoint({320 - (11*((int)answers2.at(i).size()-1)),(92 - i*35) + y,20,20* (int)answers.at(i).size()},{win.event.mouse.x,win.event.mouse.y})){
				textBox += answers2.at(i);
			}
		}
		RSGL::drawRect({0,115,350,200},{38,38,38});
		RSGL::drawRect({0,115,350,1},{0,0,0});
		RSGL::drawRect({0,180,350,200},{34,34,34});
		RSGL::drawRect({0,180,350,1},{0,0,0});
		RSGL::drawRoundRect(answerScroll.r,answerScroll.color);
		if (textBox.size() > 30) x1 = 11*(textBox.size()-30);
		else x1=0;
		RSGL::drawText(textBox,{10-x1,130,20},"/usr/share/fonts/TTF/DejaVuSans.ttf",{200,188,188});
		for (int i=0; i < buttons.size(); i++){ 
			buttons.at(i).events();
			RSGL::drawRoundRect(buttons.at(i).r,buttons.at(i).color); RSGL::drawRoundRect(buttons.at(i).r,{0,0,0},false);
			int x2=20, y2=4;
			if (i == buttons.size()-1){ x2=30; y2=-4; }
			RSGL::drawText(buttons.at(i).text,{ buttons.at(i).r.x+x2, buttons.at(i).r.y+y2, (int)(buttons.at(i).r.width/2.5) },"/usr/share/fonts/TTF/DejaVuSans.ttf",{255,255,255});
			if (buttons.at(i).pressed){
				if (buttons.at(i).text == "C") textBox="";
				else if (buttons.at(i).text == "<"){ if(textBox.size()) textBox.erase(textBox.end()-1);}
				else if (buttons.at(i).text == "="){ 
					answers.insert(answers.begin(),textBox);
					answers2.insert(answers2.begin(),parse(textBox));
					textBox = "";
				}
				else textBox += buttons.at(i).text;
			}	
		}
		switch (win.event.type){
			case RSGL::quit: running=false; break;
			case RSGL::KeyPressed:
				if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "exclam") textBox += '1';
				else if ( !win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "at") textBox += '2';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "numbersign") textBox += '3';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "dollar") textBox += '4';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "percent") textBox += '5';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "asciicircum") textBox += '6';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "ampersand") textBox += '7';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "asterisk") textBox += '8';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "parenleft") textBox += '9';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "parenright") textBox += '0';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "question") textBox += '/';
				else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R") && win.event.key == "underscore") textBox += '-';
				else if (win.event.key == "plus" && win.isPressed("Shift_L") || win.event.key == "plus" &&  win.isPressed("Shift_R")) textBox += '+';
				else if (win.event.key == "greater" && win.isPressed("Shift_L") ||  win.event.key == "greater" &&  win.isPressed("Shift_R")) textBox += '.';
				else if (win.event.key == "percent") textBox += '%';
				else if (win.event.key == "asciicircum") textBox += '^';
				else if (win.event.key == "parenleft") textBox += '(';
				else if (win.event.key == "parenright") textBox += ')';
				else if (win.event.key == "space") textBox += ' ';
				else if ( win.event.key == "asterisk") textBox += '*';
				
				else if (win.event.key.size() == 1){ 
					if (win.isPressed("Shift_L") || win.isPressed("Shift_R")) textBox += win.event.key;
					else if (!win.isPressed("Shift_L") && !win.isPressed("Shift_R")) textBox += lower(win.event.key);
				}
				else if (win.event.key == "BackSpace") { 
					//if ()
					if(textBox.size() && textBox.at(textBox.size()-1) == ']') textBox.erase(textBox.end()-1);
				}
				else if (win.event.key == "Return"){
					answers.insert(answers.begin(),textBox);
					answers2.insert(answers2.begin(),parse(textBox));
					textBox = "";
				}
				break; 
			case RSGL::MousePosChanged:
				if (win.event.mouse.y > 115) answerScroll.c.a = 0;
				else answerScroll.c.a = 225;
				if (pmouseY < win.event.mouse.y && answerScroll.clicked && answerScroll.r.y+3 <= 64 && answery > 0){ answerScroll.r.y += 3; answery--; }
				else if (pmouseY > win.event.mouse.y && answerScroll.clicked && answerScroll.r.y-6 >= 0 && answery < answers.size()-3){ answerScroll.r.y -= 3; answery++; }
				pmouseY = win.event.mouse.y;
				break;
			case RSGL::MouseButtonReleased:
				if (win.event.button == RSGL::mouseScrollUp){ if (answery < answers.size()-3) answery+=1;}
				else if (win.event.button == RSGL::mouseScrollDown){ if (answery > 0) answery-=1;}
				break;
			default: break;
		}
		win.clear();
	} win.close();
}