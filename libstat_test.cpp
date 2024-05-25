/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-24 00:01:05
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-26 00:06:38
 * @FilePath: /Statistics/libstat_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "libstat.h"

#include <cassert>
#include <cmath>
#include <sstream>

namespace statistics{
    namespace tests{
        namespace detail{
            template <typename T>
            std::string GetPrinterValue(statistics::AggregPrinter<T>& printer){
                std::ostringstream out;
                printer.Print(out);

                return std::move(out).str();
            }
        }
        void AggregSum() {
            aggregations::Sum aggreg;
            assert(*aggreg.Get() == 0);

            aggreg.PutValue(10.);
            aggreg.PutValue(20.);
            aggreg.PutValue(-40.);

            assert(*aggreg.Get() == -10.);
        }

        void AggregMax() {
            aggregations::Max aggreg;
            assert(!aggreg.Get());

            aggreg.PutValue(10.);
            aggreg.PutValue(20.);
            aggreg.PutValue(-40.);

            assert(*aggreg.Get() == 20.);
        }

        void AggregMean() {
            aggregations::Mean aggreg;
            assert(!aggreg.Get());

            aggreg.PutValue(10.);
            aggreg.PutValue(20.);
            aggreg.PutValue(-40.);
            aggreg.PutValue(30.);

            assert(*aggreg.Get() == 5.);
        }

        void AggregStandardDeviation() {
            aggregations::StandardDeviation aggreg;
            assert(!aggreg.Get());

            aggreg.PutValue(10.);
            aggreg.PutValue(10.);
            aggreg.PutValue(10.);
            aggreg.PutValue(10.);

            assert(std::abs(*aggreg.Get()) < 1e-5);

            aggreg.PutValue(20.);
            aggreg.PutValue(20.);
            aggreg.PutValue(20.);
            aggreg.PutValue(20.);

            assert(std::abs(*aggreg.Get() - 5.) < 1e-5);
        }

        void AggregMode() {
            aggregations::Mode aggreg;
            assert(!aggreg.Get());

            aggreg.PutValue(1.1);
            aggreg.PutValue(0.9);
            aggreg.PutValue(2.1);
            aggreg.PutValue(2.2);
            aggreg.PutValue(2.1);
            aggreg.PutValue(-1.0);
            aggreg.PutValue(3.0);
            aggreg.PutValue(3.0);
            aggreg.PutValue(1000.);

            assert(std::round(*aggreg.Get()) == 2.);
        }

        void AggregPrinter() {
            statistics::AggregPrinter<aggregations::Max> printer;

            assert(statistics::tests::detail::GetPrinterValue(printer) == "max is undefined\n"s);
            printer.PutValue(10.);
            printer.PutValue(20.);
            printer.PutValue(-40.);

            std::ostringstream out;
            out << 20.;

            assert(statistics::tests::detail::GetPrinterValue(printer) == "max is "s + out.str() + "\n"s);
        }
    }
}