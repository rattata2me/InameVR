#ifndef INAME_SRC_INAME_CONTROLLER_H_
#define INAME_SRC_INAME_CONTROLLER_H_

class InameComponent{
	
public:
	InameComponent(int id);
	virtual ~InameComponent();
	int getId() const;
	void setId(int newid);
	
private:
	int component_id;
};

#endif