#include <cassert>
#include <list>

//lets test the indexing algorithm
int workspaceManagerScreen(std::list<int>&  list,std::size_t idx)
{
	// a bit more complex for big O(n/2) time
	if (idx < (list.size() / 2))
	{
		auto it{list.begin()};
		std::advance(it, idx);
		return *it;
	}
	else
	{
		auto it{list.rend()};
		std::advance(it, list.size() - idx);
		return *it;
	}
}
int main (int argc, char *argv[]) {
  
  std::list l {0, 1, 2, 3, 4, 5, 6};
  
  assert(workspaceManagerScreen(l, 2) == 2);
  assert(workspaceManagerScreen(l, 5) == 5);
  return 0;
}
