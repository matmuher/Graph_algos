#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GLFW
{
	struct ScopeGuard
	{
		ScopeGuard()
		{
			glfwInit();
		}

		~ScopeGuard()
		{
			glfwTerminate();	
		}
	};

	static void initOpenGL(int versionMajor, int versionMinor)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	struct Window
	{
		GLFWwindow* window = nullptr;

		Window(int width, int height, const char* title)
		{
			window = glfwCreateWindow(width, height, title, NULL, NULL);
		
			if (!window)
			{
				throw "Cant create glfw window";
			}

			makeContextCurrent();

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			{
				throw "Glad cant load GL functions";
			}

			glViewport(0, 0, width, height);
		}

		void makeContextCurrent()
		{
			glfwMakeContextCurrent(window);
		}

		bool shouldClose()
		{
			return glfwWindowShouldClose(window);
		}

		void swapBuffers()
		{
			glfwSwapBuffers(window);
		}

		bool isPressed(int key_code)
		{
		    return glfwGetKey(window, key_code) == GLFW_PRESS;
		}

		int processInput()
		{   
		    static float last_time = 0.;

		    float current_time = glfwGetTime();
		    float delta_time = current_time - last_time;

		    if (delta_time > 0.05) // delay time
		    {

			    if (isPressed(GLFW_KEY_ESCAPE))
			    {
    			    last_time = current_time;
			        glfwSetWindowShouldClose(window, true);
			        return GLFW_KEY_ESCAPE;
			    }
			    else if (isPressed(GLFW_KEY_LEFT))
			    {
			    	last_time = current_time;
			        return GLFW_KEY_LEFT; 
			    }
			    else if (isPressed(GLFW_KEY_RIGHT))
			    {
			    	last_time = current_time;
			        return GLFW_KEY_RIGHT;
			    }
			}

			return 0;
		}
	};

	void pollEvents()
	{
		glfwPollEvents();
	}
}

const float TriangleModel[] = 	{
								0., 0., 0.,
								1., 0., 0.,
								0., 1., 0.
								}; 

const float QuadModel[] = 	{
							0., 0., 0.,
							1., 0., 0.,
							0., 1., 0.,
							1., 1., 0.
							};

const GLuint QuadIndices[] = {	0, 1, 2,
								1, 2, 3};
struct GridDrawer
{
public:

	Shader shader;

	GridDrawer(size_t GridSize)
	:
		shader{"../src/shaders/default.vs", "../src/shaders/default.fs"},
		GridSize_{GridSize}
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER,
					sizeof(QuadModel),
					QuadModel,
					GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					 sizeof(QuadIndices),
					 QuadIndices,
					 GL_STATIC_DRAW);

		glGenBuffers(1, &colorsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferData(	GL_ARRAY_BUFFER,
						GridSize * GridSize * sizeof(GA::Color),
						NULL,
						GL_DYNAMIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(	0,
								3, GL_FLOAT,
								GL_FALSE,
								3 * sizeof(float),
								(void*) 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(	1,
								3, GL_FLOAT,
								GL_FALSE,
								sizeof(GA::Color),
								(void*) 0);
		glVertexAttribDivisor(1, 1);
	}

	void updateColors(const void* start)
	{
		glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
		glBufferSubData(GL_ARRAY_BUFFER,
						0,
						GridSize_ * GridSize_ * sizeof(GA::Color),
						start
						);

		glCheckError();
	}

	void drawGrid()
	{
		glBindVertexArray(VAO);
		
		glDrawElementsInstanced(GL_TRIANGLES,
								6,
								GL_UNSIGNED_INT,
								0,
								GridSize_ * GridSize_);

		glCheckError();
	}

	size_t GridSize_;
	GLuint VAO;
	
	GLuint VBO; // quad vertices positions
	GLuint colorsVBO; // per instance color

	GLuint EBO;
};
