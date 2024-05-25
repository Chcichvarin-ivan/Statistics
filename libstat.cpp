/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-24 00:00:01
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-26 00:16:49
 * @FilePath: /Statistics/libstat.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "libstat.h"

namespace statistics{
    namespace aggregations{
        void Sum::PutValue(double value) {
            sum_ += value;
        }

        std::optional<double> Sum::Get() const {
            return sum_;
        }

        void Max::PutValue(double value) {
            cur_max_ = std::max(value, cur_max_.value_or(value));
        }

        std::optional<double> Max::Get() const {
            return cur_max_;
        }

        void Mean::PutValue(double value) {
            sum_.PutValue(value);
            ++count_;
        }

        std::optional<double> Mean::Get() const {
            auto val = sum_.Get();
            if (!val || count_ == 0) {
                return std::nullopt;
            }

            return *val / static_cast<double>(count_);
        }

        void StandardDeviation::PutValue(double value) {
            sum_.PutValue(value);
            sum_sq_.PutValue(value * value);
            ++count_;
        }

        std::optional<double> StandardDeviation::Get() const {
            auto val = sum_.Get();
            auto val2 = sum_sq_.Get();

            if (!val || !val2 || count_ < 2) {
                return std::nullopt;
            }

            return ::std::sqrt((*val2 - *val * *val / static_cast<double>(count_)) / static_cast<double>(count_));
        }

        void Mode::PutValue(double value) {
            const size_t new_count = ++counts_[round(value)];

            if (new_count > cur_count_) {
                cur_max_ = value;
                cur_count_ = new_count;
            }
        }

        std::optional<double> Mode::Get() const {
            return cur_max_;
        }
    }
}