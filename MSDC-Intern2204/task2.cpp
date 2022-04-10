int solution(vector<int>& blocks) {
	int n = blocks.size();
	vector<int> left;
	//calculating possible left movemenent for each position
	left.push_back(0);
	for (int i = 1; i < n; i++)
		if (blocks[i] <= blocks[i - 1])
			left.push_back(left[i - 1] + 1);
		else
			left.push_back(0);

	int right = 0;
	int max_dist = left[n - 1]; // at the beggining, we guess our optimal position is the most right one
	for (int i = n - 2; i >= 0; i--) {
		if (blocks[i] <= blocks[i + 1]) // and then we iterate through the array from right side to left, keep track of possible right movements, and calculate the max_dist in that case
			right++;
		else 
			right = 0;

		if (left[i] + right > max_dist) // if that is the biggest distance, we keep it
			max_dist = left[i] + right;
	}
	
	return max_dist + 1; // "The distance between blocks K and J is K-J+1", that's why we add 1
}