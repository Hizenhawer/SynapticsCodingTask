#include "pch.h"
#include "CppUnitTest.h"
#include "../SynapticsCodingTask/RGB.h"
#include "../SynapticsCodingTask/Display.h"
#include "../SynapticsCodingTask/RGB.cpp"
#include "../SynapticsCodingTask/Display.cpp"
#define private public
#include "../SynapticsCodingTask/Gradient.h"
#include "../SynapticsCodingTask/Gradient.cpp"
#undef private
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SynapticsCodingTaskTests
{
	TEST_CLASS(RGBToString)
	{
	public:

		TEST_METHOD(Black)
		{
			string expected = "R: 0 G: 0 B: 0";
			string result = RGB(0x0).to_string();
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(White)
		{
			string expected = "R: 31 G: 63 B: 31";
			string result = RGB(0xFFFF).to_string();
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(Mix)
		{
			string expected = "R: 20 G: 44 B: 29";
			string result = RGB(0xA59D).to_string();
			Assert::AreEqual(expected, result);
		}
		TEST_METHOD(SecondConstructor)
		{
			uint16_t expected = 0xA59D;
			uint16_t result = RGB(20, 44, 29).getRGB();
			Assert::AreEqual((int)expected, (int)result);
		}
	};

	TEST_CLASS(GradientTests) {
		TEST_METHOD(GenerateOneGradientEasy) {
			uint16_t expected = 0x0000;
			RGB color1(0, 0, 0);
			RGB color2(0, 0, 0);
			uint16_t result = Gradient::generate_gradient(color1, color2, 1)[0];
			Assert::AreEqual((int)expected, (int)result);
		}
		TEST_METHOD(GenerateOneGradientHard) {
			uint16_t expected = 0x28a0;
			RGB color1(1, 9, 0);
			RGB color2(9, 2, 0);
			uint16_t result = Gradient::generate_gradient(color1, color2, 1)[0];
			Assert::AreEqual((int)expected, (int)result);
		}
		TEST_METHOD(GenerateArrayGradientHard) {
			uint16_t expected[] = { 18474,16454,12355 };
			RGB color1(11, 1, 13);
			RGB color2(5, 2, 0);
			uint16_t* result = Gradient::generate_gradient(color1, color2, 3);
			bool comparator = true;
			for (int i = 0; i < 3; i++)
			{
				if (expected[i] != result[i]) {
					comparator = false;
					cout << expected << endl;
					cout << result << endl;
					break;
				}
			}
			Assert::IsTrue(comparator);
		}
		TEST_METHOD(TestGradient1) {
			//uint16_t expected[] = {0x01e0,0x3200,0x5820,0x09a0,0x2100,0x4040,0x1180,0x20c,0x2840};
			uint16_t expected[] = {
				RGB(0,15,0).getRGB(),RGB(6,8,0).getRGB(),RGB(11,1,0).getRGB(),
				RGB(1,12,0).getRGB(),RGB(5,7,0).getRGB(),RGB(8,2,0).getRGB(),
				RGB(2,10,0).getRGB(),RGB(4,6,0).getRGB(),RGB(5,2,0).getRGB()
			};
			RGB rgbs[] = { RGB(0,15,0),RGB(11,1,0),RGB(2,10,0),RGB(5,2,0) };
			Gradient grad = Gradient(rgbs, { 3,3 });
			uint16_t* result = grad.getPixels();
			bool comparator = true;
			for (int i = 0; i < 9; i++)
			{
				if (expected[i] != result[i]) {
					comparator = false;
					cout << expected << endl;
					cout << result << endl;
					break;
				}
			}
			Assert::IsTrue(comparator);
		}
		TEST_METHOD(TestGradient2) {
			uint16_t expected[] = {
				RGB(0,0,0).getRGB(),RGB(0,0,7).getRGB(),RGB(0,0,13).getRGB(),RGB(0,0,20).getRGB(),
				RGB(0,0,3).getRGB(),RGB(0,0,8).getRGB(),RGB(0,0,12).getRGB(),RGB(0,0,17).getRGB(),
				RGB(0,0,7).getRGB(),RGB(0,0,9).getRGB(),RGB(0,0,11).getRGB(),RGB(0,0,13).getRGB(),
				RGB(0,0,10).getRGB(),RGB(0,0,10).getRGB(),RGB(0,0,10).getRGB(),RGB(0,0,10).getRGB()
			};
			RGB rgbs[] = { RGB(0,0,0),RGB(0,0,20),RGB(0,0,10),RGB(0,0,10) };
			Gradient grad = Gradient(rgbs, { 4,4 });
			uint16_t* result = grad.getPixels();
			bool comparator = true;
			for (int i = 0; i < 16; i++)
			{
				if (expected[i] != result[i]) {
					comparator = false;
					cout << expected << endl;
					cout << result << endl;
					break;
				}
			}
			Assert::IsTrue(comparator);
		}
		TEST_METHOD(TestGradientRectangle1) {
			uint16_t expected[] = {
				RGB(0,0,0).getRGB(),RGB(0,0,7).getRGB(),RGB(0,0,13).getRGB(),RGB(0,0,20).getRGB(),
				RGB(0,0,4).getRGB(),RGB(0,0,8).getRGB(),RGB(0,0,12).getRGB(),RGB(0,0,16).getRGB(),
				RGB(0,0,7).getRGB(),RGB(0,0,9).getRGB(),RGB(0,0,11).getRGB(),RGB(0,0,13).getRGB()
			};
			RGB rgbs[] = { RGB(0,0,0),RGB(0,0,20),RGB(0,0,7),RGB(0,0,13) };
			Gradient grad = Gradient(rgbs, { 4,3 });
			uint16_t* result = grad.getPixels();
			bool comparator = true;
			for (int i = 0; i < 12; i++)
			{
				if (expected[i] != result[i]) {
					comparator = false;
					cout << expected << endl;
					cout << result << endl;
					break;
				}
			}
			Assert::IsTrue(comparator);
		}
		TEST_METHOD(TestGradientRectangle2) {
			uint16_t expected[] = {
				RGB(0,0,0).getRGB(),RGB(0,0,4).getRGB(),RGB(0,0,7).getRGB(),
				RGB(0,0,7).getRGB(),RGB(0,0,8).getRGB(),RGB(0,0,9).getRGB(),
				RGB(0,0,13).getRGB(),RGB(0,0,12).getRGB(),RGB(0,0,11).getRGB(),
				RGB(0,0,20).getRGB(),RGB(0,0,16).getRGB(),RGB(0,0,13).getRGB()
			};
			RGB rgbs[] = { RGB(0,0,0),RGB(0,0,7),RGB(0,0,20),RGB(0,0,13) };
			Gradient grad = Gradient(rgbs, { 3,4 });
			uint16_t* result = grad.getPixels();
			bool comparator = true;
			for (int i = 0; i < 12; i++)
			{
				if (expected[i] != result[i]) {
					comparator = false;
					cout << expected << endl;
					cout << result << endl;
					break;
				}
			}
			Assert::IsTrue(comparator);
		}
	};
}
