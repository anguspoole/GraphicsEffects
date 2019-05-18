//   __   __    _ _             
//   \ \ / /  _| | |____ _ _ _  
//    \ V / || | | / / _` | ' \ 
//     \_/ \_,_|_|_\_\__,_|_||_|
//                              
/// LunarG SDK: https://vulkan.lunarg.com/

#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>

int main(int argc, char* argv[])
{

	glfwInit();

	glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

	GLFWwindow* window = glfwCreateWindow( 800, 600, "I Love Vulkan", NULL, NULL );

	uint32_t extensionCount = 0;

	vkEnumerateInstanceExtensionProperties( NULL, &extensionCount, NULL );



	return 0;
}


