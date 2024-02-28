#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
typedef struct {
	double x;
	double y;
} Point;
class Equation {
public:
	// Equation like a*x + b*y <= or >= c
	double a;
	double b;
	double c;
	int sign;
	Equation() {
		a = 0;
		b = 0;
		c = 0;
	}
	double getA() {
		return a;
	};
	double getB() {
		return b;
	};
	double getC() {
		return c;
	};
	int getSign() {
		return sign;
	};
	void setA(double _a) {
		a = _a;
	}
	void setB(double _b) {
		b = _b;
	}
	void setC(double _c) {
		c = _c;
	}
	void setSign(int _sign) {
		sign = _sign;
	}
	void inputValues() {
		double _a;
		double _b;
		double _c;
		//cin >> _a >> _b >> _c;
		cout << "Enter A: ";
		cin >> _a;
		cout << "Enter B: ";
		cin >> _b;
		cout << "Enter C: ";
		cin >> _c;
		a = _a;
		b = _b;
		c = _c;
	}
	double getFunctionValue(Point point) {
		return point.x * a + point.y * b - c;
	}
	Point getIntersection(Equation equation2) {
		Point result;
		double denominator = getDeterminant(a, b, equation2.getA(), equation2.getB());
		if (denominator == 0) {
			result.x = result.y = -999999;
			return result;
		}
		result.x = getDeterminant(c, b, equation2.getC(), equation2.getB()) / denominator;
		result.y = getDeterminant(a, c, equation2.getA(), equation2.getC()) / denominator;
		return result;
	}
	double getDeterminant(double a,
		double b,
		double c,
		double d) {
		return a * d - b * c;
	}
};
bool checkValues(Point point, Equation equation) {
	double func = equation.getFunctionValue(point);
	double sign = equation.getSign();
	if (point.x < 0 || point.y < 0)
		return false;
	if (sign == 1)
		return (func >= 0 ? true : false);
	if (sign == 0)
		return (func <= 0 ? true : false);
}
int main() {
    cout << "LR # 1, Pavlo Valchevskyi, group OI-11 sp, variant # 91" << endl;
	Equation targetFunction;
	int numOfEquations;
	cout << "Enter the coof-s of target function: A*x + B*y <= or >= C: " << endl;
	targetFunction.inputValues();
	cout << "Enter the amount of limit-equations: ";
	cin >> numOfEquations;
	vector <Equation> limits;
	int s;
	for (int i = 0; i < numOfEquations; i++) {
		Equation temp;
		cout << "Enter the coof-s for" << i + 1 << " equation A*x + B*y <= or >= C: " << endl;;
		temp.inputValues();
		cout << "Choose the sign: \n\t1: >= \n\t0: <=\nSign: ";
		cin >> s;
		temp.setSign(s);
		limits.push_back(temp);
	}
	vector<Point>pointsArr;
	int i = 0;
	while (i < numOfEquations * 2) {
		Point temp;
		temp.x = 0;
		temp.y = limits[i / 2].getC() / limits[i / 2].getB();
		pointsArr.push_back(temp);
		i++;
		temp.y = 0;
		temp.x = limits[i / 2].getC() / limits[i / 2].getA();
		pointsArr.push_back(temp);
		i++;
	}
	for (int lim1 = 0; lim1 < numOfEquations; lim1++)
		for (int lim2 = lim1 + 1; lim2 < numOfEquations; lim2++, i++)
			pointsArr.push_back(limits[lim1].getIntersection(limits[lim2]));
	for (int j = 0; j < i; j++) {
		int flag = 0;
		for (int k = 0; k < numOfEquations; k++) {
			if (checkValues(pointsArr[j], limits[k]) == false) {
				flag++;
				break;
			}
		}
		if (flag) {
			pointsArr.erase(pointsArr.begin() + j);
			j--;
			i--;
		}
	}
	int minPoint = 0;
	int maxPoint = 0;
	double minN;
	double maxN;
	double func;
	minN = maxN = targetFunction.getFunctionValue(pointsArr[0]);
	i = pointsArr.size();
	for (int j = 1; j < i; j++) {
		func = targetFunction.getFunctionValue(pointsArr[j]);
		if (func > maxN) {
			maxN = func;
			maxPoint = j;
		}
		if (func < minN) {
			minN = func;
			minPoint = j;
		}
	}
	cout << "Maximum of target function is: " << maxN << " at the point: " << pointsArr[maxPoint].x
		<< " " << pointsArr[maxPoint].y << endl;
	cout << "Minimum of target function is: " << minN << " at the point: " << pointsArr[minPoint].x <<
		" " << pointsArr[minPoint].y << endl;

	return 0;
}