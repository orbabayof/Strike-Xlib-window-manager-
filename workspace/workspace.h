#include "tiler.h"
#include "util.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <list>
#include <vector>

class workspace
{
  public:
	workspace(Screen *screen);

	void add(Window w);
	void remove(Window w);

	void hide();
	void show();
  
  //might add showIFEmpty

  private:
	// used to config next variables
	Screen *m_screen{nullptr};

	Window m_workspace_root{g_root};
	tiler m_tiler{};

	Window attachWorkspaceRoot();
};

class workspace_manager
{
  public:
	workspace_manager(int screen_num, std::size_t num_of_workspaces);
	workspace_manager() = delete;

	void moveTo(std::size_t workspace_num);
	workspace &workSpace(std::size_t workspace_num);

	void add(Window w);
	void remove(Window w);

  private:
	Screen *m_screen{};
	std::size_t m_curr_workspace{};
	std::vector<workspace> m_workspaces{};
};

class screen_manager
{
  public:

	screen_manager() = default;
  void screenInit();

	workspace_manager &screenNum(std::size_t screen_num);

  private:
	// ordered by screen number
	std::list<workspace_manager> m_workspaces_managers;

	workspace_manager &workspaceManagerScreen(std::size_t idx);
};

// help for the test

inline workspace &getWorkSpace(int screen_num)
{
	static workspace w{XScreenOfDisplay(dpy(), screen_num)};
	return w;
}
