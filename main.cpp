/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-23 23:58:41
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-25 23:56:12
 * @FilePath: /Statistics/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "libstat.h"

#include <iostream>
using namespace std;

int main() {
    statistics::tests::AggregSum();
    statistics::tests::AggregMax();
    statistics::tests::AggregMean();
    statistics::tests::AggregStandardDeviation();
    statistics::tests::AggregMode();
    statistics::tests::AggregPrinter();

    cout << "Test passed!"sv << endl;
}