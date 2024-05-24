#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};


class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::min()} {}

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
	Max() : m_max{std::numeric_limits<double>::min()} {}

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
		avg_sum += next;
	}

	double eval() const override {
		avg = avg_sum / list.size();
		for (double num : list) {
			list_pows.push_back(pow(num - avg, 2));
		}

		for (double num : list_pows) {
			avg_pows_sum += num;
		}

		return sqrt(avg_pows_sum / list_pows.size());
	}

	const char* name() const override {
		return "std";
	}

private:
	mutable double avg_pows_sum;
	double avg_sum;
	double mutable avg;
	std::vector<double> list;
	mutable std::vector<double> list_pows;

};

class Pct90 : public IStatistics {
public:

	void update(double next) override {
		N += 1;
	}

	double eval() const override {
		pct90 = 0.9 * (N - 1);
		return pct90;
	}

	const char* name() const override {
		return "pct90";
	}

private:
	mutable double pct90;
	double N;


};

class Pct95 : public IStatistics {
public:

	void update(double next) override {
		N += 1;
	}

	double eval() const override {
		pct95 = 0.95 * (N - 1);
		return pct95;
	}

	const char* name() const override {
		return "pct95";
	}

private:
	mutable double pct95;
	double N;

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