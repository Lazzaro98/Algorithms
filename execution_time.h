#include <chrono>

template<typename F, typename... Args>
double ftime(F func, Args&&... args) { //ms
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	func(std::forward<Args>(args)...);
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
}

// Returns execution time of any function
