
int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int min(int a, int b) {
	if (a < b)return a;
	return b;
}

bool is_valid(int i, int j, int m, int n) {
	return i >= 0 && i < m&& j >= 0 && j < n;
}

bool is_valid(pair<int, int> pos, int m, int n) {
	return is_valid(pos.first, pos.second, m, n);
}

void process(vector<vector<int>>& A, int m, int n, pair<int, int> p, int& cnt){
    if (is_valid(p, m, n) && A[p.first][p.second] == 0){
        A[p.first][p.second] = 2;
        cnt++;
    }
}
int mark_neighbour_fields(vector<vector<int>>& A, int x, int y, int m, int n, int K) {
	K = min(max(m, n) + 1, K);
	int cnt = 1;
	for (int i = 0; i <= K; i++) {
		for (int j = 0; j <= (K - i); j++) {
			pair<int, int> p1, p2, p3, p4;
			p1.first = x + i; p1.second = y + j;
			p2.first = x + i; p2.second = y - j;
			p3.first = x - i; p3.second = y + j;
			p4.first = x - i; p4.second = y - j;
            process(p1, m, n, A, cnt);
            process(p2, m, n, A, cnt);
            process(p3, m, n, A, cnt);
            process(p4, m, n, A, cnt);
		}
	}
	return cnt;
}
int solution(vector<vector<int>>& A, int K) {
	int m = A.size();
	int n = A[0].size();
	int cnt = 0;
	for (int i = 0; i < m; i++) // mark fields where we CANNOT build 
		for (int j = 0; j < n; j++)
			if (A[i][j] == 1)
				cnt += mark_neighbour_fields(A, i, j, m, n, K);
	return m * n - cnt;
}