#ifndef _sScene_HG_
#define _sScene_HG_

// This represents all the things in a "scene".
// Objects are identified by ID or name

#include "cMeshSceneObject.h"
#include <vector>
#include <string>

class cScene
{
public:
	cScene();
	~cScene();

	std::string name;

	bool LoadSceneFromFile(std::string fileName);
	bool SaveSceneToFile(std::string fileName);

	std::vector<cMeshSceneObject> vecMeshObjects;

};

#endif
