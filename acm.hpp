#ifndef ACM_H
#define ACM_H
#include <string>

/**
 * 打印所有天干地支的排列组合
 *
 * @param rowStem 天干行式排列
 */
void listStemBranchCombinations(bool rowStem = false);

/**
 * 获取年份年干支（年柱）
 *
 * @param year 年份
 * @param showZodiacAnimal 显示生肖
 * @param beforeChrist 是否公元前
 * @return 年干支（年柱）
 */
std::string getYearStemBranch(unsigned int year, bool showZodiacAnimal = false, bool beforeChrist = false);
#endif //ACM_H
