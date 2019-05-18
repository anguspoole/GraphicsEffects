#ifndef _cBasicTextureManager_HG_
#define _cBasicTextureManager_HG_

#include <string>
#include <map>
#include "CTextureFromBMP.h"
#include <vector>

// The texture manager now holds information for the FBOs, too
// This is so it can look them up as "normal" textures
#include "../cFBO.h"

class cBasicTextureManager
{
public:
	bool Create2DTextureFromBMPFile( std::string textureFileName, bool bGenerateMIPMap );

	bool Create2DTextureFromBMPFile_ASYNC( std::string textureFileName, bool bGenerateMIPMap );

	// Picks a random texture from the textures loaded
	std::string PickRandomTexture(void);


	bool CreateCubeTextureFromBMPFiles( std::string cubeMapName, 
		                                std::string posX_fileName, std::string negX_fileName, 
		                                std::string posY_fileName, std::string negY_fileName, 
										std::string posZ_fileName, std::string negZ_fileName, 
										bool bIsSeamless, std::string &errorString );

	// This will be for the off screen FBO textures
	struct sFBOTextureInfo
	{
		GLuint FBO_ID;				// Not really needed
		std::string friendlyName;
		GLuint textureID;
	};
	bool AddFBOTextures( cFBO* pTheFBO, std::vector<sFBOTextureInfo> );

	// returns 0 on error
	// Note: This is being called multiple times per frame, usually.
	GLuint getTextureIDFromName( std::string textureFileName );

	void SetBasePath(std::string basepath);


	// Check to see if the texture has been loaded, and is ready to go into the GPU
	// This gets called every frame (maybe) to see if there are some textures ready to go.
	bool CheckForPendingTextureGPULoads(void);

private:




	std::string m_basePath;
	std::string m_lastError;
	void m_appendErrorString( std::string nextErrorText );
	void m_appendErrorStringLine( std::string nextErrorTextLine );

	// Alter this a little bit so that it also shows when the texture
	// has been loaded from the hard drive and is ready to be copied
	// into the GPU.... 

	std::map< std::string, CTextureFromBMP* > m_map_TexNameToTexture;

	// This does the actual loading of the textures
	bool m_LoadPendingTextureIntoGPU(std::map< std::string, CTextureFromBMP* >::iterator itTextureToLoad);

};

#endif
