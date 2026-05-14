#pragma once
#include <string>
using namespace std;
class PotionShop;

class BaseUI
{
public:
    
    static void Clear();
    static void Wait_AnyKey();
    
    static void Print(string text);
    
    static void Print_t(string text);
    static void Print_ln(string text);
    
    static void Print_t(int repeat = 1);
    static void Print_ln(int repeat = 1);
    
    static void Print_BorderLine_Single();
    static void Print_BorderLine_Double();
 
    static void SelectPotionShop(PotionShop& PotionShop, int& position);
    
 
     
    static const int& Print_Choice_Number(const int& min, const int& max);
};