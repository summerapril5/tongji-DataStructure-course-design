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
		//����������ֵ������������ǿ��������������������������������
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
	hero Quesanti(500, 20, 50, 100, 200,50,1);//ħ��̹��
	hero Tam(600,40,30,200,100,60,2);//����̹��
	hero Yongen(400, 70, 0, 50, 50, 60, 2);//����սʿ
	hero yasuo(400, 30, 60, 60, 60, 30, 3);//����սʿ
	hero Shamila(300, 70, 20, 40, 40, 70, 2);//��������
	hero Vex(300, 0, 90, 40, 40,60, 3);//��ʦ

}