#include "acm.hpp"
#include <iostream>
#include <vector>
#include <format>

using namespace std;

// 天干数组
const std::string heavenlyStems[10] = {
    "甲", "乙", "丙", "丁", "戊",
    "己", "庚", "辛", "壬", "癸"
};
// 地支数组
const std::string earthlyBranches[12] = {
    "子", "丑", "寅", "卯",
    "辰", "巳", "午", "未",
    "申", "酉", "戌", "亥"
};
// 生肖数组
const std::string chineseZodiacs[12] = {
    "鼠", "牛", "虎", "兔",
    "龙", "蛇", "马", "羊",
    "猴", "鸡", "狗", "猪"
};

vector<string> generateStemBranchCombinations() {
    vector<string> combinations;
    int stemIndex = 0, branchIndex = 0;
    for (int i = 0; i < 60; ++i) {
        // 组合天干地支
        string combination = format("{0}{1}", heavenlyStems[stemIndex], earthlyBranches[branchIndex]);
        combinations.push_back(combination);
        // 更新天干和地支的索引
        stemIndex = (stemIndex + 1) % 10;
        branchIndex = (branchIndex + 1) % 12;
    }
    return combinations;
}

void listStemBranchCombinations(const bool rowStem) {
    int stemIndex = 0, branchIndex = 0;
    string sixtyCycle[6][10] = {};

    for (int i = 0; i < 60; ++i) {
        // 组合天干地支
        string combination = format("{0}{1}", heavenlyStems[stemIndex], earthlyBranches[branchIndex]);

        const int row = (i + 1) / 10, col = (i + 1) % 10 - 1;
        sixtyCycle[row][col] = format("{:02} {}", i + 1, combination);

        // 更新天干和地支的索引
        stemIndex = (stemIndex + 1) % 10;
        branchIndex = (branchIndex + 1) % 12;
    }

    std::cout << std::format("六十干支周名称顺序表（天干{}式排列）：\n", rowStem ? "行" : "列") << std::endl;
    if (rowStem) {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << format("{0}{1}", sixtyCycle[i][j], j == 9 ? "" : "\t");
            }
            if (i < 5) {
                cout << endl;
            }
        }
    } else {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 6; ++j) {
                cout << format("{0}{1}", sixtyCycle[j][i], j == 5 ? "" : "\t");
            }
            if (i < 9) {
                cout << endl;
            }
        }
    }
}

std::string getYearStemBranch(const unsigned int year, const bool showZodiacAnimal, const bool beforeChrist) {
    if (year == 0) {
        // todo 抛出异常
    }
    // 年天干 = 公历年份除以 10 所得余数
    unsigned int stem = year % 10;
    // 计算天干索引
    unsigned int stemIndex = 0;

    // 公元前，将天干转换为公元后相应的值
    if (beforeChrist) {
        // if (stem <= 1) {
        //     stem = 1 - stem; // <= 1 用 1 减
        // } else {
        //     stem = 11 - stem; // 否则用 11 减
        // }
        // stemIndex = (stemIndex + 1) % 10;
        stem = (11 - stem) % 10;
    }

    // 天干索引
    // if (stem >= 4) {
    //     stemIndex = stem - 4;
    // } else {
    //     stemIndex = stem + 6;
    // }
    stemIndex = (stem + 6) % 10;

    // 地支 = 公历年份除以 12 所得余数
    unsigned int branch = year % 12;
    // 计算地支索引
    unsigned int branchIndex = 0;

    // 公元前,将地支转换为公元后相应的值
    if (beforeChrist) {
        // if (branch <= 1) {
        //     branch = 1 - branch; // <= 1 用 1 减
        // } else {
        //     branch = 13 - branch; // 否则用 13 减
        // }
        branch = (13 - branch) % 12;
    }

    // 公元后地支索引
    // if (branch >= 4) {
    //     branchIndex = branch - 4;
    // } else {
    //     branchIndex = branch + 8;
    // }
    branchIndex = (branch + 8) % 12;

    string result = format("{}{}", heavenlyStems[stemIndex], earthlyBranches[branchIndex]);
    if (showZodiacAnimal) {
        result += format("({})", chineseZodiacs[branchIndex]);
    }
    return result;
}

void printExampleData(const std::vector<ExampleData> &data) {
    std::cout << "干支纪年法历史示例：\n" << std::endl;
    for (const auto &[year, beforeChrist, remark]: data) {
        auto s1 = format("公元{0:<3}\t{1:>4}年", beforeChrist ? "前" : "", year);
        auto s2 = getYearStemBranch(year, true, beforeChrist) + "年";
        std::cout << std::format("{} | {:^6} | {:8}", s1, s2, remark) << std::endl;
    }
}
