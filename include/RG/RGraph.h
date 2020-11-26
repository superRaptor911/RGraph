#ifndef RGRAPH_H
#define RGRAPH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <RG/Signal.h>
#include <glm/glm.hpp>
#include <RG/Window.h>
#include <list>


namespace rg
{
	class RGraph
	{
	private:

		float m_GL_version = 0.f;
		float m_max_GL_version = 0.f;
		bool m_is_initiated = false;

		Window *m_current_window = nullptr;
		Window m_default_window;

	private:

		void m_getGLVersion();

		static void m_error_callback(int error, const char* description);

		inline static RGraph *m_instance_ptr = nullptr;

	public:

		RGraph();
		
		Signal<> RGraph_initiated_signal;
		Signal<> Window_initiated_signal;

		void getGL_version();

		bool InitRgraph();

		void TerminateRgraph();

		static RGraph *getInstancePtr() { return m_instance_ptr;}

		Window *getDefaultWindow();
		
		~RGraph();
	};
	
	
}

#endif
