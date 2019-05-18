#include "globalOpenGLStuff.h"
#include "globalStuff.h"		// for g_pRogerRabbit

#include "cVAOMeshManager.h"
#include "cMeshSceneObject.h"

#include "DebugRenderer/cDebugRenderer.h"

#include <iostream>

#include "sModelDrawInfo.h"	

#include "cAnimationState.h"

// Skinned mesh object 
// Declared in globalStuff.h
extern cSimpleAssimpSkinnedMesh* g_pRPGSkinnedMesh = NULL;


// Here's the 'Assimp to VAO Converer" thing....
bool AssimpSM_to_VAO_Converter( cSimpleAssimpSkinnedMesh* pTheAssimpSM,
								unsigned int shaderProgramID )
{
	sModelDrawInfo theSMDrawInfo;

	theSMDrawInfo.meshFileName = pTheAssimpSM->fileName;
	theSMDrawInfo.friendlyName = pTheAssimpSM->friendlyName;

	// Copy the data from assimp format into the sModelDrawInfo format...

	theSMDrawInfo.numberOfVertices = pTheAssimpSM->pScene->mMeshes[0]->mNumVertices;
	theSMDrawInfo.numberOfTriangles = pTheAssimpSM->pScene->mMeshes[0]->mNumFaces;

	// We used the "triangulate" option when loading so all the primitives
	//	will be triangles, but BEWARE!
	theSMDrawInfo.numberOfIndices = theSMDrawInfo.numberOfTriangles * 3;

	
	// Allocate the vertex array (it's a c-style array)
	theSMDrawInfo.pMeshData = new cMesh();

	theSMDrawInfo.pMeshData->pVertices = new sVertex_xyz_rgba_n_uv2_bt_4Bones[theSMDrawInfo.numberOfVertices];
	
	// Danger Will Robinson! 
	// You don't really need to do this, but at least it will clear it to zero.
	// (compiler will complain that it's 'not safe', etc.)
	memset( theSMDrawInfo.pMeshData->pVertices, 0, 
			sizeof(sVertex_xyz_rgba_n_uv2_bt_4Bones) * theSMDrawInfo.numberOfVertices );


	for ( unsigned int vertIndex = 0; vertIndex != theSMDrawInfo.numberOfVertices; vertIndex++ )
	{
		theSMDrawInfo.pMeshData->pVertices[vertIndex].x
			= pTheAssimpSM->pScene->mMeshes[0]->mVertices[vertIndex].x;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].y
			= pTheAssimpSM->pScene->mMeshes[0]->mVertices[vertIndex].y;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].z
			= pTheAssimpSM->pScene->mMeshes[0]->mVertices[vertIndex].z;

		// Normals... 
		theSMDrawInfo.pMeshData->pVertices[vertIndex].nx
			= pTheAssimpSM->pScene->mMeshes[0]->mNormals[vertIndex].x;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].ny
			= pTheAssimpSM->pScene->mMeshes[0]->mNormals[vertIndex].y;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].nz
			= pTheAssimpSM->pScene->mMeshes[0]->mNormals[vertIndex].z;

		// Colours... 
		// (If there are no colours, make it hit pink)
		// Note: the method is because you could have more than one set of 
		//	vertex colours in the model (Why? Who the heck knows?) 
		if ( pTheAssimpSM->pScene->mMeshes[0]->HasVertexColors(0) )
		{
			theSMDrawInfo.pMeshData->pVertices[vertIndex].r
				= pTheAssimpSM->pScene->mMeshes[0]->mColors[vertIndex]->r;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].g
				= pTheAssimpSM->pScene->mMeshes[0]->mColors[vertIndex]->g;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].b
				= pTheAssimpSM->pScene->mMeshes[0]->mColors[vertIndex]->b;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].a
				= pTheAssimpSM->pScene->mMeshes[0]->mColors[vertIndex]->a;
		}
		else
		{	// hotpink	#FF69B4	rgb(255,105,180)
			theSMDrawInfo.pMeshData->pVertices[vertIndex].r = 1.0f;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].g = 105.0f/255.0f;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].b = 180.0f/255.0f;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].a = 1.0f;
		}

		//bi-normal  (or bi-tangent)
		theSMDrawInfo.pMeshData->pVertices[vertIndex].bx
			= pTheAssimpSM->pScene->mMeshes[0]->mBitangents[vertIndex].x;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].by
			= pTheAssimpSM->pScene->mMeshes[0]->mBitangents[vertIndex].y;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].bz
			= pTheAssimpSM->pScene->mMeshes[0]->mBitangents[vertIndex].z;

		// Tangent
		theSMDrawInfo.pMeshData->pVertices[vertIndex].tx
			= pTheAssimpSM->pScene->mMeshes[0]->mTangents[vertIndex].x;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].ty
			= pTheAssimpSM->pScene->mMeshes[0]->mTangents[vertIndex].y;
		theSMDrawInfo.pMeshData->pVertices[vertIndex].tz
			= pTheAssimpSM->pScene->mMeshes[0]->mTangents[vertIndex].z;
		
		// uv2 (which are odd in assimp)
		// Note that there is an array of texture coordinates, 
		// up to 8 (actually). Usually, there's only 1
		if ( pTheAssimpSM->pScene->mMeshes[0]->HasTextureCoords(0) )	// 1st UV coords
		{
			// Assume there's 1... (at least)
			theSMDrawInfo.pMeshData->pVertices[vertIndex].u0 
			= pTheAssimpSM->pScene->mMeshes[0]->mTextureCoords[0][vertIndex].x;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].v0
			= pTheAssimpSM->pScene->mMeshes[0]->mTextureCoords[0][vertIndex].y;
		}
		if ( pTheAssimpSM->pScene->mMeshes[0]->HasTextureCoords(1) )	// 2nd UV coords
		{
			theSMDrawInfo.pMeshData->pVertices[vertIndex].u0 
			= pTheAssimpSM->pScene->mMeshes[0]->mTextureCoords[1]->x;
			theSMDrawInfo.pMeshData->pVertices[vertIndex].v0
			= pTheAssimpSM->pScene->mMeshes[0]->mTextureCoords[1]->y;
		}
		// TODO: add additional texture coordinates (mTextureCoords[1], etc.)


		// 4Bones: ids and weights
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneID[0] = pTheAssimpSM->vecVertexBoneData[vertIndex].ids[0];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneID[1] = pTheAssimpSM->vecVertexBoneData[vertIndex].ids[1];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneID[2] = pTheAssimpSM->vecVertexBoneData[vertIndex].ids[2];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneID[3] = pTheAssimpSM->vecVertexBoneData[vertIndex].ids[3];

		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneWeights[0] = pTheAssimpSM->vecVertexBoneData[vertIndex].weights[0];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneWeights[1] = pTheAssimpSM->vecVertexBoneData[vertIndex].weights[1];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneWeights[2] = pTheAssimpSM->vecVertexBoneData[vertIndex].weights[2];
		theSMDrawInfo.pMeshData->pVertices[vertIndex].boneWeights[3] = pTheAssimpSM->vecVertexBoneData[vertIndex].weights[3];

		
	}//for ( unsigned int vertIndex = 0;

	// And the triangles

	// Allocate the array to hold the indices (triangle) info


	// Allocate the array for that (indices NOT triangles)
	theSMDrawInfo.pMeshData->pIndices = new unsigned int[theSMDrawInfo.numberOfIndices];
	
	// Danger Will Robinson! 
	// You don't really need to do this, but at least it will clear it to zero.
	// (compiler will complain that it's 'not safe', etc.)
	memset( theSMDrawInfo.pMeshData->pIndices, 0, 
			sizeof(unsigned int) * theSMDrawInfo.numberOfIndices );


	unsigned int numTriangles = pTheAssimpSM->pScene->mMeshes[0]->mNumFaces;
	unsigned int triIndex = 0;		// Steps through the triangles.
	unsigned int indexIndex = 0;	// Setps through the indices (index buffer)
	for ( ; triIndex != theSMDrawInfo.numberOfTriangles; 
		  triIndex++, indexIndex += 3 )	// Note, every 1 triangle = 3 index steps
	{
		// Get the triangle at this triangle index...
		aiFace* pAIFace = &(pTheAssimpSM->pScene->mMeshes[0]->mFaces[triIndex]);

		theSMDrawInfo.pMeshData->pIndices[indexIndex + 0]				// Offset by 0 (zero)
			= pAIFace->mIndices[0];	// vertex 0

		theSMDrawInfo.pMeshData->pIndices[indexIndex + 1]				// Offset by 1
			= pAIFace->mIndices[1];	// vertex 1

		theSMDrawInfo.pMeshData->pIndices[indexIndex + 2]				// Offset by 2
			= pAIFace->mIndices[2];	// vertex 1
	}//for ( ; triIndex != numVertices; 


	// Calculate the extents on the mesh
	// (Note, because I'm a bone head, this is dupicated...)
	theSMDrawInfo.pMeshData->name = theSMDrawInfo.friendlyName;
	theSMDrawInfo.pMeshData->numberOfIndices = theSMDrawInfo.numberOfIndices;
	theSMDrawInfo.pMeshData->numberOfTriangles = theSMDrawInfo.numberOfTriangles;
	theSMDrawInfo.pMeshData->numberOfVertices = theSMDrawInfo.numberOfVertices;
	theSMDrawInfo.pMeshData->CalculateExtents();

	// ...then pass it to the mesh manager

	::g_pTheVAOMeshManager->LoadModelIntoVAO( theSMDrawInfo, shaderProgramID );
	return true;
}




void LoadSkinnedMeshModel( std::vector<cMeshSceneObject*> &vec_pObjectsToDraw, 
						   GLuint shaderProgramID )
{ 
	::g_pRPGSkinnedMesh = new cSimpleAssimpSkinnedMesh();

	//if ( ! ::g_pRPGSkinnedMesh->LoadMeshFromFile( "assets/modelsMD5monsters/hellknight/attack2.md5anim" ) ) 
	//{
	//	std::cout << "Didn't load the army pilot" << std::endl;
	//}

	//if ( ! ::g_pRPGSkinnedMesh->LoadMeshFromFile( "assets/modelsFBX/ArmyPilot(FBX2013).fbx" ) ) 
	//{
	//	std::cout << "Didn't load the army pilot" << std::endl;
	//}
	//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsFBX/RPG-Character(FBX2013).FBX" ) ) 
//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsFBX/RPG-Character_Unarmed-Attack-Kick-L1(FBX2013).FBX" ) ) 
//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsFBX/RPG-Character_Unarmed-Walk(FBX2013).FBX" ) ) 
//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsFBX/RPG-Character_Unarmed-Idle(FBX2013).fbx" ) ) 
//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsMD5/hellknight/attack2.md5anim" ) ) 
//	if ( ! ::g_pSkinnedMesh01->LoadMeshFromFile( "assets/modelsFBX/RPG-Character_Unarmed-Fall(FBX2013).fbx" ) ) 
	//if ( ! ::g_pRPGSkinnedMesh->LoadMeshFromFile( "RPG-Character", "assets/modelsFBX/RPG-Character(FBX2013).FBX" ) )
	//if ( ! ::g_pRPGSkinnedMesh->LoadMeshFromFile( "RPG-Character", "assets/modelsFBX/rockgolem(FBX2013).fbx" ) )
	if ( ! ::g_pRPGSkinnedMesh->LoadMeshFromFile( "RPG-Character", "assets/modelsFBX/kachujin(2013).fbx" ) )
	{
		std::cout << "Error: problem loading the skinned mesh" << std::endl;
	}
	std::vector<std::string> vecBoneNames;
	::g_pRPGSkinnedMesh->GetListOfBoneIDandNames( vecBoneNames );

	// Now load another animation file... 
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Idle", "assets/modelsFBX/RPG-Character_Unarmed-Idle(FBX2013).fbx" );
	::g_pRPGSkinnedMesh->LoadMeshAnimation("Idle", "assets/modelsFBX/kachujin_Walking(2013).fbx");
	::g_pRPGSkinnedMesh->LoadMeshAnimation( "Unarmed-Attack-Kick-L1", "assets/modelsFBX/RPG-Character_Unarmed-Attack-Kick-L1(FBX2013).FBX" );
	::g_pRPGSkinnedMesh->LoadMeshAnimation( "Unarmed-Walk", "assets/modelsFBX/RPG-Character_Unarmed-Walk(FBX2013).FBX" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Unarmed-Fall", "assets/modelsFBX/RPG-Character_Unarmed-Fall(FBX2013).fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Roll-Backward", "assets/modelsFBX/RPG-Character_Unarmed-Roll-Backward(FBX2013).fbx" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Roll-Forwards", "assets/modelsFBX/RPG-Character_Unarmed-Roll-Forward(FBX2013).FBX" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Roll-Left", "assets/modelsFBX/RPG-Character_Unarmed-Roll-Left(FBX2013).FBX" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Roll-Right", "assets/modelsFBX/RPG-Character_Unarmed-Roll-Right(FBX2013).FBX" );
	//::g_pRPGSkinnedMesh->LoadMeshAnimation( "Unarmed-Jump", "assets/modelsFBX/RPG-Character_Unarmed-Jump(FBX2013).FBX" );

	::g_pRPGSkinnedMesh->friendlyName = "RPG-Character";

	cMesh* pTheMesh = ::g_pRPGSkinnedMesh->CreateMeshObjectFromCurrentModel();

	if ( pTheMesh )
	{
		std::cout << "Mesh got loaded" << std::endl;
	}
	else
	{
		std::cout << "Didn't load the skinned mesh model" << std::endl;
	}

	// Copy the mesh information from assimp into our cMesh object, 
	// then into the sModelDrawInfo thing, and pass to the VAOManager

	if ( ! AssimpSM_to_VAO_Converter( ::g_pRPGSkinnedMesh, shaderProgramID ) )
	{
		std::cout << "Error: Didn't copy the skinned mesh into the VAO format." << std::endl;
	}
	else
	{
		std::cout << "Copied the skinned mesh into the VAO format" << std::endl;

		// Add this mesh model into the "models to draw" vector

		{	// Bind pose Skinned Mesh object
			cMeshSceneObject* pTestSM = new cMeshSceneObject();
			pTestSM->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 0.0f ) );	// Yellow
			pTestSM->setAlphaTransparency( 1.0f );
			pTestSM->friendlyName = "SM_Object";
			pTestSM->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pTestSM->setUniformScale(1.0f);
			pTestSM->meshName = "RPG-Character.ply";	
			pTestSM->bIsVisible = false;
			
			// Wireframe, to make it easier to see (for now)
//			pTestSM->bIsWireFrame = true;
//			pTestSM->bDontLight = true;
			
			// Set this mesh to the skinned mesh object
			pTestSM->pSimpleSkinnedMesh = ::g_pRPGSkinnedMesh;
			// HACK
			//pTestSM->currentAnimation = "assets/modelsFBX/RPG-Character_Unarmed-Idle(FBX2013).fbx";
//			pTestSM->currentAnimation = "Idle";

			cAnimationState* pAniState;
			pTestSM->pAniState = new cAnimationState();

			pTestSM->pAniState->defaultAnimation.name = "Idle";
			
			

			sTextureInfo testObjectTexture;
			testObjectTexture.name = "grass.bmp";
			testObjectTexture.strength = 1.0f;

			pTestSM->vecTextures.push_back( sTextureInfo(testObjectTexture) );
			pTestSM->setUniformScale(1.0f);
			vec_pObjectsToDraw.push_back( pTestSM );
		}		
	}//if ( ! AssimpSM_to_VAO_Converter(

	//if ( pTheMesh )
	//{
	//	if ( ! pVAOManager->loadMeshIntoVAO( *pTheMesh, shaderID, false ) )
	//	{
	//		std::cout << "Could not load skinned mesh model into new VAO" << std::endl;
	//	}
	//}
	//else
	//{
	//	std::cout << "Could not create a cMesh object from skinned mesh file" << std::endl;
	//}
	//// Delete temporary mesh if still around
	//if ( pTheMesh )
	//{
	//	delete pTheMesh;
	//}


	return;
}

// Loading models was moved into this function
void LoadModelTypes( cVAOMeshManager* pTheVAOMeshManager, GLuint shaderProgramID )
{

		// Load the textures, too
	::g_pTheTextureManager->SetBasePath("assets/textures");

	// Async load
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("Justin.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("grass.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("water-1514818_960_720.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("brick-wall.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("220px-Emma_Watson_2013.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("Flowers.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("Smoke_1.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("Plasma_Ring.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("rock_cave_stylized_height.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("fo_rock_wall_xy_df.bmp", true );
	::g_pTheTextureManager->Create2DTextureFromBMPFile_ASYNC("reticle.bmp", true );


	//	pTheVAOMeshManager->changeLoaderToOriginal();
	pTheVAOMeshManager->changeLoaderToPly5n();

	pTheVAOMeshManager->SetBasePath("assets/models");

	// Player
	{
		sModelDrawInfo playerBody;
		playerBody.meshFileName = "Player_Body.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerBody, shaderProgramID);

		sModelDrawInfo playerHead;
		playerHead.meshFileName = "Player_Head.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerHead, shaderProgramID);

		sModelDrawInfo playerLeftBottomWing;
		playerLeftBottomWing.meshFileName = "Player_Left_Bottom_Wing.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerLeftBottomWing, shaderProgramID);

		sModelDrawInfo playerLeftTopWing;
		playerLeftTopWing.meshFileName = "Player_Left_Top_Wing.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerLeftTopWing, shaderProgramID);

		sModelDrawInfo playerRightBottomWing;
		playerRightBottomWing.meshFileName = "Player_Right_Bottom_Wing.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerRightBottomWing, shaderProgramID);

		sModelDrawInfo playerRightTopWing;
		playerRightTopWing.meshFileName = "Player_Right_Top_Wing.ply";			// "ssj100_xyz.ply";
		pTheVAOMeshManager->LoadModelIntoVAO(playerRightTopWing, shaderProgramID);
	}

	sModelDrawInfo bunnyInfo;
	//bunnyInfo.meshFileName = "bun_res3_xyz.ply";
	//bunnyInfo.meshFileName = "bun_res3_xyz_n_uv.ply";	// NOW, WITH NORMALS!!
	bunnyInfo.meshFileName = "bun_zipper_hi_res_xyz_n_smartUVBlender.ply";	// NOW, WITH NORMALS!!
	if ( ! pTheVAOMeshManager->LoadModelIntoVAO(bunnyInfo, shaderProgramID) )
	{
		std::cout << "Didn't load the bunny" << std::endl;
		std::cout << pTheVAOMeshManager->GetLastError() << std::endl;
	}

	sModelDrawInfo gentleTerrain;
	gentleTerrain.meshFileName = "Gentle_Terrain_xyz_uv.ply";			// "ssj100_xyz.ply";
	if ( pTheVAOMeshManager->LoadModelIntoVAO(gentleTerrain, shaderProgramID) )
	{
		std::cout << "Gentle terrain is loaded" << std::endl;
	}

	sModelDrawInfo airplaneInfo;
	airplaneInfo.meshFileName = "ssj100_xyz_n_GARBAGE_uv.ply";			// "ssj100_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(airplaneInfo, shaderProgramID);

	sModelDrawInfo backToTheFuture;
	backToTheFuture.meshFileName = "de--lorean_xyz_n_GARBAGE_uv.ply";	// "de--lorean.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(backToTheFuture, shaderProgramID);

	sModelDrawInfo migInfo;
	migInfo.meshFileName = "mig29_xyz_n_GARBAGE_uv.ply";					// "mig29_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(migInfo, shaderProgramID);

	sModelDrawInfo teapotInfo;
	teapotInfo.meshFileName = "Utah_Teapot_xyz_n_GARBAGE_uv.ply";			// "Utah_Teapot_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(teapotInfo, shaderProgramID);

	sModelDrawInfo fishInfo;
	fishInfo.meshFileName = "PacificCod0_rotated_xyz_n_GARBAGE_uv.ply";		// "PacificCod0_rotated_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(fishInfo, shaderProgramID);

	sModelDrawInfo terrainInfo;
	terrainInfo.meshFileName = "MeshLab_Fractal_Terrain_xyz_n_uv.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	terrainInfo.bVertexBufferIsDynamic = true;

	pTheVAOMeshManager->LoadModelIntoVAO(terrainInfo, shaderProgramID);
	
	sModelDrawInfo sphereInfo;
	sphereInfo.meshFileName = "Sphere_320_faces_xyz_n_GARBAGE_uv.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInfo, shaderProgramID);

	sModelDrawInfo sphereInvertedNormalsInfo;
	sphereInvertedNormalsInfo.meshFileName = "Sphere_320_faces_xyz_n_GARBAGE_uv_INVERTED_NORMALS.ply";			// "Sphere_320_faces_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(sphereInvertedNormalsInfo, shaderProgramID);

	sModelDrawInfo lonelyTri;
	lonelyTri.meshFileName = "singleTriangle_xyz_n.ply";			// "singleTriangle_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(lonelyTri, shaderProgramID);

	sModelDrawInfo cube1x1x1;
	cube1x1x1.meshFileName = "cube_flat_shaded_xyz_n_uv.ply";			// "cube_flat_shaded_xyz.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(cube1x1x1, shaderProgramID);

	sModelDrawInfo dalek;
	dalek.meshFileName = "dalek2005_xyz_uv_res_2.ply";			// "dalek2005_xyz_uv_res_2.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(dalek, shaderProgramID);

	sModelDrawInfo tvBody;
	tvBody.meshFileName = "RetroTV.edited.bodyonly.ply";			// "RetroTV.edited.bodyonly.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(tvBody, shaderProgramID);

	sModelDrawInfo tvScreen;
	tvScreen.meshFileName = "RetroTV.edited.screenonly.ply";			// "RetroTV.edited.screenonly.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(tvScreen, shaderProgramID);

	sModelDrawInfo cityInfo;
	cityInfo.meshFileName = "ScifiCityRuins.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	// Will alow me to update the vertex data in the mesh
	cityInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(cityInfo, shaderProgramID);

	sModelDrawInfo camdroneInfo;
	camdroneInfo.meshFileName = "camdrone.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	camdroneInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(camdroneInfo, shaderProgramID);

	sModelDrawInfo monitorInfo;
	monitorInfo.meshFileName = "monitor.ply";	// "MeshLab_Fractal_Terrain_xyz.ply";
	monitorInfo.bVertexBufferIsDynamic = true;
	pTheVAOMeshManager->LoadModelIntoVAO(monitorInfo, shaderProgramID);

	// Room to be used for the stencil buffer
	sModelDrawInfo room;
	room.meshFileName = "Room_2_Bigger_Triangulated.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(room, shaderProgramID);

	sModelDrawInfo doors;
	doors.meshFileName = "Room_2_Bigger_Doorways.ply";
	pTheVAOMeshManager->LoadModelIntoVAO(doors, shaderProgramID);

	//sModelDrawInfo oldhouse;
	//oldhouse.meshFileName = "Old_House_Combined_xyz_n.ply";		
	//pTheVAOMeshManager->LoadModelIntoVAO(oldhouse, shaderProgramID);

	sModelDrawInfo skyPirate;
	skyPirate.meshFileName = "Sky_Pirate_Combined_xyz_n_BlenderSmart_uv.ply";		
	if ( pTheVAOMeshManager->LoadModelIntoVAO(skyPirate, shaderProgramID) )
	{
		std::cout << "Sky Pirate is loaded" << std::endl;
	}

	// At this point, mesh in in GPU
	std::cout << "Mesh was loaded OK" << std::endl;


	sModelDrawInfo imposterObject_1;
	imposterObject_1.meshFileName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";				// Flat, 2 sided 'classic' imposter
	pTheVAOMeshManager->LoadModelIntoVAO(imposterObject_1, shaderProgramID);

	sModelDrawInfo imposterObject_2;
	imposterObject_2.meshFileName = "1x1_Star_1_Quad_2_Sided_xyz_n_uv.ply";				// More complicated "star" shaped imposter
	pTheVAOMeshManager->LoadModelIntoVAO(imposterObject_2, shaderProgramID);

	sModelDrawInfo imposterObject_3;
	imposterObject_3.meshFileName = "Sphere_UV_xyz_n_uv.ply";							// A simple UV mapped sphere (low poly)
	pTheVAOMeshManager->LoadModelIntoVAO(imposterObject_3, shaderProgramID);

//	if ( ! ::g_pTheTextureManager->Create2DTextureFromBMPFile("Justin.bmp", true ) )
//	{
//		std::cout << "Didn't load texture" << std::endl;
//	}
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("grass.bmp", true );
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("water-1514818_960_720.bmp", true );
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("brick-wall.bmp", true );
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("220px-Emma_Watson_2013.bmp", true );
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("Flowers.bmp", true );

	// For the particle imposters
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("Smoke_1.bmp", true );
//	::g_pTheTextureManager->Create2DTextureFromBMPFile("Plasma_Ring.bmp", true );
//
//	if ( ::g_pTheTextureManager->Create2DTextureFromBMPFile("rock_cave_stylized_height.bmp", true ) )
//	{
//		std::cout << "loaded height map, too" << std::endl;
//	}

	// Load the cube map
	::g_pTheTextureManager->SetBasePath("assets/textures/cubemaps");
	std::string errorString;
	//if ( ::g_pTheTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap", 
	//	 "city_lf.bmp", "city_rt.bmp",				// reverse these
	//	 "city_dn.bmp", "city_up.bmp",				// Rotate the image "right 90 degrees")
	//	 "city_ft.bmp", "city_bk.bmp", true, errorString ) )
	//{
	//	std::cout << "Loaded the city cube map OK" << std::endl;
	//}
	//else
	//{
	//	std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	//}
	//if (::g_pTheTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap",
	//	"SpaceBox_right1_posX.bmp", "SpaceBox_left2_negX.bmp",
	//	"SpaceBox_top3_posY.bmp", "SpaceBox_bottom4_negY.bmp",
	//	"SpaceBox_front5_posZ.bmp", "SpaceBox_back6_negZ.bmp", true, errorString))
	//{
	//	std::cout << "Loaded the city cube map OK" << std::endl;
	//}
	//else
	//{
	//	std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	//}
	if ( ::g_pTheTextureManager->CreateCubeTextureFromBMPFiles("CityCubeMap", 
		 "TropicalSunnyDayLeft2048.bmp", "TropicalSunnyDayRight2048.bmp",		// Alternate these
		 "TropicalSunnyDayDown2048.bmp", "TropicalSunnyDayUp2048.bmp", 			// Rotate these 90 degrees
		 "TropicalSunnyDayFront2048.bmp", "TropicalSunnyDayBack2048.bmp", true, errorString ) )
	{
		std::cout << "Loaded the city cube map OK" << std::endl;
	}
	else
	{
		std::cout << "Error: city cube map DIDN't load. On no!" << std::endl;
	}


	sModelDrawInfo testObject;
	testObject.meshFileName = "SM_Env_Tree_Canopy_04.ply";							// A simple UV mapped sphere (low poly)
	pTheVAOMeshManager->SetBasePath("assets/models/final");
	pTheVAOMeshManager->LoadModelIntoVAO(testObject, shaderProgramID);

	return;
}


void LoadPlayerModels_LOJAM( std::vector<cMeshSceneObject*> &vec_pObjectsToDraw )
{
	{ // STARTOF: Player
		cMeshSceneObject* pPlayerBody = new cMeshSceneObject();
		cMeshSceneObject* pPlayerHead = new cMeshSceneObject();
		cMeshSceneObject* pPlayerTopLeftWing = new cMeshSceneObject();
		cMeshSceneObject* pPlayerTopRightWing = new cMeshSceneObject();
		cMeshSceneObject* pPlayerBottomLeftWing = new cMeshSceneObject();
		cMeshSceneObject* pPlayerBottomRightWing = new cMeshSceneObject();

		sTextureInfo playerObjectTexture;
		playerObjectTexture.name = "water-1514818_960_720.bmp";
		playerObjectTexture.strength = 1.0f;

		{//Player body
			pPlayerBody->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerBody->setAlphaTransparency( 1.0f );
			pPlayerBody->friendlyName = "PlayerBody";
			pPlayerBody->position = glm::vec3(0.0f, 0.0f, 15.0f);
			pPlayerBody->setUniformScale(1.0f);
			pPlayerBody->meshName = "Player_Body.ply";	

//			pTestObject->bIsWireFrame = true;
//			pPlayerBody->bDontLight = true;

			pPlayerBody->vecTextures.push_back( playerObjectTexture );
			pPlayerBody->setUniformScale(1.0f);
			vec_pObjectsToDraw.push_back( pPlayerBody );
		}//Player body

		{//Player head
			pPlayerHead->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerHead->setAlphaTransparency( 1.0f );
			pPlayerHead->friendlyName = "PlayerHead";
			pPlayerHead->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pPlayerHead->setUniformScale(1.0f);
			pPlayerHead->meshName = "Player_Head.ply";	
			pPlayerHead->vecTextures.push_back( playerObjectTexture );
			pPlayerHead->setUniformScale(1.0f);
			pPlayerBody->vec_pChildObjectsToDraw.push_back(pPlayerHead);
		}//Player body

		{//Player Top Left Wing
			pPlayerTopLeftWing->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerTopLeftWing->setAlphaTransparency( 1.0f );
			pPlayerTopLeftWing->friendlyName = "PlayerTopLeftWing";
			pPlayerTopLeftWing->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pPlayerTopLeftWing->setUniformScale(1.0f);
			pPlayerTopLeftWing->meshName = "Player_Left_Top_Wing.ply";	
			pPlayerTopLeftWing->vecTextures.push_back( playerObjectTexture );
			pPlayerTopLeftWing->setUniformScale(1.0f);
			pPlayerBody->vec_pChildObjectsToDraw.push_back(pPlayerTopLeftWing);
		}//Player Top Left Wing

		{//Player Top Right Wing
			pPlayerTopRightWing->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerTopRightWing->setAlphaTransparency( 1.0f );
			pPlayerTopRightWing->friendlyName = "PlayerTopRightWing";
			pPlayerTopRightWing->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pPlayerTopRightWing->setUniformScale(1.0f);
			pPlayerTopRightWing->meshName = "Player_Right_Top_Wing.ply";	
			pPlayerTopRightWing->vecTextures.push_back( playerObjectTexture );
			pPlayerTopRightWing->setUniformScale(1.0f);
			pPlayerBody->vec_pChildObjectsToDraw.push_back(pPlayerTopRightWing);
		}//Player Top Right Wing
	
		{//Player Bottom Right Wing
			pPlayerBottomRightWing->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerBottomRightWing->setAlphaTransparency( 1.0f );
			pPlayerBottomRightWing->friendlyName = "PlayerBottomRightWing";
			pPlayerBottomRightWing->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pPlayerBottomRightWing->setUniformScale(1.0f);
			pPlayerBottomRightWing->meshName = "Player_Right_Bottom_Wing.ply";	
			pPlayerBottomRightWing->vecTextures.push_back( playerObjectTexture );
			pPlayerBottomRightWing->setUniformScale(1.0f);
			pPlayerBody->vec_pChildObjectsToDraw.push_back(pPlayerBottomRightWing);
		}//Player Bottom Right Wing
	
		{//Player Bottom Left Wing
			pPlayerBottomLeftWing->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
			pPlayerBottomLeftWing->setAlphaTransparency( 1.0f );
			pPlayerBottomLeftWing->friendlyName = "PlayerBottomLeftWing";
			pPlayerBottomLeftWing->position = glm::vec3(0.0f, 0.0f, 0.0f);
			pPlayerBottomLeftWing->setUniformScale(1.0f);
			pPlayerBottomLeftWing->meshName = "Player_Left_Bottom_Wing.ply";	
			pPlayerBottomLeftWing->vecTextures.push_back( playerObjectTexture );
			pPlayerBottomLeftWing->setUniformScale(1.0f);
			pPlayerBody->vec_pChildObjectsToDraw.push_back(pPlayerBottomLeftWing);
		}//Player Bottom Left Wing
	
	}// ENDOF: Player

	return;
}




	
// Loads the models we are drawing into the vector
void LoadModelsIntoScene( std::vector<cMeshSceneObject*> &vec_pObjectsToDraw )
{

	//LoadPlayerModels_LOJAM(vec_pObjectsToDraw);


	//{	// The 2D 2 triangle "flat" imposter object
	//	cMeshSceneObject* pTestObject = new cMeshSceneObject();
	//	pTestObject->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
	//	pTestObject->setAlphaTransparency( 1.0f );
	//	pTestObject->friendlyName = "GentleTerrain";
	//	pTestObject->position = glm::vec3(0.0f, -0.0f, 0.0f);
	//	pTestObject->setUniformScale(1.0f);
	//	pTestObject->meshName = "Gentle_Terrain_xyz_uv.ply";		

	//	sTextureInfo testObjectTexture;
	//	testObjectTexture.name = "grass.bmp";
	//	testObjectTexture.strength = 1.0f;

	//	pTestObject->vecTextures.push_back( sTextureInfo(testObjectTexture) );
	//	pTestObject->setUniformScale(1.0f);
	//	vec_pObjectsToDraw.push_back( pTestObject );
	//}	

//{	// The 2D 2 triangle "flat" imposter object
//	cMeshSceneObject* pTestObject = new cMeshSceneObject();
//	pTestObject->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
//	pTestObject->setAlphaTransparency( 1.0f );
//	pTestObject->friendlyName = "TestObject";
//	pTestObject->position = glm::vec3(0.0f, -25.0f, 0.0f);
//	pTestObject->setUniformScale(1.0f);
//	pTestObject->meshName = "Gentle_Terrain_xyz_uv.ply";		
//	//pTestObject->meshName = "SM_Env_Tree_Canopy_04.ply";		// Flat, classic imposter
//
//	sTextureInfo testObjectTexture;
//	testObjectTexture.name = "grass.bmp";
//	testObjectTexture.strength = 1.0f;
//
//	pTestObject->vecTextures.push_back( sTextureInfo(testObjectTexture) );
//	pTestObject->setUniformScale(1.0f);
//	vec_pObjectsToDraw.push_back( pTestObject );
//}		

	//cMeshObject teapot;									// Stack
	//teapot.position = glm::vec3( -3.0f, 0.0f, 0.0f );
	//teapot.objColour = glm::vec3( 1.0f, 0.0f, 0.0f );
	//teapot.meshName =  "Utah_Teapot_xyz.ply";
	//teapot.nonUniformScale = glm::vec3(0.005f,0.005f,0.005f);
	//vecObjectsToDraw.push_back( teapot );		// [1]

	//std::vector< cMeshObject* > vec_pObjectsToDraw;

	//cMeshObject* pRogerRabbit = NULL;

	{
		//cMeshObject* pBunny = new cMeshObject();
		::g_pRogerRabbit = new cMeshSceneObject();
//		::g_pRogerRabbit->preRotation = glm::vec3( 0.0f, 0.0f, 0.0f );
		::g_pRogerRabbit->position = glm::vec3(  0.0f, 25.0f, 0.0f );
		//::g_pRogerRabbit->postRotation = glm::vec3( glm::radians(45.0f), 0.0f, 0.0f );

		::g_pRogerRabbit->setMeshOrientationEulerAngles( glm::vec3( glm::radians(45.0f), 0.0f, 0.0f ) );

//		::g_pRogerRabbit->nonUniformScale = glm::vec3(9.0f, 9.0f, 9.0f);
		::g_pRogerRabbit->setUniformScale( 5.0f );
//		::g_pRogerRabbit->objColour = glm::vec3( 1.0f, 1.0f, 0.0f );
//		::g_pRogerRabbit->setDiffuseColour( glm::vec3(1.0f, 1.0f, 0.0f) );
		::g_pRogerRabbit->bUseVertexColour = true;

		// Make the terrain really shinny...
		::g_pRogerRabbit->setSpecularPower( 10.0f );
//		::g_pRogerRabbit->setSpecularColour( glm::vec3(1.0f, 0.0f, 0.0f) );
//		::g_pRogerRabbit->setSpecularPower( 0.54f );


		// "Gold" bunny?
		::g_pRogerRabbit->setDiffuseColour( glm::vec3(1.0f, 223.0f/255.0f, 0.0f) );
		::g_pRogerRabbit->bUseVertexColour = false;
		// Taken from: https://docs.unrealengine.com/en-us/Engine/Rendering/Materials/PhysicallyBased
		// Note that the specular HIGHLIGHT colour is DIFFERENT from 
		// the diffuse... 
		::g_pRogerRabbit->setSpecularPower( 100.0f );
		::g_pRogerRabbit->setSpecularColour( glm::vec3(1.000f, 0.766f, 0.336f) );

		

//		::g_pRogerRabbit->meshName = "bun_res3_xyz.ply";
		::g_pRogerRabbit->meshName = "bun_zipper_hi_res_xyz_n_smartUVBlender.ply";
		::g_pRogerRabbit->bIsVisible = false;
		// 
		::g_pRogerRabbit->friendlyName = "Roger";

		::g_pRogerRabbit->pDebugRenderer = ::g_pDebugRenderer;


		sTextureInfo flowers;
		flowers.name = "Flowers.bmp";
		flowers.strength = 1.0f;
		::g_pRogerRabbit->vecTextures.push_back( flowers );

		sTextureInfo justin;
		justin.name = "Justin.bmp";
		justin.strength = 0.0f;
		::g_pRogerRabbit->vecTextures.push_back( justin );


		vec_pObjectsToDraw.push_back( ::g_pRogerRabbit );
	}
	int indexSelectedObject = 0;
	{
		cMeshSceneObject* pBunny = new cMeshSceneObject();
//		pBunny->preRotation = glm::vec3( 0.0f, 0.0f, 0.0f );

		pBunny->setMeshOrientationEulerAngles( glm::vec3( 0.0f, 0.0f, 0.0f ) );

		pBunny->position = glm::vec3(  0.0f, 25.0f, 0.0f );
//		pBunny->postRotation = glm::vec3( glm::radians(45.0f), 0.0f, 0.0f );
		pBunny->nonUniformScale = glm::vec3(9.0f, 9.0f, 9.0f);
//		pBunny->objColour = glm::vec3( 1.0f, 1.0f, 0.0f );
		pBunny->setDiffuseColour( glm::vec3(1.0f, 1.0f, 0.0f) );
		pBunny->meshName = "bun_zipper_hi_res_xyz_n_smartUVBlender.ply";
		pBunny->bIsVisible = true;
		pBunny->friendlyName = "Bugs";

		pBunny->pDebugRenderer = ::g_pDebugRenderer;

		//vec_pObjectsToDraw.push_back( pBunny );
	}

	{	// This will be our "skybox" object.
			// (could also be a cube, or whatever)
		cMeshSceneObject* pSkyBoxObject = new cMeshSceneObject();
		pSkyBoxObject->setDiffuseColour(glm::vec3(0.0f, 0.0f, 1.0f));
		pSkyBoxObject->bUseVertexColour = false;
		pSkyBoxObject->friendlyName = "SkyBoxObject";
		float scale = 5000.0f;
		pSkyBoxObject->nonUniformScale = glm::vec3(scale, scale, scale);
		pSkyBoxObject->meshName = "Sphere_320_faces_xyz_n_GARBAGE_uv_INVERTED_NORMALS.ply";			// "Sphere_320_faces_xyz.ply";
//		pSkyBoxObject->bIsWireFrame = true;

		// Invisible until I need to draw it
		//pSkyBoxObject->bIsVisible = true;

		vec_pObjectsToDraw.push_back(pSkyBoxObject);
	}


	// ENDOF: Updated physics object

	{	// This sphere is the tiny little debug sphere
		cMeshSceneObject* pDebugSphere = new cMeshSceneObject();
		pDebugSphere->position = glm::vec3( 0.0f, 0.0f, 0.0f );
//		pDebugSphere->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pDebugSphere->setDiffuseColour( glm::vec3(0.0f, 1.0f, 0.0f) );
		float scale = 0.1f;
		pDebugSphere->friendlyName = "DebugSphere";
		pDebugSphere->nonUniformScale = glm::vec3(scale,scale,scale);
		pDebugSphere->meshName = "Sphere_320_faces_xyz_n_GARBAGE_uv.ply";		// "Sphere_320_faces_xyz.ply";
		pDebugSphere->bIsWireFrame = true;
		pDebugSphere->bIsVisible = false;
		pDebugSphere->pDebugRenderer = ::g_pDebugRenderer;

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back( pDebugSphere );
	}

	{	// This is the tv body
		cMeshSceneObject* pTVBody = new cMeshSceneObject();
		pTVBody->position = glm::vec3(50.0f, 25.0f, 100.0f);
		//		pDebugSphere->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pTVBody->setDiffuseColour(glm::vec3(0.0f, 0.0f, 1.0f));
		float scale = 0.55f;
		pTVBody->friendlyName = "tvBody";
		pTVBody->nonUniformScale = glm::vec3(scale, scale, scale);
		//pTVBody->adjMeshOrientationEulerAngles(glm::vec3(0.0f, 1.5f, 0.0f));
		pTVBody->meshName = "RetroTV.edited.bodyonly.ply";		// "Sphere_320_faces_xyz.ply";
		pTVBody->bIsWireFrame = false;
		//pTVBody->bIsVisible = true;
		pTVBody->bIsVisible = true;
		pTVBody->bDontLight = false;
		pTVBody->pDebugRenderer = ::g_pDebugRenderer;

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pTVBody);
	}

	{	// This is the tv screen
		cMeshSceneObject* pTVScreen = new cMeshSceneObject();
		pTVScreen->position = glm::vec3(50.0f, 30.0f, 80.0f);
		//		pDebugSphere->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pTVScreen->setDiffuseColour(glm::vec3(0.0f, 1.0f, 1.0f));
		float scale = 0.5f;
		pTVScreen->friendlyName = "tvScreen";
		pTVScreen->nonUniformScale = glm::vec3(scale + 0.2f, scale, scale);
		//pTVScreen->adjMeshOrientationEulerAngles(glm::vec3(glm::radians(-140.0f), 0.0f, 0.0f));
		//pTVScreen->adjMeshOrientationEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		pTVScreen->adjMeshOrientationEulerAngles(glm::vec3(1.5f, 0.0f, 0.0f));
		pTVScreen->meshName = "RetroTV.edited.screenonly.ply";		// "Sphere_320_faces_xyz.ply";
		pTVScreen->bIsWireFrame = false;
		pTVScreen->bIsVisible = false;
		pTVScreen->bDontLight = true;
		pTVScreen->pDebugRenderer = ::g_pDebugRenderer;

		sTextureInfo reticleTexture;
		//reticleTexture.name = "reticle.bmp";
		reticleTexture.name = "Plasma_Ring.bmp";
		reticleTexture.strength = 1.0f;

		pTVScreen->vecTextures.push_back(sTextureInfo(reticleTexture));


		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pTVScreen);
	}

	//*********
	// FULL SCREEN QUAD
	//*********
	{	// One of the "star shaped" imposter object
		cMeshSceneObject* p2SidedQuad = new cMeshSceneObject();
		p2SidedQuad->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
		p2SidedQuad->setAlphaTransparency(1.0f);
		p2SidedQuad->friendlyName = "FullScreenQuad";
		//		p2SidedQuad->meshName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";		// Multi-faced imposter
		p2SidedQuad->meshName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";

		p2SidedQuad->setUniformScale(10.0f);
		p2SidedQuad->position = glm::vec3(0.0f, 0.0f, 0.0f);
		p2SidedQuad->setMeshOrientationEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		p2SidedQuad->bIsVisible = false;

		sTextureInfo reticleTexture;
		//reticleTexture.name = "reticle.bmp";
		reticleTexture.name = "Plasma_Ring.bmp";
		reticleTexture.strength = 0.0f;

		p2SidedQuad->vecTextures.push_back(sTextureInfo(reticleTexture));

		vec_pObjectsToDraw.push_back(p2SidedQuad);
	}





	{	// This sphere is the tiny little debug sphere
		cMeshSceneObject* pDalek = new cMeshSceneObject();
		pDalek->position = glm::vec3(0.0f, 0.0f, 0.0f);
		//		pDebugSphere->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pDalek->setDiffuseColour(glm::vec3(1.0f, 1.0f, 0.0f));
		float scale = 0.05f;
		pDalek->friendlyName = "Dalek";
		pDalek->nonUniformScale = glm::vec3(scale, scale, scale);
		pDalek->adjMeshOrientationEulerAngles(glm::vec3(glm::radians(135.0f), 0.0f, 0.0f));
		pDalek->meshName = "dalek2005_xyz_uv_res_2.ply";		// "Sphere_320_faces_xyz.ply";
		pDalek->bIsWireFrame = false;
		pDalek->bIsVisible = true;
		pDalek->bDontLight = false;
		pDalek->pDebugRenderer = ::g_pDebugRenderer;

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back(pDalek);
	}


	{
		cMeshSceneObject* pTerrain = new cMeshSceneObject();
		//pTerrain->position = glm::vec3(  0.0f, -10.0f, 0.0f );
		pTerrain->position = glm::vec3(0.0f, 100.0f, 0.0f);
		//		pTerrain->objColour = glm::vec3( 1.0f, 1.0f, 1.0f );
		//		pTerrain->setDiffuseColour( glm::vec3(1.0f, 1.0f, 1.0f) );
		pTerrain->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));

		// Make the terrain really shinny...
		pTerrain->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pTerrain->setSpecularPower(100.0f);
		//		pTerrain->setSpecularPower( 2.0f );


		pTerrain->bUseVertexColour = false;
		//		pTerrain->u
		//		pTerrain->meshName = "MeshLab_Fractal_Terrain_xyz_n_uv.ply";		// "MeshLab_Fractal_Terrain_xyz.ply";
				//pTerrain->vecLODMeshs.push_back(sLODInfo("MeshLab_Fractal_Terrain_xyz_n_uv.ply"));
		pTerrain->meshName = "ScifiCityRuins.ply";
		pTerrain->friendlyName = "The Terrain";
		//pTerrain->bIsWireFrame = true;
		pTerrain->bIsVisible = true;

		pTerrain->pDebugRenderer = ::g_pDebugRenderer;


		//sTextureInfo grassTexture;
		//grassTexture.name = "grass.bmp";
		//grassTexture.strength = 1.0f;
		//pTerrain->vecTextures.push_back(grassTexture);


		//sTextureInfo metal;
		//metal.name = "metallplates.bmp";
		//metal.strength = 0.2;
		//pTerrain->vecTextures.push_back( metal );

		sTextureInfo halo;
		halo.name = "metal_halomap.bmp";
		halo.strength = 0.8;
		pTerrain->vecTextures.push_back(halo);

		sTextureInfo tech;
		tech.name = "tech_skin_1.bmp";
		tech.strength = 0.2f;
		pTerrain->vecTextures.push_back(tech);

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		//vec_pObjectsToDraw.push_back(pTerrain);
	}

	{
		cMeshSceneObject* pCamDrone = new cMeshSceneObject();
		//pCamDrone->position = glm::vec3(0.0f, 30.0f, 0.0f);
		pCamDrone->position = glm::vec3(30.0f, 10.0f, 2.0f);
		pCamDrone->setUniformScale(0.25f);
		pCamDrone->adjMeshOrientationEulerAngles(glm::vec3(0.5f, 1.2f, 0.0f));

		pCamDrone->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));

		pCamDrone->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pCamDrone->setSpecularPower(100.0f);

		pCamDrone->bUseVertexColour = false;
		pCamDrone->meshName = "camdrone.ply";
		pCamDrone->friendlyName = "CamDrone0";
		pCamDrone->bIsVisible = true;

		pCamDrone->pDebugRenderer = ::g_pDebugRenderer;


		sTextureInfo metal;
		metal.name = "metallplates.bmp";
		metal.strength = 0.2;
		pCamDrone->vecTextures.push_back(metal);

		sTextureInfo halo;
		halo.name = "metal_halomap.bmp";
		halo.strength = 0.8;
		pCamDrone->vecTextures.push_back(halo);

		vec_pObjectsToDraw.push_back(pCamDrone);
	}

	{
		cMeshSceneObject* pCamDrone = new cMeshSceneObject();
		//pCamDrone->position = glm::vec3(50.0f, 30.0f, 40.0f);
		pCamDrone->position = glm::vec3(40.0f, 20.0f, 20.0f);
		pCamDrone->setUniformScale(0.25f);
		pCamDrone->adjMeshOrientationEulerAngles(glm::vec3(0.85f, 0.0f, 0.0f));

		pCamDrone->setDiffuseColour(glm::vec3(0.0f, 0.0f, 1.0f));
		pCamDrone->setAlphaTransparency(1.0f);
		//pCamDrone->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));

		pCamDrone->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pCamDrone->setSpecularPower(100.0f);

		pCamDrone->bUseVertexColour = false;
		pCamDrone->meshName = "camdrone.ply";
		pCamDrone->friendlyName = "CamDrone1";
		pCamDrone->bIsVisible = true;

		pCamDrone->pDebugRenderer = ::g_pDebugRenderer;


		//sTextureInfo metal;
		//metal.name = "metallplates.bmp";
		//metal.strength = 0.2;
		//pCamDrone->vecTextures.push_back(metal);

		//sTextureInfo halo;
		//halo.name = "metal_halomap.bmp";
		//halo.strength = 0.8;
		//pCamDrone->vecTextures.push_back(halo);

		vec_pObjectsToDraw.push_back(pCamDrone);
	}

	{
		cMeshSceneObject* pMonitor = new cMeshSceneObject();
		pMonitor->position = glm::vec3(75.0f, 10.0f, 46.0f);
		pMonitor->setUniformScale(2.0f);
		pMonitor->adjMeshOrientationEulerAngles(glm::vec3(0.0f, -0.8f, 0.0f));
		//pCamDrone->adjMeshOrientationEulerAngles(glm::vec3(0.05f, -0.0f, 0.4f));

		pMonitor->setDiffuseColour(glm::vec3(1.0f, 0.0f, 1.0f));

		pMonitor->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pMonitor->setSpecularPower(100.0f);

		pMonitor->bUseVertexColour = false;
		pMonitor->meshName = "monitor.ply";
		pMonitor->friendlyName = "Monitor0";
		pMonitor->bIsVisible = true;

		pMonitor->pDebugRenderer = ::g_pDebugRenderer;


		sTextureInfo metal;
		metal.name = "metallplates.bmp";
		metal.strength = 0.2;
		pMonitor->vecTextures.push_back(metal);

		sTextureInfo halo;
		halo.name = "metal_halomap.bmp";
		halo.strength = 0.8;
		pMonitor->vecTextures.push_back(halo);

		vec_pObjectsToDraw.push_back(pMonitor);
	}

	{
		cMeshSceneObject* pMonitor = new cMeshSceneObject();
		pMonitor->position = glm::vec3(20.0f, 10.0f, 40.0f);
		pMonitor->setUniformScale(4.0f);
		pMonitor->adjMeshOrientationEulerAngles(glm::vec3(0.4f, 0.78f, -0.5f));
		//pMonitor->adjMeshOrientationEulerAngles(glm::vec3(0.0f, 0.5f, 0.0f));

		pMonitor->setDiffuseColour(glm::vec3(1.0f, 0.0f, 1.0f));

		pMonitor->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pMonitor->setSpecularPower(100.0f);

		pMonitor->bUseVertexColour = false;
		pMonitor->meshName = "monitor.ply";
		pMonitor->friendlyName = "Monitor1";
		pMonitor->bIsVisible = true;

		pMonitor->pDebugRenderer = ::g_pDebugRenderer;


		sTextureInfo metal;
		metal.name = "metallplates.bmp";
		metal.strength = 0.2;
		pMonitor->vecTextures.push_back(metal);

		sTextureInfo halo;
		halo.name = "metal_halomap.bmp";
		halo.strength = 0.8;
		pMonitor->vecTextures.push_back(halo);

		vec_pObjectsToDraw.push_back(pMonitor);
	}

	{
		cMeshSceneObject* pMonitor = new cMeshSceneObject();
		pMonitor->position = glm::vec3(20.0f, 10.0f, 40.0f);
		pMonitor->setUniformScale(4.0f);
		pMonitor->adjMeshOrientationEulerAngles(glm::vec3(0.4f, 0.78f, -0.5f));
		//pMonitor->adjMeshOrientationEulerAngles(glm::vec3(0.0f, 0.5f, 0.0f));

		pMonitor->setDiffuseColour(glm::vec3(1.0f, 0.0f, 1.0f));

		pMonitor->setSpecularColour(glm::vec3(1.0f, 1.0f, 1.0f));
		pMonitor->setSpecularPower(100.0f);

		pMonitor->bUseVertexColour = false;
		pMonitor->meshName = "monitor.ply";
		pMonitor->friendlyName = "Monitor1";
		pMonitor->bIsVisible = true;

		pMonitor->pDebugRenderer = ::g_pDebugRenderer;


		sTextureInfo metal;
		metal.name = "metallplates.bmp";
		metal.strength = 0.2;
		pMonitor->vecTextures.push_back(metal);

		sTextureInfo halo;
		halo.name = "metal_halomap.bmp";
		halo.strength = 0.8;
		pMonitor->vecTextures.push_back(halo);

		vec_pObjectsToDraw.push_back(pMonitor);
	}



	{	// This sphere is the tiny little debug sphere
		cMeshSceneObject* pCubeForBallsToBounceIn = new cMeshSceneObject();
//		pCubeForBallsToBounceIn->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pCubeForBallsToBounceIn->setDiffuseColour( glm::vec3( 0.0f, 0.1f, 0.0f ) );
		pCubeForBallsToBounceIn->bDontLight = false;
		pCubeForBallsToBounceIn->friendlyName = "CubeBallsBounceIn";
		pCubeForBallsToBounceIn->meshName = "cube_flat_shaded_xyz_n_uv.ply";		// "cube_flat_shaded_xyz.ply";
		pCubeForBallsToBounceIn->nonUniformScale = glm::vec3(100.0f, 10.0f, 100.0f);
		// Cube is 2x2x2, so with a scale of 100x means it's
		//	200x200x200, centred around the origin (0,0,0)
		// The GROUND_PLANE_Y = -3.0f, so place it +97.0 lines up the 'bottom'
		pCubeForBallsToBounceIn->position = glm::vec3(  0.0f, -12.0f, 0.0f );
		pCubeForBallsToBounceIn->bIsWireFrame = false;
				
		pCubeForBallsToBounceIn->pDebugRenderer = ::g_pDebugRenderer;

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		vec_pObjectsToDraw.push_back( pCubeForBallsToBounceIn );
	}


//    ___   ___ _    _        _    ___               _    ____            ___   __  __                       __  
//   |_  ) / __(_)__| |___ __| |  / _ \ _  _ __ _ __| |  / / _|___ _ _   / _ \ / _|/ _|___ __ _ _ ___ ___ _ _\ \ 
//    / /  \__ \ / _` / -_) _` | | (_) | || / _` / _` | | |  _/ _ \ '_| | (_) |  _|  _(_-</ _| '_/ -_) -_) ' \| |
//   /___| |___/_\__,_\___\__,_|  \__\_\\_,_\__,_\__,_| | |_| \___/_|    \___/|_| |_| /__/\__|_| \___\___|_||_| |
//                                                       \_\                                                 /_/ 
	{	// One of the "star shaped" imposter object
		cMeshSceneObject* p2SidedQuad = new cMeshSceneObject();
		p2SidedQuad->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
		p2SidedQuad->setAlphaTransparency( 1.0f );
		p2SidedQuad->friendlyName = "2SidedQuad";
		p2SidedQuad->meshName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";		// Multi-faced imposter

		p2SidedQuad->setUniformScale(10.0f);
		p2SidedQuad->position = glm::vec3(0.0f, 0.0f, 0.0f);
		p2SidedQuad->setMeshOrientationEulerAngles( glm::vec3(0.0f, 0.0f, 0.0f) );
		p2SidedQuad->bIsVisible = false;
		vec_pObjectsToDraw.push_back( p2SidedQuad );
	}

	{	// One of the "star shaped" imposter object
		cMeshSceneObject* p2SidedQuad = new cMeshSceneObject();
		p2SidedQuad->setDiffuseColour(glm::vec3(1.0f, 1.0f, 1.0f));
		p2SidedQuad->setAlphaTransparency(1.0f);
		p2SidedQuad->friendlyName = "secondQuad";
		p2SidedQuad->meshName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";		// Multi-faced imposter

		p2SidedQuad->setUniformScale(10.0f);
		p2SidedQuad->position = glm::vec3(0.0f, 0.0f, 0.0f);
		p2SidedQuad->setMeshOrientationEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f));
		p2SidedQuad->bIsVisible = false;
		vec_pObjectsToDraw.push_back(p2SidedQuad);
	}

	{	// The 2D 2 triangle "flat" imposter object
		cMeshSceneObject* pPlasmaBlast = new cMeshSceneObject();
		pPlasmaBlast->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
		pPlasmaBlast->setAlphaTransparency( 1.0f );
		pPlasmaBlast->friendlyName = "PlasmaRingImposterObject";
		// ***********************************************************
		// FLAT IMPOSTER
		// ***********************************************************
		pPlasmaBlast->meshName = "1x1_2Tri_Quad_2_Sided_xyz_n_uv.ply";		// Flat, classic imposter
//		pSmoke->meshName = "1x1_Star_1_Quad_2_Sided_xyz_n_uv.ply";		// Multi-faced imposter
//		pSmoke->meshName = "Sphere_UV_xyz_n_uv.ply";					// Imposter can be any shape, really

		// NOTE: This is a "plasma ring" (that's what I googled...)
		sTextureInfo plasmaRingTexture;
		plasmaRingTexture.name = "Plasma_Ring.bmp";
		plasmaRingTexture.strength = 1.0f;

		pPlasmaBlast->vecTextures.push_back( sTextureInfo(plasmaRingTexture) );
		pPlasmaBlast->setUniformScale(1.0f);
		pPlasmaBlast->bIsVisible = false;
		vec_pObjectsToDraw.push_back( pPlasmaBlast );
	}	
	

	
	return;
}

void LoadStencilBufferModels(std::vector<cMeshSceneObject*> &vec_pObjectsToDraw)
{
	glm::vec3 RoomPosition = glm::vec3(20.0f, 0.0f, 0.0f);
	float RoomScale = 5.0f;

	//std::vector< cMeshObject* > vec_pObjectsToDraw;
	{
		cMeshSceneObject* pRoom = new cMeshSceneObject();
		pRoom->friendlyName = "Room";
		pRoom->bIsVisible = false;
		pRoom->position = RoomPosition;
		pRoom->setMeshOrientationEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f), true);
		pRoom->setDiffuseColour(glm::vec3(0.0f, 0.0f, 0.0f));
		pRoom->setSpecularPower(100.0f);
		pRoom->meshName = "Room_2_Bigger_Triangulated.ply";
		pRoom->setUniformScale(RoomScale);
		sTextureInfo grassTexture;
		grassTexture.name = "grass.bmp";
		grassTexture.strength = 1.0f;
		pRoom->vecTextures.push_back(grassTexture);
		pRoom->pDebugRenderer = ::g_pDebugRenderer;
		vec_pObjectsToDraw.push_back(pRoom);
	}

	//std::vector< cMeshObject* > vec_pObjectsToDraw;
	{
		cMeshSceneObject* pDoors = new cMeshSceneObject();
		pDoors->friendlyName = "Doors";
		pDoors->bIsVisible = false;

		pDoors->position = RoomPosition;
		pDoors->setMeshOrientationEulerAngles(glm::vec3(0.0f, 0.0f, 0.0f), true);
		pDoors->setDiffuseColour(glm::vec3(1.0f, 0.0f, 0.0f));
		pDoors->setSpecularPower(100.0f);
		pDoors->meshName = "Room_2_Bigger_Doorways.ply";
		pDoors->setUniformScale(RoomScale);
		sTextureInfo grassTexture;
		grassTexture.name = "grass.bmp";
		grassTexture.strength = 1.0f;
		pDoors->vecTextures.push_back(grassTexture);
		pDoors->pDebugRenderer = ::g_pDebugRenderer;
		vec_pObjectsToDraw.push_back(pDoors);
	}

}

// For the particle emitter examples
void setUpParticleEmitters(void)
{
	return;
}








// LoJam code:
void LoadModelsIntoScene_LOJAM( std::vector<cMeshSceneObject*> &vec_pObjectsToDraw )
{

	LoadPlayerModels_LOJAM(vec_pObjectsToDraw);



	{	// The 2D 2 triangle "flat" imposter object
		cMeshSceneObject* pTestObject = new cMeshSceneObject();
		pTestObject->setDiffuseColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
		pTestObject->setAlphaTransparency( 1.0f );
		pTestObject->friendlyName = "GentleTerrain";
		pTestObject->position = glm::vec3(0.0f, -20.0f, 0.0f);
		pTestObject->setUniformScale(1.0f);
		pTestObject->meshName = "Gentle_Terrain_xyz_uv.ply";	

		//pTestObject->bIsWireFrame = true;
		//pTestObject->bDontLight = true;

		sTextureInfo testObjectTexture;
		testObjectTexture.name = "grass.bmp";
		testObjectTexture.strength = 1.0f;

		pTestObject->vecTextures.push_back( sTextureInfo(testObjectTexture) );
		pTestObject->setUniformScale(1.0f);
		//vec_pObjectsToDraw.push_back( pTestObject );
	}	

//	{	// This will be our "skybox" object.
//		// (could also be a cube, or whatever)
//		cMeshSceneObject* pSkyBoxObject = new cMeshSceneObject();
//		pSkyBoxObject->setDiffuseColour( glm::vec3( 1.0f, 105.0f/255.0f, 180.0f/255.0f ) );
//		pSkyBoxObject->bUseVertexColour = false;
//		pSkyBoxObject->friendlyName = "SkyBoxObject";
//		float scale = 5000.0f;	
//		pSkyBoxObject->nonUniformScale = glm::vec3(scale,scale,scale);
//		pSkyBoxObject->meshName = "Sphere_320_faces_xyz_n_GARBAGE_uv_INVERTED_NORMALS.ply";			// "Sphere_320_faces_xyz.ply";
////		pSkyBoxObject->bIsWireFrame = true;
//
//		// Invisible until I need to draw it
//		pSkyBoxObject->bIsVisible = false;
//
//		vec_pObjectsToDraw.push_back( pSkyBoxObject );
//	}

	{	// This sphere is the tiny little debug sphere
		cMeshSceneObject* pDebugSphere = new cMeshSceneObject();
		pDebugSphere->position = glm::vec3( 0.0f, 0.0f, 0.0f );
//		pDebugSphere->objColour = glm::vec3( 0.0f, 1.0f, 0.0f );
		pDebugSphere->setDiffuseColour( glm::vec3(0.0f, 1.0f, 0.0f) );
		float scale = 0.1f;
		pDebugSphere->friendlyName = "DebugSphere";
		pDebugSphere->nonUniformScale = glm::vec3(scale,scale,scale);
		pDebugSphere->meshName = "Sphere_320_faces_xyz_n_GARBAGE_uv.ply";		// "Sphere_320_faces_xyz.ply";
		pDebugSphere->bIsWireFrame = true;
		pDebugSphere->bIsVisible = false;
		pDebugSphere->pDebugRenderer = ::g_pDebugRenderer;

		//pTerrain->nonUniformScale = glm::vec3(0.1f,0.1f,0.1f);
		//vec_pObjectsToDraw.push_back( pDebugSphere );
	}

	return;
}