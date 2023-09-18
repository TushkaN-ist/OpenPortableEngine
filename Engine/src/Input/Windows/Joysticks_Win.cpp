#include <Input/Windows/Joysticks_Win.h>
#include <typeinfo>

std::vector<WJoystick*> joys;
std::map<int,Joystick*> joysMap;
libenjoy_context *ctx=NULL;

uint8_t WJoystick::BitCheck(uint8_t keycode){
	return ((keys[keycode/16]>>((keycode%16)*2))&3);
}
WJoystick::WJoystick(int id){
	SetInfo(id);
	joys.push_back(this);
}
WJoystick::WJoystick(libenjoy_joy_info* info){
	SetInfo(info);
	joys.push_back(this);
}
WJoystick::~WJoystick(){
	Close();
	if (ctx){
		for(std::map<int,Joystick*>::iterator i = joysMap.begin(); i!=joysMap.end(); i++){
			if (i->second == (Joystick*)this){
				joysMap.erase(i);
			}
		}
	}
	for(std::vector<WJoystick*>::iterator i = joys.begin();i!=joys.end();i++){
		if (*i==this)
		{
			joys.erase(i);
			break;
		}
	}
}
void WJoystick::Init(){
	if (ctx==NULL){
		ctx = libenjoy_init();
		printf("Joys Init\n");
	}
	libenjoy_enumerate(ctx);
}
void WJoystick::Free(){
	if (ctx){
		std::vector<Joystick*> joys;
		for(std::map<int,Joystick*>::iterator i = joysMap.begin(); i!=joysMap.end();i++){
			joys.push_back(i->second);
		}
		joysMap.clear();
		int joyCount=joys.size();
		for(int i=0;i<joyCount;++i){
			delete joys[i];
		}
		joys.clear();
		libenjoy_close(ctx);
		ctx=NULL;
		printf("Joys Free:%i\n",joyCount);
	}
}
void WJoystick::Update(){
	if (!ctx)
		return;
    libenjoy_event ev;
	int i=0;
	while(libenjoy_poll(ctx, &ev)){i++;}
	/*for(std::map<int,Joystick*>::iterator i = joysMap.begin(); i!=joysMap.end(); i++){
		if (typeid(i->second) == typeid(WJoystick)){
			printf("%s\n",i->second->Name());
			((WJoystick*)(i->second))->UpdateBTNS();
		}
	}*/
	/*for(std::vector<WJoystick*>::iterator i = joys.begin();i!=joys.end();i++){
		(*i)->UpdateBTNS();
	}*/
	if (i>0){
		int joyCount = joys.size();
		for(int i=0;i<joyCount;++i){
			joys[i]->UpdateBTNS();
		}
	}
}
Joystick* WJoystick::GetJoy(int id){
	std::map<int,Joystick*>::iterator f = joysMap.find(id);
	Joystick *joy;
	if (f == joysMap.end()){
		if (ctx && id < ctx->info_list.count){
			joy = new WJoystick(ctx->info_list.list[id]);
		}else{
			joy = new Joystick();
		}
		joysMap.insert(std::pair<int,Joystick*>(id,joy));
	}else{
		joy = f->second;
		if (typeid(joy) != typeid(WJoystick)){
			delete joy;
			joy = new WJoystick(ctx->info_list.list[id]);
			joysMap[id] = joy;// .insert(std::pair<int,Joystick*>(id,joy));
		}
	}
	return joy;
}
void WJoystick::UpdateStates(){
	int i=0;
	int btins = BtnsCount();
	//printf("BTNS:%u\n",btins);
	while(i<btins){
		bool d = Press(i);
		if (_joy->os->buttons[i]){
			if (!d)
				PressKey(i);
		}else{
			if (d){
				ReleaseKey(i);
			}
		}
		++i;
	}
}
void WJoystick::UpdateBTNS(){
	for(uint8_t i=0;i<1;++i){
		//uint32_t k = keys[i];
		keys[i]&=0xAAAAAAAA;
		//printf("%u:%u\n",k,keys[i]);
	}
	UpdateStates();
}
void WJoystick::Reset(){
	for(uint8_t i=0;i<1;++i){
		keys[i]=0;
	}
	//printf("%x\n",keys[0]);
}
void WJoystick::PressKey(uint8_t keycode){
	uint32_t ks=3<<((keycode%16)*2);
	uint32_t k = (keys[keycode/16]&~ks)|ks;
	keys[keycode/16]=k;//3<<((keycode%16)*2);
}
void WJoystick::ReleaseKey(uint8_t keycode){
	uint32_t ks=3<<((keycode%16)*2);
	uint32_t k = (keys[keycode/16]&~ks)|(1<<((keycode%16)*2));
	keys[keycode/16]=k;//3<<((keycode%16)*2);
}
void WJoystick::SetInfo(int id){
	libenjoy_joy_info_list *list = &ctx->info_list;
	SetInfo(list->list[id]);
}
void WJoystick::SetInfo(libenjoy_joy_info* info){
	_info = info;
}

const char* WJoystick::Name(){
	return _info->name;
}
float WJoystick::Axis01(unsigned char axis, float deadzone){
	return (Axis(axis,deadzone)+1.0f)/2.0f;
}
float WJoystick::Axis(unsigned char axis, float deadzone){
	return AxisRaw(axis,32767*deadzone)/32767.0f;
}
short WJoystick::AxisRaw(unsigned char axis,short deadzone){
	if (_joy){
		short value = _joy->os->axes[axis];
		value=value<-32767?-32767:value;
		return value<deadzone && value>-deadzone?0:value;
	}else{
		return 0;
	}
}
unsigned char WJoystick::AxisCount(){
	if (_joy)
		return _joy->num_axes;
	else
		return 0;
}
unsigned char WJoystick::BtnsCount(){
	if (_joy)
		return _joy->num_buttons;
	else
		return 0;
}
void WJoystick::Open(){
	printf("Try open Joy:%s state:",Name());
	Reset();
	if (_joy == nullptr){
		if (ctx){
			_joy = libenjoy_open_joystick(ctx, _info->id);
			printf("OK\n");
		}else
			printf("Error library not Init\n");
	}
}
bool WJoystick::IsOpen(){
	return _joy;
}
void WJoystick::Close(){
	if (_joy != nullptr && ctx){
       	libenjoy_close_joystick(_joy);
		_joy = nullptr;
		printf("Close Joy:%s\n",Name());
	}
}
bool WJoystick::Down(unsigned char keycode){
	return !(BitCheck(keycode)^3);
}
bool WJoystick::Press(unsigned char keycode){
	return BitCheck(keycode)&2;
}
bool WJoystick::Up(unsigned char keycode){
	return !(BitCheck(keycode)^1);
}

void Joystick::Init(){
	WJoystick::Init();
}
void Joystick::Free(){
	WJoystick::Free();
}
int Joystick::GetConnected(){
	if (ctx){
		int joyCount=ctx->info_list.count;
		for(int i =0;i<joyCount;i++){
			printf("ID:%i Name:%s\n",ctx->info_list.list[i]->id,ctx->info_list.list[i]->name);
		}
		return joyCount;
	}else{
		return 0;
	}
}
Joystick* Joystick::GetJoy(int id){
	return WJoystick::GetJoy(id);
}