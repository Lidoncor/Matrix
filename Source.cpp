#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
using namespace std;

class Matrix {
public:
	Matrix() {
		rows = cols = 0;
		data.resize(cols, vector<int>(rows));
	}
	Matrix(int num_rows, int num_cols) {
		rows = num_rows;
		cols = num_cols;
		if ((rows < 0) || (cols < 0)) throw out_of_range("");
		data.resize(cols, vector<int>(rows));
	}
	void Reset(int num_rows, int num_cols) {
		rows = num_rows;
		cols = num_cols;
		data.clear();
		if ((rows < 0) || (cols < 0)) throw out_of_range("");
		data.resize(cols, vector<int>(rows));
	}
	int At(int row, int col) const {
		if ((row >= rows) || (col >= cols) || (row < 0) || (col < 0)) throw out_of_range("");
		return data[col][row];
	}
	int& At(int row, int col) {
		if ((row >= rows) || (col >= cols) || (row < 0) || (col < 0)) throw out_of_range("");
		return data[col][row];
	}
	int GetNumRows() const { return rows; }
	int GetNumColumns() const { return cols; }
private:
	vector<vector<int>> data;
	int rows, cols;
};

istream& operator>>(istream& stream, Matrix& mx) {
	int r, c;
	stream >> r;
	stream.ignore(1);
	stream >> c;
	stream.ignore(1);
	mx = { r, c };
	for (int i = 0; i != r; i++) {
		for (int k = 0; k != c; k++) {
			stream >> mx.At(i, k);
			stream.ignore(1);
		}
	}
	return stream;
};

ostream& operator<<(ostream& stream, const Matrix& mx) {
	if (mx.GetNumColumns() != 0 && mx.GetNumRows() != 0) {
		stream << mx.GetNumRows() << ' ' << mx.GetNumColumns() << endl;
		for (int i = 0; i != mx.GetNumRows(); i++) {
			for (int k = 0; k != mx.GetNumColumns(); k++) {
				stream << mx.At(i, k) << ' ';
			}
			stream << endl;
		}
		return stream;
	}
	else return stream;
};

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if ((lhs.GetNumColumns() == 0 || lhs.GetNumRows() == 0) && (rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0)) return true;
	else if ((lhs.GetNumRows() != rhs.GetNumRows()) || (lhs.GetNumColumns() != rhs.GetNumColumns())) return false;
	for (int i = 0; i != lhs.GetNumRows(); i++) {
		for (int k = 0; k != lhs.GetNumColumns(); k++) {
			if (lhs.At(i, k) != rhs.At(i, k)) return false;
		}
	}
	return true;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	Matrix res;
	if ((lhs.GetNumColumns() == 0 || lhs.GetNumRows() == 0) && (rhs.GetNumColumns() == 0 || rhs.GetNumRows() == 0)) return res;
	else if ((lhs.GetNumRows() != rhs.GetNumRows()) || (lhs.GetNumColumns() != rhs.GetNumColumns())) throw invalid_argument("");
	res = { lhs.GetNumRows(), lhs.GetNumColumns() };
	for (int i = 0; i != lhs.GetNumRows(); i++) {
		for (int k = 0; k != lhs.GetNumColumns(); k++) {
			res.At(i, k) = lhs.At(i, k) + rhs.At(i, k);
		}
	}
	return res;
};