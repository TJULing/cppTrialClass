
#include <iostream>

enum Bike_Type {vivi, giant, flyingPigeon};
class Speed
{
public:
	// 构造函数中，对成员变量使用“默认值”: a.初始化 vs b.赋值
	/*
	结论：尽量使用“初始化列表”对成员变量进行初始化
		1.性能方面：对于含有自定义类型成员变量的类，相比后者（先创建<对于自定义类型的成员变量，此时将调用该自定义类的默认构造函数>，再赋值<调用该定义类的赋值=函数>），
		使用“初始化列表”时，仅会调用该自定义类的复制构造函数完成初始化，
		2.含有以下几种成员变量，则必须使用初始化列表：
			（1）常量成员，因为常量只能初始化不能赋值，所以必须放在初始化列表里面
			（2）引用类型成员，引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面
			（3）没有默认构造函数的自定义类型成员，因为使用初始化列表可以不必调用默认构造函数来初始化，而是直接调用复制构造函数初始化。
				（ps:若自定义了任意构造函数，则系统将不提供默认构造函数。）
	参考：
	1. https://www.cnblogs.com/graphics/archive/2010/07/04/1770900.html
	2. https://www.runoob.com/w3cnote/cpp-construct-function-initial-list.html
	*/
	// 1、不接受参数的构造函数
	//Speed(): vilocity(0), angle(0) {} //a. “初始化”：在“初始化列表”中指定初始值（推荐）；
	//Speed() { vilocity = 0, angle =0; } // b. 成员变量创建后 在“函数体内”{成员变量=右值}，对
	//（Alert：不适用于给含有const或引用成员变量的类；也不适用于成员变量为自定义类，而该类不含默认构造函数；此外，也多出operator=操作）；
	
	// 2、接受参数的构造函数
	/*ps：构造函数、其他成员函数 也和常规函数一样————1.“在函数声明中”指定形参的默认取值；2.从右向左；3.函数声明中的形参名和函数定义中的形参名可以不同。*/
	//Speed(int dftVilocity, int dftAngle = 0); // 重载构造函数：可接受2个、1个参数（若缺失无参数的构造函数，编译器会报错：没有合适的默认构造函数可用）
	Speed(int dftVilocity = 0, int dftAngle = 0); // 重载构造函数：可接受2个、1个、0个参数（若已有无参数的构造函数，编译器会报错：重载函数不明确）
	//: vilocity(dftVilocity), angle(dftAngle) {} //a. “初始化列表”
	//{ vilocity = dftVilocity; angle = dftAngle; } //b.“函数体内”
	Speed(const Speed & rhs) { vilocity = rhs.getVilocity(); angle = rhs.getAngle(); std::cout << "copy constructor is called. \n"; } // 复制构造函数
	~Speed() {} // 析构函数 （注意：不能重载）
	void showSpeed() { std::cout << "current speed is: \n"; std::cout << "vilocity = " << vilocity<<"\n"; std::cout << "angle = " << angle<<"\n"; };
	void setVilocity(int newVilocity) { vilocity = newVilocity; }
	void setAngle(int newAngle) { angle = newAngle; }
	int getVilocity() const { return vilocity; }
	int getAngle() const { return angle; }
	void vilocityUP() { vilocity++; }
	void vilocityDown() { vilocity--; }
	void angleUp() { angle++; }
	void angleDown() { angle--; }

private:
	int vilocity;
	int angle;
};
Speed::Speed(int newVilocity, int newAngle) : vilocity(newVilocity), angle(newAngle)
{
//	vilocity = newVilocity;
//	angle = 360;//在初始化列表里面初始化完后，依然可以在函数体内重新赋值
}

class Bike
{
public:
	Bike():bikeType(vivi) { std::cout << "Bike constructor: creat a default Bike object.\n"; };
	Bike(Bike_Type newBikeType, const Speed & newSpeed) :bikeType(newBikeType), crtSpeed(newSpeed) { std::cout << "Bike constructor: creat a specific Bike object.\n"; };//此处初始化列表对speed成员变量调用了复制构造函数进行初始化
	Bike(const Bike &rhsBike) { std::cout << "Bike copy constructor\n"; bikeType = rhsBike.getBikeType(); crtSpeed = rhsBike.getBikeSpeed(); }
	~Bike() { std::cout << "Bike destructor.\n"; };
	void setBikeType(Bike_Type newBikeType) { bikeType = newBikeType; }
	void setBikeSpeed(int newVilocity, int newAngle) { crtSpeed.setVilocity(newVilocity); crtSpeed.setAngle(newAngle); };
	void setBikeSpeed(Speed &newSpeed) { crtSpeed = newSpeed; };
	Bike_Type getBikeType() const { return bikeType; };
	Speed getBikeSpeed() const { return crtSpeed; }
	void showBike() const { std::cout <<"Bike type:\t"<<bikeType<<"\ncurrent volicity:\t"<<crtSpeed.getVilocity()<<"\ncurrent angle:\t"<<crtSpeed.getAngle()<<"\n"; }
	void ring() { std::cout << "Bike rings...\n"; }
	void pedal() { crtSpeed.vilocityUP(); }
	void brake() { crtSpeed.vilocityDown(); }
	void turnLt() { crtSpeed.angleUp(); }
	void turnRt() { crtSpeed.angleDown(); }

private:
	Bike_Type bikeType;
	Speed crtSpeed;

};

int main()
{
    std::cout << "Hello World!\n";
	Speed myspeed;
	Speed myspeed2(15);
	Speed myspeed3(myspeed2);
	myspeed.showSpeed();
	myspeed2.showSpeed();
	myspeed3.showSpeed();
	int fast = 25, northEast = 45;
	Speed myspeed4(fast,northEast);
	myspeed4.showSpeed();

	Bike *mybike = new Bike;
	(*mybike).showBike();
	delete mybike;
	mybike = NULL;
	Bike mybike2(giant,myspeed4);
	mybike2.showBike();
	Bike mybike3(mybike2);
	mybike3.showBike();

	return 0;
}


