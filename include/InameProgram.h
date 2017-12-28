#ifndef INAME_SRC_INAME_PROGRAM_H_
#define INAME_SRC_INAME_PROGRAM_H_

#include <iostream>
#include <map>

#include "InameComponent.h"


class InameProgramConfig{
	
};

typedef std::map<int, InameComponent*> ComponentsMap;

class InameProgram{

public:
	
	InameProgram(InameProgramConfig* config);
	virtual ~InameProgram();
	InameComponent* getComponent(int id);
	virtual void onStart() = 0;
	void clearComponents();
	void addComponent(InameComponent* component_p);
	void start();
	
	
private:
	
	void enterMainLoop();
	ComponentsMap components;
	
};

#endif