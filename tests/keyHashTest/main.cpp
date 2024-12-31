#include "key.h"
#include <X11/Xlib.h>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_set>

void keyHash_test()
{

  std::unordered_set<key> keys; 
  int coll_count { 0 };
  std::size_t biggest_bucket { 0 };

	for (unsigned long i{0}; i < 37; ++i)
	{
		for (int j{0}; j < 37; ++j)
		{
      keys.emplace(key{i,j});
		}
	}


  for(size_t bucket = 0; bucket < keys.bucket_count(); bucket++) {
      if(keys.bucket_size(bucket) > 1) {
          coll_count += keys.bucket_size(bucket);
          biggest_bucket = std::max(keys.bucket_size(bucket),biggest_bucket);
      }
  }

  std::cout << "coll num -> " << coll_count << '\n';
  std::cout << "biggest -> " << biggest_bucket << '\n'; 
}


int main(int argc, char *argv[])
{

  keyHash_test();
	return 0;
}
