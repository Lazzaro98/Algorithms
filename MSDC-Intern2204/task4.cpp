#define int_max 1000000000 //constraint given in the problem description

bool is_collinear(int i1, int j1, int i2, int j2, int i3, int j3) {
	return (i3 - i1) * (j2 - j1) == (i2 - i1) * (j3 - j1);
}
int calculate_distance(int i1, int j1, int i2, int j2) {
	return (i2 - i1) * (i2 - i1) + (j2 - j1) * (j2 - j1); // we don't have to use sqrt here because we don't need exact distance, but only to find the smallest distance
}

// As a first point, we can choose any
// And then we can find 2 nearest points to that one
// But we have to make sure that third point will not be in the same line as first two
vector<int> solution(vector<int>& X, vector<int>& Y) {
	vector<int> ret;
	int n = X.size();
	if (n < 3) return ret;
	int first = 0, second = 0, third = 0;

	int min_dist = int_max;

	for (int i = 1; i < n; i++) {
		int dist = calculate_distance(X[i], Y[i], X[first], Y[first]);
		if (dist < min_dist) {
			min_dist = dist;
			second = i;
		}
	}

	min_dist = int_max;
	for (int i = 1; i < n; i++)
		if (i != first && i != second) {
			int dist = calculate_distance(X[i], Y[i], X[first], Y[first]);
			if (!is_collinear(X[first], Y[first], X[second], Y[second], X[i], Y[i])
				&& dist < min_dist) {
				min_dist = dist;
				third = i;
			}
		}

	//we have to check if these three are colinear, in case all three values(first, second and third) kept their initial values
	if (second != 0 && third != 0 &&
		!is_collinear(X[first], Y[first], X[second], Y[second], X[third], Y[third])) {
		ret.push_back(first);
		ret.push_back(second);
		ret.push_back(third);
	}

	return ret;
}