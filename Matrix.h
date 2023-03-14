#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

class Row {
private:
	std::vector<double> numbers;
	int length;
public:
	Row() { this->length = 0; }
	Row(std::size_t length) {
		this->length = length;
		numbers = std::vector<double>(length, 0);
	}
	double operator [](std::size_t i) const {
		return numbers[i];
	}
	double& operator [](std::size_t i) {
		return numbers[i];
	}
	Row operator +(Row& other) {
		Row result;
		std::size_t minSize = std::min(this->numbers.size(), other.numbers.size());

		for (std::size_t i = 0; i < minSize; i++) {
			result.numbers.push_back(this->get(i) + other.get(i));
		}

		for (std::size_t i = minSize; i < this->numbers.size(); i++) {
			result.numbers.push_back(this->get(i));
		}

		for (std::size_t i = minSize; i < other.numbers.size(); i++) {
			result.numbers.push_back(other.get(i));
		}

		return result;
	}
	Row operator += (Row& other)
	{
		for (int i = 0; i < other.size(); i++)
		{
			this->numbers[i] += other[i];
		}
	}
	Row operator *(double& by) {
		Row result;
		result.numbers = this->numbers;
		for (std::size_t i = 0; i < numbers.size(); i++) {
			result.numbers[i] *= by;
		}
		return result;
	}
	void add(double value) {

		this->numbers.push_back(value);
	}
	void set(double value, std::size_t index) {
		numbers[index] = value;
	}
	void setLenth(int length) { this->length = length; }
	double get(std::size_t index) {
		return numbers[index];
	}
	int getLenth() { return this->length; }
	std::size_t size() {
		return numbers.size();
	}
	void print() const {
		for (int i = 0; i < numbers.size(); i++) {
			std::cout << numbers[i] << std::endl;
		}
	}
	bool operator ==(Row other) const {
		double delta = 0.00001;
		if (this->numbers.size() != other.numbers.size()) {
			return false;
		}
		else {
			for (int i = 0; i < this->numbers.size(); i++) {
				if (abs(this->numbers[i] - other.numbers[i]) > delta) {
					return false;
				}
			}
		}
		return true;
	}
	bool operator !=(Row other) {
		Row row = *this;
		return !(row == other);
	}

	void setRandomValues()
	{
		for (int i = 0; i < this->length; i++)
		{
			if (rand() % 2 == 0)
			{
				this->numbers[i] = -1.f / ((double)(rand() % 100) + 1);
			}

			else
			{
				this->numbers[i] = 1.f / ((double)(rand() % 100) + 1);
			}
		}
	}

	void addValueByIndex(int position, double value )
	{
		this->numbers[position] += value;
	}

	void addValue(double value)
	{
		this->numbers.push_back(value);
	}

};

class Matrix {

private:

	std::vector<Row> table;
	int x;
	int y;

public:

	Row operator [](std::size_t i) const {
		return table[i];
	}
	Row& operator [](std::size_t i) {
		return table[i];
	}
	Matrix operator *(Matrix other) 
	{
		Matrix ans{other.getX(), this->y};

		double value = 0;
		for(int i = 0; i < y; i++)
		{
			for(int j = 0; j < other.getX(); j++)
			{
				for(int k = 0; k < other.getY(); k++)
				{
					ans[i][j] += table[i][k] * other[k][j];
				}
			}
		}
		
		return ans;
	}

	Matrix(int x, int y) {
		this->x = x;
		this->y = y;
		for (int i = 0; i < y; i++) {
			table.push_back(Row(x));
		}
	}
	Matrix() {
		x = 0;
		y = 0;
	}

	void setRandomValues()
	{
		for (int i = 0; i < this->y; i++)
		{
			for (int j = 0; j < this->x; j++)
			{
				if (rand() % 2 == 0)
				{
					this->table[i][j] = -1.f / ((float)(rand() % 20) + 1);
				}
				else
				{
					this->table[i][j] = 1.f / ((float)(rand() % 20) + 1);
				}
			}
		}
	}
	int getX() 
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
	void print() {
		std::cout << "Matrix:" << std::endl;

		for (int i = 0; i < this->y; i++) {
			for (int j = 0; j < this->x; j++) {
				std::cout << table[i][j] << "\t";
			}
			std::cout << std::endl;
		}
	}
};

#endif MATRIX_H