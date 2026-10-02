#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename K, typename V>
void display_pair(pair<K, V> p) {
	cout << p.first << " = $" << p.second << endl;
}

struct PriceUnder {
	double limit;

	PriceUnder(double l) {
		limit = l;
	}

	bool operator()(pair<string, double> p) const {
		return p.second < limit;
	}
};

int main()
{
	cout<< "Product Inventory\n\n";

	map<string, double> products{
		{"Minecraft", 199.99},
		{"Ark", 799.99},
		{"Roblox", 249.99},
		{"Five Nights At Freddy's", 489.99},
		{"Subnotica", 120.50}
	};

	cout << "All Products:\n";
	for_each(products.begin(), products.end(), display_pair<string, double>);

	double totalValue = accumulate(products.begin(), products.end(), 0.0,
		[](double sum, pair<string, double> p) {
			return sum + p.second;
		}
	);

	cout << "Total Inventory Value = $" << totalValue << endl;

	double limit = 500;
	int underLimit = count_if(products.begin(), products.end(), PriceUnder(limit));
	cout << "Number Of Products Under $" << limit << ": " << underLimit << endl;

	auto iter = find_if(products.begin(), products.end(), PriceUnder(150));
	if (iter != products.end()) {
		cout << "Found Product Under $150: " << iter->first << " $" << iter->second;
	}
	else {
		cout << "No Products Found Under $150.\n" << endl;
	}

	return 0;
}
