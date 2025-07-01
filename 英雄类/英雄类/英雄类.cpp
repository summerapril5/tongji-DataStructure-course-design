#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class hero {
private:
	double hp;
	double aggressivity;
	double spell_power;
	double defense;
	double spell_resistance;
	double energy;
	double cost;

public:
	hero(double hp1, double aggressivity1,double spell_power1,double defense1,double spell_resistance1,double energy1,double cost1 ) {
		//依次是生命值，攻击力，法强，防御，法抗，能量（蓝条），费用
		hp = hp1;
		aggressivity = aggressivity1;
		spell_power = spell_power1;
		defense = defense1;
		spell_resistance = spell_resistance1;
		energy = energy1;
		cost = cost1;
	}
};


int main() {
	hero Quesanti(500, 20, 50, 100, 200,50,1);//魔法坦克
	hero Tam(600,40,30,200,100,60,2);//物理坦克
	hero Yongen(400, 70, 0, 50, 50, 60, 2);//物理战士
	hero yasuo(400, 30, 60, 60, 60, 30, 3);//法术战士
	hero Shamila(300, 70, 20, 40, 40, 70, 2);//物理射手
	hero Vex(300, 0, 90, 40, 40,60, 3);//法师

}