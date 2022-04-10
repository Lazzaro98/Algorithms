// whenever we substract a number by 1 and bitwise it with itself, the rightmost bit will be unset
// so if we do it in a loop, and count how many times loop executed
// it will be our solution
// perf: O(k) where k is number of set bits
int solution(int A, int B) {
	unsigned long long sol = (unsigned long long)A * B;
	int cnt;
	for (cnt = 0; sol; cnt++)
		sol &= sol - 1;
	return cnt;
}// Brian Kernighan's Algorithm

// I decided not to use lookup table because we have only one check (for the number A*B)
// LUT would be useful if we had muliple numbers to check
