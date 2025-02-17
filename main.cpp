#include <iostream>
#include <format>
#include <CLI/CLI.hpp>
#include "acm.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

void setupConsoleEncoding() {
#ifdef _WIN32
    // 如果是 Windows 系统，设置控制台输出编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif
}

struct YearValidator : CLI::Validator {
    YearValidator() {
        name_ = "YEAR";
        func_ = [](const std::string &str) {
            if (const int num = std::stoi(str); num <= 0) {
                return std::string("年份必须为大于零的整数");
            }
            return std::string();
        };
    }
};

const static YearValidator year_validator;

struct ss {
    unsigned int year;
    bool bc;
    string remark;
};

void printTable(const std::vector<ss> &data, const std::vector<int> &columnWidths) {
    std::cout << std::format("|{:^20}|{:^14}|{:14}|", "公历纪年", "干支纪年", "备注") << std::endl;
    for (const auto &[year, bc, remark]: data) {
        auto s1 = format("公元{0:2}{1:5}年", bc ? "前" : "后", year);
        std::cout << std::format("|{:^20}|{:^14}|{:14}|", s1, getYearStemBranch(year, true, bc), remark) << std::endl;
    }
}

int main(const int argc, char *argv[]) {
    // 设置控制台输出编码为 UTF-8
    setupConsoleEncoding();

    CLI::App app{"AI 历法大师"};

    app.require_subcommand(0, 1);
    app.set_help_flag("-h,--help", "显示帮助信息");

    // 六十干支周显示
    const auto sc = app.add_subcommand("sc", "六十干支周");
    bool show_table = true, row_stem = false;
    sc->add_flag("-t", show_table, "以表格形式展示");
    sc->add_flag("-r,--row-stem", row_stem, "行式显示天干");
    sc->callback([&] {
        if (show_table) {
            listStemBranchCombinations(row_stem);
        } else {
            cout << "其他展示方式待实现";
        }
    });

    // 年天干计算
    const auto hseb = app.add_subcommand("hseb", "天干地支");
    const std::time_t now = std::time(nullptr);
    bool show_example = false;
    unsigned int year = std::localtime(&now)->tm_year + 1900;
    bool before_christ = false;
    hseb->add_flag("-E,--example", show_example, "年份")->required(false);
    hseb->add_option("-y,--year", year, "年份")->required(false)->check(year_validator);
    hseb->add_flag("-B,--before-christ", before_christ, "公元前");
    hseb->callback([&] {
        if (show_example) {
            const std::vector<ss> tableData = {
                ss{403, true, "资治通鉴卷第一"},
                ss{369, true, "资治通鉴卷第一"},
                ss{1894, false, "中日甲午战争"},
                ss{1898, false, "戊戌变法"},
                ss{1900, false, "庚子国变"},
                ss{1911, false, "辛亥革命"},
            };
            printTable(tableData, {20, 20, 20});
        } else {
            const string out = format("公元{2} {0:>4} 年为{1:>4}年",
                                      year, getYearStemBranch(year, true, before_christ), before_christ ? "前" : "");
            cout << out << endl;
        }
    });

    CLI11_PARSE(app, argc, argv);

    return 0;
}
