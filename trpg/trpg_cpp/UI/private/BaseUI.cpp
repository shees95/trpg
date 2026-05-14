#include <iostream>
#include <string>

#include "../public/BaseUI.h"

using namespace std;

void BaseUI::Clear()
{
    BaseUI::Print_ln(10);
}

void BaseUI::Wait_AnyKey()
{
    BaseUI::Print("\nPress Enter to continue...");
    cin.ignore(256, '\n'); // 이전 입력의 잔여물 제거
    cin.get(); // 엔터 입력 대기
}

void BaseUI::Print(string text)
{
    cout << text;
}


void BaseUI::Print_t(string text = "\t")
{
    Print(text + "\t");
}
void BaseUI::Print_ln(string text = "\n")
{
    Print(text + "\n");
}


void BaseUI::Print_t(int repeat)
{
    for(int i = 0; i < repeat; i++) Print("\t");
}
void BaseUI::Print_ln(int repeat)
{
    for (int i = 0; i < repeat; i++) Print("\n");
}


void BaseUI::Print_BorderLine_Single()
{
    Print("\n-------------------------------------------\n");
}
void BaseUI::Print_BorderLine_Double()
{
    Print("\n===========================================\n");
}




const int& BaseUI::Print_Choice_Number(const int& min, const int& max)
{
    int input;
    while (true)
    {
        Print("Select Number : ");
        if (!(cin >> input)) // 숫자가 아닌 값이 들어오면 false 반환
        {
            cin.clear(); // 에러 플래그 초기화
            cin.ignore(256, '\n'); // 버퍼 비우기
            Print_ln("! Invalid input. Please enter a number.");
            continue;
        }

        if (input >= min && input <= max) break;
        
        Print_ln("! Out of range. Try again.");
    }

    Print_ln(1);
    Print_BorderLine_Single();
    return input;
}