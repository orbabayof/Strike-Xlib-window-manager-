#include "util.h"
#include <list>
#include <settings.h>
#include <workspace.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstddef>
#include <iterator>
#include <vector>

workspace::workspace(Screen *screen) : m_screen{screen}, m_tiler{m_screen}, m_workspace_root{attachWorkspaceRoot()}
{
}

void workspace::add(Window w)
{
	m_tiler.add(w);
	XReparentWindow(dpy(), w, m_workspace_root, 0, 0);
}

void workspace::remove(Window w)
{
	m_tiler.extract(w);
}

void workspace::hide()
{
  //will have to check that it works
	//XUnmapSubwindows(dpy(), m_workspace_root);
  XUnmapWindow(dpy(), m_workspace_root);
}

void workspace::show()
{
  //will have to check that it works
	//XMapSubwindows(dpy(), m_workspace_root);
  XMapWindow(dpy(), m_workspace_root);
}

Window workspace::attachWorkspaceRoot()
{
	// a dummy window that will be used to acesss his child windows
	return XCreateWindow(dpy(), g_root, 0, 0, WidthOfScreen(m_screen), HeightOfScreen(m_screen), 0, CopyFromParent,
						 InputOutput, CopyFromParent, 0, nullptr);
}

workspace_manager::workspace_manager(int screen_num, std::size_t num_of_workspaces)
	: m_screen{ScreenOfDisplay(dpy(), screen_num)}, m_curr_workspace{0}
{
	m_workspaces.reserve(num_of_workspaces);

	for (std::size_t i{0}; i < num_of_workspaces; ++i)
		m_workspaces.emplace_back(workspace{m_screen});
}

workspace &workspace_manager::workSpace(std::size_t workspace_num)
{
	if (workspace_num == 0 || workspace_num > m_workspaces.size())
		return m_workspaces[m_curr_workspace];

	return m_workspaces[workspace_num + 1];
}

void workspace_manager::moveTo(std::size_t workspace_num)
{
	workSpace(m_curr_workspace).hide();
	workSpace(workspace_num).show();

	m_curr_workspace = workspace_num;
}

void workspace_manager::add(Window w)
{
	workSpace(m_curr_workspace).add(w);
}

void workspace_manager::remove(Window w)
{
	workSpace(m_curr_workspace).remove(w);
}

workspace_manager &screen_manager::workspaceManagerScreen(std::size_t idx)
{
	// a bit more complex for big O(n/2) time
	if (idx < (m_workspaces_managers.size() / 2))
	{
		auto it{m_workspaces_managers.begin()};
		std::advance(it, idx);
		return *it;
	}
	else
	{
		auto it{m_workspaces_managers.rend()};
		std::advance(it, m_workspaces_managers.size() - idx);
		return *it;
	}
}

workspace_manager &screen_manager::screenNum(std::size_t num)
{
	if (num < m_workspaces_managers.size())
	{
		return workspaceManagerScreen(num);
	}

	return workspaceManagerScreen(0);
}

screen_manager::screen_manager()
{
	for (int curr_screen{0}; curr_screen < XScreenCount(dpy()); ++curr_screen)
		m_workspaces_managers.emplace_back(workspace_manager{curr_screen, settings::defualt_num_of_workspaces});
}
