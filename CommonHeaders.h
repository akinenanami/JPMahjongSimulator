//
// Created by tyl on 2021/12/29.
//

#ifndef JPMAHJONGSIMULATOR_COMMONHEADERS_H
#define JPMAHJONGSIMULATOR_COMMONHEADERS_H

// C compatibility headers

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++ 98/03 headers

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

// C++ 11 headers

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

// C++ 14 headers

#include <shared_mutex>

// C++ 17 headers

#include <any>
#include <charconv>
#include <execution>
#include <filesystem>
#include <memory_resource>
#include <optional>
#include <string_view>
#include <variant>

// C++ 20 headers

#include <barrier>
#include <bit>
#include <compare>
#include <concepts>
#include <coroutine>
#include <format>
#include <latch>
#include <numbers>
#include <ranges>
#include <semaphore>
#include <source_location>
#include <span>
#include <stop_token>
#include <syncstream>
#include <version>

const int RIICHI         = 0;     //立直
const int TANYAO         = 1;     //断幺
const int ZUMA           = 2;     //门前自摸
const int MENFON         = 3;     //门风
const int CHANFON        = 4;     //场风
const int HAKU           = 5;     //白
const int HATSU          = 6;     //发
const int TYUN           = 7;     //中
const int PINHU          = 8;     //平胡
const int IPEKO          = 9;     //一杯口
const int CHANGAN        = 10;    //枪杠
const int RINSHAN        = 11;    //岭上开花
const int HAIDE          = 12;    //海底摸月
const int KOUDE          = 13;    //河底捞鱼
const int IHATSU         = 14;    //一发
const int WRIICHI        = 15;    //两立直
const int SANSYOKUDOUJUN = 16;    //三色同顺
const int SANSYOKUDOUKO  = 17;    //三色同刻
const int SANKANTSU      = 18;    //三杠子
const int TOITOI         = 19;    //对对和
const int SANANKO        = 20;    //三暗刻
const int SYOSANGEN      = 21;    //小三元
const int HONROTO        = 22;    //混老头
const int CHITOI         = 23;    //七对子
const int ITTSU          = 24;    //一气贯通
const int CHANTA         = 25;    //混全
const int JUNCHAN        = 26;    //纯全
const int RYANPEKO       = 27;    //两杯口
const int HONITSU        = 28;    //混一色
const int CHINITSU       = 29;    //清一色

const int TENHOU        = 32;    //天和
const int CHIHOU        = 33;    //地和
const int DAISANGEN     = 34;    //大三元
const int SUANKO        = 35;    //四暗刻
const int TSUISOU       = 36;    //字一色
const int RYUISO        = 37;    //绿一色
const int CHINROTO      = 38;    //清老头
const int KOKUSHI       = 39;    //国士无双
const int SUKANTSU      = 40;    //四杠子
const int TYURENPOTO    = 41;    //九莲宝灯
const int SYOSUSHI      = 42;    //小四喜
const int DAISUSHI      = 43;    //大四喜
const int SUANKOTANKI   = 44;    //四暗刻单骑
const int KOKUSHUJUUSAN = 45;    //国士十三面
const int TYURENKYUU    = 46;    //纯九莲

enum class Operation
{
    DRAW = 0,    //摸
    BON,         //碰
    CHI,         //吃
    KAN,         //杠
    RON          //荣和
};

struct Exposure
{    //副露面子
    std::vector<uint8_t> cards;
    int                  resonance_card;    //鸣牌获得的牌
    int                  card_from;         //鸣牌来源, 0为自家, 1为下家, 2为对家, 3为上家
    int                  type;              //面子类型，0为刻子，1为顺子

    Exposure(std::vector<uint8_t> cards, int resonance_card, int card_from, int type)
    {
        this->cards          = cards;
        this->resonance_card = resonance_card;
        this->card_from      = card_from;
        this->type           = type;
    }
};

#endif    //JPMAHJONGSIMULATOR_COMMONHEADERS_H
