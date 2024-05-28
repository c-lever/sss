#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};


class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};


class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::lowest()} {}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:

	void update(double next) override {
		sum += next;
		n += 1;
	}

	double eval() const override {
		return sum / n;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double sum;
	double n;


};

class Std : public IStatistics {
public:

	void update(double next) override {
		list.push_back(next);
		sum += next;
	}

	double eval() const override {
		if (result == 0) {
			avg = sum / list.size();
			for (int i = 0; i < list.size(); i++) {
				list[i] = pow(list[i] - avg, 2);
				pows_sum += list[i];
			}
			result = sqrt(pows_sum / list.size());
		}

		return result;
	}



	const char* name() const override {
		return "std";
	}

private:
	mutable double pows_sum;
	double sum;
	mutable double avg;
	mutable std::vector<double> list;
	mutable double result;
};

class Pct90 : public IStatistics {
public:

	void update(double next) override {
		list.push_back(next);
	}

	double eval() const override {
		std::sort(list.begin(), list.end());
		if (list.size() % 2 != 0) {
			pct90 = list[static_cast<int>(list.size() * 90 / 100)];
		} else {
			pct90 = ( list[static_cast<int>(list.size() * 90 / 100)-1] + list[static_cast<int>(list.size() * 90 / 100)] ) / 2;
		}
		return pct90;
	}

	const char* name() const override {
		return "pct90";
	}

private:
	mutable double pct90;
	mutable int index;
	mutable std::vector<double> list;


};

class Pct95 : public IStatistics {
public:

	void update(double next) override {
		list.push_back(next);
	}

	double eval() const override {
		std::sort(list.begin(), list.end());
		if (list.size() % 2 != 0) {
			pct95 = list[static_cast<int>(list.size() * 95 / 100)];
		} else {
			pct95 = (list[static_cast<int>(list.size() * 95 / 100)-1]+list[static_cast<int>(list.size() * 95 / 100)])/2;
		}
		return pct95;
	}


	const char* name() const override {
		return "pct95";
	}

private:
	mutable double pct95;
	mutable int index;
	mutable std::vector<double> list;

};


int main() {
	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};

	double val = 0;


	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}
